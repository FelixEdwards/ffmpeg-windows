/*
 * Musepack demuxer
 * Copyright (c) 2006 Konstantin Shishkov
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "libavcodec/get_bits.h"
#include "avformat.h"
#include "apetag.h"
#include "id3v1.h"

#define MPC_FRAMESIZE  1152
#define DELAY_FRAMES   32

static const int mpc_rate[4] = { 44100, 48000, 37800, 32000 };
typedef struct
{
    int64_t pos;
    int size, skip;
} MPCFrame;

typedef struct
{
    int ver;
    uint32_t curframe, lastframe;
    uint32_t fcount;
    MPCFrame *frames;
    int curbits;
    int frames_noted;
} MPCContext;

static int mpc_probe(AVProbeData *p)
{
    const uint8_t *d = p->buf;
    if (d[0] == 'M' && d[1] == 'P' && d[2] == '+' && (d[3] == 0x17 || d[3] == 0x7))
        return AVPROBE_SCORE_MAX;
    return 0;
}

static int mpc_read_header(AVFormatContext *s, AVFormatParameters *ap)
{
    MPCContext *c = s->priv_data;
    AVStream *st;

    if(avio_rl24(s->pb) != MKTAG('M', 'P', '+', 0))
    {
        av_log(s, AV_LOG_ERROR, "Not a Musepack file\n");
        return -1;
    }
    c->ver = avio_r8(s->pb);
    if(c->ver != 0x07 && c->ver != 0x17)
    {
        av_log(s, AV_LOG_ERROR, "Can demux Musepack SV7, got version %02X\n", c->ver);
        return -1;
    }
    c->fcount = avio_rl32(s->pb);
    if((int64_t)c->fcount * sizeof(MPCFrame) >= UINT_MAX)
    {
        av_log(s, AV_LOG_ERROR, "Too many frames, seeking is not possible\n");
        return -1;
    }
    c->frames = av_malloc(c->fcount * sizeof(MPCFrame));
    c->curframe = 0;
    c->lastframe = -1;
    c->curbits = 8;
    c->frames_noted = 0;

    st = av_new_stream(s, 0);
    if (!st)
        return AVERROR(ENOMEM);
    st->codec->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codec->codec_id = CODEC_ID_MUSEPACK7;
    st->codec->channels = 2;
    st->codec->bits_per_coded_sample = 16;

    st->codec->extradata_size = 16;
    st->codec->extradata = av_mallocz(st->codec->extradata_size + FF_INPUT_BUFFER_PADDING_SIZE);
    avio_read(s->pb, st->codec->extradata, 16);
    st->codec->sample_rate = mpc_rate[st->codec->extradata[2] & 3];
    av_set_pts_info(st, 32, MPC_FRAMESIZE, st->codec->sample_rate);
    /* scan for seekpoints */
    st->start_time = 0;
    st->duration = c->fcount;

    /* try to read APE tags */
    if (s->pb->seekable)
    {
        int64_t pos = avio_tell(s->pb);
        ff_ape_parse_tag(s);
        if (!av_metadata_get(s->metadata, "", NULL, AV_METADATA_IGNORE_SUFFIX))
            ff_id3v1_read(s);
        avio_seek(s->pb, pos, SEEK_SET);
    }

    return 0;
}

static int mpc_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    MPCContext *c = s->priv_data;
    int ret, size, size2, curbits, cur = c->curframe;
    int64_t tmp, pos;

    if (c->curframe >= c->fcount)
        return -1;

    if(c->curframe != c->lastframe + 1)
    {
        avio_seek(s->pb, c->frames[c->curframe].pos, SEEK_SET);
        c->curbits = c->frames[c->curframe].skip;
    }
    c->lastframe = c->curframe;
    c->curframe++;
    curbits = c->curbits;
    pos = avio_tell(s->pb);
    tmp = avio_rl32(s->pb);
    if(curbits <= 12)
    {
        size2 = (tmp >> (12 - curbits)) & 0xFFFFF;
    }
    else
    {
        tmp = (tmp << 32) | avio_rl32(s->pb);
        size2 = (tmp >> (44 - curbits)) & 0xFFFFF;
    }
    curbits += 20;
    avio_seek(s->pb, pos, SEEK_SET);

    size = ((size2 + curbits + 31) & ~31) >> 3;
    if(cur == c->frames_noted)
    {
        c->frames[cur].pos = pos;
        c->frames[cur].size = size;
        c->frames[cur].skip = curbits - 20;
        av_add_index_entry(s->streams[0], cur, cur, size, 0, AVINDEX_KEYFRAME);
        c->frames_noted++;
    }
    c->curbits = (curbits + size2) & 0x1F;

    if (av_new_packet(pkt, size) < 0)
        return AVERROR(EIO);

    pkt->data[0] = curbits;
    pkt->data[1] = (c->curframe > c->fcount);
    pkt->data[2] = 0;
    pkt->data[3] = 0;

    pkt->stream_index = 0;
    pkt->pts = cur;
    ret = avio_read(s->pb, pkt->data + 4, size);
    if(c->curbits)
        avio_seek(s->pb, -4, SEEK_CUR);
    if(ret < size)
    {
        av_free_packet(pkt);
        return AVERROR(EIO);
    }
    pkt->size = ret + 4;

    return 0;
}

static int mpc_read_close(AVFormatContext *s)
{
    MPCContext *c = s->priv_data;

    av_freep(&c->frames);
    return 0;
}

/**
 * Seek to the given position
 * If position is unknown but is within the limits of file
 * then packets are skipped unless desired position is reached
 *
 * Also this function makes use of the fact that timestamp == frameno
 */
static int mpc_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    AVStream *st = s->streams[stream_index];
    MPCContext *c = s->priv_data;
    AVPacket pkt1, *pkt = &pkt1;
    int ret;
    int index = av_index_search_timestamp(st, timestamp - DELAY_FRAMES, flags);
    uint32_t lastframe;

    /* if found, seek there */
    if (index >= 0)
    {
        c->curframe = st->index_entries[index].pos;
        return 0;
    }
    /* if timestamp is out of bounds, return error */
    if(timestamp < 0 || timestamp >= c->fcount)
        return -1;
    timestamp -= DELAY_FRAMES;
    /* seek to the furthest known position and read packets until
       we reach desired position */
    lastframe = c->curframe;
    if(c->frames_noted) c->curframe = c->frames_noted - 1;
    while(c->curframe < timestamp)
    {
        ret = av_read_frame(s, pkt);
        if (ret < 0)
        {
            c->curframe = lastframe;
            return -1;
        }
        av_free_packet(pkt);
    }
    return 0;
}


AVInputFormat ff_mpc_demuxer =
{
    "mpc",
    NULL_IF_CONFIG_SMALL("Musepack"),
    sizeof(MPCContext),
    mpc_probe,
    mpc_read_header,
    mpc_read_packet,
    mpc_read_close,
    mpc_read_seek,
    .extensions = "mpc",
};

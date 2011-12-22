/*
 * Musepack SV8 decoder
 * Copyright (c) 2007 Konstantin Shishkov
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

#ifndef AVCODEC_MPC8HUFF_H
#define AVCODEC_MPC8HUFF_H

#include <stdint.h>

#define MPC8_BANDS_SIZE 33
#define MPC8_BANDS_BITS 9

static const uint8_t mpc8_bands_codes[MPC8_BANDS_SIZE] =
{
    0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04,
    0x05, 0x06, 0x01, 0x02, 0x03, 0x00, 0x04, 0x05,
    0x06, 0x07, 0x08, 0x01, 0x09, 0x0A, 0x0B, 0x07,
    0x08, 0x09, 0x06, 0x07, 0x05, 0x05, 0x03, 0x03,
    0x01,
};
static const int8_t mpc8_bands_bits[MPC8_BANDS_SIZE] =
{
    1,  3,  5,  6,  7,  8,  8,  9,
    10, 11, 12, 12, 12, 13, 12, 12,
    12, 12, 12, 13, 12, 12, 12, 11,
    11, 11, 10, 10,  9,  8,  6,  5,
    2,
};

#define MPC8_SCFI0_SIZE 4
#define MPC8_SCFI0_BITS 3

static const uint8_t mpc8_scfi0_codes[MPC8_SCFI0_SIZE] =
{
    0x00, 0x01, 0x01, 0x01,
};
static const int8_t mpc8_scfi0_bits[MPC8_SCFI0_SIZE] =
{
    3,  3,  1,  2,
};

#define MPC8_SCFI1_SIZE 16
#define MPC8_SCFI1_BITS 7

static const uint8_t mpc8_scfi1_codes[MPC8_SCFI1_SIZE] =
{
    0x01, 0x00, 0x02, 0x03, 0x01, 0x03, 0x04, 0x05,
    0x04, 0x06, 0x02, 0x02, 0x05, 0x07, 0x03, 0x03,

};
static const int8_t mpc8_scfi1_bits[MPC8_SCFI1_SIZE] =
{
    6,  7,  6,  6,  7,  5,  5,  5,
    6,  5,  2,  3,  6,  5,  3,  2,

};

#define MPC8_DSCF0_SIZE 64
#define MPC8_DSCF0_BITS 9

static const uint8_t mpc8_dscf0_codes[MPC8_DSCF0_SIZE] =
{
    0x03, 0x04, 0x05, 0x04, 0x05, 0x06, 0x05, 0x06,
    0x07, 0x08, 0x09, 0x07, 0x08, 0x09, 0x0A, 0x07,
    0x08, 0x09, 0x0A, 0x07, 0x08, 0x09, 0x0A, 0x06,
    0x07, 0x05, 0x04, 0x05, 0x06, 0x06, 0x07, 0x0A,
    0x08, 0x05, 0x06, 0x07, 0x09, 0x07, 0x08, 0x09,
    0x0B, 0x0B, 0x0C, 0x0D, 0x0B, 0x0C, 0x0D, 0x0B,
    0x0C, 0x0D, 0x07, 0x08, 0x09, 0x06, 0x07, 0x03,
    0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
};
static const int8_t mpc8_dscf0_bits[MPC8_DSCF0_SIZE] =
{
    12, 12, 12, 11, 11, 11, 10, 10,
    10, 10, 10,  9,  9,  9,  9,  8,
    8,  8,  8,  7,  7,  7,  7,  6,
    6,  5,  4,  4,  5,  4,  4, 10,
    4,  3,  3,  3,  4,  5,  6,  6,
    7,  8,  8,  8,  9,  9,  9, 10,
    10, 10, 11, 11, 11, 12, 12, 13,
    13, 13, 14, 14, 14, 14, 14, 14,

};

#define MPC8_DSCF1_SIZE 65
#define MPC8_DSCF1_BITS 9

static const uint8_t mpc8_dscf1_codes[MPC8_DSCF1_SIZE] =
{
    0x00, 0x03, 0x04, 0x04, 0x05, 0x06, 0x05, 0x06,
    0x07, 0x08, 0x07, 0x08, 0x09, 0x0A, 0x07, 0x08,
    0x09, 0x0A, 0x07, 0x08, 0x09, 0x06, 0x07, 0x05,
    0x06, 0x04, 0x03, 0x03, 0x04, 0x03, 0x04, 0x05,
    0x06, 0x07, 0x05, 0x04, 0x05, 0x05, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0B, 0x0C, 0x0D, 0x0B, 0x0C,
    0x0D, 0x09, 0x0A, 0x0B, 0x0C, 0x07, 0x08, 0x09,
    0x05, 0x06, 0x07, 0x01, 0x02, 0x03, 0x04, 0x05,
    0x0D,
};
static const int8_t mpc8_dscf1_bits[MPC8_DSCF1_SIZE] =
{
    15, 14, 14, 13, 13, 13, 12, 12,
    12, 12, 11, 11, 11, 11, 10, 10,
    10, 10,  9,  9,  9,  8,  8,  7,
    7,  6,  5,  4,  4,  3,  3,  3,
    3,  3,  4,  5,  5,  6,  7,  8,
    8,  9,  9, 10, 10, 10, 11, 11,
    11, 12, 12, 12, 12, 13, 13, 13,
    14, 14, 14, 15, 15, 15, 15, 15,
    12,
};

#define MPC8_RES_SIZE 17
#define MPC8_RES_BITS 9

static const uint8_t mpc8_res_codes[2][MPC8_RES_SIZE] =
{
    {
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01,
        0x01,
    },
    {
        0x01, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x00, 0x01, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01,
        0x03,
    }
};
static const int8_t mpc8_res_bits[2][MPC8_RES_SIZE] =
{
    {
        1,  2,  4,  5,  6,  7,  9, 10,
        11, 12, 13, 14, 15, 16, 16,  8,
        3,
    },
    {
        2,  2,  3,  5,  7,  8, 10, 12,
        14, 14, 14, 14, 11,  9,  6,  4,
        2,
    }
};

#define MPC8_Q1_SIZE 19
#define MPC8_Q1_BITS 9

static const uint8_t mpc8_q1_codes[MPC8_Q1_SIZE] =
{
    0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x03, 0x04, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x00, 0x01,
};
static const int8_t mpc8_q1_bits[MPC8_Q1_SIZE] =
{
    6,  4,  4,  3,  3,  3,  3,  3,
    4,  4,  4,  5,  7,  8,  9, 10,
    11, 12, 12,
};

#define MPC8_Q9UP_SIZE 256
#define MPC8_Q9UP_BITS 9

static const uint8_t mpc8_q9up_codes[MPC8_Q9UP_SIZE] =
{
    0x01, 0x02, 0x03, 0x04, 0x05, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x26, 0x27, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
    0x28, 0x26, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E,
    0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E,
    0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
    0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E,
    0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56,
    0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E,
    0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
    0x67, 0x68, 0x69, 0x6A, 0x56, 0x57, 0x58, 0x59,
    0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61,
    0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x3E,
    0x3F, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x6B, 0x7B, 0x6C, 0x6D, 0x6E,
    0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
    0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E,
    0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86,
    0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E,
    0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,
    0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E,
    0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6,
    0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0x27, 0x28, 0x29,
    0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41,
    0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4A, 0x4B, 0x06, 0x07, 0x08, 0x09, 0x00, 0x01,
};
static const int8_t mpc8_q9up_bits[MPC8_Q9UP_SIZE] =
{
    10, 10, 10, 10, 10,  9,  9,  9,
    9,  9,  9,  9,  9,  9,  9,  9,
    9,  9,  9,  8,  8,  9,  9,  9,
    9,  9,  9,  9,  9,  9,  9,  9,
    9,  9,  9,  9,  9,  9,  9,  9,
    8,  9,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  7,  7,  7,  7,
    7,  7,  7,  7,  7,  7,  7,  7,
    7,  7,  7,  7,  7,  7,  7,  6,
    6,  7,  7,  7,  7,  7,  7,  7,
    7,  7,  7,  7,  7,  7,  7,  7,
    7,  7,  7,  8,  7,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  9,  9,  9,
    9,  9,  9,  9,  9,  9,  9,  9,
    9,  9,  9,  9,  9,  9,  9,  9,
    9,  9,  9,  9,  9,  9,  9,  9,
    9,  9,  9,  9,  9,  9,  9,  9,
    9,  9, 10, 10, 10, 10, 11, 11,
};

#define MPC8_Q2_SIZE 125
#define MPC8_Q2_BITS 9

static const uint8_t mpc8_q2_codes[2][MPC8_Q2_SIZE] =
{
    {
        0x02, 0x03, 0x0F, 0x04, 0x00, 0x05, 0x0C, 0x12,
        0x0D, 0x06, 0x07, 0x13, 0x15, 0x14, 0x08, 0x09,
        0x0E, 0x15, 0x0F, 0x0A, 0x03, 0x0B, 0x10, 0x0C,
        0x01, 0x0D, 0x10, 0x16, 0x11, 0x0E, 0x12, 0x0F,
        0x10, 0x16, 0x13, 0x17, 0x11, 0x08, 0x12, 0x18,
        0x14, 0x13, 0x14, 0x17, 0x15, 0x0F, 0x16, 0x19,
        0x17, 0x10, 0x11, 0x1A, 0x18, 0x1B, 0x12, 0x1C,
        0x15, 0x09, 0x16, 0x1D, 0x19, 0x0A, 0x07, 0x0B,
        0x1A, 0x1E, 0x17, 0x0C, 0x18, 0x1F, 0x13, 0x20,
        0x1B, 0x21, 0x14, 0x11, 0x18, 0x22, 0x19, 0x12,
        0x1A, 0x19, 0x1A, 0x1B, 0x1B, 0x23, 0x1C, 0x0D,
        0x1D, 0x24, 0x1C, 0x1C, 0x1E, 0x1F, 0x1D, 0x13,
        0x1E, 0x25, 0x1F, 0x14, 0x02, 0x15, 0x15, 0x16,
        0x04, 0x17, 0x20, 0x26, 0x21, 0x18, 0x16, 0x27,
        0x1D, 0x28, 0x19, 0x1A, 0x22, 0x29, 0x23, 0x1B,
        0x03, 0x1C, 0x17, 0x1D, 0x05,
    },
    {
        0x02, 0x03, 0x0F, 0x04, 0x00, 0x05, 0x0C, 0x0D,
        0x0E, 0x06, 0x07, 0x0F, 0x1E, 0x10, 0x10, 0x08,
        0x11, 0x12, 0x13, 0x09, 0x03, 0x0A, 0x11, 0x0B,
        0x01, 0x0C, 0x14, 0x15, 0x16, 0x0D, 0x17, 0x12,
        0x0E, 0x13, 0x18, 0x19, 0x14, 0x0F, 0x10, 0x1A,
        0x1B, 0x15, 0x11, 0x16, 0x1C, 0x0E, 0x1D, 0x1E,
        0x1F, 0x0F, 0x12, 0x20, 0x1F, 0x21, 0x13, 0x22,
        0x12, 0x13, 0x14, 0x23, 0x20, 0x15, 0x0F, 0x16,
        0x21, 0x24, 0x17, 0x18, 0x19, 0x25, 0x14, 0x26,
        0x22, 0x27, 0x15, 0x10, 0x28, 0x29, 0x2A, 0x11,
        0x2B, 0x17, 0x1A, 0x18, 0x2C, 0x2D, 0x1B, 0x1C,
        0x19, 0x2E, 0x2F, 0x1A, 0x1D, 0x1B, 0x30, 0x12,
        0x31, 0x32, 0x33, 0x13, 0x02, 0x14, 0x15, 0x16,
        0x04, 0x17, 0x34, 0x35, 0x36, 0x18, 0x16, 0x37,
        0x23, 0x38, 0x19, 0x1A, 0x39, 0x3A, 0x3B, 0x1B,
        0x03, 0x1C, 0x17, 0x1D, 0x05,
    }
};
static const int8_t mpc8_q2_bits[2][MPC8_Q2_SIZE] =
{
    {
        12, 11, 10, 11, 13, 11,  9,  8,
        9, 11, 11,  8,  7,  8, 11, 11,
        9,  8,  9, 11, 12, 11, 10, 11,
        13, 11,  9,  8,  9, 11,  9,  6,
        6,  7,  9,  8,  6,  4,  6,  8,
        9,  6,  6,  7,  9, 11,  9,  8,
        9, 11, 10,  8,  7,  8, 10,  8,
        6,  4,  6,  8,  7,  4,  3,  4,
        7,  8,  6,  4,  6,  8, 10,  8,
        7,  8, 10, 11,  9,  8,  9, 11,
        9,  6,  6,  6,  9,  8,  6,  4,
        6,  8,  9,  7,  6,  6,  9, 11,
        9,  8,  9, 11, 13, 11, 10, 11,
        12, 11,  9,  8,  9, 11, 10,  8,
        7,  8, 11, 11,  9,  8,  9, 11,
        13, 11, 10, 11, 12,
    },
    {
        11, 10,  9, 10, 12, 10,  8,  8,
        8, 10, 10,  8,  7,  8,  9, 10,
        8,  8,  8, 10, 11, 10,  9, 10,
        12, 10,  8,  8,  8, 10,  8,  6,
        5,  6,  8,  8,  6,  5,  5,  8,
        8,  6,  5,  6,  8, 10,  8,  8,
        8, 10,  9,  8,  7,  8,  9,  8,
        5,  5,  5,  8,  7,  5,  4,  5,
        7,  8,  5,  5,  5,  8,  9,  8,
        7,  8,  9, 10,  8,  8,  8, 10,
        8,  6,  5,  6,  8,  8,  5,  5,
        6,  8,  8,  6,  5,  6,  8, 10,
        8,  8,  8, 10, 12, 10, 10, 10,
        11, 10,  8,  8,  8, 10,  9,  8,
        7,  8, 10, 10,  8,  8,  8, 10,
        12, 10,  9, 10, 11,
    }
};

#define MPC8_Q3_SIZE 49
#define MPC8_Q3_BITS 9
#define MPC8_Q3_OFFSET -48

static const uint8_t mpc8_q3_codes[MPC8_Q3_SIZE] =
{
    0x07, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08, 0x0F,
    0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x13, 0x12, 0x11,
    0x10, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09,
    0x11, 0x10, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A,
    0x09, 0x08, 0x07, 0x06, 0x05, 0x09, 0x08, 0x07,
    0x06, 0x05, 0x04, 0x03, 0x02, 0x03, 0x02, 0x01,
    0x00,
};
static const int8_t mpc8_q3_bits[MPC8_Q3_SIZE] =
{
    3,  4,  4,  4,  4,  4,  4,  5,
    5,  5,  5,  5,  5,  6,  6,  6,
    6,  6,  6,  6,  6,  6,  6,  6,
    7,  7,  7,  7,  7,  7,  7,  7,
    7,  7,  7,  7,  7,  8,  8,  8,
    8,  8,  8,  8,  8,  9,  9,  9,
    9,
};
static const int8_t mpc8_q3_syms[MPC8_Q3_SIZE] =
{
    48,    65,    64,    49,    63,    32,    47,    80,
    79,    50,    62,    33,    16,    82,    81,    95,
    94,    66,    78,    34,    46,    17,    31,    30,
    97,    96,   111,    67,    77,    51,    61,    35,
    45,    18,     1,     0,    15,    98,   110,    83,
    93,    19,    29,     2,    14,    99,   109,     3,
    13,
};

#define MPC8_Q4_SIZE 81
#define MPC8_Q4_BITS 9
#define MPC8_Q4_OFFSET -64

static const uint8_t mpc8_q4_codes[MPC8_Q4_SIZE] =
{
    0x0F, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17,
    0x16, 0x15, 0x14, 0x13, 0x12, 0x23, 0x22, 0x21,
    0x20, 0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19,
    0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11,
    0x10, 0x0F, 0x0E, 0x0D, 0x19, 0x18, 0x17, 0x16,
    0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0F, 0x0E,
    0x0D, 0x0C, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12,
    0x11, 0x10, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A,
    0x09, 0x08, 0x07, 0x06, 0x05, 0x09, 0x08, 0x07,
    0x06, 0x05, 0x04, 0x03, 0x02, 0x03, 0x02, 0x01,
    0x00,
};
static const int8_t mpc8_q4_bits[MPC8_Q4_SIZE] =
{
    4,  5,  5,  5,  5,  5,  5,  5,
    5,  5,  5,  5,  5,  6,  6,  6,
    6,  6,  6,  6,  6,  6,  6,  6,
    6,  6,  6,  6,  6,  6,  6,  6,
    6,  6,  6,  6,  7,  7,  7,  7,
    7,  7,  7,  7,  7,  7,  7,  7,
    7,  7,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  9,  9,  9,
    9,  9,  9,  9,  9, 10, 10, 10,
    10,
};
static const int8_t mpc8_q4_syms[MPC8_Q4_SIZE] =
{
    64,    96,    81,    80,    95,    66,    65,    79,
    78,    49,    48,    63,    32,   113,   112,    98,
    97,   111,   110,    83,    82,    94,    93,    67,
    77,    51,    50,    62,    61,    34,    33,    47,
    46,    17,    16,    31,   128,   114,   127,   126,
    99,   109,    68,    76,    35,    45,    18,    30,
    0,    15,   130,   129,   143,   142,   115,   125,
    100,   108,    84,    92,    52,    60,    36,    44,
    19,    29,     2,     1,    14,   131,   141,   116,
    124,    20,    28,     3,    13,   132,   140,     4,
    12,
};

#define MPC8_Q5_SIZE 15
#define MPC8_Q5_BITS 7
#define MPC8_Q5_OFFSET -7

static const uint8_t mpc8_q5_codes[2][MPC8_Q5_SIZE] =
{
    {
        0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03,
        0x04, 0x05, 0x03, 0x03, 0x03, 0x02, 0x03,
    },
    {
        0x00, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x04, 0x05, 0x03, 0x02, 0x03,
    }
};
static const int8_t mpc8_q5_bits[2][MPC8_Q5_SIZE] =
{
    {
        7,  7,  6,  5,  4,  3,  3,  2,
        3,  3,  4,  5,  6,  7,  7,
    },
    {
        6,  6,  5,  4,  4,  3,  3,  3,
        3,  3,  4,  4,  5,  6,  6,
    }
};

#define MPC8_Q6_SIZE 31
#define MPC8_Q6_BITS 9
#define MPC8_Q6_OFFSET -15

static const uint8_t mpc8_q6_codes[2][MPC8_Q6_SIZE] =
{
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x04, 0x03,
        0x04, 0x05, 0x05, 0x06, 0x04, 0x05, 0x04, 0x03,
        0x05, 0x06, 0x07, 0x07, 0x06, 0x07, 0x08, 0x09,
        0x05, 0x06, 0x07, 0x04, 0x05, 0x06, 0x07,
    },
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x04, 0x05, 0x04,
        0x05, 0x06, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
        0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x07, 0x08, 0x09,
        0x06, 0x07, 0x05, 0x06, 0x07, 0x02, 0x03,
    }
};
static const int8_t mpc8_q6_bits[2][MPC8_Q6_SIZE] =
{
    {
        9,  9,  9,  9,  8,  8,  7,  6,
        6,  6,  5,  5,  4,  4,  3,  2,
        3,  4,  4,  5,  6,  6,  6,  6,
        7,  8,  8,  9,  9,  9,  9,
    },
    {
        8,  8,  7,  7,  7,  6,  6,  5,
        5,  5,  4,  4,  4,  4,  4,  4,
        4,  4,  4,  4,  4,  5,  5,  5,
        6,  6,  7,  7,  7,  8,  8,
    }
};

#define MPC8_Q7_SIZE 63
#define MPC8_Q7_BITS 9
#define MPC8_Q7_OFFSET -31

static const uint8_t mpc8_q7_codes[2][MPC8_Q7_SIZE] =
{
    {
        0x00, 0x01, 0x02, 0x08, 0x09, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x0A, 0x0B, 0x0C, 0x0D, 0x0A, 0x0B,
        0x0C, 0x0D, 0x0E, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
        0x0A, 0x0B, 0x0C, 0x08, 0x09, 0x06, 0x04, 0x03,
        0x05, 0x07, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x0F,
        0x10, 0x11, 0x12, 0x0F, 0x13, 0x10, 0x11, 0x12,
        0x13, 0x0E, 0x0F, 0x10, 0x11, 0x08, 0x09, 0x0A,
        0x0B, 0x0C, 0x12, 0x13, 0x0D, 0x0E, 0x0F,
    },
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x09, 0x0A,
        0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x0C, 0x0D,
        0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
        0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
        0x1E, 0x1F, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
        0x17, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x09, 0x0A,
        0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x02, 0x03,
    }
};
static const int8_t mpc8_q7_bits[2][MPC8_Q7_SIZE] =
{
    {
        10, 10, 10,  9,  9, 10, 10, 10,
        10, 10,  9,  9,  9,  9,  8,  8,
        8,  8,  8,  7,  7,  7,  7,  7,
        6,  6,  6,  5,  5,  4,  3,  2,
        3,  4,  5,  5,  6,  6,  6,  7,
        7,  7,  7,  8,  7,  8,  8,  8,
        8,  9,  9,  9,  9, 10, 10, 10,
        10, 10,  9,  9, 10, 10, 10,
    },
    {
        9,  9,  8,  8,  8,  8,  8,  8,
        8,  7,  7,  7,  7,  7,  6,  6,
        6,  6,  6,  6,  6,  6,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  6,  6,  6,  6,  6,  6,
        6,  7,  7,  7,  7,  7,  8,  8,
        8,  8,  8,  8,  8,  9,  9,
    }
};

#define MPC8_Q8_SIZE 127
#define MPC8_Q8_BITS 9
#define MPC8_Q8_OFFSET -63

static const uint8_t mpc8_q8_codes[2][MPC8_Q8_SIZE] =
{
    {
        0x03, 0x04, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x1A,
        0x0F, 0x1B, 0x10, 0x00, 0x01, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x11, 0x0C, 0x12, 0x13,
        0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1C, 0x1A,
        0x1B, 0x1C, 0x1D, 0x1E, 0x1D, 0x1E, 0x1F, 0x20,
        0x21, 0x22, 0x23, 0x24, 0x19, 0x25, 0x1A, 0x1B,
        0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17,
        0x0E, 0x0F, 0x10, 0x11, 0x0B, 0x07, 0x04, 0x03,
        0x05, 0x0C, 0x0D, 0x12, 0x13, 0x14, 0x15, 0x18,
        0x19, 0x1A, 0x1B, 0x20, 0x21, 0x22, 0x23, 0x24,
        0x25, 0x26, 0x27, 0x26, 0x27, 0x28, 0x29, 0x2A,
        0x2B, 0x2C, 0x2D, 0x2E, 0x1F, 0x20, 0x2F, 0x21,
        0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
        0x0D, 0x0E, 0x2A, 0x0F, 0x10, 0x11, 0x12, 0x02,
        0x13, 0x03, 0x04, 0x05, 0x2B, 0x2C, 0x30, 0x31,
        0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33,
    },
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x15, 0x16,
        0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
        0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
        0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E,
        0x2F, 0x30, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
        0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33,
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
        0x3C, 0x3D, 0x3E, 0x31, 0x3F, 0x32, 0x33, 0x34,
        0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C,
        0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44,
        0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x16,
        0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
        0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
        0x27, 0x28, 0x29, 0x04, 0x05, 0x06, 0x07,
    }
};
static const int8_t mpc8_q8_bits[2][MPC8_Q8_SIZE] =
{
    {
        11, 11, 10, 10, 10, 10, 10,  9,
        10,  9, 10, 12, 12, 11, 11, 11,
        11, 11, 11, 11, 10, 11, 10, 10,
        10, 10, 10, 10, 10, 10,  9, 10,
        10, 10, 10, 10,  9,  9,  9,  9,
        9,  9,  9,  9,  8,  9,  8,  8,
        8,  8,  8,  8,  7,  7,  7,  7,
        6,  6,  6,  6,  5,  4,  3,  2,
        3,  5,  5,  6,  6,  6,  6,  7,
        7,  7,  7,  8,  8,  8,  8,  8,
        8,  8,  8,  9,  9,  9,  9,  9,
        9,  9,  9,  9, 10, 10,  9, 10,
        10, 10, 10, 10, 10, 10, 10, 10,
        11, 11, 10, 11, 11, 11, 11, 12,
        11, 12, 12, 12, 10, 10,  9,  9,
        10, 10, 10, 10, 10, 10, 10,
    },
    {
        9,  9,  9,  9,  8,  8,  8,  8,
        8,  8,  8,  8,  8,  8,  8,  8,
        8,  8,  8,  8,  8,  8,  7,  7,
        7,  7,  7,  7,  7,  7,  7,  7,
        7,  7,  7,  7,  7,  7,  7,  7,
        7,  7,  7,  7,  7,  7,  7,  7,
        7,  7,  6,  6,  6,  6,  6,  6,
        6,  6,  6,  6,  6,  6,  6,  6,
        6,  6,  6,  6,  6,  6,  6,  6,
        6,  6,  6,  7,  6,  7,  7,  7,
        7,  7,  7,  7,  7,  7,  7,  7,
        7,  7,  7,  7,  7,  7,  7,  7,
        7,  7,  7,  7,  7,  7,  7,  8,
        8,  8,  8,  8,  8,  8,  8,  8,
        8,  8,  8,  8,  8,  8,  8,  8,
        8,  8,  8,  9,  9,  9,  9,
    }
};

#endif /* AVCODEC_MPC8HUFF_H */

//*****************************************************************************
//
//! @file arial6pt8b.c
//!
//! @brief NemaGFX example.
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2020, Ambiq Micro, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision SBL-AP4A-v1-RC-25-g74e0ec548 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#ifndef ARIAL6PT8B_C
#define ARIAL6PT8B_C

#include "arial6pt8b.h"

#ifndef NEMA_GPU_MEM
#define NEMA_GPU_MEM
#endif // NEMA_GPU_MEM

/* This will be read by the GPU only */
static uint8_t NEMA_GPU_MEM arial6pt8bBitmaps[] =
{
    // 0x20 - 0x7f
    0x50, 0x90, 0x49, 0x89, 0x36, 0x77, 0x22, 0x65, 0x00, 0x00, 0x48, 0x88,
    0x9F, 0x7F, 0x77, 0x86, 0x4E, 0x5E, 0x00, 0x7E, 0x15, 0x98, 0x00, 0xEC,
    0xFF, 0xFF, 0xFF, 0x58, 0x00, 0x94, 0x14, 0x83, 0x00, 0xEC, 0xFF, 0xFF,
    0xFF, 0x58, 0x4B, 0x49, 0x7B, 0x1D, 0x00, 0x7E, 0x15, 0x98, 0x00, 0x00,
    0x33, 0xE0, 0xF4, 0x8E, 0x00, 0x89, 0x5D, 0x68, 0x00, 0x00, 0x27, 0xCE,
    0xBE, 0x27, 0x00, 0x00, 0x01, 0x9F, 0xCF, 0x02, 0x98, 0x48, 0x7A, 0xC9,
    0x07, 0x26, 0xD7, 0xF5, 0x79, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x38,
    0xEE, 0x8E, 0x00, 0x6B, 0x25, 0x00, 0x7F, 0x41, 0xB7, 0x0B, 0x85, 0x00,
    0x00, 0x3A, 0xEF, 0x8D, 0x75, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x11, 0x82,
    0x7C, 0xF1, 0x4A, 0x00, 0x00, 0x7D, 0x18, 0xB1, 0x2E, 0x96, 0x00, 0x17,
    0x7F, 0x00, 0x7C, 0xF1, 0x4A, 0x00, 0x86, 0xF3, 0x72, 0x00, 0x00, 0x00,
    0xC6, 0x1A, 0xBA, 0x00, 0x00, 0x00, 0x8D, 0xC9, 0x34, 0x00, 0x00, 0x4F,
    0x90, 0xA8, 0x60, 0x70, 0x00, 0x9B, 0x53, 0x15, 0xE5, 0x70, 0x00, 0x2C,
    0xD7, 0xEC, 0x80, 0xAF, 0x06, 0xA3, 0x27, 0x8C, 0x0F, 0x00, 0x69, 0x21,
    0x09, 0x98, 0x00, 0x50, 0x62, 0x00, 0x7A, 0x42, 0x00, 0x79, 0x3C, 0x00,
    0x4D, 0x62, 0x00, 0x09, 0x98, 0x00, 0x00, 0x6B, 0x22, 0x41, 0x49, 0x00,
    0x00, 0xA3, 0x00, 0x00, 0x88, 0x2C, 0x00, 0x66, 0x56, 0x00, 0x62, 0x53,
    0x00, 0x87, 0x28, 0x00, 0xA2, 0x00, 0x42, 0x4C, 0x00, 0x43, 0x9B, 0x48,
    0x31, 0xA0, 0x42, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x00, 0xAC, 0x00,
    0x00, 0x8C, 0xFF, 0xFF, 0xFF, 0x3C, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00,
    0x00, 0xAC, 0x00, 0x00, 0x48, 0x84, 0x3A, 0x53, 0xC0, 0xFF, 0x6C, 0x44,
    0x88, 0x00, 0x7A, 0x15, 0x00, 0x90, 0x00, 0x0D, 0x81, 0x00, 0x50, 0x40,
    0x00, 0x8A, 0x06, 0x00, 0x90, 0x00, 0x00, 0x15, 0xCF, 0xEB, 0x53, 0x00,
    0x7D, 0x6B, 0x1D, 0xCA, 0x00, 0xA5, 0x1B, 0x00, 0xB2, 0x0A, 0xA0, 0x19,
    0x00, 0xB2, 0x08, 0x77, 0x6B, 0x1B, 0xCB, 0x00, 0x14, 0xCB, 0xF0, 0x58,
    0x00, 0x00, 0x0E, 0xCE, 0x11, 0xB8, 0xD3, 0x05, 0x04, 0xB4, 0x00, 0x00,
    0xB4, 0x00, 0x00, 0xB4, 0x00, 0x00, 0xB4, 0x1A, 0xCE, 0xF2, 0x74, 0x00,
    0x84, 0x51, 0x1A, 0xCE, 0x00, 0x00, 0x00, 0x19, 0xA9, 0x00, 0x00, 0x35,
    0xB7, 0x1D, 0x00, 0x2F, 0xA6, 0x0C, 0x00, 0x00, 0xA6, 0xFF, 0xFF, 0xFF,
    0x08, 0x44, 0xE5, 0xEA, 0x5B, 0x00, 0x00, 0x00, 0x32, 0xB3, 0x00, 0x00,
    0x3C, 0xF7, 0x70, 0x00, 0x00, 0x00, 0x09, 0xC9, 0x09, 0x8A, 0x58, 0x17,
    0xD1, 0x05, 0x1B, 0xCF, 0xED, 0x61, 0x00, 0x00, 0x00, 0x9C, 0x4C, 0x00,
    0x00, 0x43, 0xCF, 0x4C, 0x00, 0x0B, 0xA3, 0x6A, 0x4C, 0x00, 0x88, 0x27,
    0x68, 0x4C, 0x00, 0xE4, 0xFF, 0xFF, 0xFF, 0x10, 0x00, 0x00, 0x68, 0x4C,
    0x00, 0x14, 0xFF, 0xFF, 0xDC, 0x00, 0x45, 0x7A, 0x00, 0x00, 0x00, 0x74,
    0xD1, 0xF1, 0x7B, 0x00, 0x00, 0x00, 0x11, 0xC9, 0x0E, 0x8E, 0x65, 0x14,
    0xC8, 0x0A, 0x1D, 0xD0, 0xED, 0x65, 0x00, 0x0E, 0xBC, 0xF6, 0x9D, 0x00,
    0x73, 0x66, 0x02, 0x00, 0x00, 0xA3, 0xAD, 0xF1, 0x73, 0x00, 0xAA, 0x58,
    0x11, 0xC9, 0x05, 0x82, 0x64, 0x12, 0xC4, 0x02, 0x17, 0xC6, 0xEC, 0x65,
    0x00, 0xA0, 0xFF, 0xFF, 0xFF, 0x15, 0x00, 0x00, 0x35, 0x90, 0x00, 0x00,
    0x00, 0xBB, 0x0D, 0x00, 0x00, 0x39, 0x8D, 0x00, 0x00, 0x00, 0x94, 0x2E,
    0x00, 0x00, 0x00, 0xBD, 0x04, 0x00, 0x00, 0x20, 0xD5, 0xF2, 0x6A, 0x00,
    0x5D, 0x84, 0x28, 0xBB, 0x00, 0x17, 0xE6, 0xFF, 0x67, 0x00, 0x8E, 0x4C,
    0x14, 0xC4, 0x06, 0x97, 0x51, 0x12, 0xCA, 0x08, 0x24, 0xD3, 0xF0, 0x70,
    0x00, 0x22, 0xD3, 0xEC, 0x56, 0x00, 0x94, 0x56, 0x15, 0xC5, 0x01, 0x98,
    0x4C, 0x13, 0xD8, 0x11, 0x29, 0xDC, 0xDD, 0xCA, 0x0D, 0x00, 0x00, 0x1C,
    0xBF, 0x00, 0x46, 0xE9, 0xE8, 0x4B, 0x00, 0x48, 0x88, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x48, 0x88, 0x48, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x48, 0x84, 0x3A, 0x53, 0x0A, 0x47, 0x8A, 0xCE, 0x3A, 0x90, 0xE5,
    0x93, 0x3E, 0x02, 0x0A, 0x48, 0x8B, 0xCF, 0x3A, 0x8C, 0xFF, 0xFF, 0xFF,
    0x3C, 0x8C, 0xFF, 0xFF, 0xFF, 0x3C, 0x85, 0xB8, 0x74, 0x31, 0x01, 0x0D,
    0x5A, 0xB0, 0xF7, 0x3C, 0x85, 0xB9, 0x75, 0x32, 0x01, 0x4F, 0xE6, 0xF6,
    0x9C, 0x00, 0x00, 0x00, 0x1B, 0xC9, 0x01, 0x00, 0x00, 0xB2, 0x31, 0x00,
    0x00, 0x1E, 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34,
    0x9C, 0x00, 0x00, 0x00, 0x07, 0x88, 0xE3, 0xF7, 0xCA, 0x43, 0x00, 0x00,
    0xA7, 0xAB, 0xF7, 0xC6, 0xF3, 0xC5, 0x2C, 0x36, 0x80, 0xBA, 0x3B, 0x4D,
    0xB0, 0x1A, 0x8B, 0x7B, 0x25, 0xB6, 0x00, 0x2C, 0x80, 0x08, 0x8C, 0x88,
    0x12, 0xCC, 0x12, 0xA9, 0x61, 0x9D, 0x42, 0x5E, 0x56, 0x7E, 0xE8, 0x9F,
    0xED, 0x74, 0x00, 0x07, 0xC3, 0x67, 0x18, 0x04, 0x20, 0x85, 0x7D, 0x00,
    0x16, 0x98, 0xDF, 0xF9, 0xDA, 0x61, 0x00, 0x00, 0x00, 0x0B, 0xF3, 0x31,
    0x00, 0x00, 0x00, 0x00, 0x5E, 0xA4, 0x95, 0x00, 0x00, 0x00, 0x00, 0xA0,
    0x0C, 0xAC, 0x09, 0x00, 0x00, 0x1B, 0xFD, 0xFF, 0xFF, 0x5D, 0x00, 0x00,
    0x78, 0x43, 0x00, 0x0D, 0xB8, 0x00, 0x00, 0xC4, 0x04, 0x00, 0x00, 0xAE,
    0x26, 0x68, 0xFF, 0xFF, 0xE8, 0x49, 0x68, 0x58, 0x01, 0x54, 0x65, 0x68,
    0xFF, 0xFF, 0xFD, 0x6D, 0x68, 0x58, 0x00, 0x2B, 0xD4, 0x68, 0x58, 0x00,
    0x25, 0xBE, 0x68, 0xFF, 0xFF, 0xE0, 0x42, 0x00, 0x73, 0xE7, 0xEE, 0x74,
    0x00, 0x45, 0xC4, 0x1B, 0x1B, 0xB6, 0x2B, 0x8B, 0x45, 0x00, 0x00, 0x00,
    0x00, 0x89, 0x49, 0x00, 0x00, 0x15, 0x10, 0x44, 0xC4, 0x20, 0x16, 0xB9,
    0x3D, 0x00, 0x7E, 0xEC, 0xEE, 0x7B, 0x00, 0x60, 0xFF, 0xFE, 0xE6, 0x58,
    0x00, 0x60, 0x60, 0x01, 0x22, 0xCF, 0x15, 0x60, 0x60, 0x00, 0x00, 0x7A,
    0x48, 0x60, 0x60, 0x00, 0x00, 0x81, 0x4A, 0x60, 0x60, 0x00, 0x24, 0xD8,
    0x15, 0x60, 0xFF, 0xFE, 0xE4, 0x5C, 0x00, 0x5C, 0xFF, 0xFF, 0xFF, 0xC8,
    0x5C, 0x64, 0x00, 0x00, 0x00, 0x5C, 0xFF, 0xFF, 0xFF, 0x90, 0x5C, 0x64,
    0x00, 0x00, 0x00, 0x5C, 0x64, 0x00, 0x00, 0x00, 0x5C, 0xFF, 0xFF, 0xFF,
    0xE8, 0x58, 0xFF, 0xFF, 0xFF, 0x84, 0x58, 0x6C, 0x00, 0x00, 0x00, 0x58,
    0xFF, 0xFF, 0xFF, 0x1C, 0x58, 0x6C, 0x00, 0x00, 0x00, 0x58, 0x6C, 0x00,
    0x00, 0x00, 0x58, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x66, 0xE0, 0xF1, 0xA5,
    0x0B, 0x38, 0xC8, 0x28, 0x0D, 0x7E, 0x73, 0x84, 0x4F, 0x00, 0x00, 0x02,
    0x05, 0x86, 0x46, 0x00, 0xB4, 0xFF, 0xB8, 0x3B, 0xCE, 0x2E, 0x09, 0x35,
    0xB8, 0x00, 0x63, 0xDE, 0xF4, 0xC1, 0x3A, 0x5C, 0x68, 0x00, 0x00, 0xA0,
    0x24, 0x5C, 0x68, 0x00, 0x00, 0xA0, 0x24, 0x5C, 0xFF, 0xFF, 0xFF, 0xFF,
    0x24, 0x5C, 0x68, 0x00, 0x00, 0xA0, 0x24, 0x5C, 0x68, 0x00, 0x00, 0xA0,
    0x24, 0x5C, 0x68, 0x00, 0x00, 0xA0, 0x24, 0x40, 0x80, 0x40, 0x80, 0x40,
    0x80, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80, 0x00, 0x00, 0x60, 0x60, 0x00,
    0x00, 0x60, 0x60, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x60, 0x60, 0xAA,
    0x20, 0x89, 0x55, 0x54, 0xF0, 0xC7, 0x0F, 0x68, 0x58, 0x00, 0x50, 0xB3,
    0x06, 0x68, 0x58, 0x49, 0xBA, 0x09, 0x00, 0x68, 0x9B, 0xEC, 0x11, 0x00,
    0x00, 0x68, 0xC9, 0x7B, 0x83, 0x00, 0x00, 0x68, 0x58, 0x01, 0xB5, 0x3F,
    0x00, 0x68, 0x58, 0x00, 0x19, 0xD0, 0x12, 0x68, 0x58, 0x00, 0x00, 0x00,
    0x68, 0x58, 0x00, 0x00, 0x00, 0x68, 0x58, 0x00, 0x00, 0x00, 0x68, 0x58,
    0x00, 0x00, 0x00, 0x68, 0x58, 0x00, 0x00, 0x00, 0x68, 0xFF, 0xFF, 0xFF,
    0x2C, 0x68, 0xE4, 0x01, 0x00, 0x21, 0xFF, 0x10, 0x68, 0xD6, 0x3C, 0x00,
    0x78, 0xD5, 0x10, 0x68, 0x81, 0x91, 0x00, 0xA6, 0xAC, 0x10, 0x68, 0x54,
    0xBD, 0x2B, 0x7F, 0xAC, 0x10, 0x68, 0x54, 0x83, 0xBC, 0x2A, 0xAC, 0x10,
    0x68, 0x54, 0x2E, 0xD6, 0x00, 0xAC, 0x10, 0x64, 0xB7, 0x00, 0x00, 0x9C,
    0x20, 0x64, 0xEA, 0x63, 0x00, 0x9C, 0x20, 0x64, 0x6C, 0xDA, 0x1C, 0x9C,
    0x20, 0x64, 0x58, 0x53, 0xB7, 0x9C, 0x20, 0x64, 0x58, 0x00, 0xA8, 0xEA,
    0x20, 0x64, 0x58, 0x00, 0x14, 0xE9, 0x20, 0x00, 0x67, 0xE1, 0xF2, 0x97,
    0x07, 0x3C, 0xC2, 0x22, 0x18, 0x9B, 0x7F, 0x86, 0x43, 0x00, 0x00, 0x0C,
    0xC9, 0x8F, 0x3F, 0x00, 0x00, 0x07, 0xC9, 0x42, 0xC2, 0x21, 0x11, 0x96,
    0x81, 0x00, 0x6F, 0xE7, 0xF2, 0x9A, 0x08, 0x60, 0xFF, 0xFF, 0xEE, 0x61,
    0x60, 0x60, 0x00, 0x1A, 0xD4, 0x60, 0x60, 0x00, 0x1F, 0xD0, 0x60, 0xFF,
    0xFF, 0xE6, 0x58, 0x60, 0x60, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00,
    0x00, 0x00, 0x79, 0xE8, 0xF2, 0x9A, 0x08, 0x4D, 0xBA, 0x1E, 0x1A, 0xA2,
    0x83, 0x99, 0x35, 0x00, 0x00, 0x12, 0xC8, 0x99, 0x35, 0x00, 0x25, 0x0D,
    0xB2, 0x4C, 0xBB, 0x1D, 0xB2, 0xBD, 0x48, 0x00, 0x77, 0xE9, 0xF0, 0xC4,
    0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x60, 0xFF, 0xFF, 0xFA, 0xAC,
    0x01, 0x60, 0x64, 0x00, 0x0F, 0xC6, 0x25, 0x60, 0xFF, 0xFF, 0xFA, 0xAA,
    0x03, 0x60, 0x64, 0x0C, 0xB1, 0x35, 0x00, 0x60, 0x64, 0x00, 0x22, 0xCE,
    0x03, 0x60, 0x64, 0x00, 0x00, 0x8E, 0x65, 0x0E, 0xB2, 0xF2, 0xC4, 0x1F,
    0x58, 0x82, 0x06, 0x46, 0x9D, 0x1B, 0xB4, 0x7B, 0x3D, 0x01, 0x00, 0x02,
    0x33, 0x7A, 0x94, 0x89, 0x6D, 0x0B, 0x22, 0xC8, 0x11, 0xAF, 0xF0, 0xDB,
    0x49, 0xD0, 0xFF, 0xFF, 0xFF, 0xBC, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00,
    0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x60, 0x64, 0x00, 0x00, 0xA0,
    0x24, 0x60, 0x64, 0x00, 0x00, 0xA0, 0x24, 0x60, 0x64, 0x00, 0x00, 0xA0,
    0x24, 0x5D, 0x68, 0x00, 0x00, 0xA8, 0x21, 0x3F, 0xBB, 0x14, 0x21, 0xDC,
    0x09, 0x01, 0x9B, 0xF5, 0xEA, 0x67, 0x00, 0xC1, 0x0D, 0x00, 0x00, 0xA9,
    0x1A, 0x6A, 0x5A, 0x00, 0x0D, 0xAE, 0x00, 0x12, 0xA8, 0x00, 0x5D, 0x57,
    0x00, 0x00, 0xA4, 0x0C, 0xA4, 0x08, 0x00, 0x00, 0x4E, 0x69, 0x91, 0x00,
    0x00, 0x00, 0x05, 0xD7, 0x37, 0x00, 0x00, 0xBE, 0x04, 0x00, 0xC9, 0x60,
    0x00, 0x6A, 0x55, 0x86, 0x32, 0x10, 0xB4, 0xA1, 0x00, 0xA2, 0x14, 0x45,
    0x6A, 0x51, 0x5D, 0xB3, 0x00, 0xAD, 0x00, 0x0A, 0x9B, 0x93, 0x17, 0x88,
    0x3A, 0x8B, 0x00, 0x00, 0x98, 0xA0, 0x00, 0x42, 0x9C, 0x48, 0x00, 0x00,
    0x7A, 0x82, 0x00, 0x06, 0xDE, 0x0B, 0x00, 0x5E, 0x82, 0x00, 0x17, 0xB1,
    0x02, 0x00, 0xAA, 0x29, 0xA4, 0x22, 0x00, 0x00, 0x17, 0xDE, 0x67, 0x00,
    0x00, 0x00, 0x34, 0xD6, 0x93, 0x00, 0x00, 0x0B, 0xC6, 0x1A, 0xB0, 0x43,
    0x00, 0x9C, 0x4F, 0x00, 0x16, 0xCB, 0x0E, 0xA6, 0x3E, 0x00, 0x08, 0xC2,
    0x0F, 0x16, 0xBC, 0x02, 0x7F, 0x48, 0x00, 0x00, 0x60, 0xA7, 0x97, 0x00,
    0x00, 0x00, 0x00, 0xD1, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0x98,
    0x00, 0x00, 0x07, 0xB5, 0x34, 0x00, 0x01, 0xA6, 0x53, 0x00, 0x00, 0x8D,
    0x77, 0x00, 0x00, 0x6D, 0x98, 0x00, 0x00, 0x00, 0xD8, 0xFF, 0xFF, 0xFF,
    0xB0, 0x74, 0xFF, 0x18, 0x74, 0x40, 0x00, 0x74, 0x40, 0x00, 0x74, 0x40,
    0x00, 0x74, 0x40, 0x00, 0x74, 0x40, 0x00, 0x74, 0x40, 0x00, 0x74, 0xFF,
    0x18, 0x8F, 0x00, 0x00, 0x8A, 0x06, 0x00, 0x50, 0x40, 0x00, 0x0E, 0x81,
    0x00, 0x00, 0x90, 0x00, 0x00, 0x79, 0x16, 0xD8, 0xB4, 0x00, 0xB4, 0x00,
    0xB4, 0x00, 0xB4, 0x00, 0xB4, 0x00, 0xB4, 0x00, 0xB4, 0xD8, 0xB4, 0x00,
    0xA3, 0x62, 0x00, 0x1D, 0xA2, 0xB6, 0x01, 0x8C, 0x2C, 0x66, 0x50, 0x20,
    0xFF, 0xFF, 0xFF, 0xFF, 0x8C, 0x3D, 0x84, 0x42, 0xDF, 0xF4, 0x93, 0x00,
    0x00, 0x00, 0x10, 0xCE, 0x00, 0x23, 0xA4, 0xD5, 0xE3, 0x00, 0xA3, 0x63,
    0x53, 0xDA, 0x00, 0x60, 0xF2, 0xB2, 0xB6, 0x08, 0x78, 0x3C, 0x00, 0x00,
    0x00, 0x78, 0xA4, 0xEB, 0x6A, 0x00, 0x78, 0x7F, 0x15, 0xCD, 0x04, 0x78,
    0x32, 0x00, 0xA0, 0x17, 0x78, 0x7A, 0x17, 0xCB, 0x03, 0x78, 0xA4, 0xEF,
    0x5F, 0x00, 0x1C, 0xCF, 0xEA, 0x3C, 0x84, 0x5C, 0x27, 0xB3, 0xA6, 0x0F,
    0x00, 0x00, 0x89, 0x59, 0x1F, 0xB6, 0x1B, 0xCD, 0xEB, 0x45, 0x00, 0x00,
    0x00, 0xB4, 0x24, 0xDB, 0xC6, 0xBA, 0x8E, 0x50, 0x26, 0xD4, 0xAD, 0x07,
    0x00, 0xAC, 0x8A, 0x55, 0x24, 0xD2, 0x17, 0xD6, 0xD2, 0xB1, 0x18, 0xC7,
    0xEC, 0x55, 0x00, 0x88, 0x55, 0x13, 0xBF, 0x01, 0xAC, 0xFF, 0xFF, 0xFF,
    0x16, 0x8C, 0x51, 0x02, 0x00, 0x00, 0x1B, 0xCA, 0xF7, 0xA4, 0x01, 0x31,
    0xF0, 0x6A, 0xEC, 0xFF, 0x34, 0x4C, 0x64, 0x00, 0x4C, 0x64, 0x00, 0x4C,
    0x64, 0x00, 0x4C, 0x64, 0x00, 0x22, 0xD9, 0xCC, 0xB4, 0x90, 0x51, 0x24,
    0xDC, 0xB2, 0x04, 0x00, 0xB0, 0x92, 0x50, 0x21, 0xDB, 0x20, 0xD6, 0xC6,
    0xBF, 0x00, 0x00, 0x2D, 0xC6, 0x58, 0xEE, 0xEB, 0x47, 0x78, 0x3C, 0x00,
    0x00, 0x78, 0xA2, 0xEC, 0x74, 0x78, 0x8A, 0x15, 0xC9, 0x78, 0x40, 0x00,
    0xB4, 0x78, 0x3C, 0x00, 0xB4, 0x78, 0x3C, 0x00, 0xB4, 0x78, 0x3C, 0x78,
    0x3C, 0x78, 0x3C, 0x78, 0x3C, 0x78, 0x3C, 0x78, 0x3C, 0x00, 0x78, 0x3C,
    0x00, 0x78, 0x3C, 0x00, 0x78, 0x3C, 0x00, 0x78, 0x3C, 0x00, 0x78, 0x3C,
    0x00, 0x78, 0x3C, 0x01, 0x8A, 0x37, 0x49, 0xE1, 0x0F, 0x78, 0x3C, 0x00,
    0x00, 0x78, 0x3C, 0x86, 0x62, 0x78, 0x9C, 0x89, 0x00, 0x78, 0xC7, 0x92,
    0x00, 0x78, 0x3C, 0xAD, 0x26, 0x78, 0x3C, 0x2B, 0xAD, 0x7C, 0x38, 0x7C,
    0x38, 0x7C, 0x38, 0x7C, 0x38, 0x7C, 0x38, 0x7C, 0x38, 0x78, 0x95, 0xF2,
    0x5A, 0xDD, 0xC5, 0x03, 0x78, 0x85, 0x26, 0xE0, 0x17, 0xAF, 0x21, 0x78,
    0x3E, 0x00, 0xB5, 0x00, 0x8C, 0x28, 0x78, 0x3C, 0x00, 0xB4, 0x00, 0x8C,
    0x28, 0x78, 0x3C, 0x00, 0xB4, 0x00, 0x8C, 0x28, 0x78, 0xC2, 0xF2, 0x79,
    0x78, 0x85, 0x16, 0xCD, 0x78, 0x3F, 0x00, 0xB4, 0x78, 0x3C, 0x00, 0xB4,
    0x78, 0x3C, 0x00, 0xB4, 0x1C, 0xCE, 0xEE, 0x63, 0x00, 0x91, 0x56, 0x17,
    0xCD, 0x08, 0xB3, 0x04, 0x00, 0x99, 0x21, 0x93, 0x56, 0x16, 0xD0, 0x0A,
    0x1F, 0xCD, 0xF1, 0x5F, 0x00, 0x78, 0xA0, 0xF3, 0x70, 0x00, 0x78, 0x84,
    0x16, 0xCD, 0x01, 0x78, 0x33, 0x00, 0xA0, 0x14, 0x78, 0x7A, 0x15, 0xC9,
    0x00, 0x78, 0xAD, 0xEE, 0x64, 0x00, 0x78, 0x3C, 0x00, 0x00, 0x00, 0x78,
    0x3C, 0x00, 0x00, 0x00, 0x22, 0xDB, 0xCF, 0xAA, 0x8D, 0x52, 0x28, 0xD3,
    0xAF, 0x07, 0x00, 0xA8, 0x8B, 0x56, 0x22, 0xD0, 0x1A, 0xCF, 0xCE, 0xBC,
    0x00, 0x00, 0x00, 0xB4, 0x00, 0x00, 0x00, 0xB4, 0x7C, 0xB3, 0x9F, 0x7C,
    0x75, 0x0C, 0x7C, 0x3C, 0x00, 0x7C, 0x38, 0x00, 0x7C, 0x38, 0x00, 0x42,
    0xE9, 0xE4, 0x3E, 0x96, 0x65, 0x09, 0x00, 0x32, 0xD7, 0xF2, 0x4D, 0xA2,
    0x3D, 0x50, 0x9F, 0x31, 0xE2, 0xE2, 0x39, 0x0A, 0x1E, 0x00, 0x58, 0x5C,
    0x00, 0xDC, 0xFF, 0x10, 0x58, 0x5C, 0x00, 0x58, 0x5C, 0x00, 0x57, 0x66,
    0x01, 0x33, 0xF2, 0x1C, 0x7C, 0x38, 0x00, 0xB4, 0x7C, 0x38, 0x00, 0xB4,
    0x7C, 0x38, 0x00, 0xB6, 0x74, 0x6A, 0x2E, 0xD7, 0x25, 0xE1, 0xC7, 0xA8,
    0xB1, 0x08, 0x05, 0xB0, 0x6B, 0x49, 0x44, 0x6F, 0x1B, 0x94, 0x91, 0x20,
    0x00, 0xA7, 0xAB, 0x00, 0x00, 0x78, 0x7F, 0x00, 0xB1, 0x00, 0x8F, 0x58,
    0x14, 0x95, 0x95, 0x0E, 0x8D, 0x89, 0x4B, 0x54, 0x56, 0x44, 0x7B, 0xAC,
    0x81, 0x13, 0x16, 0xB2, 0x53, 0xA0, 0x8B, 0x00, 0x00, 0xD4, 0x21, 0x71,
    0x89, 0x00, 0x8A, 0x3D, 0x35, 0x89, 0x0D, 0x97, 0x95, 0x0D, 0x00, 0x92,
    0x96, 0x00, 0x1A, 0xC2, 0xCA, 0x1C, 0xA3, 0x37, 0x3D, 0xA4, 0xB1, 0x10,
    0x00, 0xAE, 0x63, 0x59, 0x2E, 0x78, 0x13, 0xA4, 0x74, 0x29, 0x00, 0xA9,
    0xA0, 0x00, 0x00, 0x6A, 0x8A, 0x00, 0x04, 0x8E, 0x39, 0x00, 0x80, 0xB4,
    0x00, 0x00, 0xB0, 0xFF, 0xFF, 0xB1, 0x00, 0x00, 0x9C, 0x38, 0x00, 0x7F,
    0x6D, 0x00, 0x5C, 0xA0, 0x00, 0x00, 0xD7, 0xFF, 0xFF, 0xD4, 0x00, 0xB9,
    0x7B, 0x00, 0xB3, 0x01, 0x23, 0xA1, 0x00, 0xC4, 0x33, 0x00, 0x30, 0x93,
    0x00, 0x00, 0xA8, 0x00, 0x00, 0xB6, 0x03, 0x00, 0xA9, 0x7A, 0x44, 0x58,
    0x44, 0x58, 0x44, 0x58, 0x44, 0x58, 0x44, 0x58, 0x44, 0x58, 0x44, 0x58,
    0x44, 0x58, 0xCC, 0x68, 0x00, 0x17, 0xA2, 0x00, 0x00, 0xBE, 0x07, 0x00,
    0x8C, 0x74, 0x00, 0xB7, 0x09, 0x02, 0xA5, 0x00, 0x18, 0x9D, 0x00, 0xCA,
    0x58, 0x00, 0x51, 0xE9, 0x76, 0x1F, 0x41, 0x55, 0x1B, 0xAD, 0xDE, 0x1A,
    0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x20,
    0x20, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x20, 0xFF, 0xFF, 0xFF, 0xFF
};

/* This struct will be read by the CPU only */
static const nema_glyph_t arial6pt8bGlyphs0[] =
{
    {     0,   0,   2,    0,    1 },   // 0x20 ' '
    {     0,   2,   2,    0,   -5 },   // 0x21 '!'
    {    12,   3,   3,    0,   -5 },   // 0x22 '"'
    {    18,   5,   4,    0,   -5 },   // 0x23 '#'
    {    48,   5,   4,    0,   -5 },   // 0x24 '$'
    {    83,   7,   7,    0,   -5 },   // 0x25 '%'
    {   125,   6,   5,    0,   -5 },   // 0x26 '&'
    {   161,   2,   2,    0,   -5 },   // 0x27 '''
    {   165,   3,   3,    0,   -5 },   // 0x28 '('
    {   189,   3,   3,    0,   -5 },   // 0x29 ')'
    {   213,   3,   3,    0,   -5 },   // 0x2A '*'
    {   219,   5,   5,    0,   -4 },   // 0x2B '+'
    {   244,   2,   2,    0,    0 },   // 0x2C ','
    {   248,   3,   3,    0,   -2 },   // 0x2D '-'
    {   251,   2,   2,    0,    0 },   // 0x2E '.'
    {   253,   3,   2,    0,   -5 },   // 0x2F '/'
    {   271,   5,   4,    0,   -5 },   // 0x30 '0'
    {   301,   3,   4,    0,   -5 },   // 0x31 '1'
    {   319,   5,   4,    0,   -5 },   // 0x32 '2'
    {   349,   5,   4,    0,   -5 },   // 0x33 '3'
    {   379,   5,   4,    0,   -5 },   // 0x34 '4'
    {   409,   5,   4,    0,   -5 },   // 0x35 '5'
    {   439,   5,   4,    0,   -5 },   // 0x36 '6'
    {   469,   5,   4,    0,   -5 },   // 0x37 '7'
    {   499,   5,   4,    0,   -5 },   // 0x38 '8'
    {   529,   5,   4,    0,   -5 },   // 0x39 '9'
    {   559,   2,   2,    0,   -4 },   // 0x3A ':'
    {   569,   2,   2,    0,   -4 },   // 0x3B ';'
    {   581,   5,   5,    0,   -3 },   // 0x3C '<'
    {   596,   5,   5,    0,   -3 },   // 0x3D '='
    {   606,   5,   5,    0,   -3 },   // 0x3E '>'
    {   621,   5,   4,    0,   -5 },   // 0x3F '?'
    {   651,   8,   8,    0,   -5 },   // 0x40 '@'
    {   715,   7,   5,   -1,   -5 },   // 0x41 'A'
    {   757,   5,   5,    0,   -5 },   // 0x42 'B'
    {   787,   6,   6,    0,   -5 },   // 0x43 'C'
    {   823,   6,   6,    0,   -5 },   // 0x44 'D'
    {   859,   5,   5,    0,   -5 },   // 0x45 'E'
    {   889,   5,   5,    0,   -5 },   // 0x46 'F'
    {   919,   6,   6,    0,   -5 },   // 0x47 'G'
    {   955,   6,   6,    0,   -5 },   // 0x48 'H'
    {   991,   2,   2,    0,   -5 },   // 0x49 'I'
    {  1003,   4,   4,    0,   -5 },   // 0x4A 'J'
    {  1027,   6,   5,    0,   -5 },   // 0x4B 'K'
    {  1063,   5,   4,    0,   -5 },   // 0x4C 'L'
    {  1093,   7,   7,    0,   -5 },   // 0x4D 'M'
    {  1135,   6,   6,    0,   -5 },   // 0x4E 'N'
    {  1171,   6,   6,    0,   -5 },   // 0x4F 'O'
    {  1207,   5,   5,    0,   -5 },   // 0x50 'P'
    {  1237,   6,   6,    0,   -5 },   // 0x51 'Q'
    {  1279,   6,   6,    0,   -5 },   // 0x52 'R'
    {  1315,   5,   5,    0,   -5 },   // 0x53 'S'
    {  1345,   5,   5,    0,   -5 },   // 0x54 'T'
    {  1375,   6,   6,    0,   -5 },   // 0x55 'U'
    {  1411,   6,   5,    0,   -5 },   // 0x56 'V'
    {  1447,   8,   8,    0,   -5 },   // 0x57 'W'
    {  1495,   6,   5,    0,   -5 },   // 0x58 'X'
    {  1531,   6,   5,    0,   -5 },   // 0x59 'Y'
    {  1567,   5,   5,    0,   -5 },   // 0x5A 'Z'
    {  1597,   3,   2,    0,   -5 },   // 0x5B '['
    {  1621,   3,   2,    0,   -5 },   // 0x5C '\'
    {  1639,   2,   2,    0,   -5 },   // 0x5D ']'
    {  1655,   4,   4,    0,   -5 },   // 0x5E '^'
    {  1667,   6,   4,   -1,    2 },   // 0x5F '_'
    {  1673,   2,   3,    0,   -5 },   // 0x60 '`'
    {  1675,   5,   4,    0,   -4 },   // 0x61 'a'
    {  1700,   5,   4,    0,   -5 },   // 0x62 'b'
    {  1730,   4,   4,    0,   -4 },   // 0x63 'c'
    {  1750,   4,   4,    0,   -5 },   // 0x64 'd'
    {  1774,   5,   4,    0,   -4 },   // 0x65 'e'
    {  1799,   3,   2,    0,   -5 },   // 0x66 'f'
    {  1817,   4,   4,    0,   -4 },   // 0x67 'g'
    {  1845,   4,   4,    0,   -5 },   // 0x68 'h'
    {  1869,   2,   2,    0,   -5 },   // 0x69 'i'
    {  1881,   3,   2,   -1,   -5 },   // 0x6A 'j'
    {  1905,   4,   4,    0,   -5 },   // 0x6B 'k'
    {  1929,   2,   2,    0,   -5 },   // 0x6C 'l'
    {  1941,   7,   7,    0,   -4 },   // 0x6D 'm'
    {  1976,   4,   4,    0,   -4 },   // 0x6E 'n'
    {  1996,   5,   4,    0,   -4 },   // 0x6F 'o'
    {  2021,   5,   4,    0,   -4 },   // 0x70 'p'
    {  2056,   4,   4,    0,   -4 },   // 0x71 'q'
    {  2084,   3,   3,    0,   -4 },   // 0x72 'r'
    {  2099,   4,   4,    0,   -4 },   // 0x73 's'
    {  2119,   3,   2,    0,   -6 },   // 0x74 't'
    {  2140,   4,   4,    0,   -4 },   // 0x75 'u'
    {  2160,   4,   4,    0,   -4 },   // 0x76 'v'
    {  2180,   6,   6,    0,   -4 },   // 0x77 'w'
    {  2210,   4,   4,    0,   -4 },   // 0x78 'x'
    {  2230,   4,   4,    0,   -4 },   // 0x79 'y'
    {  2258,   4,   4,    0,   -4 },   // 0x7A 'z'
    {  2278,   3,   3,    0,   -5 },   // 0x7B '{'
    {  2302,   2,   2,    0,   -5 },   // 0x7C '|'
    {  2318,   3,   3,    0,   -5 },   // 0x7D '}'
    {  2342,   5,   5,    0,   -2 },   // 0x7E '~'
    {  2352,   4,   6,    1,   -5 },   // 0x7F
    {  2376,   0,   0,    0,    0 }
};

/* This struct will be read by the CPU only */
static const nema_font_range_t arial6pt8b_ranges[] =
{
    {0x00000020, 0x0000007f, arial6pt8bGlyphs0},
    {0, 0, NULL}
};

/* This struct will be read by the CPU only */
nema_font_t arial6pt8b =
{
    {
        .base_virt = (void *) arial6pt8bBitmaps,
        .base_phys = (uintptr_t) arial6pt8bBitmaps,
        .size      = (int) sizeof(arial6pt8bBitmaps)
    },
    arial6pt8b_ranges,
    (int)sizeof(arial6pt8bBitmaps),
    arial6pt8bBitmaps,
    0,
    2, 9, 7, 8
};
#endif // ARIAL6PT8B_C

//*****************************************************************************
//
//! @file rotating_crate.c
//!
//! @brief NemaGFX example.
//! this example shows a rotating crate with texture rending support. with Nema
//! GPU support, it can significantly reduce the general CPU effort to calculate
//! the data inside the frame buffer
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

// -----------------------------------------------------------------------------
// Copyright (c) 2019 Think Silicon S.A.
// Think Silicon S.A. Confidential Proprietary
// -----------------------------------------------------------------------------
//     All Rights reserved - Unpublished -rights reserved under
//         the Copyright laws of the European Union
//
//  This file includes the Confidential information of Think Silicon S.A.
//  The receiver of this Confidential Information shall not disclose
//  it to any third party and shall protect its confidentiality by
//  using the same degree of care, but not less than a reasonable
//  degree of care, as the receiver uses to protect receiver's own
//  Confidential Information. The entire notice must be reproduced on all
//  authorised copies and copies may only be made to the extent permitted
//  by a licensing agreement from Think Silicon S.A..
//
//  The software is provided 'as is', without warranty of any kind, express or
//  implied, including but not limited to the warranties of merchantability,
//  fitness for a particular purpose and noninfringement. In no event shall
//  Think Silicon S.A. be liable for any claim, damages or other liability, whether
//  in an action of contract, tort or otherwise, arising from, out of or in
//  connection with the software or the use or other dealings in the software.
//
//
//                    Think Silicon S.A.
//                    http://www.think-silicon.com
//                    Patras Science Park
//                    Rion Achaias 26504
//                    Greece
// -----------------------------------------------------------------------------

#include "nema_core.h"
#include "nema_matrix4x4.h"
#include "nema_math.h"
#include "nema_utils.h"

#ifndef DONT_USE_NEMADC
#include "nema_dc.h"
#endif

#ifdef ENABLE_DSI
    #include "am_devices_dsi_rm67162.h"
#else
    #include "am_devices_nemadc_rm67162.h"
#endif

#ifndef RESX
#define RESX 280
#endif

#ifndef RESY
#define RESY 280
#endif

#ifndef COLOR_CUBE
#define COLOR_CUBE 0
#endif

typedef enum
{
    PRIM_LINE,
    PRIM_RECT,
    PRIM_TRI,
    PRIM_QUAD,
    PRIM_MAX
} primitive_e;


#define FRAME_BUFFERS 2
img_obj_t fb[FRAME_BUFFERS];

#ifndef DONT_USE_NEMADC
nemadc_layer_t layer[FRAME_BUFFERS] = {{0}};
#endif

#define CRATE_FORMAT NEMA_RGB565
// #define CRATE_PATH   "crate.512x512.rgba"

#include "crate_280x280_rgba565.h"

img_obj_t crate  = {{0}, RESX, RESY, -1, 0, CRATE_FORMAT, 0};

void
load_objects(void)
{
    int i;
    for ( i = 0; i < FRAME_BUFFERS; ++i )
    {
        fb[i].w = RESX;
        fb[i].h = RESY;
        fb[i].format = NEMA_RGB565;
        fb[i].stride = RESX * 2;
        fb[i].bo = nema_buffer_create(fb[i].stride * fb[i].h);
        nema_buffer_map(&fb[i].bo);

#ifndef DONT_USE_NEMADC
        layer[i].sizex = layer[i].resx = fb[i].w;
        layer[i].sizey = layer[i].resy = fb[i].h;
        layer[i].stride = fb[i].stride;
        layer[i].format = NEMADC_RGB565;
        layer[i].blendmode = NEMADC_BF_ONE;
        layer[i].baseaddr_phys = fb[i].bo.base_phys;
        layer[i].baseaddr_virt = fb[i].bo.base_virt;
#endif
    }

    // crate.bo = nema_load_file(CRATE_PATH, -1, (void *)0);

    crate.bo = nema_buffer_create(crate_280x280_rgba565_length);
    nema_memcpy(crate.bo.base_virt, crate_280x280_rgba565, crate_280x280_rgba565_length);
}

int mouse_x = 0;
int mouse_y = 0;

void draw_cube_side(float *v, int v0, int v1, int v2, int v3, uint32_t col)
{
#if COLOR_CUBE
    //fill with color
    nema_fill_quad(v[v0 * 3], v[v0 * 3 + 1],
                   v[v1 * 3], v[v1 * 3 + 1],
                   v[v2 * 3], v[v2 * 3 + 1],
                   v[v3 * 3], v[v3 * 3 + 1], col);
#else
    //blit
    nema_blit_quad_fit(v[v0 * 3], v[v0 * 3 + 1],
                   v[v1 * 3], v[v1 * 3 + 1],
                   v[v2 * 3], v[v2 * 3 + 1],
                   v[v3 * 3], v[v3 * 3 + 1]);
#endif
}

void innercube(int angle_x, int angle_y, int angle_z)
{
    float box_size_2 = 0.2f;
    float FoV = 28.0724869359f;
    float v[] =
    {               //x     y    z
                    -box_size_2, -box_size_2,  box_size_2,  //0  0
                     box_size_2, -box_size_2,  box_size_2,  //1  3
                     box_size_2,  box_size_2,  box_size_2,  //2  6
                    -box_size_2,  box_size_2,  box_size_2,  //3  9
                    -box_size_2, -box_size_2, -box_size_2,  //4  12
                     box_size_2, -box_size_2, -box_size_2,  //5  15
                     box_size_2,  box_size_2, -box_size_2,  //6  18
                    -box_size_2,  box_size_2, -box_size_2   //7  21
    };

    //projection
    nema_matrix4x4_t mvp;

    nema_mat4x4_load_perspective(mvp, FoV, (float)RESX / RESY, 0.2f, 100.f);

    nema_matrix4x4_t proj;
    nema_mat4x4_load_identity(proj);
    nema_mat4x4_rotate_X(proj, angle_x);
    nema_mat4x4_rotate_Y(proj, angle_y);
    nema_mat4x4_rotate_Z(proj, angle_z);
    nema_mat4x4_translate(proj, 0, 0, 2.f-box_size_2);

    nema_mat4x4_mul(mvp, mvp, proj);

    float w = 1.f;
    int i;

    for (i = 0; i < 24; i += 3)
    {
        nema_mat4x4_obj_to_win_coords(mvp, 0.f, 0.f, RESX, RESY,
                                      1.f, 100.f,
                                      &v[i  ], &v[i + 1], &v[i + 2], &w);
    }

    //blend color with background
#if COLOR_CUBE
    nema_set_blend_fill(NEMA_BL_SIMPLE);
#else
    nema_set_blend_blit(NEMA_BL_SRC);
#endif
    nema_bind_src_tex(crate.bo.base_phys, crate.w, crate.h, crate.format, crate.stride, NEMA_FILTER_BL);

    //remove this to draw back sides also
    nema_tri_cull(NEMA_CULL_CW);
    draw_cube_side(v, 0, 1, 2, 3, 0x60ffffff); //front
    draw_cube_side(v, 4, 0, 3, 7, 0x600000ff); //left
    draw_cube_side(v, 1, 5, 6, 2, 0x60ff00ff); //right
    draw_cube_side(v, 4, 5, 1, 0, 0x60ff0000); //top
    draw_cube_side(v, 3, 2, 6, 7, 0x6000ff00); //bottom
    draw_cube_side(v, 5, 4, 7, 6, 0x60808080); //back
    nema_tri_cull(NEMA_CULL_NONE);
}

int cur_fb = 0;
uintptr_t cur_fb_base_phys = 0;

void
swap_buffers(void)
{

#ifndef DONT_USE_NEMADC
//    nemadc_wait_vsync();
    nemadc_set_layer(0, &layer[cur_fb]);
#endif

    cur_fb = (cur_fb + 1) % FRAME_BUFFERS;
    cur_fb_base_phys = fb[cur_fb].bo.base_phys;
}

nema_cmdlist_t cl;
nema_cmdlist_t cl_clear;

void
nema_gfx_display_function()
{
    static int angle_x = 0.f;
    static int angle_y = 0.f;
    static int angle_z = 80.f;

    angle_x = (angle_x + 1) % 360;
    angle_y = (angle_y + 2) % 360;
    angle_z = (angle_z + 2) % 360;


    nema_cl_bind(&cl_clear);
    nema_cl_rewind(&cl_clear);

    nema_set_clip(0, 0, RESX, RESY);
    nema_bind_dst_tex(cur_fb_base_phys, fb[0].w, fb[0].h, fb[0].format, fb[0].stride);
    nema_clear(0);

    nema_cl_submit(&cl_clear);
    nema_cl_wait(&cl_clear);
#ifdef ENABLE_DSI
    dsi_send_frame_single(NEMADC_OUTP_OFF);
#else
    nemadc_send_frame_single();
#endif


    nema_cl_bind(&cl);
    nema_cl_rewind(&cl);

    nema_set_clip(0, 0, RESX, RESY);
    nema_bind_dst_tex(cur_fb_base_phys, fb[0].w, fb[0].h, fb[0].format, fb[0].stride);

    innercube(angle_x, angle_y, angle_z);

    nema_cl_submit(&cl);
    nema_cl_wait(&cl);
#ifdef ENABLE_DSI
    dsi_send_frame_single(NEMADC_OUTP_OFF);
#else
    nemadc_send_frame_single();
#endif

    swap_buffers();
}

#ifdef STANDALONE
int main()
#else
int rotating_crate()
#endif
{
    int ret;

    //Initialize NemaGFX
    ret = nema_init();
    if (ret != 0)
    {
        return ret;
    }
    //Initialize Nema|dc
    ret = nemadc_init();
    if (ret != 0)
    {
        return ret;
    }
#ifdef ENABLE_DSI
    uint8_t ui8LanesNum = 1;
    uint8_t ui8DbiWidth = 8;
    if ( am_hal_dsi_initialize(ui8LanesNum, ui8DbiWidth) != 0 )
    {
        return -3;
    }
#endif

#ifdef ENABLE_SPI4
    uint16_t panel_resx = 390; //panel's max resolution
    uint16_t panel_resy = 390; //panel's max resolution
#endif
#ifdef ENABLE_QSPI
    uint16_t panel_resx = 360; //panel's max resolution
    uint16_t panel_resy = 360; //panel's max resolution
#endif
#ifdef ENABLE_DSI
    uint16_t panel_resx = 390; //panel's max resolution
    uint16_t panel_resy = 390; //panel's max resolution
#endif
    uint16_t minx, miny;

    //Set the display region to center
    if ( RESX > panel_resx )
    {
        minx = 0; // set the minimum value to 0
    }
    else
    {
        minx = (panel_resx - RESX) / 2;
    }

    if ( RESY > panel_resy )
    {
        miny = 0; // set the minimum value to 0
    }
    else
    {
        miny = (panel_resy - RESY) / 2;
    }

#ifdef ENABLE_SPI4
    am_devices_nemadc_rm67162_init(MIPICFG_SPI4, MIPICFG_1RGB332_OPT0, RESX, RESY, minx, miny);
#endif
#ifdef ENABLE_QSPI
    am_devices_nemadc_rm67162_init( MIPICFG_QSPI | MIPICFG_SPI4, MIPICFG_4RGB565_OPT0, RESX, RESY, minx, miny);
#endif
#ifdef ENABLE_DSI
    am_devices_dsi_rm67162_init(MIPICFG_8RGB888_OPT0, RESX, RESY, minx, miny);
#endif

    load_objects();

    cur_fb_base_phys = fb[cur_fb].bo.base_phys;

    //Create Command Lists
    cl  = nema_cl_create();
    cl_clear = nema_cl_create();

    while(1)
    {
        nema_gfx_display_function();
        nema_calculate_fps();
    }
}

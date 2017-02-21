/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of The Linux Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*---------------------------------------------------------------------------
 * This file is autogenerated file using gcdb parser. Please do not edit it.
 * Update input XML file to add a new entry or update variable in this file
 * VERSION = "1.0"
 *---------------------------------------------------------------------------*/

#ifndef _PANEL_R63315_1080P_VIDEO_H_
#define _PANEL_R63315_1080P_VIDEO_H_
/*---------------------------------------------------------------------------*/
/* HEADER files                                                              */
/*---------------------------------------------------------------------------*/
#include "panel.h"

/*---------------------------------------------------------------------------*/
/* Panel configuration                                                       */
/*---------------------------------------------------------------------------*/
static struct panel_config r63315_1080p_video_panel_data = {
	"qcom,mdss_dsi_r63315_1080p_video", "dsi:0:", "qcom,mdss-dsi-panel",
	10, 0, "DISPLAY_1", 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel resolution                                                          */
/*---------------------------------------------------------------------------*/
static struct panel_resolution r63315_1080p_video_panel_res = {
	1080, 1920, 96, 64, 16, 0, 4, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel color information                                                   */
/*---------------------------------------------------------------------------*/
static struct color_info r63315_1080p_video_color = {
	24, 0, 0xff, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel on/off command information                                          */
/*---------------------------------------------------------------------------*/

static char r63315_1080p_cmd1[] = {
		0x02,0x00,0x29,0xC0,
		0xB0,0x04,0xFF,0xFF
};
static char r63315_1080p_cmd2[] = {
		0x02,0x00,0x23,0xC0,
		0xD6,0x01,0xFF,0xFF};
static char r63315_1080p_cmd3[] = {
		0x07,0x00,0x29,0xC0,
		0xB3,0x14,0x00,0x00,
		0x00,0x00,0x00,0xFF};
static char r63315_1080p_cmd4[] = {
		0x03,0x00,0x29,0xC0,
		0xB6,0x3A,0xC3,0xFF};
static char r63315_1080p_cmd5[] = {
		0x23,0x00,0x29,0xC0,
		0xC1,0x84,0x60,0x00,
		0x20,0xA9,0x30,0xFE,
		0x62,0xFF,0xFF,0xFF,
		0x9B,0x7B,0xCF,0xB5,
		0xFF,0xFF,0xFF,0x6C,
		0x7D,0x22,0x54,0x02,
		0x00,0x00,0x00,0x00,
		0x00,0x62,0x03,0x00,
		0x22,0x00,0x01,0xFF};
static char r63315_1080p_cmd6[] = {
		0x08,0x00,0x29,0xC0,
		0xC2,0x32,0xF7,0x80,
		0x08,0x08,0x00,0x00};
static char r63315_1080p_cmd7[] = {
		0x17,0x00,0x29,0xC0,
		0xC4,0x70,0x0C,0x0C,
		0x55,0x55,0x00,0x00,
		0x00,0x00,0x05,0x05,
		0x00,0x0C,0x0C,0x55,
		0x55,0x00,0x00,0x00,
		0x00,0x05,0x05,0xFF};
static char r63315_1080p_cmd8[] = {
		0x29,0x00,0x29,0xC0,
		0xC6,0x75,0x32,0x32,
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x09,0x19,
		0x09,0x75,0x32,0x32,
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x09,0x19,
		0x09,0xFF,0xFF,0xFF};
static char r63315_1080p_cmd9[] = {
		0x1F,0x00,0x29,0xC0,
		0xC7,0x00,0x08,0x0F,
		0x18,0x27,0x37,0x42,
		0x54,0x38,0x40,0x4C,
		0x59,0x62,0x69,0x79,
		0x00,0x08,0x0F,0x18,
		0x27,0x37,0x42,0x54,
		0x38,0x40,0x4C,0x59,
		0x62,0x69,0x79,0xFF};
/*static char r63315_1080p_cmd10[] = {
		0x14,0x00,0x29,0xC0,
		0xC8,0x01,0x00,0xFF,
		0xFE,0xF8,0xFC,0x00,
		0x00,0x00,0x01,0xFD,
		0xDB,0x00,0x00,0xFF,
		0x03,0x05,0xF6,0x00};*/
static char r63315_1080p_cmd11[] = {
		0x0A,0x00,0x29,0xC0,
		0xCB,0xFF,0xFF,0xFF,
		0xFF,0x00,0x00,0x00,
		0x00,0xC0,0xFF,0xFF};
static char r63315_1080p_cmd12[] = {
		0x02,0x00,0x29,0xC0,
		0xCC,0x11,0xFF,0xFF};
static char r63315_1080p_cmd13[] = {
		0x0B,0x00,0x29,0xC0,
		0xD0,0xC4,0x81,0xBB,
		0x58,0x58,0x4C,0x19,
		0x19,0x04,0x00,0xFF};
static char r63315_1080p_cmd14[] = {
		0x1A,0x00,0x29,0xC0,
		0xD3,0x1B,0x33,0xBB,
		0xBB,0xB3,0x33,0x33,
		0x33,0x00,0x01,0x00,
		0xA0,0xD8,0xA0,0x00,
		0x44,0x44,0x33,0x3B,
		0x22,0x72,0x57,0x3D,
		0xBF,0x99,0xFF,0xFF};
static char r63315_1080p_cmd15[] = {
		0x08,0x00,0x29,0xC0,
		0xD5,0x06,0x00,0x00,
		0x01,0x22,0x01,0x22};
/*static char r63315_1080p_cmd15[] = {0x02,0x00,0x29,0xC0,
				0x51,0xff,0xFF,0xFF};
static char r63315_1080p_cmd16[] = {0x02,0x00,0x29,0xC0,
				0x53,0x2C,0xFF,0xFF};
static char r63315_1080p_cmd17[] = {0x02,0x00,0x29,0xC0,
				0x55,0x00,0xFF,0xFF};*/
static char r63315_1080p_exit_sleep[] = {
	0x29,0x00,0x05,0x80};
static char r63315_1080p_display_on[] = {
	0x11,0x00,0x05,0x80};

static struct mipi_dsi_cmd r63315_1080p_video_on_command[] = {
{ARRAY_SIZE(r63315_1080p_cmd1), r63315_1080p_cmd1, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd2), r63315_1080p_cmd2, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd3), r63315_1080p_cmd3, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd4), r63315_1080p_cmd4, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd5), r63315_1080p_cmd5, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd6), r63315_1080p_cmd6, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd7), r63315_1080p_cmd7, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd8), r63315_1080p_cmd8, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd9), r63315_1080p_cmd9, 0x00},
//{ARRAY_SIZE(r63315_1080p_cmd10), r63315_1080p_cmd10, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd11), r63315_1080p_cmd11, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd12), r63315_1080p_cmd12, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd13), r63315_1080p_cmd13, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd14), r63315_1080p_cmd14, 0x00},
{ARRAY_SIZE(r63315_1080p_cmd15), r63315_1080p_cmd15, 0x00},
//{ARRAY_SIZE(r63315_1080p_cmd16), r63315_1080p_cmd16, 0x00},
//{ARRAY_SIZE(r63315_1080p_cmd17), r63315_1080p_cmd17, 0x00},
{ARRAY_SIZE(r63315_1080p_exit_sleep), r63315_1080p_exit_sleep, 0x23},
{ARRAY_SIZE(r63315_1080p_display_on), r63315_1080p_display_on, 0x78},
};

#define R63315_1080P_VIDEO_ON_COMMAND 16



static char r63315_1080p_videooff_cmd1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd r63315_1080p_video_off_command[] = {
	{0x4, r63315_1080p_videooff_cmd1, 0x79}
};

#define R63315_1080P_VIDEO_OFF_COMMAND 1


static struct command_state r63315_1080p_video_state = {
	0, 1
};

/*---------------------------------------------------------------------------*/
/* Command mode panel information                                            */
/*---------------------------------------------------------------------------*/
static struct commandpanel_info r63315_1080p_video_command_panel = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Video mode panel information                                              */
/*---------------------------------------------------------------------------*/
static struct videopanel_info r63315_1080p_video_video_panel = {
	0, 0, 0, 0, 1, 1, 2, 0, 0x9
};

/*---------------------------------------------------------------------------*/
/* Lane configuration                                                        */
/*---------------------------------------------------------------------------*/
static struct lane_configuration r63315_1080p_video_lane_config = {
	4, 0, 1, 1, 1, 1
};

/*---------------------------------------------------------------------------*/
/* Panel timing                                                              */
/*---------------------------------------------------------------------------*/
static const uint32_t r63315_1080p_video_timings[] = {
	//0xf9, 0x3d, 0x34, 0x00, 0x58, 0x4d, 0x36, 0x3f, 0x53, 0x03, 0x04, 0x00
	0xe7, 0x36, 0x24, 0x00, 0x66, 0x6a, 0x2a, 0x3a, 0x2d, 0x03, 0x04, 0x00
};

static struct panel_timing r63315_1080p_video_timing_info = {
	0, 4, 0x04, 0x1B
};

/*---------------------------------------------------------------------------*/
/* Panel reset sequence                                                      */
/*---------------------------------------------------------------------------*/
static struct panel_reset_sequence r63315_1080p_video_reset_seq = {
	{1, 0, 1, }, {20, 200, 20,}, 2
};

/*---------------------------------------------------------------------------*/
/* Backlight setting                                                         */
/*---------------------------------------------------------------------------*/
static struct backlight r63315_1080p_video_backlight = {
	0, 1, 255, 0, 0, 0
};

#endif /*_PANEL_R63315_1080P_VIDEO_H_*/

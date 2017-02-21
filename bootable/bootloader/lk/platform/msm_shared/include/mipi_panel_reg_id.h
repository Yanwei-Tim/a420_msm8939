#ifndef _MIPI_ID_REG_H_
#define _MIPI_ID_REG_H_
#include <msm_panel.h>
#include <mipi_dsi.h>
/*---------------------------------------------------------------------------*/
/* static panel selection variable                                           */
/*---------------------------------------------------------------------------*/
typedef uint32_t (*get_ic_id_func)(void);
uint32_t mipi_otm8018b_manufacture_id(void);
uint32_t mipi_hx8389b_manufacture_id(void);
uint32_t mipi_hx8394d_manufacture_id(void);
uint32_t mipi_ili9806c_manufacture_id(void);
uint32_t mipi_ili9806e_manufacture_id(void);
uint32_t mipi_ili9881_manufacture_id(void);
uint32_t mipi_rm68171_manufacture_id(void);
uint32_t mipi_otm9605a_manufacture_id(void);
uint32_t mipi_sh1282_manufacture_id(void);
uint32_t mipi_otm8019_manufacture_id(void);
uint32_t mipi_nt35596_manufacture_id(void);
uint32_t mipi_nt35590_manufacture_id(void);
uint32_t mipi_r61318_manufacture_id(void);
uint32_t mipi_rm68172_manufacture_id(void);
uint32_t mipi_default_manufacture_id(void);
uint32_t mipi_nt35512s_manufacture_id(void);
uint32_t mipi_otm1901_manufacture_id(void);
uint32_t mipi_otm1284_manufacture_id(void);
uint32_t mipi_otm1283_manufacture_id(void);
uint32_t mipi_r63315_manufacture_id(void);
uint32_t mipi_ST7701_manufacture_id(void);
uint32_t mipi_otm8019_manufacture_id(void);

enum {
	JDI_1080P_VIDEO_PANEL,
	NT35590_720P_VIDEO_PANEL,
	ILI9881_720P_CPT_5INCH_VIDEO_PANEL,
	ILI9881_720P_CPT_5INCH_HLT_VIDEO_PANEL,
	OTM8019A_FWVGA_VIDEO_PANEL,
	RM61318_720P_CPT_VIDEO_PANEL,
	ILI9806E_FWVGA_5INCH_IVO_HUASHI_VIDEO_PANEL,
	OTM1283A_720P_VIDEO_PANEL,
	NT35590_720P_CMD_PANEL,
	INNOLUX_720P_VIDEO_PANEL,
	SH1282_FWVGA_BOE_PANEL,
	ILI9806E_WVGA_BOE_PANEL,
	OTM8019_WVGA_BOE_PANEL,
	RM68191_WVGA_BOE_PANEL,
	SHARP_LS040T3SW01_QHD_VIDEO_PANEL,
	OTM9605A_F551G_WVGA_VIDEO_PANEL,
	OTM9605A_QHD_VIDEO_PANEL,
	OTM1284_720P_VIDEO_PANEL,
	OTM1283_720P_VIDEO_PANEL,
	RM68172_TM_WVGA_VIDEO_PANEL,
	ST7701_TM_VIDEO_PANEL,
	ST7701_480P_VIDEO_PANEL,
	RM68172_WANCHANGLONG_WVGA_VIDEO_PANEL,
	HX8394D_720P_VIDEO_PANEL,
	NT35512S_WVGA_VIDEO_PANEL,
	OTM1284A_BOE_HD_VIDEO_PANEL,
	ILL9881C_BOE_HD_VIDEO_PANEL,
	OTM1284A_HD_VIDEO_PANEL,
	NT35596_1080P_VIDEO_PANEL,
	SHARP_WQXGA_DUALDSI_VIDEO_PANEL,
	JDI_FHD_VIDEO_PANEL,
	HX8379A_FWVGA_VIDEO_PANEL,
	R61318_HD_VIDEO_PANEL,
	OTM1284_1080P_VIDEO_PANEL,//wangqing.yu modify for S500 LCM
	NT35532_1080P_VIDEO_PANEL,//s550
	OTM1901_1080P_VIDEO_PANEL,//s550
	NT35521_WXGA_VIDEO_PANEL,
	R63417_1080P_VIDEO_PANEL,
	JDI_A216_FHD_VIDEO_PANEL,
	R63315_1080P_VIDEO_PANEL,//jijin.wang modify for s500 turly LCM
	HX8394D_A470_VIDEO_PANEL,//wjj modify for a470 lcm
	HUASHI_ILI9881C_VIDEO_PANEL,
	SSD2080M_720P_VIDEO_PANEL,
	SHARP_LQ050T1SX05_VIDEO_PANEL,
	HX8394D_P800_VIDEO_PANEL,
	OTM8019_TM_VIDEO_PANEL,
	NT35512_TM_WVGA_VIDEO,
	HX8394F_A420_720P_VIDEO_PANEL,
	UNKNOWN_PANEL
};

#define OTM9605A_ID 0x9605
#define OTM1284_ID 0x1287
#define OTM1283_ID 0x1283
#define OTM1901_ID 0x1901
#define OTM8018B_ID 0x40
#define ILI9806C_ID 0x16
#define ILI9806E_ID 0x9806
#define ILI9881_ID 0x9881
#define R61318_ID   0x1318

#define HX8389B_ID  0x89
#define RM68171_ID  0x7181
#define RM68172_ID  0x7281
#define SH1282_ID   0x1202
#define OTM8019_ID  0x8019
#define RM68191_ID  0x8191
#define UNKNOWN_ID  0xFFFF

#define NT35596_ID  0x96
#define NT35590_ID  0x90
#define NT35512S_ID  0x5521
#define R63315_ID 0x3315

#define MIPI_DEFAULT_ID  1
#define ST7701_ID  0x2177
#define HX8394D_ID  0x8394
#define HX8394D_P800_ID  0x83



/* otm1284 read chip_id */
static char otm1284_set_pkt_size[] = {
	0x06,0x00,0x37,0x80};
static struct mipi_dsi_cmd otm1284_set_pkt_size_cmd[] = {
	{sizeof(otm1284_set_pkt_size), otm1284_set_pkt_size},
};
static char otm1284_panel_manufacture_id[] = {
	0xA1,0x00,0x06,0xA0};
static struct mipi_dsi_cmd otm1284_panel_manufacture_id_cmd[] = {
	{sizeof(otm1284_panel_manufacture_id), otm1284_panel_manufacture_id},
};

/* nt35512s get chip id select */
static char nt35512s_select_page2_cmds_01[] = {
	0x06, 0x00, 0x39, 0xC0,
	0xF0, 0x55, 0xAA, 0x52,
	0x08, 0x02, 0xFF, 0xFF
};
static char nt35512s_select_page2_cmds_02[] = {
	0x02, 0x00, 0x39, 0xC0,
	0xea, 0x02, 0xFF, 0xFF
};
static char nt35512s_select_page1_cmds_01[] = {
	0x06, 0x00, 0x39, 0xC0,
	0xF0, 0x55, 0xAA, 0x52,
	0x08, 0x01, 0xFF, 0xFF
};
static char nt35512s_panel_manufacture_id[] = {
	0xC5, 0x00, 0x24, 0xA0
};
static struct mipi_dsi_cmd nt35512s_panel_enable_page2_cmd[] = {
	{sizeof(nt35512s_select_page2_cmds_01), nt35512s_select_page2_cmds_01},
	{sizeof(nt35512s_select_page2_cmds_02), nt35512s_select_page2_cmds_02},
};
static struct mipi_dsi_cmd nt35512s_panel_enable_page1_cmd[] = {
	{sizeof(nt35512s_select_page1_cmds_01), nt35512s_select_page1_cmds_01}
};
static struct mipi_dsi_cmd nt35512s_panel_manufacture_id_cmd[] = {
	{sizeof(nt35512s_panel_manufacture_id), nt35512s_panel_manufacture_id},
};


/* NT35590 read chip_id */
static char nt35590_panel_set_pkt_size[] = {
        0x06, 0x00, 0x37, 0x80};
static struct mipi_dsi_cmd nt35590_panel_set_pkt_size_cmd[] = {
        {sizeof(nt35590_panel_set_pkt_size), nt35590_panel_set_pkt_size},
};
static char nt35590_panel_manufacture_id[] = {
        0xF4, 0x00, 0x24, 0xA0};
static struct mipi_dsi_cmd nt35590_panel_manufacture_id_cmd[] = {
        {sizeof(nt35590_panel_manufacture_id), nt35590_panel_manufacture_id},
};


/* NT35596 read chip_id*/
static char nt35596_select_page1_cmd[] = {
	0x02, 0x00, 0x39, 0xC0,
	0xFF, 0x00, 0xFF, 0xFF};
static struct mipi_dsi_cmd nt35596_panel_enable_page1_cmd[] = {
        {sizeof(nt35596_select_page1_cmd), nt35596_select_page1_cmd},
};
static char nt35596_panel_set_pkt_size[] = {
	0x04, 0x00, 0x39, 0xC0,
	0x06, 0x00, 0x37, 0x80};
static struct mipi_dsi_cmd nt35596_panel_set_pkt_size_cmd[] = {
        {sizeof(nt35596_panel_set_pkt_size), nt35596_panel_set_pkt_size},
};
static char nt35596_panel_manufacture_id[] = {
	0xF4, 0x00, 0x24, 0xA0};
static struct mipi_dsi_cmd nt35596_panel_manufacture_id_cmd[] = {
        {sizeof(nt35596_panel_manufacture_id), nt35596_panel_manufacture_id},
};


/* OTM8018B read chip_id */
static char otm8018b_panel_manufacture_id[4] = {0xDA, 0x00, 0x06, 0xA0};
static struct mipi_dsi_cmd otm8018b_panel_manufacture_id_cmd[] = {
	{ 0x4, otm8018b_panel_manufacture_id},
};

/* ili9806c read chip_id */
static char ili9806c_set_enable_register[]  = {
        0x04,0x00,0x29,0xC0,
        0xFF,0xFF,0x98,0x16};
static char ili9806c_panel_manufacture_id[] = {
        0xD3,0x00,0x04,0xA0};
static struct mipi_dsi_cmd ili9806c_panel_manufacture_id_cmd[] = {
        { 0x8, ili9806c_set_enable_register},
        { 0x4, ili9806c_panel_manufacture_id},
};

/* ili9806e read chip_id */
static char ili9806e_set_page1_cmd1[] = {
	0x02,0x00,0x29,0xC0,
	0x00,0x00,0xff,0xff};
static char ili9806e_set_page1_cmd2[] = {
	0x06,0x00,0x29,0xC0,
	0xFF,0xFF,0x98,0x06,
	0x04,0x01,0xFF,0xFF};
static char ili9806c_set_pkt_size1[] = {
	0x06,0x00,0x37,0x80};
static char ili9806e_panel_manufacture_id1[] = {
	0x00,0x00,0x06,0xA0};
static struct mipi_dsi_cmd ili9806e_panel_manufacture_id1_cmd[] = {
	{sizeof(ili9806e_set_page1_cmd1), ili9806e_set_page1_cmd1},
	{sizeof(ili9806e_set_page1_cmd2), ili9806e_set_page1_cmd2},
	{sizeof(ili9806c_set_pkt_size1), ili9806c_set_pkt_size1},
	{sizeof(ili9806e_panel_manufacture_id1), ili9806e_panel_manufacture_id1},
};
static char ili9806e_set_page1_cmd3[] = {
	0x02,0x00,0x29,0xC0,
	0x00,0x00,0xff,0xff};
static char ili9806e_set_page1_cmd4[] = {
	0x06,0x00,0x29,0xC0,
	0xFF,0xFF,0x98,0x06,
	0x04,0x01,0xFF,0xFF};
static char ili9806c_set_pkt_size2[] = {
	0x06,0x00,0x37,0x80};
static char ili9806e_panel_manufacture_id2[] = {
	0x01,0x00,0x06,0xA0};
static struct mipi_dsi_cmd ili9806e_panel_manufacture_id2_cmd[] = {
	{sizeof(ili9806e_set_page1_cmd3), ili9806e_set_page1_cmd3},
	{sizeof(ili9806e_set_page1_cmd4), ili9806e_set_page1_cmd4},
	{sizeof(ili9806c_set_pkt_size2), ili9806c_set_pkt_size2},
	{sizeof(ili9806e_panel_manufacture_id2), ili9806e_panel_manufacture_id2},
};

/*himax 8389b*/
static char hx8389b_id_cmd1[] = {
	0x04, 0x00, 0x39, 0xc0,
	0xB9, 0xFF, 0x83, 0x89
};
static char hx_panel_manufacture_id[] = {0xF4, 0x00, 0x06, 0xA0};
static struct mipi_dsi_cmd hx8389b_panel_manufacture_id_cmd[] = {
	{sizeof(hx8389b_id_cmd1), hx8389b_id_cmd1},
	{sizeof(hx_panel_manufacture_id), hx_panel_manufacture_id},
};

static char def_panel_manufacture_id[4] = {0xDA, 0x00, 0x06, 0xA0};
static struct mipi_dsi_cmd def_panel_manufacture_id_cmd[] = {
	{ 0x4, def_panel_manufacture_id},
};

/*otm9605a read chip_id */
static char otm9605a_set_pkt_size[] = {
	0x06, 0x00, 0x37, 0x80
};
static struct mipi_dsi_cmd otm9605a_panel_set_pkt_size_cmd[] = {
	{sizeof(otm9605a_set_pkt_size), otm9605a_set_pkt_size, 0},
};

static char otm9605a_panel_manufacture_id[] = {
	0xA1, 0x00, 0x06, 0xA0
};
static struct mipi_dsi_cmd otm9605a_panel_manufacture_id_cmd[] = {
	{sizeof(otm9605a_panel_manufacture_id), otm9605a_panel_manufacture_id, 0},
};
/* rm68171 get chip id select */
static char rm68171_select_page2_cmds_01[] = {
	0x06, 0x00, 0x39, 0xC0,
	0xF0, 0x55, 0xAA, 0x52,
	0x08, 0x02, 0xFF, 0xFF
};
static char rm68171_select_page2_cmds_02[] = {
	0x02, 0x00, 0x39, 0xC0,
	0xea, 0x02, 0xFF, 0xFF
};
static char rm68171_select_page1_cmds_01[] = {
	0x06, 0x00, 0x39, 0xC0,
	0xF0, 0x55, 0xAA, 0x52,
	0x08, 0x01, 0xFF, 0xFF
};
static char rm68171_panel_manufacture_id[] = {
	0xC5, 0x00, 0x24, 0xA0
};
static struct mipi_dsi_cmd rm68171_panel_enable_page2_cmd[] = {
	{sizeof(rm68171_select_page2_cmds_01), rm68171_select_page2_cmds_01},
	{sizeof(rm68171_select_page2_cmds_02), rm68171_select_page2_cmds_02},
};
static struct mipi_dsi_cmd rm68171_panel_enable_page1_cmd[] = {
	{sizeof(rm68171_select_page1_cmds_01), rm68171_select_page1_cmds_01}
};
static struct mipi_dsi_cmd rm68171_panel_manufacture_id_cmd[] = {
	{sizeof(rm68171_panel_manufacture_id), rm68171_panel_manufacture_id},
};

/* rm68172 get chip id select */
static char rm68172_select_page1_cmds_01[] = {
	0x06, 0x00, 0x39, 0xC0,
	0xF0, 0x55, 0xAA, 0x52,
	0x08, 0x01, 0xFF, 0xFF
};
static char rm68172_panel_manufacture_id[] = {
	0xC5, 0x00, 0x24, 0xA0
};
static struct mipi_dsi_cmd rm68172_panel_manufacture_id_cmd[] = {
	{sizeof(rm68172_select_page1_cmds_01), rm68172_select_page1_cmds_01},
	{sizeof(rm68172_panel_manufacture_id), rm68172_panel_manufacture_id},
};

/* ST7701 read chip_id*/
static char ST7701_select_page1_cmds_01[] = {
	0x06, 0x00, 0x39, 0xC0,
	0xF0, 0x55, 0xAA, 0x52,
	0x08, 0x01, 0xFF, 0xFF
};
static char ST7701_panel_manufacture_id[] = {
	0xA1, 0x00, 0x24, 0xA0
};
static struct mipi_dsi_cmd ST7701_panel_manufacture_id_cmd[] = {
	{sizeof(ST7701_select_page1_cmds_01), ST7701_select_page1_cmds_01},
	{sizeof(ST7701_panel_manufacture_id), ST7701_panel_manufacture_id},
};

/* sh1282 read chip_id*/
static char sh1282_select_page1_cmd[] = {
	0x06,0x00,0x29,0xC0,
	0xF0,0x55,0xAA,0x52,
	0x08,0x01,0xFF,0xFF};
static struct mipi_dsi_cmd sh1282_panel_enable_page1_cmd[] = {
	{sizeof(sh1282_select_page1_cmd), sh1282_select_page1_cmd},
};
static char sh1282_panel_set_pkt_size[] = {
	0x06,0x00,0x37,0x80};
static struct mipi_dsi_cmd sh1282_panel_set_pkt_size_cmd[] = {
	{sizeof(sh1282_panel_set_pkt_size), sh1282_panel_set_pkt_size},
};
static char sh1282_panel_manufacture_id[] = {
	0xC6, 0x00, 0x24, 0xA0};
static struct mipi_dsi_cmd sh1282_panel_manufacture_id_cmd[] = {
	{sizeof(sh1282_panel_manufacture_id), sh1282_panel_manufacture_id},
};
/* OTM8019 read chip_id */
static char otm8019_set_pkt_size[] = {
	0x06,0x00,0x37,0x80};
static struct mipi_dsi_cmd otm8019_set_pkt_size_cmd[] = {
	{sizeof(otm8019_set_pkt_size), otm8019_set_pkt_size},
};
static char otm8019_panel_manufacture_id[] = {
	0xA1,0x00,0x06,0xA0};
static struct mipi_dsi_cmd otm8019_panel_manufacture_id_cmd[] = {
	{sizeof(otm8019_panel_manufacture_id), otm8019_panel_manufacture_id},
};

/* ili9881 read chip_id */
static char ili9881_set_page1_cmd1[] = {
	0x04,0x00,0x29,0xC0,
	0xFF,0x98,0x81,0x01,
};
static char ili9881_set_pkt_size1[] = {
	0x06,0x00,0x37,0x80};
static char ili9881_panel_manufacture_id1[] = {
	0x00,0x00,0x06,0xA0};
static struct mipi_dsi_cmd ili9881_panel_manufacture_id1_cmd[] = {
	{sizeof(ili9881_set_page1_cmd1), ili9881_set_page1_cmd1},
	{sizeof(ili9881_set_pkt_size1), ili9881_set_pkt_size1},
	{sizeof(ili9881_panel_manufacture_id1), ili9881_panel_manufacture_id1},
};

/* r61318 get chip id select */
static char r61318_access_proctect_cmd1[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xB0, 0x00, 0xFF, 0xFF
};
static char r61318_set_pkt_size1[] = {
	0x04,0x00,0x37,0x80};
static char r61318_panel_manufacture_id[] = {
	0xBF,0x00,0x14,0xA0};
static struct mipi_dsi_cmd r61318_panel_access_proctect_cmd[] = {
	{sizeof(r61318_access_proctect_cmd1), r61318_access_proctect_cmd1},
};
static struct mipi_dsi_cmd r61318_set_pkt_size_cmd[] = {
	{sizeof(r61318_set_pkt_size1), r61318_set_pkt_size1}
};
static struct mipi_dsi_cmd r61318_panel_manufacture_id_cmd[] = {
	{sizeof(r61318_panel_manufacture_id), r61318_panel_manufacture_id},
};
/* r63315 get chip id select */
static char r63315_access_proctect_cmd1[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xB0, 0x00, 0xFF, 0xFF
};
static char r63315_set_pkt_size1[] = {
	0x04,0x00,0x37,0x80};
static char r63315_panel_manufacture_id[] = {
	0xBF,0x00,0x14,0xA0};
static struct mipi_dsi_cmd r63315_panel_access_proctect_cmd[] = {
	{sizeof(r63315_access_proctect_cmd1), r63315_access_proctect_cmd1},
};
static struct mipi_dsi_cmd r63315_set_pkt_size_cmd[] = {
	{sizeof(r63315_set_pkt_size1), r63315_set_pkt_size1}
};
static struct mipi_dsi_cmd r63315_panel_manufacture_id_cmd[] = {
	{sizeof(r63315_panel_manufacture_id), r63315_panel_manufacture_id},
};
#endif



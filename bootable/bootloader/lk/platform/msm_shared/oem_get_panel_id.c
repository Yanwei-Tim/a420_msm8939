/*
 * This file for oem_platform get real panel chip id.
 */
#include <stdlib.h>
#include <debug.h>
#include <err.h>
#include <platform/gpio.h>
#include <platform/timer.h>
#include <target/display.h>

#define PANEL_RESET_IO 25

uint32_t current_id = UNKNOWN_ID;
uint8_t get_id_flag = 0;
static void panel_reset_gpio(unsigned int t)
{
	dprintf(INFO, "panel_reset_gpio()\n");

	gpio_set_dir(reset_gpio.pin_id, 2);
	mdelay(10);
	gpio_set_dir(reset_gpio.pin_id, 0);
	mdelay(10);
	gpio_set_dir(reset_gpio.pin_id, 2);
	mdelay(t);
}
#if (A420) || (A406_F16)
   static void panel_reset2_gpio(int enable)
   {
       dprintf(INFO, "panel_reset2_gpio()\n"); 
       if(enable){
      				gpio_set_dir(reset_gpio2.pin_id, 2);
       			mdelay(10);
       			gpio_set_dir(reset_gpio2.pin_id, 0);
       			mdelay(10);
       			gpio_set_dir(reset_gpio2.pin_id, 2);
       			mdelay(50);
       }
       else{
       			gpio_set_dir(reset_gpio2.pin_id, 0);
       }
   }
   #endif 

uint32_t mipi_otm1901_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data, data1, data2;
	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(otm1284_set_pkt_size_cmd, ARRAY_SIZE(otm1284_set_pkt_size_cmd));
	mdelay(10);
	mipi_dsi_cmds_tx(otm1284_panel_manufacture_id_cmd, ARRAY_SIZE(otm1284_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);
	lp = (uint32_t *)(rp);
	data1 = (uint32_t)(*lp);
	data1 = ntohl(data1);
	data1 = data1 & 0xff;

	lp = (uint32_t *)(rp + 4);
	data2 = (uint32_t)(*lp);
	data2 = data2 & 0xff;

	data = (data1 << 8) | data2;

	dprintf(INFO, "mipi otm1901_lcd manufacture id =0x %x, data1 = 0x %x, data2 = 0x %x \n",data, data1, data2);

	return ((data == OTM1901_ID) ? OTM1901_ID : 0);
}
uint32_t mipi_otm1284_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data, data1, data2;
	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(otm1284_set_pkt_size_cmd, ARRAY_SIZE(otm1284_set_pkt_size_cmd));
	mdelay(10);
	mipi_dsi_cmds_tx(otm1284_panel_manufacture_id_cmd, ARRAY_SIZE(otm1284_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);
	lp = (uint32_t *)(rp);
	data1 = (uint32_t)(*lp);
	data1 = ntohl(data1);
	data1 = data1 & 0xff;

	lp = (uint32_t *)(rp + 4);
	data2 = (uint32_t)(*lp);
	data2 = data2 & 0xff;

	data = (data1 << 8) | data2;

	dprintf(INFO, "mipi otm1287_lcd manufacture id =0x %x, data1 = 0x %x, data2 = 0x %x \n",data, data1, data2);

	return ((data == OTM1284_ID) ? OTM1284_ID : 0);
}
uint32_t mipi_otm1283_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data, data1, data2;
	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(otm1284_set_pkt_size_cmd, ARRAY_SIZE(otm1284_set_pkt_size_cmd));
	mdelay(10);
	mipi_dsi_cmds_tx(otm1284_panel_manufacture_id_cmd, ARRAY_SIZE(otm1284_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);
	lp = (uint32_t *)(rp);
	data1 = (uint32_t)(*lp);
	data1 = ntohl(data1);
	data1 = data1 & 0xff;

	lp = (uint32_t *)(rp + 4);
	data2 = (uint32_t)(*lp);
	data2 = data2 & 0xff;

	data = (data1 << 8) | data2;

	dprintf(INFO, "mipi otm1283_lcd manufacture id =0x %x, data1 = 0x %x, data2 = 0x %x \n",data, data1, data2);

	return ((data == OTM1283_ID) ? OTM1283_ID : 0);
}
uint32_t mipi_nt35512s_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp,data,data1,data2;

	//panel_reset_gpio(20);
	mipi_dsi_cmds_tx(nt35512s_panel_enable_page2_cmd, ARRAY_SIZE(nt35512s_panel_enable_page2_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(nt35512s_panel_enable_page1_cmd, ARRAY_SIZE(nt35512s_panel_enable_page1_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(nt35512s_panel_manufacture_id_cmd, ARRAY_SIZE(nt35512s_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp,3);
	lp = (uint32_t *) (rp+5);
	data1 = (uint32_t)(*lp);
	data1 = ntohl(data1);
	lp = (uint32_t *) (rp+7);
	data2 = (uint32_t)(*lp);
	data2 = ntohl(data2);
	data = (data1 >> 16) | (data2 >> 24);
	data = data & 0xFFFF;
	dprintf(INFO, "Get nt35512s mipi chip id =0x%x, *lp =0x%x \n", data, *lp);

		return ((data == NT35512S_ID) ? NT35512S_ID: 0);
}
uint32_t mipi_nt35590_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(nt35590_panel_set_pkt_size_cmd, ARRAY_SIZE(nt35590_panel_set_pkt_size_cmd));
	mdelay(10);
	mipi_dsi_cmds_tx(nt35590_panel_manufacture_id_cmd, ARRAY_SIZE(nt35590_panel_manufacture_id_cmd));
	mdelay(10);

	mipi_dsi_cmds_rx(&rp, 4);

	lp = (uint32_t *)rp;
	data = (uint32_t)(*lp);
	data = ntohl(data);
	data = ((data>>24) & 0xff);

	dprintf(INFO, "Get nt35590 id = 0x%x, *lp =0x%x \n",data, *lp);

	return ((data == NT35590_ID) ? NT35590_ID : 0);
}

uint32_t mipi_nt35596_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(nt35596_panel_enable_page1_cmd, ARRAY_SIZE(nt35596_panel_enable_page1_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(nt35596_panel_set_pkt_size_cmd, ARRAY_SIZE(nt35596_panel_set_pkt_size_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(nt35596_panel_manufacture_id_cmd, ARRAY_SIZE(nt35596_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 4);

	lp = (uint32_t *)(rp + 2);
	data = (uint32_t)(*lp);
	data = ntohl(data);
	data = (data & 0xff);

	dprintf(INFO, "mipi nt35596 lcd manufacture id =0x %x, *lp =0x %x \n",data, *lp);
	return ((data == NT35596_ID) ? NT35596_ID : 0);
}


uint32_t mipi_otm8018b_manufacture_id(void)
{
	char ref_buf[24];
	char *rp = ref_buf;
	uint32_t *lp, ret_data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(otm8018b_panel_manufacture_id_cmd, ARRAY_SIZE(otm8018b_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 4);
	lp = (uint32_t *)(rp + 2);
	ret_data = (uint32_t)(*lp);
	ret_data = ntohl(ret_data);
	ret_data = (ret_data  & 0xff);

	dprintf(INFO, "Get otm8018 id =0x%x, *lp =0x %x \n",ret_data, *lp);

	return ((ret_data == OTM8018B_ID) ? OTM8018B_ID : 0);
}

uint32_t mipi_hx8389b_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;
	//int i;
	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(hx8389b_panel_manufacture_id_cmd, ARRAY_SIZE(hx8389b_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);

	lp = (uint32_t *)(rp + 8);
	data = (uint32_t)(*lp);
	//data = ntohl(data);
	data = ((data >> 8) & 0xff);

	dprintf(INFO, "Get hx8389b id =0x%x, *lp =0x %x \n",data, *lp);

	return  ((data == HX8389B_ID) ? HX8389B_ID : 0);
}

uint32_t mipi_hx8394d_manufacture_id(void)
{
	char ref_buf[24];
	char *rp = ref_buf;
	uint32_t *lp, ret_data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(def_panel_manufacture_id_cmd, ARRAY_SIZE(def_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 4);
	lp = (uint32_t *)(rp + 2);
	ret_data = (uint32_t)(*lp);
	ret_data = ntohl(ret_data);
	ret_data = (ret_data  & 0xff);

	dprintf(INFO, "Get 8394d id =0x%x, *lp =0x %x \n",ret_data, *lp);

	return ((ret_data == HX8394D_P800_ID) ? HX8394D_P800_ID : 0);
}

uint32_t mipi_ili9806c_manufacture_id(void)
{
	char ref_buf[24];
	char *rp = ref_buf;
	uint32_t *lp, ret_data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(ili9806c_panel_manufacture_id_cmd, ARRAY_SIZE(ili9806c_panel_manufacture_id_cmd));

	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 4);

	lp = (uint32_t *)(rp + 8);
	ret_data = (uint32_t)(*lp);
	ret_data = ntohl(ret_data);
	ret_data = ((ret_data >> 16) & 0xff);

	dprintf(INFO, "Get ili9806c id =0x%x, *lp =0x %x \n",ret_data, *lp);

	return ((ret_data == ILI9806C_ID) ? ILI9806C_ID : 0);
}

uint32_t mipi_ili9806e_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data, data1, data2;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(ili9806e_panel_manufacture_id1_cmd, ARRAY_SIZE(ili9806e_panel_manufacture_id1_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);

	lp = (uint32_t *)(rp + 4);
	data1 = (uint32_t)(*lp);
	data1 = ntohl(data1);
	data1 = ((data1 >> 16) & 0xff);


	mipi_dsi_cmds_tx(ili9806e_panel_manufacture_id2_cmd, ARRAY_SIZE(ili9806e_panel_manufacture_id2_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);

	lp = (uint32_t *)(rp + 4);
	data2 = (uint32_t)(*lp);
	data2 = ntohl(data2);
	data2 = ((data2 >> 16) & 0xff);


	data = (data1 << 8) | data2;
	dprintf(INFO, "Get ili9806e id =0x%x, data1=0x%x, data2=0x%x \n",data, data1, data2);

	return ((data == ILI9806E_ID) ? ILI9806E_ID : 0);
}

uint32_t mipi_ili9881_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data, data1;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(ili9881_panel_manufacture_id1_cmd, ARRAY_SIZE(ili9881_panel_manufacture_id1_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);

	lp = (uint32_t *)(rp + 4);
	data1 = (uint32_t)(*lp);
	data1 = ntohl(data1);

	data = data1 & 0xff;
	data1 = ((data1 >> 16) & 0xff);

	data = (data1 << 8) | data;
	dprintf(INFO, "Get ili9881 id =0x%x, data1=0x%x\n",data, data1);

	return ((data == ILI9881_ID) ? ILI9881_ID : 0);
}

uint32_t mipi_rm68171_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(rm68171_panel_enable_page2_cmd, ARRAY_SIZE(rm68171_panel_enable_page2_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(rm68171_panel_enable_page1_cmd, ARRAY_SIZE(rm68171_panel_enable_page1_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(rm68171_panel_manufacture_id_cmd, ARRAY_SIZE(rm68171_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);

	lp = (uint32_t *) (rp+4);
	data = (uint32_t)(*lp);
	data = ntohl(data);
	data = (data >> 16) & 0xFFFF;

	dprintf(INFO, "Get rm68171 mipi chip id =0x%x, *lp =0x%x \n", data, *lp);

		return ((data == RM68171_ID) ? RM68171_ID: 0);
}

uint32_t mipi_rm68172_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(rm68172_panel_manufacture_id_cmd, ARRAY_SIZE(rm68172_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);

	lp = (uint32_t *) (rp+1);
	data = (uint32_t)(*lp);
	data = ntohl(data);
	data = data  & 0xFFFF;

	dprintf(INFO, "Get rm68172 mipi chip id =0x%x, *lp =0x%x \n", data, *lp);

		return ((data == RM68172_ID) ? RM68172_ID: 0);
}

uint32_t mipi_ST7701_manufacture_id(void)
   {
       char rec_buf[24];
       char *rp = rec_buf;
       uint32_t *lp, data;
       //panel_reset_gpio(20);
#if (A420) || (A406_F16)
       panel_reset2_gpio(0);
   #endif
       mipi_dsi_cmds_tx(ST7701_panel_manufacture_id_cmd, ARRAY_SIZE(ST7701_panel_manufacture_id_cmd)); 
       mdelay(10);
       mipi_dsi_cmds_rx(&rp, 4);
       lp = (uint32_t *)(rp + 4);
       data = (uint32_t)(*lp);
       data = ntohl(data);
       data = ((data >> 16) & 0xffff); 
       dprintf(INFO, "mipi ST7701_lcd manufacture id =0x %x, *lp =0x %x \n",data, *lp);
#if (A420) || (A406_F16)
       panel_reset2_gpio(1); 
   #endif
       return ((data == ST7701_ID) ? ST7701_ID : 0);
   } 

uint32_t mipi_otm9605a_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp1, *lp2, data, data1, data2;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(otm9605a_panel_set_pkt_size_cmd, ARRAY_SIZE(otm9605a_panel_set_pkt_size_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(otm9605a_panel_manufacture_id_cmd, ARRAY_SIZE(otm9605a_panel_manufacture_id_cmd));
	mdelay(50);

	mipi_dsi_cmds_rx(&rp, 3);
	lp1 = (uint32_t *)(rp);
	data1 = (uint32_t)(*lp1);
	data1 = ntohl(data1);
	data1 &= 0xff;

	lp2 = (uint32_t *)(rp + 1);
	data2 = (uint32_t)(*lp2);
	data2 = ntohl(data2);
	data2 &= 0xff;

	data = ((data1 << 8) | (data2));
	dprintf(INFO, "Get otm9605a id = 0x%x, data1 = 0x%x, data2 = 0x%x \n",data, data1,data2);

	return ((data == OTM9605A_ID) ? OTM9605A_ID : 0);
}
uint32_t mipi_sh1282_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(sh1282_panel_enable_page1_cmd, ARRAY_SIZE(sh1282_panel_enable_page1_cmd));
	mdelay(10);
	mipi_dsi_cmds_tx(sh1282_panel_set_pkt_size_cmd, ARRAY_SIZE(sh1282_panel_set_pkt_size_cmd));
	mdelay(10);
	mipi_dsi_cmds_tx(sh1282_panel_manufacture_id_cmd, ARRAY_SIZE(sh1282_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 4);

	lp = (uint32_t *)(rp + 4);
	data = (uint32_t)(*lp);
	data = ntohl(data);
	data = ((data >> 16) & 0xffff);

	dprintf(INFO, "mipi sh1282_lcd manufacture id =0x %x, *lp =0x %x \n",data, *lp);

	return ((data == SH1282_ID) ? SH1282_ID : 0);
}

uint32_t mipi_otm8019_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data, data1, data2;
	//panel_reset_gpio(20);
#if A406_F16
       panel_reset2_gpio(0);
#endif
	mipi_dsi_cmds_tx(otm8019_set_pkt_size_cmd, ARRAY_SIZE(otm8019_set_pkt_size_cmd));
	mdelay(10);
	mipi_dsi_cmds_tx(otm8019_panel_manufacture_id_cmd, ARRAY_SIZE(otm8019_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);

	lp = (uint32_t *)(rp);
	data1 = (uint32_t)(*lp);
	data1 = ntohl(data1);
	data1 = data1 & 0xff;

	lp = (uint32_t *)(rp + 4);
	data2 = (uint32_t)(*lp);
	data2 = data2 & 0xff;

	data = (data1 << 8) | data2;

	dprintf(INFO, "mipi otm8019_lcd manufacture id =0x %x, data1 = 0x %x, data2 = 0x %x \n",data, data1, data2);
#if A406_F16
       panel_reset2_gpio(1); 
#endif
	return ((data == OTM8019_ID) ? OTM8019_ID : 0);
}

uint32_t mipi_r61318_manufacture_id(void)
{
	char rec_buf[60];
	char *rp = rec_buf;
	uint32_t *lp, data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(r61318_panel_access_proctect_cmd, ARRAY_SIZE(r61318_panel_access_proctect_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(r61318_set_pkt_size_cmd, ARRAY_SIZE(r61318_set_pkt_size_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(r61318_panel_manufacture_id_cmd, ARRAY_SIZE(r61318_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);
	lp = (uint32_t *) (rp+4);
	data = (uint32_t)(*lp);
	data = ntohl(data);
	data = (data>>16) & 0xFFFF;

	dprintf(INFO, "Get r61318 mipi chip id =0x%x, *lp =0x%x \n", data, *lp);

	return ((data == R61318_ID) ? R61318_ID: 0);
}

uint32_t mipi_r63315_manufacture_id(void)
{
	char rec_buf[60];
	char *rp = rec_buf;
	uint32_t *lp, data;

	//panel_reset_gpio(20);

	mipi_dsi_cmds_tx(r63315_panel_access_proctect_cmd, ARRAY_SIZE(r63315_panel_access_proctect_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(r63315_set_pkt_size_cmd, ARRAY_SIZE(r63315_set_pkt_size_cmd));
	mdelay(50);
	mipi_dsi_cmds_tx(r63315_panel_manufacture_id_cmd, ARRAY_SIZE(r63315_panel_manufacture_id_cmd));
	mdelay(10);
	mipi_dsi_cmds_rx(&rp, 3);
	lp = (uint32_t *) (rp+4);
	data = (uint32_t)(*lp);
	data = ntohl(data);
	data = (data>>16) & 0xFFFF;

	dprintf(INFO, "Get r63315 mipi chip id =0x%x, *lp =0x%x \n", data, *lp);

	return ((data == R63315_ID) ? R63315_ID: 0);
}


uint32_t mipi_default_manufacture_id(void)
{
	get_id_flag = 1;
	return MIPI_DEFAULT_ID;
}

/*
 * DO NOT change the following function pointers' order optionallya.
 * e.g.
 * The first pointer of mipi_ili9806c_manufacture_id is major used in BOARD_S1_SGC113,
 * and the second one(mipi_otm8018b_manufacture_id) is subordinate.
 * This is a better way to avoid to run reading-id-cammands which is useless for the project.
 */

static uint32_t mipi_get_ic_manufacture_id(void)
{
	uint32_t lcd_chip_id;
	uint8_t retnum = 3;
	uint32_t cnt, NUM = ARRAY_SIZE(mipi_ic_manufacture_id);
	static const  get_ic_id_func  *mipi_manufacture_id;

	dprintf(INFO, "mipi_get_ic_manufacture_id\n");

	while(retnum) {
		for(mipi_manufacture_id = mipi_ic_manufacture_id, cnt = 0; cnt < NUM; ++mipi_manufacture_id, ++cnt) {
			lcd_chip_id = (*mipi_manufacture_id)();

			if(lcd_chip_id) {
				get_id_flag = 1;
				break;
			}
		}

		if(get_id_flag)
			break;
		else
			retnum--;
		panel_reset_gpio(120);
	}

	if(!get_id_flag) {
		lcd_chip_id = UNKNOWN_ID;
		dprintf(INFO,"mipi_get_ic_manufacture_id(), Not found lcd chip id. set default lcd_chip_id = 0x%x.\n",lcd_chip_id);
	}

	dprintf(INFO,"# mipi_get_ic_manufacture_id(). lcd_chip_id =0x%x.\n",lcd_chip_id);
	return lcd_chip_id;
}

unsigned char get_current_chip_id(void)
{

	current_id = mipi_get_ic_manufacture_id();

	dprintf(INFO,"# get_current_chip_id(). current_id = 0x%x \n",current_id);
	return current_id;
}

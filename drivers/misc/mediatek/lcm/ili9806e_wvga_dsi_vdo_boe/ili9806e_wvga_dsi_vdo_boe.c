/*
 * (c) MediaTek Inc. 2010
 */

#ifndef BUILD_LK
#include <linux/string.h>
#endif

#include "lcm_drv.h"

#ifdef BUILD_LK
	#include <platform/mt_gpio.h>
	#include <string.h>
#elif defined(BUILD_UBOOT)
	#include <asm/arch/mt_gpio.h>
#else
	#include <mach/mt_gpio.h>
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  										(480)
#define FRAME_HEIGHT 										(800)

#define REGFLAG_DELAY             							0XFE
#define REGFLAG_END_OF_TABLE      							0x00   // END OF REGISTERS MARKER

#define LCM_DSI_CMD_MODE									0

#ifndef TRUE
    #define   TRUE     1
#endif
 
#ifndef FALSE
    #define   FALSE    0
#endif

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    								(lcm_util.set_reset_pin((v)))

#define UDELAY(n) 											(lcm_util.udelay(n))
#define MDELAY(n) 											(lcm_util.mdelay(n))

//static kal_bool IsFirstBoot = KAL_TRUE;

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg											lcm_util.dsi_read_reg()
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)    

static struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[120];
};

static struct LCM_setting_table lcm_initialization_setting[] = {
	
	/*
	Note :

	Data ID will depends on the following rule.
	
		count of parameters > 1	=> Data ID = 0x39
		count of parameters = 1	=> Data ID = 0x15
		count of parameters = 0	=> Data ID = 0x05

	Structure Format :

	{DCS command, count of parameters, {parameter list}}
	{REGFLAG_DELAY, milliseconds of time, {}},

	...

	Setting ending by predefined flag
	
	{REGFLAG_END_OF_TABLE, 0x00, {}}
	*/

	//ILI9806E_14.04.11
//page 1 command
	{0xFF,	5,	{0xFF, 0x98, 0x06, 0x04,0x01}}, 
	{0x08,	1,	{0x10}},
	{0x21,	1,	{0x01}},
	{0x23,	1,	{0x02}},
	{0x30,	1,	{0x02}},
	{0x31,	1,	{0x02}},
	{0x40,	1,	{0x16}},
	{0x41,	1,	{0x55}},
	{0x42,	1,	{0x01}},
	{0x43,	1,	{0x09}},
	{0x44,	1,	{0x09}},
	{0x45,	1,	{0x1B}},
	{0x50,	1,	{0x78}},
	{0x51,	1,	{0x78}},
	{0x52,	1,	{0x00}},
	{0x53,	1,	{0x44}},
	{0x57,	1,	{0x50}},
	{0x60,	1,	{0x07}},
	{0x61,	1,	{0x00}},
	{0x62,	1,	{0x07}},
	{0x63,	1,	{0x00}},
//gamma setting
	{0xA0,	1,	{0x00}},
	{0xA1,	1,	{0x11}},
	{0xA2,	1,	{0x18}},
	{0xA3,	1,	{0x0D}},
	{0xA4,	1,	{0x06}},
	{0xA5,	1,	{0x0A}},
	{0xA6,	1,	{0x07}},
	{0xA7,	1,	{0x16}},
	{0xA8,	1,	{0x06}},
	{0xA9,	1,	{0x0A}},
	{0xAA,	1,	{0x11}},
	{0xAB,	1,	{0x08}},
	{0xAC,	1,	{0x0F}},
	{0xAD,	1,	{0x17}},
	{0xAE,	1,	{0x0E}},
	{0xAF,	1,	{0x00}},
//Nagitive
	{0xC0,	1,	{0x00}},
	{0xC1,	1,	{0x11}},
	{0xC2,	1,	{0x18}},
	{0xC3,	1,	{0x0D}},
	{0xC4,	1,	{0x06}},
	{0xC5,	1,	{0x0A}},
	{0xC6,	1,	{0x07}},
	{0xC7,	1,	{0x16}},
	{0xC8,	1,	{0x06}},
	{0xC9,	1,	{0x0A}},
	{0xCA,	1,	{0x11}},
	{0xCB,	1,	{0x08}},
	{0xCC,	1,	{0x0F}},
	{0xCD,	1,	{0x17}},
	{0xCE,	1,	{0x0E}},
	{0xCF,	1,	{0x00}},	
//page 6 command		
	{0xFF,	5,	{0xFF, 0x98, 0x06, 0x04,0x06}}, 
	{0x00,	1,	{0xA0}},
	{0x01,	1,	{0x05}},
	{0x02,	1,	{0x00}},
	{0x03,	1,	{0x00}},
	{0x04,	1,	{0x01}},
	{0x05,	1,	{0x01}},
	{0x06,	1,	{0x88}},
	{0x07,	1,	{0x04}},
	{0x08,	1,	{0x01}},
	{0x09,	1,	{0x90}},
	{0x0A,	1,	{0x04}},
	{0x0B,	1,	{0x01}},
	{0x0C,	1,	{0x01}},
	{0x0D,	1,	{0x01}},
	{0x0E,	1,	{0x00}},
	{0x0F,	1,	{0x00}},

	{0x10,	1,	{0x55}},
	{0x11,	1,	{0x50}},
	{0x12,	1,	{0x01}},
	{0x13,	1,	{0x85}},
	{0x14,	1,	{0x85}},
	{0x15,	1,	{0xC0}},
	{0x16,	1,	{0x0B}},
	{0x17,	1,	{0x00}},
	{0x18,	1,	{0x00}},
	{0x19,	1,	{0x00}},
	{0x1A,	1,	{0x00}},
	{0x1B,	1,	{0x00}},
	{0x1C,	1,	{0x00}},
	{0x1D,	1,	{0x00}},

	{0x20,	1,	{0x01}},
	{0x21,	1,	{0x23}},
	{0x22,	1,	{0x45}},
	{0x23,	1,	{0x67}},
	{0x24,	1,	{0x01}},
	{0x25,	1,	{0x23}},
	{0x26,	1,	{0x45}},
	{0x27,	1,	{0x67}},

	{0x30,	1,	{0x02}},
	{0x31,	1,	{0x22}},
	{0x32,	1,	{0x11}},
	{0x33,	1,	{0xAA}},
	{0x34,	1,	{0xBB}},
	{0x35,	1,	{0x66}},
	{0x36,	1,	{0x00}},
	{0x37,	1,	{0x22}},
	{0x38,	1,	{0x22}},
	{0x39,	1,	{0x22}},
	{0x3A,	1,	{0x22}},
	{0x3B,	1,	{0x22}},
	{0x3C,	1,	{0x22}},
	{0x3D,	1,	{0x22}},
	{0x3E,	1,	{0x22}},
	{0x3F,	1,	{0x22}},

	{0x40,	1,	{0x22}},
	{0x52,	1,	{0x10}},
	{0x53,	1,	{0x10}},
//page 7
	{0xFF,	5,	{0xFF, 0x98, 0x06, 0x04,0x07}}, 
	{0x17,	1,	{0x22}},
	{0x02,	1,	{0x77}},
	{0xE1,	1,	{0x79}},
//page 0
	{0xFF,	5,	{0xFF, 0x98, 0x06, 0x04,0x00}},
	
	{0x11,	0,	{0x00}},
	{REGFLAG_DELAY, 120, {}},
	
	{0x29,	0,	{0x00}},
	{REGFLAG_DELAY, 10, {}},


	// Note
	// Strongly recommend not to set Sleep out / Display On here. That will cause messed frame to be shown as later the backlight is on.

	// Setting ending by predefined flag
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};



static struct LCM_setting_table lcm_sleep_out_setting[] = {
    // Sleep Out
	{0x11, 0, {0x00}},
    {REGFLAG_DELAY, 120, {}},

    // Display ON
	{0x29, 0, {0x00}},
    {REGFLAG_DELAY, 100, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
	// Display off sequence
	{0x28, 0, {0x00}},

    // Sleep Mode On
	{0x10, 0, {0x00}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};





static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

    for(i = 0; i < count; i++) {
		
        unsigned cmd;
        cmd = table[i].cmd;
		
        switch (cmd) {
			
            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;
				
            case REGFLAG_END_OF_TABLE :
                break;
				
            default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
				//MDELAY(10);//soso add or it will fail to send register
       	}
    }
	
}


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{

		memset(params, 0, sizeof(LCM_PARAMS));
	
		params->type   = LCM_TYPE_DSI;

		params->width  = FRAME_WIDTH;
		params->height = FRAME_HEIGHT;

        #if (LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
        #else
		params->dsi.mode   = SYNC_PULSE_VDO_MODE; 
        #endif

#ifdef SLT_DEVINFO_LCM
		params->module="dijing";
		params->vendor="dijing";
		params->ic="ILI9806E";
		params->info="800*480";
#endif	
		// DSI
		// Command mode setting
		//1 Three lane or Four lane
		params->dsi.LANE_NUM				= LCM_TWO_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

		// Video mode setting		
		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
		
		params->dsi.vertical_sync_active				= 6;// 3    2
		params->dsi.vertical_backporch					= 14;// 20   1
		params->dsi.vertical_frontporch					= 20; // 1  12
		params->dsi.vertical_active_line				= FRAME_HEIGHT; 

		params->dsi.horizontal_sync_active				= 0x16;// 50  2
		params->dsi.horizontal_backporch				= 0x38;
		params->dsi.horizontal_frontporch				= 0x18;
		params->dsi.horizontal_active_pixel				= FRAME_WIDTH;

		params->dsi.PLL_CLOCK=190;
}

static void lcm_init(void)
{
	unsigned int data_array[64];

    SET_RESET_PIN(1);
    SET_RESET_PIN(0);
    MDELAY(10);//Must > 10ms
    SET_RESET_PIN(1);
    MDELAY(120);//Must > 120ms
    
	//IsFirstBoot = KAL_TRUE;

	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_suspend(void)
{
/*
    SET_RESET_PIN(1);
    SET_RESET_PIN(0);
    MDELAY(20);//Must > 10ms
    SET_RESET_PIN(1);
    MDELAY(150);//Must > 120ms
*/
	push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_resume(void)
{
	//lcm_compare_id();

	//lcm_init();
	
	push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
}
static unsigned int lcm_compare_id(void)
{
	unsigned int id = 0;
	unsigned char buffer[3];
	unsigned int array[16];
	
	SET_RESET_PIN(1);  //NOTE:should reset LCM firstly
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(120);

	array[0] = 0x00063902;//39 packet FF FF 98 06 04 01 page 1
	array[1] = 0x0698FFFF;
	array[2] = 0x00000104;
	dsi_set_cmdq(array,3,1);
	MDELAY(10);

	array[0] = 0x00033700;// 37 set max read data size
	dsi_set_cmdq(array, 1, 1);
	MDELAY(10);
	read_reg_v2(0x00, &buffer[0], 1);
	read_reg_v2(0x01, &buffer[1], 1);
	read_reg_v2(0x02, &buffer[2], 1);
	id = (buffer[0]<<16)|(buffer[1]<<8)|buffer[2];
#if defined(BUILD_LK)
	/*The Default Value should be 0x98,0x06,0x04*/
	printf("\n\n\n\n[soso]%s, id0 = 0x%x,id1 = 0x%x,id2 = 0x%x,id = 0x%x\n", __func__, buffer[0],buffer[1],buffer[2],id);
#endif
    return (id == 0x980604)?1:0;
}

static unsigned int lcm_esd_recover(void) 
{ 
	lcm_init();
	
	push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
	
	return TRUE; 
} 

LCM_DRIVER ili9806e_wvga_dsi_vdo_boe_lcm_drv = 
{
    .name			= "ili9806e_wvga_dsi_vdo_boe",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id    = lcm_compare_id,
	.esd_recover	= lcm_esd_recover,
};






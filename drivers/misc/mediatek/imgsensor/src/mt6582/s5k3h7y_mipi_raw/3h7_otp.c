/*************************************************************************************************
3h2_otp.c
---------------------------------------------------------
OTP Application file From Truly for S5K3H2
2013.01.14
---------------------------------------------------------
NOTE:
The modification is appended to initialization of image sensor. 
After sensor initialization, use the function , and get the id value.
bool otp_wb_update(BYTE zone)
and
bool otp_lenc_update(BYTE zone), 
then the calibration of AWB and LSC will be applied. 
After finishing the OTP written, we will provide you the golden_rg and golden_bg settings.
**************************************************************************************************/

#include <linux/videodev2.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <asm/atomic.h>
#include <linux/slab.h>


#include "kd_camera_hw.h"
#include "kd_imgsensor.h"
#include "kd_imgsensor_define.h"
#include "kd_imgsensor_errcode.h"


#include "s5k3h7ymipiraw_Sensor.h"
#include "s5k3h7ymipiraw_Camera_Sensor_para.h"
#include "s5k3h7ymipiraw_CameraCustomized.h"

//#include "3h7_otp.h"

extern int iWriteRegI2C(u8 *a_pSendData , u16 a_sizeSendData, u16 i2cId);
extern int iReadRegI2C(u8 *a_pSendData , u16 a_sizeSendData, u8 * a_pRecvData, u16 a_sizeRecvData, u16 i2cId);
//extern  BYTE S5K3H7Y_byteread_cmos_sensor(kal_uint32 addr);

BYTE S5K3H7Y_byteread_cmos_sensor(kal_uint32 addr)
{
	BYTE get_byte=0;
	char puSendCmd[2] = {(char)(addr >> 8) , (char)(addr & 0xFF) };
	iReadRegI2C(puSendCmd , 2, (u8*)&get_byte,1,S5K3H7YMIPI_WRITE_ID);
	return get_byte;
}
extern  void S5K3H7Y_wordwrite_cmos_sensor(u16 addr, u32 para);
extern  void S5K3H7Y_bytewrite_cmos_sensor(u16 addr, u32 para);
#define USHORT             unsigned short
#define BYTE               unsigned char
#define Sleep(ms) mdelay(ms)

#define Oflim_ID           0x07
#define VALID_OTP          0x00

#define GAIN_DEFAULT       0x0100
#define GAIN_GREEN1_ADDR   0x020E
#define GAIN_BLUE_ADDR     0x0212
#define GAIN_RED_ADDR      0x0210
#define GAIN_GREEN2_ADDR   0x0214

//USHORT golden_r;
//USHORT golden_gr;
//USHORT golden_gb;
//USHORT golden_b;

USHORT current_rg;
USHORT current_bg;
USHORT golden_rg;
USHORT golden_bg;

//kal_uint32	golden_r = 0, golden_gr = 0, golden_gb = 0, golden_b = 0;
//kal_uint32	current_r = 0, current_gr = 0, current_gb = 0, current_b = 0;
/*************************************************************************************************
* Function    :  start_read_otp
* Description :  before read otp , set the reading block setting  
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  0, reading block setting err
                 1, reading block setting ok 
**************************************************************************************************/
bool start_read_otp(BYTE zone)
{
	BYTE val = 0;
	int i;
	S5K3H7Y_wordwrite_cmos_sensor(0xFCFC, 0xD000);
	S5K3H7Y_bytewrite_cmos_sensor(0x0A02, zone);   //Select the page to write by writing to 0xD0000A02 0x01~0x0C
	S5K3H7Y_bytewrite_cmos_sensor(0x0A00, 0x01);   //Enter read mode by writing 01h to 0xD0000A00

	for(i=0;i<100;i++)
	{
		val = S5K3H7Y_byteread_cmos_sensor(0x0A01);
		if(val == 0x01)
			break;
		Sleep(2);
	}
	if(i == 100)
	{
		printk("[S5K3H7Y]Read Page %d Err!\n", zone); 
		S5K3H7Y_bytewrite_cmos_sensor(0x0A00, 0x00);   //Reset the NVM interface by writing 00h to 0xD0000A00
		return 0;
	}
	return 1;
}


/*************************************************************************************************
* Function    :  stop_read_otp
* Description :  after read otp , stop and reset otp block setting  
**************************************************************************************************/
void stop_read_otp()
{
	S5K3H7Y_bytewrite_cmos_sensor(0x0A00, 0x00);   //Reset the NVM interface by writing 00h to 0xD0000A00
}


/*************************************************************************************************
* Function    :  get_otp_flag
* Description :  get otp WRITTEN_FLAG  
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE], if 0x40 , this type has valid otp data, otherwise, invalid otp data
**************************************************************************************************/
BYTE get_otp_flag(BYTE zone)
{
	BYTE flag = 0;
	if(!start_read_otp(zone))
	{
		printk("[S5K3H7Y]Start read Page %d Fail!\n", zone);
		return 0;
	}
	flag = S5K3H7Y_byteread_cmos_sensor(0x0A0B);
	stop_read_otp();

	//flag = flag;

	printk("[S5K3H7Y]Flag:0x%02x\n",flag );

	return flag;
}

/*************************************************************************************************
* Function    :  get_otp_date
* Description :  get otp date value    
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f    
**************************************************************************************************/
/*
bool get_otp_date(BYTE zone) 
{
	BYTE year  = 0;
	BYTE month = 0;
	BYTE day   = 0;

	if(!start_read_otp(zone))
	{
		printk("Start read Page %d Fail!", zone);
		return 0;
	}

	year  = S5K3H7Y_byteread_cmos_sensor(0x0A05);
	month = S5K3H7Y_byteread_cmos_sensor(0x0A06);
	day   = S5K3H7Y_byteread_cmos_sensor(0x0A07);

	stop_read_otp();

    printk("OTP date=%02d.%02d.%02d", year,month,day);

	return 1;
}

*/
/*************************************************************************************************
* Function    :  get_otp_module_id
* Description :  get otp MID value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                 other value : module ID data , TRULY ID is 0x0001            
**************************************************************************************************/
BYTE get_otp_module_id(BYTE zone)
{
	BYTE module_id = 0;

	if(!start_read_otp(zone))
	{
		printk("Start read Page %d Fail!\n", zone);
		return 0;
	}

	module_id = S5K3H7Y_byteread_cmos_sensor(0x0A0A);

	stop_read_otp();

	printk("[S5K3H7Y]Module ID: 0x%02x.\n",module_id);

	return module_id;
}


/*************************************************************************************************
* Function    :  get_otp_lens_id
* Description :  get otp LENS_ID value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                 other value : LENS ID data             
**************************************************************************************************/
/*
BYTE get_otp_lens_id(BYTE zone)
{
	BYTE lens_id = 0;

	if(!start_read_otp(zone))
	{
		printk("Start read Page %d Fail!", zone);
		return 0;
	}
	lens_id = S5K3H7Y_byteread_cmos_sensor(0x0A0A);
	stop_read_otp();

	printk("Lens ID: 0x%02x.",lens_id);

	return lens_id;
}
*/

/*************************************************************************************************
* Function    :  get_otp_vcm_id
* Description :  get otp VCM_ID value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                 other value : VCM ID data             
**************************************************************************************************/
/*
BYTE get_otp_vcm_id(BYTE zone)
{
	BYTE vcm_id = 0;

	if(!start_read_otp(zone))
	{
		printk("Start read Page %d Fail!", zone);
		return 0;
	}

	vcm_id = S5K3H7Y_byteread_cmos_sensor(0x0A0B);

	stop_read_otp();

	printk("VCM ID: 0x%02x.",vcm_id);

	return vcm_id;	
}
*/

/*************************************************************************************************
* Function    :  get_otp_driver_id
* Description :  get otp driver id value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                 other value : driver ID data             
**************************************************************************************************/
/*
BYTE get_otp_driver_id(BYTE zone)
{
	BYTE driver_id = 0;

	if(!start_read_otp(zone))
	{
		printk("Start read Page %d Fail!", zone);
		return 0;
	}

	driver_id = S5K3H7Y_byteread_cmos_sensor(0x0A0C);

	stop_read_otp();

	printk("Driver ID: 0x%02x.",driver_id);

	return driver_id;
}
*/
/*************************************************************************************************
* Function    :  get_light_id
* Description :  get otp environment light temperature value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                        other value : driver ID data     
			            BIT0:D65(6500K) EN
						BIT1:D50(5100K) EN
						BIT2:CWF(4000K) EN
						BIT3:A Light(2800K) EN
**************************************************************************************************/
/*
BYTE get_light_id(BYTE zone)
{
	BYTE light_id = 0;

	if(!start_read_otp(zone))
	{
		printk("Start read Page %d Fail!", zone);
		return 0;
	}

	light_id = S5K3H7Y_byteread_cmos_sensor(0x0A0D);

	stop_read_otp();

	printk("Light ID: 0x%02x.",light_id);

	return light_id;
}
*/

/*************************************************************************************************
* Function    :  otp_lenc_update
* Description :  Update lens correction 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [bool] 0 : OTP data fail 
                        1 : otp_lenc update success            
**************************************************************************************************/
/*bool otp_lenc_update(USHORT zone)
{
}
*/


/*************************************************************************************************
* Function    :  wb_gain_set
* Description :  Set WB ratio to register gain setting  512x
* Parameters  :  [int] r_ratio : R ratio data compared with golden module R
                       b_ratio : B ratio data compared with golden module B
* Return      :  [bool] 0 : set wb fail 
                        1 : WB set success            
**************************************************************************************************/
bool wb_gain_set(kal_uint32 r_ratio, kal_uint32 b_ratio)
{
	USHORT R_GAIN;
	USHORT B_GAIN;
	USHORT Gr_GAIN;
	USHORT Gb_GAIN;
	USHORT G_GAIN;

if(!r_ratio || !b_ratio)
{
	printk("[S5K3H7Y]OTP WB ratio Data Err!\n");
	return 0;
}

if(r_ratio >= 512 )
{
	if(b_ratio>=512) 
	{
		R_GAIN = (USHORT)(GAIN_DEFAULT * r_ratio / 512);
		G_GAIN = GAIN_DEFAULT; 
		B_GAIN = (USHORT)(GAIN_DEFAULT * b_ratio / 512);
	}
	else
	{
		R_GAIN = (USHORT)( GAIN_DEFAULT * r_ratio / b_ratio);
		G_GAIN = (USHORT)(GAIN_DEFAULT * 512 / b_ratio );
		B_GAIN = GAIN_DEFAULT; 
	}
}
else  
{
	if(b_ratio >= 512)
	{
		R_GAIN = GAIN_DEFAULT; 
		G_GAIN =(USHORT)(GAIN_DEFAULT * 512 / r_ratio);
		B_GAIN =(USHORT)(GAIN_DEFAULT *  b_ratio / r_ratio);
	 
	} 
	else 
	{
		Gr_GAIN = (USHORT)(GAIN_DEFAULT * 512 / r_ratio );
		Gb_GAIN = (USHORT)(GAIN_DEFAULT * 512 / b_ratio );
		if(Gr_GAIN >= Gb_GAIN)
 		{
		    R_GAIN = GAIN_DEFAULT;
		    G_GAIN = (USHORT)(GAIN_DEFAULT * 512 / r_ratio );
		    B_GAIN = (USHORT)(GAIN_DEFAULT * b_ratio / r_ratio);
 		} 
        		else
        		{
		     R_GAIN =  (USHORT)(GAIN_DEFAULT * r_ratio / b_ratio );
		     G_GAIN = (USHORT)(GAIN_DEFAULT * 512 / b_ratio );
		     B_GAIN = GAIN_DEFAULT;
		}
	} 
}
	printk("[S5K3H7Y] otp wb R_GAIN = %d, B_GAIN = %d, G_GAIN = %d\n",R_GAIN,B_GAIN,G_GAIN);
	
	S5K3H7Y_wordwrite_cmos_sensor(GAIN_RED_ADDR, R_GAIN);
	S5K3H7Y_wordwrite_cmos_sensor(GAIN_BLUE_ADDR, B_GAIN); 
	S5K3H7Y_wordwrite_cmos_sensor(GAIN_GREEN1_ADDR, G_GAIN); //Green 1 default gain 1x
	S5K3H7Y_wordwrite_cmos_sensor(GAIN_GREEN2_ADDR, G_GAIN); //Green 2 default gain 1x
 
	return 1;
}



/*************************************************************************************************
* Function    :  get_otp_wb
* Description :  Get WB data    
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f      
**************************************************************************************************/
bool get_otp_wb(BYTE zone)
{
	BYTE temph = 0;
	BYTE templ = 0;
	current_rg = 0, current_bg = 0;

	if(!start_read_otp(zone))
	{
		printk("[S5K3H7Y]Start read Page %d Fail!\n", zone);
		return 0;
	}
  	golden_rg = 0x0330;
  	golden_bg = 0x028C;
  	
	temph = S5K3H7Y_byteread_cmos_sensor(0x0A04);  
	templ = S5K3H7Y_byteread_cmos_sensor(0x0A05);   
	current_rg  = (USHORT)templ + ((USHORT)temph << 8);
	
	temph = S5K3H7Y_byteread_cmos_sensor(0x0A06);  
	templ = S5K3H7Y_byteread_cmos_sensor(0x0A07);
	current_bg  = (USHORT)templ + ((USHORT)temph << 8);

	printk("[S5K3H7Y] get otp wb current_rg= 0x%4x,current_bg = 0x%4x\n",current_rg,current_bg);

	stop_read_otp();

	return 1;
}


/*************************************************************************************************
* Function    :  otp_wb_update
* Description :  Update WB correction 
* Return      :  [bool] 0 : OTP data fail 
                        1 : otp_WB update success            
**************************************************************************************************/
bool otp_wb_update(BYTE zone)
{
	kal_uint32 r_ratio;
	kal_uint32 b_ratio;
	
	if(!get_otp_wb(zone))  // get wb data from otp
		return 0;


	if(!golden_rg || !golden_bg || !current_rg || !current_bg)
	{
		printk("[S5K3H7Y]WB update Err !\n");
		return 0;
	}

	r_ratio = 512 * (golden_rg) /(current_rg);
	b_ratio = 512 * (golden_bg) /(current_bg);

	printk("[S5K3H7Y] otp wb r_ratio = %d, b_ratio = %d\n",r_ratio,b_ratio);
	
	wb_gain_set(r_ratio, b_ratio);

	printk("[S5K3H7Y]OTP WB update finished!\n");

	return 1;
}

/*************************************************************************************************
* Function    :  otp_update()
* Description :  update otp data from otp , it otp data is valid, 
                 it include get ID and WB update function  
* Return      :  [bool] 0 : update fail
                        1 : update success
**************************************************************************************************/
bool otp_update()
{
	BYTE zone = 0x01;
	BYTE FLG = 0x00;
	BYTE MID = 0x00;
	int i;
	printk("[S5K3H7Y] enter the otp_update fuction\n");
	for(i=0;i<3;i++)
	{
		FLG = get_otp_flag(zone);
		if(FLG == VALID_OTP)
			break;
		else
			zone++;
	}
	if(i==3)
	{
		printk("[S5K3H7Y]No OTP Data or OTP data is invalid\n");
		return 0;
	}
	
	MID = get_otp_module_id(zone);
	if(MID != Oflim_ID)
	{
		printk("No Oflim Module !\n");
		return 0;
	}
	//get_otp_date(zone);
	//get_otp_lens_id(zone);
	//get_otp_vcm_id(zone);
	//get_otp_driver_id(zone);
    //get_light_id(zone);

	otp_wb_update(zone);	
}


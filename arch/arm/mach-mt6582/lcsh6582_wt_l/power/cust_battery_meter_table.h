#ifndef _CUST_BATTERY_METER_TABLE_H
#define _CUST_BATTERY_METER_TABLE_H

#include <mach/mt_typedefs.h>

// ============================================================
// define
// ============================================================
#define BAT_NTC_10 1
#define BAT_NTC_47 0

#if (BAT_NTC_10 == 1)
#define RBAT_PULL_UP_R             16900	
#define RBAT_PULL_DOWN_R		   27000	
#endif

#if (BAT_NTC_47 == 1)
#define RBAT_PULL_UP_R             61900	
#define RBAT_PULL_DOWN_R		  100000	
#endif
#define RBAT_PULL_UP_VOLT          1800



// ============================================================
// ENUM
// ============================================================

// ============================================================
// structure
// ============================================================

// ============================================================
// typedef
// ============================================================
typedef struct _BATTERY_PROFILE_STRUC
{
    kal_int32 percentage;
    kal_int32 voltage;
} BATTERY_PROFILE_STRUC, *BATTERY_PROFILE_STRUC_P;

typedef struct _R_PROFILE_STRUC
{
    kal_int32 resistance; // Ohm
    kal_int32 voltage;
} R_PROFILE_STRUC, *R_PROFILE_STRUC_P;

typedef enum
{
    T1_0C,
    T2_25C,
    T3_50C
} PROFILE_TEMPERATURE;

// ============================================================
// External Variables
// ============================================================

// ============================================================
// External function
// ============================================================

// ============================================================
// <DOD, Battery_Voltage> Table
// ============================================================
#if (BAT_NTC_10 == 1)
    BATT_TEMPERATURE Batt_Temperature_Table[] = {
        {-20,70654},
        {-15,55337},
        {-10,43662},
        { -5,34696},
        {  0,27760},
        {  5,22358},
        { 10,18121},
        { 15,14778},
        { 20,12122},
        { 25,10000},
        { 30,8295},
        { 35,6916},
        { 40,5796},
        { 45,4881},
        { 50,4130},
        { 55,3510},
        { 60,2997}
    };
#endif

#if (BAT_NTC_47 == 1)
    BATT_TEMPERATURE Batt_Temperature_Table[] = {
        {-20,483954},
        {-15,360850},
        {-10,271697},
        { -5,206463},
        {  0,158214},
        {  5,122259},
        { 10,95227},
        { 15,74730},
        { 20,59065},
        { 25,47000},
        { 30,37643},
        { 35,30334},
        { 40,24591},
        { 45,20048},
        { 50,16433},
        { 55,13539},
        { 60,11210}        
    };
#endif

// T0 -10C
BATTERY_PROFILE_STRUC battery_profile_t0[] =
{
	{0  , 4333},
	{2  , 4306},
	{3  , 4285},
	{5  , 4265},
	{7  , 4245},
	{9  , 4226},
	{10 , 4207},
	{12 , 4189},
	{14 , 4170},
	{16 , 4151},
	{17 , 4131},
	{19 , 4112},
	{21 , 4095},
	{22 , 4084},
	{24 , 4069},
	{26 , 4040},
	{28 , 4003},
	{29 , 3976},
	{31 , 3957},
	{33 , 3943},
	{34 , 3932},
	{36 , 3924},
	{38 , 3915},
	{40 , 3905},
	{41 , 3894},
	{43 , 3883},
	{45 , 3872},
	{47 , 3862},
	{48 , 3852},
	{50 , 3843},
	{52 , 3834},
	{53 , 3826},
	{55 , 3818},
	{57 , 3811},
	{59 , 3804},
	{60 , 3798},
	{62 , 3792},
	{64 , 3786},
	{66 , 3781},
	{67 , 3777},
	{69 , 3773},
	{71 , 3770},
	{72 , 3766},
	{74 , 3762},
	{76 , 3758},
	{78 , 3753},
	{79 , 3748},
	{81 , 3742},
	{83 , 3735},
	{84 , 3729},
	{86 , 3724},
	{88 , 3719},
	{90 , 3713},
	{91 , 3706},
	{93 , 3694},
	{95 , 3673},
	{97 , 3637},
	{98 , 3584},
	{100, 3499},
	{100, 3434},
	{100, 3387}      
};      
        
// T1 0C 
BATTERY_PROFILE_STRUC battery_profile_t1[] =
{
	{0  , 4317},
	{2  , 4295},
	{3  , 4276},
	{5  , 4257},
	{7  , 4237},
	{9  , 4218},
	{10 , 4200},
	{12 , 4182},
	{14 , 4164},
	{15 , 4146},
	{17 , 4128},
	{19 , 4110},
	{20 , 4094},
	{22 , 4085},
	{24 , 4069},
	{26 , 4039},
	{27 , 4006},
	{29 , 3982},
	{31 , 3965},
	{32 , 3951},
	{34 , 3940},
	{36 , 3929},
	{37 , 3918},
	{39 , 3905},
	{41 , 3893},
	{43 , 3881},
	{44 , 3870},
	{46 , 3860},
	{48 , 3851},
	{49 , 3842},
	{51 , 3834},
	{53 , 3827},
	{55 , 3820},
	{56 , 3814},
	{58 , 3807},
	{60 , 3802},
	{61 , 3797},
	{63 , 3791},
	{65 , 3787},
	{66 , 3782},
	{68 , 3779},
	{70 , 3775},
	{72 , 3772},
	{73 , 3769},
	{75 , 3765},
	{77 , 3761},
	{78 , 3756},
	{80 , 3750},
	{82 , 3743},
	{83 , 3736},
	{85 , 3729},
	{87 , 3718},
	{89 , 3710},
	{90 , 3705},
	{92 , 3700},
	{94 , 3695},
	{95 , 3674},
	{97 , 3616},
	{99 , 3520},
	{100, 3346},
	{100, 3189}	       
};           

// T2 25C
BATTERY_PROFILE_STRUC battery_profile_t2[] =
{
	{0   , 4326},         
	{2   , 4303},         
	{3   , 4283},         
	{5   , 4263},         
	{7   , 4243},         
	{8  , 4224},         
	{10  , 4205},         
	{12  , 4187},         
	{14  , 4168},         
	{15  , 4150},         
	{17  , 4132},         
	{19  , 4114},         
	{20  , 4097},         
	{22  , 4083},         
	{24  , 4072},         
	{25  , 4053},         
	{27  , 4027},         
	{29  , 4005},         
	{31  , 3991},         
	{32  , 3979},         
	{34  , 3968},         
	{36  , 3955},         
	{37  , 3939},         
	{39  , 3921},         
	{41  , 3904},         
	{42  , 3889},         
	{44  , 3876},         
	{46  , 3865},         
	{48  , 3855},         
	{49  , 3846},         
	{51  , 3837},         
	{53  , 3829},         
	{54  , 3822},         
	{56  , 3816},         
	{58  , 3810},         
	{59  , 3804},         
	{61  , 3799},         
	{63  , 3794},         
	{65  , 3789},         
	{66  , 3785},         
	{68  , 3780},         
	{70  , 3776},         
	{71  , 3771},         
	{73  , 3765},         
	{75  , 3759},         
	{76  , 3753},         
	{78  , 3748},         
	{80  , 3742},         
	{81  , 3736},         
	{83  , 3728},         
	{85 , 3719},         
	{87 , 3711},         
	{88 , 3699},         
	{90 , 3693},         
	{92 , 3690},         
	{93 , 3687},         
	{95 , 3674},         
	{97 , 3617},         
	{98 , 3529},         
	{100 , 3381},         
	{100 , 3381} 
};     

// T3 50C
BATTERY_PROFILE_STRUC battery_profile_t3[] =
{
	{0   , 4327},         
	{2   , 4305},         
	{3   , 4284},         
	{5   , 4264},         
	{7   , 4244},         
	{8  , 4224},         
	{10  , 4205},         
	{12  , 4186},         
	{14  , 4167},         
	{15  , 4149},         
	{17  , 4131},         
	{19  , 4113},         
	{20  , 4095},         
	{22  , 4078},         
	{24  , 4062},         
	{25  , 4047},         
	{27  , 4029},         
	{29  , 4012},         
	{30  , 3998},         
	{32  , 3985},         
	{34  , 3971},         
	{36  , 3957},         
	{37  , 3943},         
	{39  , 3927},         
	{41  , 3908},         
	{42  , 3891},         
	{44  , 3877},         
	{46  , 3865},         
	{47  , 3855},         
	{49  , 3846},         
	{51  , 3837},         
	{53  , 3829},         
	{54  , 3822},         
	{56  , 3815},         
	{58  , 3808},         
	{59  , 3802},         
	{61  , 3797},         
	{63  , 3792},         
	{64  , 3787},         
	{66  , 3782},         
	{68  , 3777},         
	{69  , 3771},         
	{71  , 3760},         
	{73  , 3751},         
	{75  , 3744},         
	{76  , 3737},         
	{78  , 3732},         
	{80  , 3726},         
	{81  , 3721},         
	{83  , 3714},         
	{85 , 3705},         
	{86 , 3697},         
	{88 , 3686},         
	{90 , 3678},         
	{91 , 3676},         
	{93 , 3673},         
	{95 , 3662},         
	{97 , 3613},         
	{98 , 3532},         
	{100 , 3406},         
	{100 , 3121} 	       
};           

// battery profile for actual temperature. The size should be the same as T1, T2 and T3
BATTERY_PROFILE_STRUC battery_profile_temperature[] =
{
  {0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },  
	{0  , 0 }, 
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },  
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 }

};    

// ============================================================
// <Rbat, Battery_Voltage> Table
// ============================================================
// T0 -10C
R_PROFILE_STRUC r_profile_t0[] =
{
	{812 , 4333},
	{812 , 4306},
	{815 , 4285},
	{818 , 4265},
	{816 , 4245},
	{809 , 4226},
	{815 , 4207},
	{816 , 4189},
	{819 , 4170},
	{816 , 4151},
	{816 , 4131},
	{810 , 4112},
	{802 , 4095},
	{809 , 4084},
	{827 , 4069},
	{818 , 4040},
	{792 , 4003},
	{781 , 3976},
	{774 , 3957},
	{771 , 3943},
	{772 , 3932},
	{774 , 3924},
	{775 , 3915},
	{774 , 3905},
	{773 , 3894},
	{773 , 3883},
	{776 , 3872},
	{779 , 3862},
	{783 , 3852},
	{788 , 3843},
	{791 , 3834},
	{798 , 3826},
	{805 , 3818},
	{814 , 3811},
	{820 , 3804},
	{827 , 3798},
	{837 , 3792},
	{843 , 3786},
	{846 , 3781},
	{857 , 3777},
	{862 , 3773},
	{871 , 3770},
	{874 , 3766},
	{879 , 3762},
	{884 , 3758},
	{896 , 3753},
	{904 , 3748},
	{918 , 3742},
	{933 , 3735},
	{960 , 3729},
	{998 , 3724},
	{1053, 3719},
	{1126, 3713},
	{1223, 3706},
	{1373, 3694},
	{1598, 3673},
	{1842, 3637},
	{2018, 3584},
	{2301, 3499},
	{2139, 3434},
	{2021, 3387}	       
};      

// T1 0C
R_PROFILE_STRUC r_profile_t1[] =
{
	{447 , 4317},
	{447 , 4295},
	{451 , 4276},
	{453 , 4257},
	{456 , 4237},
	{459 , 4218},
	{463 , 4200},
	{466 , 4182},
	{471 , 4164},
	{474 , 4146},
	{470 , 4128},
	{463 , 4110},
	{458 , 4094},
	{467 , 4085},
	{476 , 4069},
	{468 , 4039},
	{457 , 4006},
	{450 , 3982},
	{443 , 3965},
	{437 , 3951},
	{431 , 3940},
	{429 , 3929},
	{425 , 3918},
	{420 , 3905},
	{417 , 3893},
	{416 , 3881},
	{416 , 3870},
	{416 , 3860},
	{418 , 3851},
	{418 , 3842},
	{421 , 3834},
	{423 , 3827},
	{425 , 3820},
	{428 , 3814},
	{429 , 3807},
	{433 , 3802},
	{435 , 3797},
	{436 , 3791},
	{438 , 3787},
	{438 , 3782},
	{440 , 3779},
	{442 , 3775},
	{443 , 3772},
	{444 , 3769},
	{444 , 3765},
	{447 , 3761},
	{447 , 3756},
	{449 , 3750},
	{450 , 3743},
	{452 , 3736},
	{455 , 3729},
	{453 , 3718},
	{447 , 3710},
	{475 , 3705},
	{505 , 3700},
	{537 , 3695},
	{573 , 3674},
	{611 , 3616},
	{757 , 3520},
	{1174, 3346},
	{782 , 3189}	       
};     

// T2 25C
R_PROFILE_STRUC r_profile_t2[] =
{
	{200   , 4326},         
	{200   , 4303},         
	{203   , 4283},         
	{205   , 4263},         
	{206   , 4243},         
	{208  , 4224},         
	{210  , 4205},         
	{213  , 4187},         
	{216  , 4168},         
	{218  , 4150},         
	{222  , 4132},         
	{223  , 4114},         
	{227  , 4097},         
	{230  , 4083},         
	{237  , 4072},         
	{238  , 4053},         
	{238  , 4027},         
	{240  , 4005},         
	{243  , 3991},         
	{245  , 3979},         
	{246  , 3968},         
	{244  , 3955},         
	{237  , 3939},         
	{226  , 3921},         
	{217  , 3904},         
	{211  , 3889},         
	{206  , 3876},         
	{206  , 3865},         
	{204  , 3855},         
	{204  , 3846},         
	{204  , 3837},         
	{204  , 3829},         
	{206  , 3822},         
	{208  , 3816},         
	{209  , 3810},         
	{210  , 3804},         
	{212  , 3799},         
	{214  , 3794},         
	{215  , 3789},         
	{215  , 3785},         
	{215  , 3780},         
	{213  , 3776},         
	{212  , 3771},         
	{209  , 3765},         
	{206  , 3759},         
	{204  , 3753},         
	{206  , 3748},         
	{208  , 3742},         
	{209  , 3736},         
	{208  , 3728},         
	{208 , 3719},         
	{212 , 3711},         
	{205 , 3699},         
	{207 , 3693},         
	{216 , 3690},         
	{228 , 3687},         
	{237 , 3674},         
	{230 , 3617},         
	{250 , 3529},         
	{305 , 3381},         
	{305 , 3381} 	       
}; 

// T3 50C
R_PROFILE_STRUC r_profile_t3[] =
{
	{166 , 4327},         
	{166 , 4305},         
	{166 , 4284},         
	{166 , 4264},         
	{167 , 4244},         
	{167 , 4224},         
	{168 , 4205},         
	{169 , 4186},         
	{171 , 4167},         
	{171 , 4149},         
	{173 , 4131},         
	{175 , 4113},         
	{175 , 4095},         
	{178 , 4078},         
	{180 , 4062},         
	{182 , 4047},         
	{184 , 4029},         
	{186 , 4012},         
	{188 , 3998},         
	{189 , 3985},         
	{191 , 3971},         
	{193 , 3957},         
	{195 , 3943},         
	{191 , 3927},         
	{180 , 3908},         
	{171 , 3891},         
	{166 , 3877},         
	{165 , 3865},         
	{163 , 3855},         
	{164 , 3846},         
	{164 , 3837},         
	{166 , 3829},         
	{168 , 3822},         
	{168 , 3815},         
	{171 , 3808},         
	{171 , 3802},         
	{175 , 3797},         
	{177 , 3792},         
	{179 , 3787},         
	{179 , 3782},         
	{181 , 3777},         
	{178 , 3771},         
	{167 , 3760},         
	{165 , 3751},         
	{165 , 3744},         
	{164 , 3737},         
	{165 , 3732},         
	{166 , 3726},         
	{167 , 3721},         
	{168 , 3714},         
	{166 , 3705},         
	{168 , 3697},         
	{168 , 3686},         
	{163 , 3678},         
	{171 , 3676},         
	{178 , 3673},         
	{183 , 3662},         
	{180 , 3613},         
	{193 , 3532},         
	{222 , 3406},         
	{768 , 3121}        
}; 

// r-table profile for actual temperature. The size should be the same as T1, T2 and T3
R_PROFILE_STRUC r_profile_temperature[] =
{
  {0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },  
	{0  , 0 }, 
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },  
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 }

};    

// ============================================================
// function prototype
// ============================================================
int fgauge_get_saddles(void);
BATTERY_PROFILE_STRUC_P fgauge_get_profile(kal_uint32 temperature);

int fgauge_get_saddles_r_table(void);
R_PROFILE_STRUC_P fgauge_get_profile_r_table(kal_uint32 temperature);

#endif	//#ifndef _CUST_BATTERY_METER_TABLE_H

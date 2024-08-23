#ifndef COMMANDS_H
#define	COMMANDS_H
/********************************************************************
* FileName:        commands.h
* Dependencies:    None
* Processor:       dsPIC33F
* Compiler:        C30 v3.11b
* Company:         Microchip Technology, Inc.
*
* � 2008 Microchip Technology Inc.
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
*
*********************************************************************/
/*-----------------------------------------------
    include files
-----------------------------------------------*/
#include "Gernirc_Type.h"

/*-----------------------------------------------
     PMBus define start here  
    Size of Pmbus:
    Ver  No.
    1.1: 145
    1.2: 157
    1.3: 164 
-----------------------------------------------*/

#define MATRIX_NUMS          256        
#define NR_COMMANDS          145
#define LUT_LINEAR_EXPONETS  32
#define UNSUPPORTED_CMD_CODE 0xFF
#define MAX_BYTES            16
/*-----------------------------------------------
    PMBus Protocols
-----------------------------------------------*/

#define SEND_BYTE 0x0
#define READ_BYTE 0x1
#define RW_BYTE READ_BYTE
#define READ_WORD 0x2
#define RW_WORD READ_WORD
#define RW_BLOCK 0x3
#define BW_BR_PROC_CALL 0x4


 /*--------------------------------------------------
    PMBUS 1.3.1 Command Codes
 --------------------------------------------------*/
 typedef enum
 {
    PAGE_CMD_0x0                = 0,
    OPERATION_COMMAND_0x1       = 1,
    ON_OFF_CONFIG_COMMAND_0x2   = 2,
    CLEAR_FAULTS_COMMAND_0x3    =3,
    PHASE_COMMAND_0x4=4,
    WRITE_POTECT_COMMAND_0x10=5,
    STORE_DEFAULT_ALL_COMMAND_0x11=6,
    RESTORE_DEFAULT_ALL_COMMAND_0x12=7,
    VOUT_MODE_COMMAND_0x20=8,
    VOUT_COMMAND_0x21=9,
    VOUT_MAX_COMMAND_0x24=10,
    VOUT_MARGIN_HIGH_COMMAND_0x25 =11,
    VOUT_MARGIN_LOW_COMMAND_0x26=12,
    VOUT_TRANSITION_RATE_COMMAND_0x27=13,
    VOUT_DROOP_COMMAND_0x28=14,
    VOUT_SCALE_LOOP_COMMAND_0x29=15,
    VOUT_SCALE_MONITOR_COMMAND_0x2A=16,
    VOUT_MIN_COMMAND_0x2B=17,
    POUT_MAX_COMMAND_0x31=18,
    MAX_DUTY_COMMAND_0x32=19,
    FREQUENCY_SWITCH_COMMAND_0x33=20,
    POWER_MODE_COMMAND_0x34=21,
    VIN_ON_COMMAND_0x35=22,
    VIN_OFF_COMMAND_0x36=23,
    IOUT_CAL_GAIN_COMMAND_0x38=24,
    IOUT_CAL_OFFSET_COMMAND_0x39=25,
    FAN_CONFIG_1_2_COMMAND_0x3A=26,
    FAN_COMMAND_1_COMMAND_0x3B=27,
    FAN_COMMAND_2_COMMAND_0x3C=28,
    FAN_CONFIG_3_4_COMMAND_0x3D=29,
    FAN_COMMAND_3_COMMAND_0x3E=30,
    FAN_COMMAND_4_COMMAND_0x3F=31,
    VOUT_OV_FAULT_LIMIT_COMMAND_0x40=32,
    VOUT_OV_FAULT_RESPONSE_COMMAND_0x41=33,
    VOUT_OV_WARN_LIMIT_COMMAND_0x42=34,
    VOUT_UV_WARN_LIMIT_COMMAND_0x43=35,
    VOUT_UV_FAULT_LIMIT_COMMAND_0x44=36,
    VOUT_UV_FAULT_RESPONS_COMMAND_0x45=37,
    IOUT_OC_FAULT_LIMIT_COMMAND_0x46=38,
    IOUT_OC_FAULT_RESPONSE_COMMAND_0x47=39,
    IOUT_OC_LV_FAULT_LIMIT_COMMAND_0x48=40,
    IOUT_OC_LV_FAULT_RESPONSE_COMMAND_0x49=41,
    IOUT_OC_WARN_LIMIT_COMMAND_0x4A=42,
    IOUT_UC_FAULT_LIMIT_COMMAND_0x4B=43,
    IOUT_UC_FAULT_RESPONS_COMMAND_0x4C=44,
    OT_FAULT_LIMIT_COMMAND_0x4F=45,
    OT_FAULT_RESPONSE_COMMAND_0x50=46,
    OT_WARN_LIMIT_COMMAND_0x51=47,
    UT_WARN_LIMIT_COMMAND_0x52=48,
    UT_FAULT_LIMIT_COMMAND_0x53=49,
    UT_FAULT_RESPONS_COMMAND_0x54=50,
    VIN_OV_FAULT_LIMIT_COMMAND_0x55=51,
    VIN_OV_FAULT_RESPONSE_COMMAND_0x56=52,
    VIN_OV_WARN_LIMIT_COMMAND_0x57=53,
    VIN_UV_WARN_LIMIT_COMMAND_0x58=54,
    VIN_UV_FAULT_LIMIT_COMMAND_0x59=55,
    VIN_UV_FAULT_RESPONSE_COMMAND_0x5A=56,
    IIN_OC_FAULT_LIMIT_COMMAND_0x5B=57,
    IIN_OC_FAULT_RESPONSE_COMMAND_0x5C=58,
    IIN_OC_WARN_LIMIT_COMMAND_0x5D=59,
    POWER_GOOD_ON_COMMAND_0x5E=60,
    POWER_GOOD_OFF_COMMAND_0x5F=61,
    TON_DELAY_COMMAND_0x60=62,
    TON_RISE_COMMAND_0x61=63,
    TON_MAX_FAULT_LIMIT_COMMAND_0x62=64,
    TON_MAX_FAULT_RESPONSE_COMMAND_0x63=65,
    TOFF_DELAY_COMMAND_0x64=66,
    TOFF_FALL_COMMAND_0x65=67,
    TOFF_MAX_WARM_LIMIT_COMMAND_0x66=68,
    POUT_OP_FAULT_LIMIT_COMMAND_0x68=69,
    POUT_OP_FAULT_RESPONSE_COMMAND_0x69=70,
    POUT_OP_WARN_LIMIT_COMMAND_0x6A=71,
    PIN_OP_WARN_LIMIT_COMMAND_0x6B=72,
    STATUS_WORD_COMMAND_0x79=73,
    STATUS_VOUT_COMMAND_0x7A=74,
    STATUS_IOUT_COMMAND_0x7B=75,
    STATUS_INPUT_COMMAND_0x7C=76,
    STATUS_TEMP_COMMAND_0x7D=77,
    STATUS_CML_COMMAND_0x7E=78,
    STATUS_OTHER_COMMAND_0x7F=79,
    STATUS_MFR_SPECIFIC_COMMAND_0x80=80,
    STATUS_FAN_1_2_COMMAND_0x81=81,
    STATUS_FAN_3_4_COMMAND_0x82=82,
    READ_KWH_IN_COMMAND_0x83=83,
    READ_KWH_OUT_COMMAND_0x84=84,
    READ_KWH_CONFIG_COMMAND_0x85=85,
    READ_EIN_COMMAND_0x86=86,
    READ_EOUT_COMMAND_0x87=87,
    READ_VIN_COMMAND_0x88=88,
    READ_IIN_COMMAND_0x89=89,
    READ_VACP_COMMAND_0x8A=90,
    READ_VOUT_COMMAND_0x8B=91,
    READ_IOUT_COMMAND_0x8C=92,
    READ_TEMP1_COMMAND_0x8D=93,
    READ_TEMP2_COMMAND_0x8E=94,
    READ_TEMP3_COMMAND_0x8F=95,
    READ_FAN_SPEED_1_COMMAND_0x90=96,
    READ_FAN_SPEED_2_COMMAND_0x91=97,
    READ_FAN_SPEED_3_COMMAND_0x92=98,
    READ_FAN_SPEED_4_COMMAND_0x93=99,
    READ_DUTY_CYCLE_COMMAND_0x94=100,
    READ_FREQUENCY_COMMAND_0x95=101,
    READ_POUT_COMMAND_0x96=102,
    READ_PIN_COMMAND_0x97=103,
    PMBUS_REVISION_COMMAND_0x98=104,
    MFR_ID_COMMAND_0x99=105,
    MFR_MODEL_COMMAND_0x9A=106,
    MFR_REVISION_COMMAND_0x9B=107,
    MFR_LOCATION_COMMAND_0x9C=108,
    MFR_DATE_COMMAND_0x9D=109,
    MFR_SERIAL_COMMAND_0x9E=110,
    APP_PROFILE_SUPPORT_COMMAND_0x9F=111,
    MFR_VIN_MIN_COMMAND_0xA0=112,
    MFR_VIN_MAX_COMMAND_0xA1=113,
    MFR_IIN_MAX_COMMAND_0xA2=114,
    MFR_PIN_MAX_COMMAND_0xA3=115,
    MFR_VOUT_MIN_COMMAND_0xA4=116,
    MFR_VOUT_MAX_COMMAND_0xA5=117,
    MFR_IOUT_MAX_COMMAND_0xA6=118,
    MFR_POUT_MAX_COMMAND_0xA7=119,
    MFR_TAMBIENT_MAX_COMMAND_0xA8=120,
    MFR_EFFICIENCY_LL_COMMAND_0xAA=121,
    MFR_EFFICIENCY_HL_COMMAND_0xAB=122,
    MFR_PIN_ACCURACY_COMMAND_0xAC=123,
    IC_DEVICE_ID_COMMAND_0xAD=124,
    IC_DEVICE_REV_COMMAND_0xAE=125,
    USER_DATA_00_COMMAND_0xB0=126,
    USER_DATA_01_COMMAND_0xB1=127,
    USER_DATA_02_COMMAND_0xB2=128,
    USER_DATA_03_COMMAND_0xB3=129,
    USER_DATA_04_COMMAND_0xB4=130,
    USER_DATA_05_COMMAND_0xB5=131,
    USER_DATA_06_COMMAND_0xB6=132,
    USER_DATA_07_COMMAND_0xB7=133,
    USER_DATA_08_COMMAND_0xB8=134,
    USER_DATA_09_COMMAND_0xB9=135,
    USER_DATA_10_COMMAND_0xBA=136,
    USER_DATA_11_COMMAND_0xBB=137,
    USER_DATA_12_COMMAND_0xBC=138,
    USER_DATA_13_COMMAND_0xBD=139,
    USER_DATA_14_COMMAND_0xBE=140,
    USER_DATA_15_COMMAND_0xBF=141,
    MFR_MAX_TEMP_1_COMMAND_0xC0=142,
    MFR_MAX_TEMP_2_COMMAND_0xC1=143,
    MFR_MAX_TEMP_3_COMMAND_0xC2=144,


 }Pmbus_Martrix_Index;
/*-----------------------------------------------
    0x1~0x8
-----------------------------------------------*/
#define OPERATION_COMMAND 			        0x1
#define ON_OFF_CONFIG_COMMAND 		        0x2
#define CLEAR_FAULTS_COMMAND 		        0x3
#define PHASE_COMMAND                       0x4
#define PAGE_PLUS_WRITE_COMMAND             0x5 
#define PAGE_PLUS_READ_COMMAND              0x6
#define ZONE_CONFIG_COMMAND                 0x7
#define ZONE_ACTIVE_COMMAND                 0x8
/*-----------------------------------------------
    0x9~0xF  Reserved
-----------------------------------------------*/
/*-----------------------------------------------
    0x10~0x1B
-----------------------------------------------*/
#define WRITE_POTECT_COMMAND                0x10
#define STORE_DEFAULT_ALL_COMMAND           0x11
#define RESTORE_DEFAULT_ALL_COMMAND         0x12
#define STORE_DEFAULT_CODE_COMMAND          0x13
#define RESTORE_DEFAULT_CODE_COMMAND        0x14
#define STORE_USER_ALL_COMMAND              0x15
#define RESTORE_USER_ALL_COMMAND            0x16
#define STORE_USER_CODE_COMMAND             0x17
#define RESTORE_USER_CODE_COMMAND           0x18
#define CAPABILITY_COMMAND			        0x19
#define QUERY_COMMAND				        0x1A
#define SMBALERT_MASK_COMMAND               0x1B   
/*-----------------------------------------------
    0x1C~0x1F Reserved
-----------------------------------------------*/
/*-----------------------------------------------
    0x20~0x2B
-----------------------------------------------*/
#define VOUT_MODE_COMMAND                   0x20
#define VOUT_COMMAND                        0x21
#define VOUT_TRIM_COMMAND                   0x22
#define VOUT_CAL_OFFSET_COMMAND             0x23
#define VOUT_MAX_COMMAND                    0x24
#define VOUT_MARGIN_HIGH_COMMAND            0x25
#define VOUT_MARGIN_LOW_COMMAND             0x26
#define VOUT_TRANSITION_RATE_COMMAND        0x27   
#define VOUT_DROOP_COMMAND                  0x28
#define VOUT_SCALE_LOOP_COMMAND             0x29
#define VOUT_SCALE_MONITOR_COMMAND          0x2A
#define VOUT_MIN_COMMAND                    0x2B
/*-----------------------------------------------
    0x2C~0x2F Reserved
-----------------------------------------------*/
/*-----------------------------------------------
    0x30~0x3F
-----------------------------------------------*/
#define COEFFICIENTS_COMMAND                0x30 
#define POUT_MAX_COMMAND                    0x31
#define MAX_DUTY_COMMAND                    0x32
#define FREQUENCY_SWITCH_COMMAND            0x33
#define POWER_MODE_COMMAND                  0x34
#define VIN_ON_COMMAND                      0x35
#define VIN_OFF_COMMAND                     0x36
#define INTERLEAVE_COMMAND                  0x37
#define IOUT_CAL_GAIN_COMMAND               0x38
#define IOUT_CAL_OFFSET_COMMAND             0x39
#define FAN_CONFIG_1_2_COMMAND		        0x3A
#define FAN_COMMAND_1_COMMAND		        0x3B
#define FAN_COMMAND_2_COMMAND		        0x3C
#define FAN_CONFIG_3_4_COMMAND		        0x3D
#define FAN_COMMAND_3_COMMAND		        0x3E
#define FAN_COMMAND_4_COMMAND		        0x3F
/*-----------------------------------------------
    0x40~0x4F
-----------------------------------------------*/
#define VOUT_OV_FAULT_LIMIT_COMMAND         0x40
#define VOUT_OV_FAULT_RESPONSE_COMMAND      0x41
#define VOUT_OV_WARN_LIMIT_COMMAND          0x42
#define VOUT_UV_WARN_LIMIT_COMMAND          0x43
#define VOUT_UV_FAULT_LIMIT_COMMAND         0x44
#define VOUT_UV_FAULT_RESPONS_COMMAND       0x45
#define IOUT_OC_FAULT_LIMIT_COMMAND         0x46
#define IOUT_OC_FAULT_RESPONSE_COMMAND      0x47
#define IOUT_OC_LV_FAULT_LIMIT_COMMAND      0x48
#define IOUT_OC_LV_FAULT_RESPONSE_COMMAND   0x49
#define IOUT_OC_WARN_LIMIT_COMMAND	        0x4A
#define IOUT_UC_FAULT_LIMIT_COMMAND         0x4B
#define IOUT_UC_FAULT_RESPONS_COMMAND       0x4C
/*-----------------------------------------------
    0x4D~0x4E  Reserved
-----------------------------------------------*/
/*-----------------------------------------------
    0x4F~0x5F   FAULT AMBLRT
-----------------------------------------------*/
#define OT_FAULT_LIMIT_COMMAND              0x4F
#define OT_FAULT_RESPONSE_COMMAND           0x50
#define OT_WARN_LIMIT_COMMAND		        0x51
#define UT_WARN_LIMIT_COMMAND               0x52
#define UT_FAULT_LIMIT_COMMAND              0x53
#define UT_FAULT_RESPONS_COMMAND            0x54
#define VIN_OV_FAULT_LIMIT_COMMAND          0x55
#define VIN_OV_FAULT_RESPONSE_COMMAND       0x56
#define VIN_OV_WARN_LIMIT_COMMAND           0x57
#define VIN_UV_WARN_LIMIT_COMMAND           0x58
#define VIN_UV_FAULT_LIMIT_COMMAND          0x59
#define VIN_UV_FAULT_RESPONSE_COMMAND       0x5A
#define IIN_OC_FAULT_LIMIT_COMMAND	        0x5B
#define IIN_OC_FAULT_RESPONSE_COMMAND	    0x5C
#define IIN_OC_WARN_LIMIT_COMMAND	        0x5D
#define POWER_GOOD_ON_COMMAND               0x5E
#define POWER_GOOD_OFF_COMMAND              0x5F
/*-----------------------------------------------
    0x60~0x6B   0x67 is Reserved by spec
-----------------------------------------------*/
#define TON_DELAY_COMMAND                   0x60
#define TON_RISE_COMMAND                    0x61
#define TON_MAX_FAULT_LIMIT_COMMAND         0x62
#define TON_MAX_FAULT_RESPONSE_COMMAND      0x63
#define TOFF_DELAY_COMMAND                  0x64
#define TOFF_FALL_COMMAND                   0x65
#define TOFF_MAX_WARM_LIMIT_COMMAND         0x66
#define POUT_OP_FAULT_LIMIT_COMMAND         0x68
#define POUT_OP_FAULT_RESPONSE_COMMAND      0x69
#define POUT_OP_WARN_LIMIT_COMMAND	        0x6A
#define PIN_OP_WARN_LIMIT_COMMAND	        0x6B
/*-----------------------------------------------
    0x6C~0x6F  Reserved
-----------------------------------------------*/
/*-----------------------------------------------
    0x70~0x77  Reserved
-----------------------------------------------*/
/*-----------------------------------------------
    0x79~0x7f   
-----------------------------------------------*/
#define STATUS_BYTE_COMMAND                0x78
#define STATUS_WORD_COMMAND 		       0x79
#define STATUS_VOUT_COMMAND 		       0x7A
#define STATUS_IOUT_COMMAND 		       0x7B
#define STATUS_INPUT_COMMAND 		       0x7C
#define STATUS_TEMP_COMMAND 		       0x7D
#define STATUS_CML_COMMAND 			       0x7E
#define STATUS_OTHER_COMMAND 		       0x7F
/*-----------------------------------------------
    0x80~0x8F   
-----------------------------------------------*/
#define STATUS_MFR_SPECIFIC_COMMAND        0x80
#define STATUS_FAN_1_2_COMMAND 		       0x81
#define STATUS_FAN_3_4_COMMAND 		       0x82
#define READ_KWH_IN_COMMAND                0x83
#define READ_KWH_OUT_COMMAND               0x84
#define READ_KWH_CONFIG_COMMAND            0x85
#define READ_EIN_COMMAND                   0x86
#define READ_EOUT_COMMAND                  0x87
#define READ_VIN_COMMAND 			       0x88
#define READ_IIN_COMMAND 			       0x89
#define READ_VACP_COMMAND                  0x8A
#define READ_VOUT_COMMAND 			       0x8B
#define READ_IOUT_COMMAND 			       0x8C
#define READ_TEMP1_COMMAND 			       0x8D
#define READ_TEMP2_COMMAND 			       0x8E
#define READ_TEMP3_COMMAND                 0x8F

/*-----------------------------------------------
    0x90~0x9F   
-----------------------------------------------*/
#define READ_FAN_SPEED_1_COMMAND 	       0x90
#define READ_FAN_SPEED_2_COMMAND 	       0x91
#define READ_FAN_SPEED_3_COMMAND 	       0x92
#define READ_FAN_SPEED_4_COMMAND 	       0x93
#define READ_DUTY_CYCLE_COMMAND            0x94
#define READ_FREQUENCY_COMMAND             0x95
#define READ_POUT_COMMAND 			       0x96
#define READ_PIN_COMMAND 			       0x97
#define PMBUS_REVISION_COMMAND		       0x98
#define MFR_ID_COMMAND                     0x99
#define MFR_MODEL_COMMAND                  0x9A
#define MFR_REVISION_COMMAND               0x9B    
#define MFR_LOCATION_COMMAND               0x9C
#define MFR_DATE_COMMAND                   0x9D
#define MFR_SERIAL_COMMAND                 0x9E
#define APP_PROFILE_SUPPORT_COMMAND        0x9F    
/*-----------------------------------------------
    0xA0~0xAE   
-----------------------------------------------*/
#define MFR_VIN_MIN_COMMAND			       0xA0
#define MFR_VIN_MAX_COMMAND			       0xA1
#define MFR_IIN_MAX_COMMAND			       0xA2
#define MFR_PIN_MAX_COMMAND			       0xA3
#define MFR_VOUT_MIN_COMMAND		       0xA4
#define MFR_VOUT_MAX_COMMAND		       0xA5
#define MFR_IOUT_MAX_COMMAND		       0xA6
#define MFR_POUT_MAX_COMMAND		       0xA7
#define MFR_TAMBIENT_MAX_COMMAND	       0xA8
#define MFR_TAMBIENT_MIN_COMMAND           0xA9
#define MFR_EFFICIENCY_LL_COMMAND 	       0xAA
#define MFR_EFFICIENCY_HL_COMMAND 	       0xAB
#define MFR_PIN_ACCURACY_COMMAND           0xAC
#define IC_DEVICE_ID_COMMAND               0xAD
#define IC_DEVICE_REV_COMMAND              0xAE
/*-----------------------------------------------
    0xAF Reserved   
-----------------------------------------------*/
/*-----------------------------------------------
    0xB0~0xBF   
-----------------------------------------------*/
#define USER_DATA_00_COMMAND               0xB0
#define USER_DATA_01_COMMAND               0xB1
#define USER_DATA_02_COMMAND               0xB2
#define USER_DATA_03_COMMAND               0xB3
#define USER_DATA_04_COMMAND               0xB4
#define USER_DATA_05_COMMAND               0xB5
#define USER_DATA_06_COMMAND               0xB6
#define USER_DATA_07_COMMAND               0xB7
#define USER_DATA_08_COMMAND               0xB8
#define USER_DATA_09_COMMAND               0xB9
#define USER_DATA_10_COMMAND               0xBA
#define USER_DATA_11_COMMAND               0xBB
#define USER_DATA_12_COMMAND               0xBC
#define USER_DATA_13_COMMAND               0xBD
#define USER_DATA_14_COMMAND               0xBE
#define USER_DATA_15_COMMAND               0xBF
/*-----------------------------------------------
    0xC0~0xCF   0xC3 Reserved   
-----------------------------------------------*/
#define MFR_MAX_TEMP_1_COMMAND             0xC0
#define MFR_MAX_TEMP_2_COMMAND             0xC1
#define MFR_MAX_TEMP_3_COMMAND             0xC2
/********** MFR_SPECIFIC from v1.3.1************/
#define MFR_SPECIFIC_C4                    0xC4
#define MFR_SPECIFIC_C5                    0xC5
#define MFR_SPECIFIC_C6                    0xC6
#define MFR_SPECIFIC_C7                    0xC7
#define MFR_SPECIFIC_C8                    0xC8
#define MFR_SPECIFIC_C9                    0xC9
#define MFR_SPECIFIC_CA                    0xCA
#define MFR_SPECIFIC_CB                    0xCB
#define MFR_SPECIFIC_CC                    0xCC
#define MFR_SPECIFIC_CD                    0xCD
#define MFR_SPECIFIC_CE                    0xCE
#define MFR_SPECIFIC_CF                    0xCF
/*-----------------------------------------------
    0xD0~0xDF   
-----------------------------------------------*/
#define MFR_SPECIFIC_D0                    0xD0
#define MFR_SPECIFIC_D1                    0xD1
#define MFR_SPECIFIC_D2                    0xD2
#define MFR_SPECIFIC_D3                    0xD3
#define MFR_SPECIFIC_D4                    0xD4
#define MFR_SPECIFIC_D5                    0xD5
#define MFR_SPECIFIC_D6                    0xD6
#define MFR_SPECIFIC_D7                    0xD7
#define MFR_SPECIFIC_D8                    0xD8
#define MFR_SPECIFIC_D9                    0xD9
#define MFR_SPECIFIC_DA                    0xDA
#define MFR_SPECIFIC_DB                    0xDB
#define MFR_SPECIFIC_DC                    0xDC
#define MFR_SPECIFIC_DD                    0xDD
#define MFR_SPECIFIC_DE                    0xDE
#define MFR_SPECIFIC_DF                    0xDF
/*-----------------------------------------------
    0xE0~0xEF   
-----------------------------------------------*/
#define MFR_SPECIFIC_E0                    0xE0
#define MFR_SPECIFIC_E1                    0xE1
#define MFR_SPECIFIC_E2                    0xE2
#define MFR_SPECIFIC_E3                    0xE3
#define MFR_SPECIFIC_E4                    0xE4
#define MFR_SPECIFIC_E5                    0xE5
#define MFR_SPECIFIC_E6                    0xE6
#define MFR_SPECIFIC_E7                    0xE7
#define MFR_SPECIFIC_E8                    0xE8
#define MFR_SPECIFIC_E9                    0xE9
#define MFR_SPECIFIC_EA                    0xEA
#define MFR_SPECIFIC_EB                    0xEB
#define MFR_SPECIFIC_EC                    0xEC
#define MFR_SPECIFIC_ED                    0xED
#define MFR_SPECIFIC_EE                    0xEE
#define MFR_SPECIFIC_EF                    0xEF
/*-----------------------------------------------
    0xF0~0xFF   
-----------------------------------------------*/
#define MFR_SPECIFIC_F0                    0xF0
#define MFR_SPECIFIC_F1                    0xF1
#define MFR_SPECIFIC_F2                    0xF2
#define MFR_SPECIFIC_F3                    0xF3
#define MFR_SPECIFIC_F4                    0xF4
#define MFR_SPECIFIC_F5                    0xF5
#define MFR_SPECIFIC_F6                    0xF6
#define MFR_SPECIFIC_F7                    0xF7
#define MFR_SPECIFIC_F8                    0xF8
#define MFR_SPECIFIC_F9                    0xF9
#define MFR_SPECIFIC_FA                    0xFA
#define MFR_SPECIFIC_FB                    0xFB
#define MFR_SPECIFIC_FC                    0xFC
#define MFR_SPECIFIC_FD                    0xFD
/************  End of v1.3 section************/
#define MFR_SPECIFIC_COMMAND_EXT           0xFE
#define MFR_PMBUS_COMMAND_EXT              0xFF


extern Pmbus_Martrix_Index Pmbus_1_3_Index;
/*--------------------------------------------------
    PMBUS buffer
--------------------------------------------------*/
/*buffer 需要另外定義這導致IDE 錯誤*/
extern uint8_t buffer[MAX_BYTES + 1];

























#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TEMPLATE_H */



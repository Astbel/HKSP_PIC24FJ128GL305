/********************************************************************
 * FileName:        PMBus_stack.c
 * Dependencies:    See INCLUDES section below
 * Processor:       dsPIC33F
 * Compiler:        C30 v3.11
 * Company:         Microchip Technology, Inc.
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
 *********************************************************************
 *
 * File Description: This file contains the i2c handler used for implementing
 *               	the pmbus stack
 *
 ********************************************************************/

#include <xc.h>
#include "../mcc_generated_files/i2c1.h"
#include "../inc/Gernirc_Type.h"
#include "../inc/commands.h"
#include "../inc/Myvalue.h"
#include "../inc/pmbus_stack.h"

/************************************************/
/*                   變數區                     */
/************************************************/
uint8_t counter_MWD;
uint8_t counter_MRD;
uint8_t byteCRC;
uint8_t codeCMD;
uint8_t dumpI2CBUF;
uint8_t matrixIndex;
uint8_t protocolCMD;
uint8_t byteNr;
/************************************************/
/*                   結構體                    */
/************************************************/
Flag global_flags = {0, 0, 0};
PMBUS_connect i2c_flags = {0, 0};
/************************************************/
/*                   PTR                        */
/************************************************/
Flag *PTR_global_flags;
PMBUS_connect *PTR_i2c_flags;
ADC_SCAN Adc_raw_data;
Pmbus_Martrix_Index Pmbus_1_3_Index;
/************************************************/

uint8_t buffer[MAX_BYTES + 1];
/************************************************
*   Pmbus_Array 1.3 Version CMD Buffer SIZE    
*   
*   Buffer only delcare Read/Write
*
************************************************/
/*10~1F*/
unsigned char PAGE[1];
unsigned char OPERATION[1];
unsigned char ON_OFF_CONFIG[1];
unsigned char PHASE[1];
unsigned char PAGE_PLUS_READ[2]; 
unsigned char ZONE_CONFIG[2]; 
unsigned char ZONE_ACTIVE[2];
unsigned char WRITE_PROTECT[1];
unsigned char CAPABILITY[1]; 
unsigned char QUERY[2];
unsigned char SMBALERT_MASK[2];

/*20~2F*/
unsigned char VOUT_MODE[1];
unsigned char VOUNT_COMMAND[2];
unsigned char VOUT_TRIM[2];
unsigned char VOUT_CAL_OFFSET[2];
unsigned char VOUT_MAX[2];
unsigned char VOUT_MARGIN_HIGH[1];
unsigned char VOUT_MARGIN_LOW[1];
unsigned char VOUT_TRANSITION_RATE[1];
unsigned char VOUT_DROOP[2];
unsigned char VOUT_SCALE_LOOP[2];
unsigned char VOUT_SCALE_MONITOR[2];
unsigned char VOUT_MIN[2];
/*30~3F*/
unsigned char COEFICIENTS[5];
unsigned char POUT_MAX[2];
unsigned char MAX_DUTY[2];
unsigned char FREQUENCY_SWITCH[2];
unsigned char POWER_MODE[1];
unsigned char VIN_ON[2];
unsigned char VIN_OFF[2];
unsigned char INTERLEAVE[2];
unsigned char IOUT_CAL_GAIN[2];
unsigned char IOUT_CAL_OFFSET[2];
unsigned char FAN_CONFIG_1_2[1];
unsigned char FAN_COMMAND_1[2];
unsigned char FAN_COMMAND_2[2];
unsigned char FAN_CONFIG_3_4[1];
unsigned char FAN_COMMAND_3[2];
unsigned char FAN_COMMAND_4[2];

/*40~4F 4D&4E unused */
unsigned char VOUT_OV_FAULT_LIMIT[2];
unsigned char VOUT_OV_FAULT_RESPONSE[1];
unsigned char VOUT_OV_WARN_LIMIT[2];
unsigned char VOUT_UV_WARN_LIMIT[2];
unsigned char VOUT_UV_FAULT_LIMIT[2];
unsigned char VOUT_UV_FAULT_RESPONSE[1];
unsigned char IOUT_OC_FAULT_LIMIT[2];
unsigned char IOUT_OC_FAULT_RESPONSE[1];
unsigned char IOUT_OC_LV_FAULT_LIMIT[2];
unsigned char IOUT_OC_LV_FAULT_RESPONSE[1];
unsigned char IOUT_OC_WARN_LIMIT[2];
unsigned char IOUT_UC_FAULT_LIMIT[2];
unsigned char IOUT_UC_FAULT_RESPONSE[1];
unsigned char OT_FAULT_LIMIT[2];

/*50~5F*/
unsigned char OT_FAULT_RESPONSE[1];
unsigned char OT_WARN_LIMIT[2];
unsigned char UT_WARN_LIMIT[2];
unsigned char UT_FAULT_LIMIT[2];
unsigned char UT_FAULT_RESPONSE[1];
unsigned char VIN_OV_FAULT_LIMIT[2];
unsigned char VIN_OV_FAULT_RESPONSE[1];
unsigned char VIN_OV_WARN_LIMIT[2];
unsigned char VIN_UV_WARN_LIMIT[2];
unsigned char VIN_UV_FAULT_LIMIT[2];
unsigned char VIN_UV_FAULT_RESPONSE[1];
unsigned char IIN_OC_FAULT_LIMIT[2];
unsigned char IIN_OC_FAULT_RESPONSE[1];
unsigned char IIN_OC_WARN_LIMIT[2];
unsigned char POWER_GOOD_ON[2];
unsigned char POWER_GOOD_OFF[2];

/*60~6B,6C~6F Reserved*/
unsigned char TON_DELAY[2];
unsigned char TON_RISE[2];
unsigned char TON_MAX_FAULT_LIMIT[2];
unsigned char TON_MAX_FAULT_RESPONSE[1];
unsigned char TOFF_DELAY[2];
unsigned char TOFF_FALL[2];
unsigned char TOFF_MAX_WARN_LIMIT[2];
unsigned char POUT_OP_FAULT_LIMIT[2];
unsigned char POUT_OP_FAULT_RESPONSE[1];
unsigned char POUT_OP_WARN_LIMIT[2];
unsigned char PIN_OP_WARN_LIMIT[2];

/*78~7F,70~77Reserved*/
unsigned char STATUS_BYTE[1];
unsigned char STATUS_WORD[2];
unsigned char STATUS_VOUT[1];
unsigned char STATUS_IOUT[1];
unsigned char STATUS_INPUT[1];
unsigned char STATUS_TEMPERATURE[1];
unsigned char STATUS_CML[1];
unsigned char STATUS_OTHER[1];

/*80~8F*/
unsigned char STATUS_MFR_SPECIFIC[1];
unsigned char STATUS_FANS_1_2[1];
unsigned char STATUS_FANS_3_4[1];
unsigned char READ_KWH_IN[4];
unsigned char READ_KWH_OUT[4];
unsigned char READ_KWH_CONFIG[2];
unsigned char READ_EIN[5];
unsigned char READ_EOUT[5];
unsigned char READ_VIN[2];
unsigned char READ_IIN[2];
unsigned char READ_VCAP[2];
unsigned char READ_VOUT[2];
unsigned char READ_IOUT[2];
unsigned char READ_TEMP1[2];
unsigned char READ_TEMP2[2];
unsigned char READ_TEMP3[2];

/*90~9F*/
unsigned char READ_FAN_SPEED_1[2];
unsigned char READ_FAN_SPEED_2[2];
unsigned char READ_FAN_SPEED_3[2];
unsigned char READ_FAN_SPEED_4[2];
unsigned char READ_DUTY_CYCLE[2];
unsigned char READ_FREQUENCY[2];
unsigned char READ_POUT[2];
unsigned char READ_PIN[2];
unsigned char PMBUS_REVISION[1];
unsigned char MFR_ID[1];
unsigned char MFR_MODEL[8];
unsigned char MFR_REVISION[1];
unsigned char MFR_LOCATION[1];
unsigned char MFR_DATE[1];
unsigned char MFR_SERIAL[1];
unsigned char APP_PROFILE_SUPPORT[2];

/*A0~AE,AF Reserved*/
unsigned char MFR_VIN_MIN[2];
unsigned char MFR_VIN_MAX[2];
unsigned char MFR_IIN_MAX[2];
unsigned char MFR_PIN_MAX[2];
unsigned char MFR_VOUT_MIN[2];
unsigned char MFR_VOUT_MAX[2];
unsigned char MFR_IOUT_MAX[2];
unsigned char MFR_POUT_MAX[2];
unsigned char MFR_TAMBIENT_MAX[2];
unsigned char MFR_TAMBIENT_MIN[2];
unsigned char MFR_EFFICIENCY_LL[14];
unsigned char MFR_EFFICIENCY_HL[14];
unsigned char MFR_PIN_ACCURACY[1];
unsigned char IC_DEVICE_ID[2];
unsigned char IC_DEVICE_REV[2];

/*B0~BF*/
unsigned char USER_DATA_00[1];
unsigned char USER_DATA_01[1];
unsigned char USER_DATA_02[1];
unsigned char USER_DATA_03[1];
unsigned char USER_DATA_04[1];
unsigned char USER_DATA_05[1];
unsigned char USER_DATA_06[1];
unsigned char USER_DATA_07[1];
unsigned char USER_DATA_08[1];
unsigned char USER_DATA_09[2];
unsigned char USER_DATA_10[2];
unsigned char USER_DATA_11[2];
unsigned char USER_DATA_12[2];
unsigned char USER_DATA_13[2];
unsigned char USER_DATA_14[2];
unsigned char USER_DATA_15[2];

/*C0~C2*/
unsigned char MFR_MAX_TEMP_1[2];
unsigned char MFR_MAX_TEMP_2[2];
unsigned char MFR_MAX_TEMP_3[2];

typedef struct
{

    char protocol;
    char nr_bytes;
    unsigned char *ptrCommandData;

} command;

command matrix[NR_COMMANDS] = 
{

    /*10~1F*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_BYTE,   0x1, PAGE},         // 0x0 	PAGE 
    {RW_BYTE,   0x1, OPERATION},    // 0x1 	OPERATION
    {RW_BYTE,   0x1, ON_OFF_CONFIG},
    {SEND_BYTE, 0x0, 0x0},          //CLEAR_FAULTS
    {RW_BYTE,   0x1, PHASE},
    {RW_BYTE,   0x1, WRITE_PROTECT},// 0x10 WRITE_POTECT 
    {SEND_BYTE, 0x0, 0x0},          //STORE_DEFAULT_ALL
    {SEND_BYTE, 0x0, 0x0},          //RESTORE_DEFAULT_ALL
     /*20~2F*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_BYTE, 0x1, VOUT_MODE},
    {RW_WORD, 0x2, VOUNT_COMMAND},
    {RW_BYTE, 0x2, VOUT_MAX},
    {RW_BYTE, 0x1, VOUT_MARGIN_HIGH},
    {RW_BYTE, 0x1, VOUT_MARGIN_LOW},
    {RW_BYTE, 0x1, VOUT_TRANSITION_RATE},
    {RW_BYTE, 0x2, VOUT_DROOP},
    {RW_BYTE, 0x2, VOUT_SCALE_LOOP},
    {RW_BYTE, 0x2, VOUT_SCALE_MONITOR},
    {RW_BYTE, 0x2, VOUT_MIN},
 
     /*30~3F*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_BYTE, 0x2, POUT_MAX},
    {RW_BYTE, 0x2, MAX_DUTY},
    {RW_BYTE, 0x2, FREQUENCY_SWITCH},
    {RW_BYTE, 0x1, POWER_MODE},
    {RW_BYTE, 0x2, VIN_ON},
    {RW_BYTE, 0x2, VIN_OFF},
    {RW_BYTE, 0x2, IOUT_CAL_GAIN},
    {RW_BYTE, 0x2, IOUT_CAL_OFFSET},
    {RW_BYTE, 0x1, FAN_CONFIG_1_2},
    {RW_BYTE, 0x2, FAN_COMMAND_1},
    {RW_BYTE, 0x2, FAN_COMMAND_2},
    {RW_BYTE, 0x1, FAN_CONFIG_3_4},
    {RW_BYTE, 0x2, FAN_COMMAND_3},
    {RW_BYTE, 0x2, FAN_COMMAND_4},
 
    /*40~4F*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_BYTE, 0x2, VOUT_OV_FAULT_LIMIT},
    {RW_BYTE, 0x1, VOUT_OV_FAULT_RESPONSE},
    {RW_BYTE, 0x2, VOUT_OV_WARN_LIMIT},
    {RW_BYTE, 0x2, VOUT_UV_WARN_LIMIT},
    {RW_BYTE, 0x2, VOUT_UV_FAULT_LIMIT},
    {RW_BYTE, 0x1, VOUT_UV_FAULT_RESPONSE},
    {RW_BYTE, 0x2, IOUT_OC_FAULT_LIMIT},
    {RW_BYTE, 0x1, IOUT_OC_FAULT_RESPONSE},
    {RW_BYTE, 0x2, IOUT_OC_LV_FAULT_LIMIT},
    {RW_BYTE, 0x1, IOUT_OC_LV_FAULT_RESPONSE},
    {RW_BYTE, 0x2, IOUT_OC_WARN_LIMIT},
    {RW_BYTE, 0x2, IOUT_UC_FAULT_LIMIT},
    {RW_BYTE, 0x1, IOUT_UC_FAULT_RESPONSE},
    {RW_BYTE, 0x2, OT_FAULT_LIMIT},

    /*50~5F*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_BYTE, 0x1, OT_FAULT_RESPONSE},
    {RW_BYTE, 0x2, OT_WARN_LIMIT},
    {RW_BYTE, 0x2, UT_WARN_LIMIT},
    {RW_BYTE, 0x2, UT_FAULT_LIMIT},
    {RW_BYTE, 0x1, UT_FAULT_RESPONSE},
    {RW_BYTE, 0x2, VIN_OV_FAULT_LIMIT},
    {RW_BYTE, 0x1, VIN_OV_FAULT_RESPONSE},
    {RW_BYTE, 0x2, VIN_OV_WARN_LIMIT},
    {RW_BYTE, 0x2, VIN_UV_WARN_LIMIT},
    {RW_BYTE, 0x2, VIN_UV_FAULT_LIMIT},
    {RW_BYTE, 0x1, VIN_UV_FAULT_RESPONSE},
    {RW_BYTE, 0x2, IIN_OC_FAULT_LIMIT},
    {RW_BYTE, 0x1, IOUT_UC_FAULT_RESPONSE},
    {RW_BYTE, 0x2, IIN_OC_WARN_LIMIT},
    {RW_BYTE, 0x2, POWER_GOOD_ON},
    {RW_BYTE, 0x2, POWER_GOOD_OFF},

    /*60~6F*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_BYTE, 0x2, TON_DELAY},
    {RW_BYTE, 0x2, TON_RISE},
    {RW_BYTE, 0x2, TON_MAX_FAULT_LIMIT},
    {RW_BYTE, 0x1, TON_MAX_FAULT_RESPONSE},
    {RW_BYTE, 0x2, TOFF_DELAY},
    {RW_BYTE, 0x2, TOFF_FALL},
    {RW_BYTE, 0x2, TOFF_MAX_WARN_LIMIT},
    {RW_BYTE, 0x2, POUT_OP_FAULT_LIMIT},
    {RW_BYTE, 0x1, POUT_OP_FAULT_RESPONSE},
    {RW_BYTE, 0x2, POUT_OP_WARN_LIMIT},
    {RW_BYTE, 0x2, PIN_OP_WARN_LIMIT},


    /*70~7F*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_BYTE, 0x2, STATUS_WORD},
    {RW_BYTE, 0x1, STATUS_VOUT},
    {RW_BYTE, 0x1, STATUS_IOUT},
    {RW_BYTE, 0x1, STATUS_INPUT},
    {RW_BYTE, 0x1, STATUS_TEMPERATURE},
    {RW_BYTE, 0x1, STATUS_CML},
    {RW_BYTE, 0x1, STATUS_OTHER},


    /*80~8F*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {READ_BYTE, 0x1, STATUS_MFR_SPECIFIC},
    {READ_BYTE, 0x1, STATUS_FANS_1_2},
    {READ_BYTE, 0x1, STATUS_FANS_3_4},
    {READ_BYTE, 0x4, READ_KWH_IN},
    {READ_BYTE, 0x4, READ_KWH_OUT},
    {READ_WORD, 0x2, READ_KWH_CONFIG},
    {RW_BLOCK,  0x5, READ_EIN},
    {RW_BLOCK,  0x5, READ_EOUT},
    {READ_WORD, 0x2, READ_VIN},
    {READ_WORD, 0x2, READ_IIN},
    {READ_WORD, 0x2, READ_VCAP},
    {READ_WORD, 0x2, READ_VOUT},
    {READ_WORD, 0x2, READ_IOUT},
    {READ_WORD, 0x2, READ_TEMP1},
    {READ_WORD, 0x2, READ_TEMP2},
    {READ_WORD, 0x2, READ_TEMP3},

    /*90~9F*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {READ_WORD, 0x2, READ_FAN_SPEED_1},
    {READ_WORD, 0x2, READ_FAN_SPEED_2},
    {READ_WORD, 0x2, READ_FAN_SPEED_3},
    {READ_WORD, 0x2, READ_FAN_SPEED_4},
    {READ_WORD, 0x2, READ_DUTY_CYCLE},
    {READ_WORD, 0x2, READ_FREQUENCY},
    {READ_WORD, 0x2, READ_POUT},
    {READ_WORD, 0x2, READ_PIN},
    {RW_BYTE,   0x1, PMBUS_REVISION},
    {BW_BR_PROC_CALL, 0x1, MFR_ID},
    {BW_BR_PROC_CALL, 0x8, MFR_MODEL},
    {BW_BR_PROC_CALL, 0x1, MFR_REVISION},
    {BW_BR_PROC_CALL, 0x1, MFR_LOCATION},
    {BW_BR_PROC_CALL, 0x1, MFR_DATE},
    {BW_BR_PROC_CALL, 0x1, MFR_SERIAL},
    {BW_BR_PROC_CALL, 0x2, APP_PROFILE_SUPPORT},

    /*A0~AF*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {READ_WORD, 0x2, MFR_VIN_MIN},
    {READ_WORD, 0x2, MFR_VIN_MAX},
    {READ_WORD, 0x2, MFR_IIN_MAX},
    {READ_WORD, 0x2, MFR_PIN_MAX},
    {READ_WORD, 0x2, MFR_VOUT_MIN},
    {READ_WORD, 0x2, MFR_VOUT_MAX},
    {READ_WORD, 0x2, MFR_IOUT_MAX},
    {READ_WORD, 0x2, MFR_POUT_MAX},
    {READ_WORD, 0x2, MFR_TAMBIENT_MAX},
   
    {RW_BLOCK,  0xe, MFR_EFFICIENCY_LL},
    {RW_BLOCK,  0xe, MFR_EFFICIENCY_HL},
    {READ_BYTE, 0x1, MFR_PIN_ACCURACY},
    {RW_BLOCK,  0x2, IC_DEVICE_ID},
    {RW_BLOCK,  0x2, IC_DEVICE_REV},

    
    /*B0~BF Block Write*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_BLOCK, 0x1, USER_DATA_00},
    {RW_BLOCK, 0x1, USER_DATA_01},
    {RW_BLOCK, 0x1, USER_DATA_02},
    {RW_BLOCK, 0x1, USER_DATA_03},
    {RW_BLOCK, 0x1, USER_DATA_04},
    {RW_BLOCK, 0x1, USER_DATA_05},
    {RW_BLOCK, 0x1, USER_DATA_06},
    {RW_BLOCK, 0x1, USER_DATA_07},
    {RW_BLOCK, 0x1, USER_DATA_08},
    {RW_BLOCK, 0x1, USER_DATA_09},
    {RW_BLOCK, 0x1, USER_DATA_10},
    {RW_BLOCK, 0x1, USER_DATA_11},
    {RW_BLOCK, 0x1, USER_DATA_12},
    {RW_BLOCK, 0x1, USER_DATA_13},
    {RW_BLOCK, 0x1, USER_DATA_14},
    {RW_BLOCK, 0x1, USER_DATA_15},

    
     /*C0~C1*/
    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_WORD, 0x2, MFR_MAX_TEMP_1},
    {RW_WORD, 0x2, MFR_MAX_TEMP_2},
    {RW_WORD, 0x2, MFR_MAX_TEMP_3},
};

/********************************************************************
 * Definition of the CMDtoMatrix array. Each command can be found
 * here at an index equal with its command code. Here it is re-defined with another
 * index for the command matrix array.
 * For example command CLEAR_FAULTS has command code 0x3. In this
 * array, at index 0x3, can be found the index of the structure
 * associated with CLEAR_FAULTS in the big array. This index is 0x2.
 *******************************************************************/
const unsigned char CMDtoMatrix[MATRIX_NUMS] =
{
    0,                    // 0x0 	PAGE 
    1,                    // 0x1 	OPERATION
    2,                    // 0x2 	ON_OFF_CONFIG
    3,                    // 0x3 	CLEAR_FAULTS
    4,                    // 0x4 	PHASE code
    UNSUPPORTED_CMD_CODE,                    // 0x5 	PAGE_PLUS_WRITE
    UNSUPPORTED_CMD_CODE,                    // 0x6 	PAGE_PLUS_READ
    UNSUPPORTED_CMD_CODE, // 0x7 	ZONE_CONFIG
    UNSUPPORTED_CMD_CODE, // 0x8 	ZONE_ACTIVE
    UNSUPPORTED_CMD_CODE, // 0x9 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xa 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xb 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xc 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf 	cmd code
    5,                    // 0x10 	WRITE_POTECT 
    6,                   // 0x11 	STORE_DEFAULT_ALL 
    7,                   // 0x12 	RESTORE_DEFAULT_ALL 
    UNSUPPORTED_CMD_CODE,                   // 0x13 	STORE_DEFAULT_CODE
    UNSUPPORTED_CMD_CODE,                   // 0x14 	RESTORE_DEFAULT_CODE
    UNSUPPORTED_CMD_CODE,                   // 0x15 	STORE_USER_ALL
    UNSUPPORTED_CMD_CODE,                   // 0x16 	RESTORE_USER_ALL
    UNSUPPORTED_CMD_CODE,                   // 0x17 	STORE_USER_CODE
    UNSUPPORTED_CMD_CODE,                   // 0x18 	RESTORE_USER_CODE
    UNSUPPORTED_CMD_CODE,                    // 0x19   CAPABILITY
    UNSUPPORTED_CMD_CODE,                    // 0x1a 	QUERY_COMMAND
    UNSUPPORTED_CMD_CODE, // 0x1b 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x1c 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x1d 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x1e 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x1f 	cmd code
    8,                 // 0x20 	VOUT_MODE
    9,                 // 0x21 	VOUT code
    UNSUPPORTED_CMD_CODE,                 // 0x22 	VOUT_TRIM
    UNSUPPORTED_CMD_CODE,                 // 0x23 	VOUT_CAL_OFFSET
    10,                 // 0x24 	VOUT_MAX
    11,                 // 0x25 	VOUT_MARGIN_HIGH
    12,                 // 0x26 	VOUT_MARGIN_LOW
    13,                 // 0x27 	VOUT_TRANSITION_RATE
    14,                 // 0x28 	VOUT_DROOP
    15,                 // 0x29 	VOUT_SCALE_LOOP
    16,                 // 0x2a 	VOUT_SCALE_MONITOR
    17,                 // 0x2b 	VOUT_MIN
    UNSUPPORTED_CMD_CODE, // 0x2c 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x2d 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x2e 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x2f 	cmd code
    UNSUPPORTED_CMD_CODE,                   // 0x30 	COEFICIENTS
    18,                   // 0x31 	POUT_MAX
    19,                   // 0x32 	MAX_DUTY
    20,                   // 0x33 	FREQUENCY_SWITCH
    21,                   // 0x34 	POWER_MODE
    22,                   // 0x35 	VIN_ON 
    23,                   // 0x36 	VIN_OFF 
    UNSUPPORTED_CMD_CODE,                   // 0x37 	INTERLEAVE
    24,                   // 0x38 	IOUT_CAL_GAIN
    25,                   // 0x39 	IOUT_CAL_OFFSET
    26,                   // 0x3a 	FAN_CONFIG_1_2
    27,                   // 0x3b 	FAN_COMMAND_1
    28,                   // 0x3c 	FAN_COMMAND_2
    29,                   // 0x3d 	FAN_CONFIG_3_4
    30,                   // 0x3e 	FAN_COMMAND_3
    31,                   // 0x3f 	FAN_COMMAND_4
    32,                   // 0x40 	VOUT_OV_FAULT_LIMIT 
    33,                   // 0x41 	VOUT_OV_FAULT_RESPONSE
    34,                   // 0x42 	VOUT_OV_WARN_LIMIT
    35,                   // 0x43 	VOUT_UV_WARN_LIMIT
    36,                   // 0x44 	VOUT_UV_FAULT_LIMIT
    37,                   // 0x45 	VOUT_UV_FAULT_RESPONSE
    38,                   // 0x46 	IOUT_OC_FAULT_LIMIT
    39,                   // 0x47 	IOUT_OC_FAULT_RESPONSE
    40,                   // 0x48 	IOUT_OC_LV_FAULT_LIMIT
    41,                   // 0x49 	IOUT_OC_LV_FAULT_RESPONSE
    42,                   // 0x4a 	IOUT_OC_WARN_LIMIT
    43,                   // 0x4b 	IOUT_UC_FAULT_LIMIT 
    44,                   // 0x4c 	IOUT_UC_FAULT_RESPONSE
    UNSUPPORTED_CMD_CODE, // 0x4d 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x4e 	cmd code
    45,                   // 0x4f 	OT_FAULT_LIMIT
    46,                   // 0x50 	OT_FAULT_RESPONSE
    47,                   // 0x51 	OT_WARN_LIMIT
    48,                   // 0x52 	UT_WARN_LIMIT
    49,                   // 0x53 	UT_FAULT_LIMIT
    50,                   // 0x54 	UT_FAULT_RESPONSE
    51,                   // 0x55 	VIN_OV_FAULT_LIMIT
    52,                   // 0x56 	VIN_OV_FAULT_RESPONSE
    53,                   // 0x57 	VIN_OV_WARN_LIMIT
    54,                   // 0x58 	VIN_UV_WARN_LIMIT
    55,                   // 0x59 	VIN_UV_FAULT_LIMIT
    56,                   // 0x5a 	VIN_UV_FAULT_RESPONSE
    57,                   // 0x5b 	IIN_OC_FAULT_LIMIT
    58,                   // 0x5c 	IIN_OC_FAULT_RESPONSE
    59,                   // 0x5d 	IIN_OC_WARN_LIMIT
    60,                   // 0x5e 	POWER_GOOD_ON
    61,                   // 0x5f 	POWER_GOOD_OFF
    62,                   // 0x60 	TON_DELAY
    63,                   // 0x61 	TON_RISE
    64,                   // 0x62 	TON_MAX_FAULT_LIMIT
    65,                   // 0x63 	TON_MAX_FAULT_RESPONSE
    66,                   // 0x64 	TOFF_DELAY
    67,                   // 0x65 	TOFF_FALL
    68,                   // 0x66 	TOFF_MAX_WARN_LIMIT
    UNSUPPORTED_CMD_CODE, // 0x67 	cmd code
    69,                   // 0x68 	POUT_OP_FAULT_LIMIT
    70,                   // 0x69 	POUT_OP_FAULT_RESPONSE
    71,                   // 0x6a 	POUT_OP_WARN_LIMIT
    72,                   // 0x6b 	PIN_OP_WARN_LIMIT
    UNSUPPORTED_CMD_CODE, // 0x6c 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x6d 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x6e 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x6f 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x70 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x71 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x72 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x73 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x74 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x75 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x76 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x77 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x78 	cmd code
    73,                    // 0x79	STATUS_WORD_COMMAND
    74,                    // 0x7a	STATUS_VOUT_COMMAND
    75,                    // 0x7b	STATUS_IOUT_COMMAND
    76,                    // 0x7c	STATUS_INPUT_COMMAND
    77,                    // 0x7d	STATUS_TEMP_COMMAND
    78,                   // 0x7e	STATUS_CML_COMMAND
    79,                   // 0x7f	STATUS_OTHER_COMMAND
    80,                   // 0x80 	STATUS_MFR_SPECIFIC
    81,                   // 0x81	STATUS_FAN_1_2_COMMAND
    82,                   // 0x82	STATUS_FAN_3_4_COMMAND
    83,                   // 0x83 	READ_KWH_IN 
    84,                  // 0x84 	READ_KWH_OUT
    85,                  // 0x85 	READ_KWH_CONFIG
    86,                  // 0x86 	READ_EIN
    87,                  // 0x87 	READ_EOUT
    88,                  // 0x88	READ_VIN_COMMAND
    89,                  // 0x89	READ_IIN_COMMAND
    90,                  // 0x8a 	READ_VCAP_COMMAND
    91,                  // 0x8b	READ_VOUT_COMMAND
    92,                  // 0x8c	READ_IOUT_COMMAND
    93,                  // 0x8d	READ_TEMP1_COMMAND
    94,                  // 0x8e	READ_TEMP2_COMMAND
    95,                  // 0x8f 	READ_TEMP3_COMMAND
    96,                  // 0x90	READ_FAN_SPEED_1_COMMAND
    97,                  // 0x91	READ_FAN_SPEED_2_COMMAND
    98,                  // 0x92 	READ_FAN_SPEED_3_COMMAND
    99,                  // 0x93 	READ_FAN_SPEED_4_COMMAND
    100,                  // 0x94 	READ_DUTY_CYCLE
    101,                  // 0x95 	READ_FREQUENCY
    102,                  // 0x96	READ_POUT_COMMAND
    103,                  // 0x97	READ_PIN_COMMAND
    104,                  // 0x98 	PMBUS_REVISION
    105,                  // 0x99 	MFR_ID 
    106,                  // 0x9a 	MFR_MODEL
    107,                  // 0x9b 	MFR_REVISION
    108,                  // 0x9c 	MFR_LOCATION
    109,                  // 0x9d 	MFR_DATE
    110,                  // 0x9e 	MFR_SERIAL
    111,                  // 0x9f 	APP_PROFILE_SUPPORT
    112,                  // 0xa0	MFR_VIN_MIN
    113,                  // 0xa1	MFR_VIN_MAX
    114,                  // 0xa2	MFR_IIN_MAX
    115,                  // 0xa3	MFR_PIN_MAX
    116,                  // 0xa4	MFR_VOUT_MIN
    117,                  // 0xa5	MFR_VOUT_MAX
    118,                  // 0xa6	MFR_IOUT_MAX
    119,                  // 0xa7	MFR_POUT_MAX
    120,                  // 0xa8	MFR_TAMBIENT_MAX
    UNSUPPORTED_CMD_CODE, // 0xa9 	cmd code
    121,                  // 0xaa 	MFR_EFFICIENCY_LL
    122,                  // 0xab	MFR_EFFICIENCY_HL
    123,                  // 0xac 	MFR_PIN_ACCURACY 
    124,                  // 0xad 	IC_DEVICE_ID 
    125,                  // 0xae 	IC_DEVICE_REV
    UNSUPPORTED_CMD_CODE, // 0xaf 	cmd code
    126,                  // 0xb0 	USER_DATA_00
    127,                  // 0xb1 	USER_DATA_01
    128,                  // 0xb2 	USER_DATA_02
    129,                  // 0xb3 	USER_DATA_03
    130,                  // 0xb4 	USER_DATA_04
    131,                  // 0xb5 	USER_DATA_05
    132,                  // 0xb6 	USER_DATA_06
    133,                  // 0xb7 	USER_DATA_07
    134,                  // 0xb8 	USER_DATA_08
    135,                  // 0xb9 	USER_DATA_09
    136,                  // 0xbA 	USER_DATA_10
    137,                  // 0xbB 	USER_DATA_11
    138,                  // 0xbC 	USER_DATA_12
    139,                  // 0xbD 	USER_DATA_13
    140,                  // 0xbE 	USER_DATA_14
    141,                  // 0xbF 	USER_DATA_15
    142,                  // 0xc0 	MFR_MAX_TEMP_1 
    143,                  // 0xc1 	MFR_MAX_TEMP_2 
    144,                  // 0xc2 	MFR_MAX_TEMP_3 
    UNSUPPORTED_CMD_CODE, // 0xc3 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xc4 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xc5 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xc6 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xc7 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xc8 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xc9 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xcA 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xcB 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xcC 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xcD 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xcE 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xcF 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd0 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd1 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd2 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd3 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd4 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd5 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd6 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd7 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd8 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd9 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xdA 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xdB 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xdC 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xdD 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xdE 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xdF 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe0 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe1 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe2 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe3 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe4 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe5 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe6 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe7 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe8 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe9 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xeA 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xeB 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xeC 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xeD 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xeE 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xeF 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf0 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf1 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf2 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf3 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf4 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf5 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf6 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf7 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf8 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf9 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xfA 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xfB 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xfC 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xfD 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xfE 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xfF 	cmd code

};
/********************************************************************
 * Function:          ClearCommandData
 *
 * PreCondition:      None
 *
 * Input:             None
 *
 * Output:            None
 *
 * Side Effects:    	 None
 *
 * Overview:          Function that can be called from the main application
 *					 to clear the RAM locations for each command
 *
 * Note:              None
 *******************************************************************/
void ClearCommandData(void)
{

    unsigned char i, j;

    for (i = 0; i < NR_COMMANDS; i++)
    {

        for (j = 0; j < matrix[i].nr_bytes; j++)
        {
            *((matrix[i].ptrCommandData) + j) = 0;
        }
    }
}

/********************************************************************
 * Function:         TransmissionContentFaultHandler
 *
 * PreCondition:     None
 *
 * Input:            Token to determine the fault nature.
 *
 * Output:           None
 *
 * Side Effects:     None
 *
 * Overview:         This function modifies stack flags
 *               	and STATUS registers as an action to a present
 *               	data transmission or data content fault.
 *
 * Note:             Cannot be called by main application
 *
 *
 *******************************************************************/

void TransmissionContentFaultHandler(char token)
{
    global_flags.comm_errors = 1;
    global_flags.ready_to_copy = 0;

    switch (token)
    {
    case 1:
        STATUS_WORD[0] |= 0x2; /* Corrupted data(Pec byte error) */
        STATUS_CML[0] |= 0x20;
        break;
    case 2:
        STATUS_WORD[0] |= 0x2; /* Not all bytes received or host reads to many bytes*/
        STATUS_CML[0] |= 0x2;  /* OR Improper address bit in the address byte */
        break;
    case 3:
        STATUS_WORD[0] |= 0x2; /* Host sends too many bytes */
        STATUS_CML[0] |= 0x40;
        break;
    case 4:
        STATUS_WORD[0] |= 0x80; /* Device busy */
        break;
    case 5:
        STATUS_WORD[0] |= 0x2; /* Unsupported commmand code */
        STATUS_CML[0] |= 0x80;
        global_flags.unsupported_command = 1;
        break;
    }
}

/********************************************************************
 * Function:        CopyBufferInRam
 *
 * PreCondition:    A successful PMBUS write transaction took place.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Following a PMBus command being received in a write
 *                  PMBus transaction, this function copies the content
 *                  of the temp BUFFER in the appropriate RAM locations
 *                  of the command
 *
 * Note:            None
 *******************************************************************/

void CopyBufferInRam(void)
{
    unsigned char temp_nr;
    unsigned char i = 0, buffer_offset = 1;

    temp_nr = buffer[0];

    if ((protocolCMD == RW_BLOCK) || (protocolCMD == BW_BR_PROC_CALL))
    {
        buffer_offset = 2; /* First data byte is at buffer[2] */
        --temp_nr;         /* Decrement by one since first byte recieved was the # of bytes to be sent*/

        if (temp_nr != buffer[1])
        {
            TransmissionContentFaultHandler(2);
            return;
        }
    }

    for (i = 0; i < temp_nr; i++)
    {
        *((matrix[matrixIndex].ptrCommandData) + i) = buffer[i + buffer_offset];
    }
}

/********************************************************************
 * Function:        WriteData
 *
 * PreCondition:    The PMBus slave is in a position which requires it
 *                  to put data on the bus.
 *
 * Input:           Data to be put on the bus
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function receives data as a parameter and fills
 *                  the I2CTRN register. At the end it disables the clock stretching
 *                  mechanism.
 *
 * Note:            None
 *******************************************************************/

void WriteData(unsigned char data)
{
    I2C1TRN = data;          /* Data to be transmitted*/
                             //   I2C1CONbits.SCLREL = 1;	/*  33F series Release SCL Clock */
    I2C1CONLbits.SCLREL = 1; /* Release SCL Clock */
}

/********************************************************************
 * Function:        BasicCrc
 *
 * PreCondition:    None
 *
 * Input:           The parameters are the result of the previous
 *                  calculation and the next byte to be added
 *
 * Output:          Result of byteCRC8 calculus
 *
 * Side Effects:    None
 *
 * Overview:        Basic byteCRC8 calculus
 *
 * Note:            None
 *******************************************************************/

unsigned char BasicCrc(unsigned char remainder, unsigned char byte)
{
    char i = 0;

    remainder ^= byte;
    for (i = 8; i > 0; --i)
    {
        if (remainder & 0x80)
        {
            remainder = (remainder << 1) ^ 0x7;
        }
        else
        {
            remainder = (remainder << 1);
        }
    }
    return remainder;
}

/********************************************************************
 * Function:        HostWritesCommandByte
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Function that verifies the validity of the first
 *                  byte received, which is the command code.
 *
 * Note:
 *******************************************************************/

void HostWritesCommandByte(void)
{
    codeCMD = dumpI2CBUF; /* Store off the command code */

    matrixIndex = CMDtoMatrix[dumpI2CBUF];

    if (matrixIndex == UNSUPPORTED_CMD_CODE) /* Verify command code is supported  */
    {
        TransmissionContentFaultHandler(5);
    }
    else
    {
        protocolCMD = matrix[matrixIndex].protocol; /* Determine protocol */
        i2c_flags.flag_rw = 1;
        byteCRC = BasicCrc(byteCRC, dumpI2CBUF);
    }
}

/********************************************************************
 * Function:        HostWritesNextBytes
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Function to process the remaining bytes received
 *                  by the slave.
 *
 * Note:            None
 *******************************************************************/
void HostWritesNextBytes(void)
{
    char extra_bytes = 1; /* If extra byte is received then need to check CRC */

    ++buffer[0]; /* Increment buffer[0] since data byte received */

    if (protocolCMD == RW_BLOCK)
    {
        extra_bytes = 2; /* Need to add 2 extra bytes: # of bytes to be sent and CRC byte*/
    }

    if ((buffer[0] == matrix[matrixIndex].nr_bytes + extra_bytes) && (protocolCMD != BW_BR_PROC_CALL))
    {
        if (dumpI2CBUF != byteCRC)
        {
            TransmissionContentFaultHandler(1); /* Wrong pec byte */
        }

        --buffer[0]; /* Remove CRC from Buffer[0] count */
    }

    else
    {
        i2c_flags.wr_prot = 1;
        byteCRC = BasicCrc(byteCRC, dumpI2CBUF);
        buffer[counter_MWD] = dumpI2CBUF;
    }
}

/********************************************************************
 * Function:        HostReadsAddr
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Function that is processed after the slave
 *                  has ACKed its address following a read
 *                  address by the host.
 *
 * Note:            None
 *******************************************************************/
void HostReadsAddr()
{

    byteNr = matrix[matrixIndex].nr_bytes;
    byteCRC = BasicCrc(byteCRC, dumpI2CBUF);

    switch (protocolCMD)
    {
    case BW_BR_PROC_CALL:

        CopyBufferInRam();
        // byteNr = Example_APP_func(codeCMD);   /* App function call Returns # of bytes to be read*/

    case RW_BLOCK:

        byteCRC = BasicCrc(byteCRC, byteNr);
        dumpI2CBUF = byteNr;

        break;

        /* Covers READ_BYTE, RW_BYTE, READ_WORD, and RW_WORD */
    case RW_BYTE:
    case RW_WORD:

        counter_MRD = 1;
        dumpI2CBUF = *(matrix[matrixIndex].ptrCommandData);
        byteCRC = BasicCrc(byteCRC, dumpI2CBUF);

        break;

    case SEND_BYTE: /* Not supported protocols */

        global_flags.comm_errors = 1;
        dumpI2CBUF = 0xFF;

        break;
    }

    WriteData(dumpI2CBUF);
}
/********************************************************************
 * Function:        HostReadsData
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        As the host keeps ACKing bytes sent by the slave,
 *                  this function takes valid data and puts it on the
 *                  bus, checking at the same time for the validity
 *                  of the host's request for more data bytes
 *
 * Note:            None
 *******************************************************************/

void HostReadsData()
{
    if (counter_MRD < byteNr)
    {
        dumpI2CBUF = *((matrix[matrixIndex].ptrCommandData) + counter_MRD);
        byteCRC = BasicCrc(byteCRC, dumpI2CBUF);
        WriteData(dumpI2CBUF);
    }

    else if (counter_MRD == byteNr)
    {
        WriteData(byteCRC);
    }

    else
    {
        TransmissionContentFaultHandler(2);
        WriteData(0xFF);
    }
}

/********************************************************************
 * Function:        I2CSlaveHandler
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Function called from the main application as a source
 *                  of interrupt from the I2C (SI2CIF flag) module has been
 *                  detected. This function achieves the functionality of
 *                  the I2C slave 7bit address
 *
 * Note:           slaver 控制器
 *******************************************************************/

void I2CSlaveHandler(void)
{
    char mask = 0x26;
    char token = 0;

    token = I2C1STAT & mask;
    dumpI2CBUF = I2C1RCV;

    switch (token)
    {
    case MasterWritesAddress: /* MASTER WRITES ADDRESS STATE */
                              /* 寫入地址校驗 */
        byteCRC = BasicCrc(0, dumpI2CBUF);
        buffer[0] = 0;
        /* 旗標清理 */
        global_flags.ready_to_copy = 0;
        global_flags.comm_errors = 0;
        global_flags.unsupported_command = 0;

        i2c_flags.wr_prot = 0;
        i2c_flags.flag_rw = 0;

        protocolCMD = 0;
        byteNr = 0;
        counter_MRD = 0;
        counter_MWD = 0;

        T1CONbits.TON = 1; /* Timer used to determine when a stop bit is detected */

        break;

    case MasterWritesData: /* MASTER WRITES DATA STATE */

        if (global_flags.comm_errors == 0)
        {
            if (counter_MWD == 0)
            {
                HostWritesCommandByte(); /*I2C CMD READ/WRITE*/
            }

            else
            {
                HostWritesNextBytes();
            }

            counter_MWD++;
        }

        break;

    case MasterReadsAddress: /* MASTER READS ADDRESS STATE */

        if ((i2c_flags.flag_rw == 1) && (global_flags.comm_errors == 0))
        {
            HostReadsAddr(); /* Address write ACKed and codeCMD received */
        }
        else
        {
            TransmissionContentFaultHandler(2); /* Improper address bit in the address byte */
            WriteData(0xFF);                    /* 錯誤代碼 &  clear memory block */
        }
        break;

    case MasterReadsData: /* MASTER READS DATA STATE */

        if (global_flags.comm_errors == 0)
        {
            HostReadsData();
            ++counter_MRD; /* Increment read counter */
        }

        else
        {
            WriteData(0xFF);
        }

        break;
    }

    //   I2C1CONbits.SCLREL = 1;			/* F series Release SCL Clock */
    I2C1CONLbits.SCLREL = 1; /* Release SCL Clock */
}

/********************************************************************
 * Function:        33F_series_Timer3 ISR/33CK_Timer1
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This interruput service routine determines when a
 *				   stop condition has occured and enables buffer to ram
 *				   copy if the command was a write protocol.
 *
 * Note:            None
 *******************************************************************/
// void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt()
// void __attribute__((weak)) TMR1_CallBack(void)
// {
//     IFS0bits.T1IF = 0; /* Clear Interrupt Flag */
//     TMR1 = 0;

//     if ((I2C1STATbits.P == 1) && (IFS1bits.SI2C1IF == 0))
//     {
//         T1CONbits.TON = 0;

//         if (((i2c_flags.wr_prot == 1) || (protocolCMD == 0x0)) && (global_flags.comm_errors == 0) && (protocolCMD != BW_BR_PROC_CALL))
//         {
//             if (codeCMD == 0x3) /* Example of call to an APP function */
//             {
//                 //				Clear_faults();
//             }

//             global_flags.ready_to_copy = 1; /* If command was write transaction setting this flag allows
//                                                     data to be copied from buffer to RAM */
//         }

//         i2c_flags.flag_rw = 0;

//         //		I2C1CONbits.SCLREL = 1;		/*33F series  Release SCL Clock */
//         I2C1CONLbits.SCLREL = 1; /* Release SCL Clock */
//     }
// }
/********************************************************************
 * Function:        Clear_faults
 *
 * PreCondition:    Appropriate action generated by the host(e.g. CLEAR_FAULTS
 *                  command received)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is supplied to the application as a mean to clear
 *                  the STATUS registers following the appropriate action generated
 *                  by the host.
 *
 * Note:            Must be placed in an application file
 *******************************************************************/
void Clear_faults(void)
{
   STATUS_WORD[0] = 0;
    STATUS_WORD[1] = 0;
    STATUS_VOUT[0] = 0;
    STATUS_IOUT[0] = 0;
    STATUS_INPUT[0] = 0;
    STATUS_TEMPERATURE[0] = 0;
    STATUS_CML[0] = 0;
    STATUS_OTHER[0] = 0;
    STATUS_FANS_1_2[0] = 0;
    STATUS_FANS_3_4[0] = 0;
}
/********************************************************************
 * Function:        call back function for Timer1
 *
 * Parameter:     uint8_t *pdata    I2C 寫入 data
 *                uint8_t length    Data 大小
 *                uint16_t address  Salver 地址
 *                I2C1_MESSAGE_STATUS *pstatus  I2C狀態
 *
 * Note:            Testting Callback I2C function
 *******************************************************************/
void I2C_Fun(void)
{

    // I2C1_MasterWrite(&writeBuffer,1,TEST_ADDR,I2C1_MESSAGE_COMPLETE);
}
/********************************************************************
 * Function:        初始化 struct class
 *
 *
 * Note:
 *******************************************************************/
void Init_Struct_Fun(void)
{
    /*Variable*/
    counter_MWD = 0;
    counter_MRD = 0;
    byteCRC = 0;
    codeCMD = 0;
    dumpI2CBUF = 0;
    matrixIndex = 0;
    protocolCMD = 0;
    byteNr = 0;

    /* struct */
    PTR_global_flags=&global_flags;
    PTR_i2c_flags=&i2c_flags;
}
/********************************************************************
 *
 * PreCondition:    Linear11     5bit 2's complement 
 *
 * Input:           number      : User Data
 *                  exponent    : Resloution Select  
 * 
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:       
 *
 * Note:          
 *******************************************************************/
uint16_t linear11(uint16_t adcValue,int8 exponent)
{
    static uint16_t Real_data = 0;
    uint16_t mantissa = 0;
    // int exponent = -3;  

    // Convert ADC value back to real voltage value (e.g., in volts).
    // Real_data = __builtin_muluu(adcValue, Volt_2_CNT);
    // Adc_raw_data.Vdc =  (adcValue*483)>>12;
  
    // Adjust Real_data as needed to calculate mantissa.
    mantissa = adcValue << exponent;

    // Ensure the mantissa fits within 11 bits.
    mantissa &= 0x07FF;

    // Handle exponent as 2's complement in 5 bits.
    exponent = (0-exponent) & 0x1F;

    // Combine exponent and mantissa.
    return (mantissa | (exponent << 11));
}
/********************************************************************
 *
 * PreCondition:    Linear16
 *
 * Input:           real_data   
 *                  exponent    
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:       
 *
 * Note:          12Vdc only
 *******************************************************************/
uint16_t linear16(uint16_t real_data, uint8_t exponent)
{
    static uint16_t linear16_Data = 0;
	/* real value multipi a gain  */
    linear16_Data = real_data << exponent;

	return linear16_Data;
}

/********************************************************************
 *
 * PreCondition:    Update_Martix_Buffer_Data
 *
 * Input:           data            User data needs write into buffer
 *                  buffer          Store in the ADDR
 *                  matrixIndex     index of Buffer
 * 
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:       select linear11 / 16 to convert pmbus formant
 *
 * Note:          
 *******************************************************************/
void Update_Martix_Buffer_Data(uint16_t data,uint8_t *buffer,FormatType Linear_select,int8 exponent,Pmbus_Martrix_Index Pmbus_1_3_Index)
{
    static uint16_t convert_data=0;
    if (Linear_select==LINEAR11)
    {
      Adc_raw_data.pmbus_data = linear11(data,exponent);
    }
    else if (Linear_select==LINEAR16)
    {
      Adc_raw_data.pmbus_data = linear16(data,exponent);
    }
    
    //ptr  func  linear 11/16
    // convert_data= adc_to_slinear11(data,12);
    // 高位字節
    buffer[0] = (Adc_raw_data.pmbus_data >> 8) & 0xFF;
    // 低位字節
    buffer[1] = Adc_raw_data.pmbus_data & 0xFF;

    matrix[Pmbus_1_3_Index].ptrCommandData = buffer;
}

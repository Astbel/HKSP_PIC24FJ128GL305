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
-----------------------------------------------*/

#define NR_COMMANDS 44

#define UNSUPPORTED_CMD_CODE 0xFF
#define MAX_BYTES 16
/*buffer 需要另外定義這導致IDE 錯誤*/
uint8_t buffer[MAX_BYTES + 1];


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
     Command Codes
 --------------------------------------------------*/

#define OPERATION_COMMAND 			0x1
#define ON_OFF_CONFIG_COMMAND 		0x2
#define CLEAR_FAULTS_COMMAND 		0x3
#define CAPABILITY_COMMAND			0x19
#define QUERY_COMMAND				0x1A
#define FAN_CONFIG_1_2_COMMAND		0x3A
#define FAN_COMMAND_1_COMMAND		0x3b
#define FAN_COMMAND_2_COMMAND		0x3c
#define IOUT_OC_WARN_LIMIT_COMMAND	0x4A
#define OT_WARN_LIMIT_COMMAND		0x51
#define IIN_OC_WARN_LIMIT_COMMAND	0x5d		
#define POUT_OP_WARN_LIMIT_COMMAND	0x6a
#define PIN_OP_WARN_LIMIT_COMMAND	0x6b
#define STATUS_WORD_COMMAND 		0x79
#define STATUS_VOUT_COMMAND 		0x7a
#define STATUS_IOUT_COMMAND 		0x7b
#define STATUS_INPUT_COMMAND 		0x7c
#define STATUS_TEMP_COMMAND 		0x7d
#define STATUS_CML_COMMAND 			0x7e
#define STATUS_OTHER_COMMAND 		0x7f
#define STATUS_FAN_1_2_COMMAND 		0x81
#define STATUS_FAN_3_4_COMMAND 		0x82
#define READ_VIN_COMMAND 			0x88
#define READ_IIN_COMMAND 			0x89
#define READ_VOUT_COMMAND 			0x8b
#define READ_IOUT_COMMAND 			0x8c
#define READ_TEMP1_COMMAND 			0x8d
#define READ_TEMP2_COMMAND 			0x8e
#define READ_FAN_SPEED_1_COMMAND 	0x90
#define READ_FAN_SPEED_2_COMMAND 	0x91
#define READ_POUT_COMMAND 			0x96
#define READ_PIN_COMMAND 			0x97
#define PMBUS_REVISION_COMMAND		0x98
#define MFR_VIN_MIN_COMMAND			0xA0
#define MFR_VIN_MAX_COMMAND			0xA1
#define MFR_IIN_MAX_COMMAND			0xA2
#define MFR_PIN_MAX_COMMAND			0xA3
#define MFR_VOUT_MIN_COMMAND		0xA4
#define MFR_VOUT_MAX_COMMAND		0xA5
#define MFR_IOUT_MAX_COMMAND		0xA6
#define MFR_POUT_MAX_COMMAND		0xA7
#define MFR_TAMBIENT_MAX_COMMAND	0xA8
#define MFR_EFFICIENCY_LL_COMMAND 	0xAA
#define MFR_EFFICIENCY_HL_COMMAND 	0xAB


























#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TEMPLATE_H */



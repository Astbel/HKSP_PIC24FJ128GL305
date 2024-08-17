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

/************************************************/
unsigned char OPERATION[1];
unsigned char ON_OFF_CONFIG[1];
unsigned char QUERY[2];
/* CLEAR_FAULTS has no associated array */
unsigned char STATUS_WORD[2];
unsigned char STATUS_VOUT[2];
unsigned char STATUS_IOUT[1];
unsigned char STATUS_INPUT[1];
unsigned char STATUS_TEMP[1];
unsigned char STATUS_CML[1];
unsigned char STATUS_OTHER[1];
unsigned char STATUS_FAN_1_2[1];
unsigned char STATUS_FAN_3_4[1];
unsigned char READ_VIN[2];
unsigned char READ_IIN[2];
unsigned char READ_VOUT[2];
unsigned char READ_IOUT[2];
unsigned char READ_TEMP1[2];
unsigned char READ_TEMP2[2];
unsigned char READ_FAN_SPEED_1[2];
unsigned char READ_FAN_SPEED_2[2];
unsigned char READ_POUT[2];
unsigned char READ_PIN[2];
unsigned char MFR_VIN_MIN[2];
unsigned char MFR_VIN_MAX[2];
unsigned char MFR_IIN_MAX[2];
unsigned char MFR_PIN_MAX[2];
unsigned char MFR_VOUT_MIN[2];
unsigned char MFR_VOUT_MAX[2];
unsigned char MFR_IOUT_MAX[2];
unsigned char MFR_POUT_MAX[2];
unsigned char MFR_TAMBIENT_MAX[2];
unsigned char MFR_EFFICIENCY_LL[14];
unsigned char MFR_EFFICIENCY_HL[14];
unsigned char IOUT_OC_WARN_LIMIT[2];
unsigned char FAN_CONFIG_1_2[1];
unsigned char FAN_COMMAND_1[2];
unsigned char FAN_COMMAND_2[2];
unsigned char OT_WARN_LIMIT[2];
unsigned char IIN_OC_WARN_LIMIT[2];
unsigned char POUT_OP_WARN_LIMIT[2];
unsigned char PIN_OP_WARN_LIMIT[2];
unsigned char CAPABILITY[1];
unsigned char PMBUS_REVISION[1];

typedef struct
{

    char protocol;
    char nr_bytes;
    unsigned char *ptrCommandData;

} command;

const command matrix[44] = {

    /* Protocol----------Nr_bytes-------Command_ram_index--*/
    {RW_BYTE, 0x1, OPERATION},
    {RW_BYTE, 0x1, ON_OFF_CONFIG},
    {SEND_BYTE, 0x0, 0x0},
    {BW_BR_PROC_CALL, 0x1, QUERY},
    {READ_BYTE, 0x1, CAPABILITY},
    {READ_WORD, 0x2, STATUS_WORD},
    {READ_BYTE, 0x2, STATUS_VOUT},
    {READ_BYTE, 0x1, STATUS_IOUT},
    {READ_BYTE, 0x1, STATUS_INPUT},
    {READ_BYTE, 0x1, STATUS_TEMP},
    {READ_BYTE, 0x1, STATUS_CML},
    {READ_BYTE, 0x1, STATUS_OTHER},
    {READ_BYTE, 0x1, STATUS_FAN_1_2},
    {READ_BYTE, 0x1, STATUS_FAN_3_4},
    {READ_WORD, 0x2, READ_VIN},
    {READ_WORD, 0x2, READ_IIN},
    {READ_WORD, 0x2, READ_VOUT},
    {READ_WORD, 0x2, READ_IOUT},
    {READ_WORD, 0x2, READ_TEMP1},
    {READ_WORD, 0x2, READ_TEMP2},
    {READ_WORD, 0x2, READ_FAN_SPEED_1},
    {READ_WORD, 0x2, READ_FAN_SPEED_2},
    {READ_WORD, 0x2, READ_POUT},
    {READ_WORD, 0x2, READ_PIN},
    {READ_WORD, 0x2, MFR_VIN_MIN},
    {READ_WORD, 0x2, MFR_VIN_MAX},
    {READ_WORD, 0x2, MFR_IIN_MAX},
    {READ_WORD, 0x2, MFR_PIN_MAX},
    {READ_WORD, 0x2, MFR_VOUT_MIN},
    {READ_WORD, 0x2, MFR_VOUT_MAX},
    {READ_WORD, 0x2, MFR_IOUT_MAX},
    {READ_WORD, 0x2, MFR_POUT_MAX},
    {READ_WORD, 0x2, MFR_TAMBIENT_MAX},
    {RW_BLOCK, 0xe, MFR_EFFICIENCY_LL},
    {RW_BLOCK, 0xe, MFR_EFFICIENCY_HL},
    {RW_WORD, 0x2, IOUT_OC_WARN_LIMIT},
    {RW_BYTE, 0x1, FAN_CONFIG_1_2},
    {RW_WORD, 0x2, FAN_COMMAND_1},
    {RW_WORD, 0x2, FAN_COMMAND_2},
    {RW_WORD, 0x2, OT_WARN_LIMIT},
    {RW_WORD, 0x2, IIN_OC_WARN_LIMIT},
    {RW_WORD, 0x2, POUT_OP_WARN_LIMIT},
    {RW_WORD, 0x2, PIN_OP_WARN_LIMIT},
    {READ_BYTE, 0x1, PMBUS_REVISION}

};

/********************************************************************
 * Definition of the CMDtoMatrix array. Each command can be found
 * here at an index equal with its command code. Here it is re-defined with another
 * index for the command matrix array.
 * For example command CLEAR_FAULTS has command code 0x3. In this
 * array, at index 0x3, can be found the index of the structure
 * associated with CLEAR_FAULTS in the big array. This index is 0x2.
 *******************************************************************/
const unsigned char CMDtoMatrix[255] = {
    UNSUPPORTED_CMD_CODE, // 0x0 	cmd code
    0,                    // 0x1 	OPERATION
    1,                    // 0x2 	ON_OFF_CONFIG
    2,                    // 0x3 	CLEAR_FAULTS
    UNSUPPORTED_CMD_CODE, // 0x4 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x5 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x6 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x7 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x8 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x9 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xa 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xb 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xc 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xd 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xe 	cmd code
    UNSUPPORTED_CMD_CODE, // 0xf 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x10 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x11 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x12 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x13 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x14 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x15 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x16 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x17 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x18 	cmd code
    4,                    // 0x19  CAPABILITY
    3,                    // 0x1a 	QUERY_COMMAND
    UNSUPPORTED_CMD_CODE, // 0x1b 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x1c 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x1d 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x1e 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x1f 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x20 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x21 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x22 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x23 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x24 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x25 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x26 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x27 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x28 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x29 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x2a 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x2b 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x2c 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x2d 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x2e 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x2f 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x30 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x31 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x32 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x33 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x34 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x35 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x36 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x37 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x38 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x39 	cmd code
    36,                   // 0x3a 	FAN_CONFIG_1_2
    37,                   // 0x3b 	FAN_COMMAND_1
    38,                   // 0x3c 	FAN_COMMAND_2
    UNSUPPORTED_CMD_CODE, // 0x3d 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x3e 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x3f 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x40 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x41 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x42 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x43 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x44 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x45 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x46 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x47 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x48 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x49 	cmd code
    35,                   // 0x4a 	IOUT_OC_WARN_LIMIT
    UNSUPPORTED_CMD_CODE, // 0x4b 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x4c 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x4d 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x4e 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x4f 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x50 	cmd code
    39,                   // 0x51 	OT_WARN_LIMIT
    UNSUPPORTED_CMD_CODE, // 0x52 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x53 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x54 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x55 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x56 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x57 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x58 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x59 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x5a 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x5b 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x5c 	cmd code
    40,                   // 0x5d 	IIN_OC_WARN_LIMIT
    UNSUPPORTED_CMD_CODE, // 0x5e 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x5f 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x60 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x61 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x62 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x63 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x64 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x65 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x66 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x67 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x68 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x69 	cmd code
    41,                   // 0x6a 	POUT_OP_WARN_LIMIT
    42,                   // 0x6b 	PIN_OP_WARN_LIMIT
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
    5,                    // 0x79	STATUS_WORD_COMMAND
    6,                    // 0x7a	STATUS_VOUT_COMMAND
    7,                    // 0x7b	STATUS_IOUT_COMMAND
    8,                    // 0x7c	STATUS_INPUT_COMMAND
    9,                    // 0x7d	STATUS_TEMP_COMMAND
    10,                   // 0x7e	STATUS_CML_COMMAND
    11,                   // 0x7f	STATUS_OTHER_COMMAND
    UNSUPPORTED_CMD_CODE, // 0x80 	cmd code
    12,                   // 0x81	STATUS_FAN_1_2_COMMAND
    13,                   // 0x82	STATUS_FAN_3_4_COMMAND
    UNSUPPORTED_CMD_CODE, // 0x83 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x84 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x85 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x86 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x87 	cmd code
    14,                   // 0x88	READ_VIN_COMMAND
    15,                   // 0x89	READ_IIN_COMMAND
    UNSUPPORTED_CMD_CODE, // 0x8a 	cmd code
    16,                   // 0x8b	READ_VOUT_COMMAND
    17,                   // 0x8c	READ_IOUT_COMMAND
    18,                   // 0x8d	READ_TEMP1_COMMAND
    19,                   // 0x8e	READ_TEMP2_COMMAND
    UNSUPPORTED_CMD_CODE, // 0x8f 	cmd code
    20,                   // 0x90	READ_FAN_SPEED_1_COMMAND
    21,                   // 0x91	READ_FAN_SPEED_2_COMMAND
    UNSUPPORTED_CMD_CODE, // 0x92 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x93 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x94 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x95 	cmd code
    22,                   // 0x96	READ_POUT_COMMAND
    23,                   // 0x97	READ_PIN_COMMAND
    43,                   // 0x98 	PMBUS_REVISION
    UNSUPPORTED_CMD_CODE, // 0x99 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x9a 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x9b 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x9c 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x9d 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x9e 	cmd code
    UNSUPPORTED_CMD_CODE, // 0x9f 	cmd code
    24,                   // 0xa0	MFR_VIN_MIN
    25,                   // 0xa1	MFR_VIN_MAX
    26,                   // 0xa2	MFR_IIN_MAX
    27,                   // 0xa3	MFR_PIN_MAX
    28,                   // 0xa4	MFR_VOUT_MIN
    29,                   // 0xa5	MFR_VOUT_MAX
    30,                   // 0xa6	MFR_IOUT_MAX
    31,                   // 0xa7	MFR_POUT_MAX
    32,                   // 0xa8	MFR_TAMBIENT_MAX
    UNSUPPORTED_CMD_CODE, // 0xa9 	cmd code
    33,                   // 0xaa 	MFR_EFFICIENCY_LL
    34,                   // 0xab	MFR_EFFICIENCY_HL

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
    STATUS_TEMP[0] = 0;
    STATUS_CML[0] = 0;
    STATUS_OTHER[0] = 0;
    STATUS_FAN_1_2[0] = 0;
    STATUS_FAN_3_4[0] = 0;
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

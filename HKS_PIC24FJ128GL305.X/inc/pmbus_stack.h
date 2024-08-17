#ifndef PMBUS_STACK_H
#define PMBUS_STACK_H

/*-----------------------------------------------
    include files
-----------------------------------------------*/
#include "MyHeader.h"

/*-----------------------------------------------
    type_def
-----------------------------------------------*/
#define MasterWritesAddress 0x2
#define MasterWritesData 0x22
#define MasterReadsAddress 0x6
#define MasterReadsData 0x24
/*-----------------------------------------------
    Struct Enum  Uion
-----------------------------------------------*/
typedef struct 
{
    uint8_t  ready_to_copy;
    uint8_t  comm_errors;
    uint8_t  unsupported_command;
}Flag ;

typedef struct 
{
    uint8_t flag_rw;
    uint8_t wr_prot;
}PMBUS_connect;

/*-----------------------------------------------
 Struct Enum  Uion
-----------------------------------------------*/
extern Flag global_flags;
extern PMBUS_connect i2c_flags;
/*-----------------------------------------------
    Ptr Struct Enum  Uion
-----------------------------------------------*/
extern Flag *PTR_global_flags;
extern PMBUS_connect *PTR_i2c_flags;

/*-----------------------------------------------
    Variable
-----------------------------------------------*/
extern uint8_t counter_MWD;
extern uint8_t counter_MRD;
extern uint8_t byteCRC;
extern uint8_t codeCMD;
extern uint8_t dumpI2CBUF;
extern uint8_t matrixIndex;
extern uint8_t protocolCMD;
extern uint8_t byteNr;

extern unsigned char codeCMD;
extern unsigned int  ram_index;
extern unsigned char protocol;
extern unsigned char nr_bytes;
extern unsigned char device_busy;
extern unsigned char buffer[];
/*字節大小*/
extern unsigned char OPERATION[1];
extern unsigned char ON_OFF_CONFIG[1];
extern unsigned char QUERRY[2];
extern unsigned char STATUS_WORD[2];
extern unsigned char STATUS_VOUT[2];
extern unsigned char STATUS_IOUT[1];
extern unsigned char STATUS_INPUT[1];
extern unsigned char STATUS_TEMP[1];
extern unsigned char STATUS_CML[1];
extern unsigned char STATUS_OTHER[1];
extern unsigned char STATUS_FAN_1_2[1];
extern unsigned char STATUS_FAN_3_4[1];
extern unsigned char READ_VIN[2];
extern unsigned char READ_IIN[2];
extern unsigned char READ_VOUT[2];
extern unsigned char READ_IOUT[2];
extern unsigned char READ_TEMP1[2];
extern unsigned char READ_TEMP2[2];
extern unsigned char READ_FAN_SPEED_1[2];
extern unsigned char READ_FAN_SPEED_2[2];
extern unsigned char READ_POUT[2];
extern unsigned char READ_PIN[2];
extern unsigned char MFR_VIN_MIN[2];
extern unsigned char MFR_VIN_MAX[2];
extern unsigned char MFR_IIN_MAX[2];
extern unsigned char MFR_PIN_MAX[2];
extern unsigned char MFR_VOUT_MIN[2];
extern unsigned char MFR_VOUT_MAX[2];
extern unsigned char MFR_IOUT_MAX[2];
extern unsigned char MFR_POUT_MAX[2];
extern unsigned char MFR_TAMBIENT_MAX[2];
extern unsigned char MFR_EFFICIENCY_LL[14];
extern unsigned char MFR_EFFICIENCY_HL[14];
extern unsigned char IOUT_OC_WARN_LIMIT[2];
extern unsigned char FAN_CONFIG_1_2[1];
extern unsigned char FAN_COMMAND_1[2];
extern unsigned char FAN_COMMAND_2[2];
extern unsigned char OT_WARN_LIMIT[2];
extern unsigned char IIN_OC_WARN_LIMIT[2];
extern unsigned char POUT_OP_WARN_LIMIT[2];
extern unsigned char PIN_OP_WARN_LIMIT[2];
extern unsigned char CAPABILITY[1];
extern unsigned char PMBUS_REVISION[1];
/*-----------------------------------------------
   public func
-----------------------------------------------*/
void I2C_Fun(void);
void I2CSlaveHandler(void);
void Clear_faults(void);
void HostWritesCommandByte(void);
void HostWritesNextBytes(void);
void HostReadsAddr(void);
void HostReadsData(void);
void TransmissionContentFaultHandler(char token);
void Clear_faults(void);
void Init_Struct_Fun(void);
char Example_APP_func(unsigned char codeCMD);
void ClearCommandData(void);
void CopyBufferInRam(void);


#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#endif /* TEMPLATE_H */

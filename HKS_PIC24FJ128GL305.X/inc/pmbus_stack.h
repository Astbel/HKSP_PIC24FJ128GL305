#ifndef PMBUS_STACK_H
#define PMBUS_STACK_H

/*-----------------------------------------------
    include files
-----------------------------------------------*/
#include "MyHeader.h"
#include "commands.h"
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
}Flag;
typedef struct 
{
    uint8_t flag_rw;
    uint8_t wr_prot;
}PMBUS_connect;
typedef enum 
{
    LINEAR11,
    LINEAR16
} FormatType;
typedef struct
{
    uint16_t data;
    uint8_t *buffer;
    FormatType linear_select;
    int8 exponent;
    Pmbus_Martrix_Index pmbus_index;
} UpdateParams;

/*-----------------------------------------------
 Struct Enum  Uion
-----------------------------------------------*/
extern Flag global_flags;
extern PMBUS_connect i2c_flags;
extern FormatType   Linear_select;
extern UpdateParams Pmbus_Updata;
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
/*pmbus 1.3.1 spec declare*/
/*10~1F*/
extern unsigned char PAGE[1];
extern unsigned char OPERATION[1];
extern unsigned char ON_OFF_CONFIG[1];
extern unsigned char PHASE[1];
extern unsigned char PAGE_PLUS_READ[2];
extern unsigned char ZONE_CONFIG[2];
extern unsigned char ZONE_ACTIVE[2];
extern unsigned char WRITE_PROTECT[1];
extern unsigned char CAPABILITY[1];
extern unsigned char QUERY[2];
extern unsigned char SMBALERT_MASK[2];

/*20~2F*/
extern unsigned char VOUT_MODE[1];
extern unsigned char VOUNT_COMMAND[2];
extern unsigned char VOUT_TRIM[2];
extern unsigned char VOUT_CAL_OFFSET[2];
extern unsigned char VOUT_MAX[2];
extern unsigned char VOUT_MARGIN_HIGH[1];
extern unsigned char VOUT_MARGIN_LOW[1];
extern unsigned char VOUT_TRANSITION_RATE[1];
extern unsigned char VOUT_DROOP[2];
extern unsigned char VOUT_SCALE_LOOP[2];
extern unsigned char VOUT_SCALE_MONITOR[2];
extern unsigned char VOUT_MIN[2];

/*30~3F*/
extern unsigned char COEFICIENTS[5];
extern unsigned char POUT_MAX[2];
extern unsigned char MAX_DUTY[2];
extern unsigned char FREQUENCY_SWITCH[2];
extern unsigned char POWER_MODE[1];
extern unsigned char VIN_ON[2];
extern unsigned char VIN_OFF[2];
extern unsigned char INTERLEAVE[2];
extern unsigned char IOUT_CAL_GAIN[2];
extern unsigned char IOUT_CAL_OFFSET[2];
extern unsigned char FAN_CONFIG_1_2[1];
extern unsigned char FAN_COMMAND_1[2];
extern unsigned char FAN_COMMAND_2[2];
extern unsigned char FAN_CONFIG_3_4[1];
extern unsigned char FAN_COMMAND_3[2];
extern unsigned char FAN_COMMAND_4[2];

/*40~4F 4D&4E unused */
extern unsigned char VOUT_OV_FAULT_LIMIT[2];
extern unsigned char VOUT_OV_FAULT_RESPONSE[1];
extern unsigned char VOUT_OV_WARN_LIMIT[2];
extern unsigned char VOUT_UV_WARN_LIMIT[2];
extern unsigned char VOUT_UV_FAULT_LIMIT[2];
extern unsigned char VOUT_UV_FAULT_RESPONSE[1];
extern unsigned char IOUT_OC_FAULT_LIMIT[2];
extern unsigned char IOUT_OC_FAULT_RESPONSE[1];
extern unsigned char IOUT_OC_LV_FAULT_LIMIT[2];
extern unsigned char IOUT_OC_LV_FAULT_RESPONSE[1];
extern unsigned char IOUT_OC_WARN_LIMIT[2];
extern unsigned char IOUT_UC_FAULT_LIMIT[2];
extern unsigned char IOUT_UC_FAULT_RESPONSE[1];
extern unsigned char OT_FAULT_LIMIT[2];

/*50~5F*/
extern unsigned char OT_FAULT_RESPONSE[1];
extern unsigned char OT_WARN_LIMIT[2];
extern unsigned char UT_WARN_LIMIT[2];
extern unsigned char UT_FAULT_LIMIT[2];
extern unsigned char UT_FAULT_RESPONSE[1];
extern unsigned char VIN_OV_FAULT_LIMIT[2];
extern unsigned char VIN_OV_FAULT_RESPONSE[1];
extern unsigned char VIN_OV_WARN_LIMIT[2];
extern unsigned char VIN_UV_WARN_LIMIT[2];
extern unsigned char VIN_UV_FAULT_LIMIT[2];
extern unsigned char VIN_UV_FAULT_RESPONSE[1];
extern unsigned char IIN_OC_FAULT_LIMIT[2];
extern unsigned char IIN_OC_FAULT_RESPONSE[1];
extern unsigned char IIN_OC_WARN_LIMIT[2];
extern unsigned char POWER_GOOD_ON[2];
extern unsigned char POWER_GOOD_OFF[2];

/*60~6B,6C~6F Reserved*/
extern unsigned char TON_DELAY[2];
extern unsigned char TON_RISE[2];
extern unsigned char TON_MAX_FAULT_LIMIT[2];
extern unsigned char TON_MAX_FAULT_RESPONSE[1];
extern unsigned char TOFF_DELAY[2];
extern unsigned char TOFF_FALL[2];
extern unsigned char TOFF_MAX_WARN_LIMIT[2];
extern unsigned char POUT_OP_FAULT_LIMIT[2];
extern unsigned char POUT_OP_FAULT_RESPONSE[1];
extern unsigned char POUT_OP_WARN_LIMIT[2];
extern unsigned char PIN_OP_WARN_LIMIT[2];

/*78~7F,70~77 Reserved*/
extern unsigned char STATUS_BYTE[1];
extern unsigned char STATUS_WORD[2];
extern unsigned char STATUS_VOUT[1];
extern unsigned char STATUS_IOUT[1];
extern unsigned char STATUS_INPUT[1];
extern unsigned char STATUS_TEMPERATURE[1];
extern unsigned char STATUS_CML[1];
extern unsigned char STATUS_OTHER[1];

/*80~8F*/
extern unsigned char STATUS_MFR_SPECIFIC[1];
extern unsigned char STATUS_FANS_1_2[1];
extern unsigned char STATUS_FANS_3_4[1];
extern unsigned char READ_KWH_IN[4];
extern unsigned char READ_KWH_OUT[4];
extern unsigned char READ_KWH_CONFIG[2];
extern unsigned char READ_EIN[5];
extern unsigned char READ_EOUT[5];
extern unsigned char READ_VIN[2];
extern unsigned char READ_IIN[2];
extern unsigned char READ_VCAP[2];
extern unsigned char READ_VOUT[2];
extern unsigned char READ_IOUT[2];
extern unsigned char READ_TEMP1[2];
extern unsigned char READ_TEMP2[2];
extern unsigned char READ_TEMP3[2];

/*90~9F*/
extern unsigned char READ_FAN_SPEED_1[2];
extern unsigned char READ_FAN_SPEED_2[2];
extern unsigned char READ_FAN_SPEED_3[2];
extern unsigned char READ_FAN_SPEED_4[2];
extern unsigned char READ_DUTY_CYCLE[2];
extern unsigned char READ_FREQUENCY[2];
extern unsigned char READ_POUT[2];
extern unsigned char READ_PIN[2];
extern unsigned char PMBUS_REVISION[1];
extern unsigned char MFR_ID[1];
extern unsigned char MFR_MODEL[8];
extern unsigned char MFR_REVISION[1];
extern unsigned char MFR_LOCATION[1];
extern unsigned char MFR_DATE[1];
extern unsigned char MFR_SERIAL[1];
extern unsigned char APP_PROFILE_SUPPORT[2];

/*A0~AE, AF Reserved*/
extern unsigned char MFR_VIN_MIN[2];
extern unsigned char MFR_VIN_MAX[2];
extern unsigned char MFR_IIN_MAX[2];
extern unsigned char MFR_PIN_MAX[2];
extern unsigned char MFR_VOUT_MIN[2];
extern unsigned char MFR_VOUT_MAX[2];
extern unsigned char MFR_IOUT_MAX[2];
extern unsigned char MFR_POUT_MAX[2];
extern unsigned char MFR_TAMBIENT_MAX[2];
extern unsigned char MFR_TAMBIENT_MIN[2];
extern unsigned char MFR_EFFICIENCY_LL[14];
extern unsigned char MFR_EFFICIENCY_HL[14];
extern unsigned char MFR_PIN_ACCURACY[1];
extern unsigned char IC_DEVICE_ID[2];
extern unsigned char IC_DEVICE_REV[2];

/*B0~BF*/
extern unsigned char USER_DATA_00[1];
extern unsigned char USER_DATA_01[1];
extern unsigned char USER_DATA_02[1];
extern unsigned char USER_DATA_03[1];
extern unsigned char USER_DATA_04[1];
extern unsigned char USER_DATA_05[1];
extern unsigned char USER_DATA_06[1];
extern unsigned char USER_DATA_07[1];
extern unsigned char USER_DATA_08[1];
extern unsigned char USER_DATA_09[2];
extern unsigned char USER_DATA_10[2];
extern unsigned char USER_DATA_11[2];
extern unsigned char USER_DATA_12[2];
extern unsigned char USER_DATA_13[2];
extern unsigned char USER_DATA_14[2];
extern unsigned char USER_DATA_15[2];

/*C0~C2*/
extern unsigned char MFR_MAX_TEMP_1[2];
extern unsigned char MFR_MAX_TEMP_2[2];
extern unsigned char MFR_MAX_TEMP_3[2];
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
/*-----------------------------------------------
   pmbus function updata rounite
-----------------------------------------------*/
uint16_t linear11(uint16_t real_data, uint8_t exponent);
uint16_t linear16(uint16_t real_data, uint8_t exponent);
void Update_Martix_Buffer_Data(uint16_t data,uint8_t *buffer,FormatType Linear_select,int8 exponent,Pmbus_Martrix_Index Pmbus_1_3_Index);
void Pmbus_Data_Updata(void);

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#endif /* TEMPLATE_H */

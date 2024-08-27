/*-----------------------------------------------
   Myinclude
-----------------------------------------------*/
#include "../inc/Myvalue.h"
#include "../mcc_generated_files/i2c1.h"
#include "../inc/pmbus_stack.h"
/*-----------------------------------------------
   Struct delcare
-----------------------------------------------*/
//I2C1_MESSAGE_STATUS status;
//I2C1_TRANSACTION_REQUEST_BLOCK readTRB[2];
/*-----------------------------------------------
   value  delcare
-----------------------------------------------*/
uint8_t i2cWrData;
uint8_t writeBuffer[3];
/*-----------------------------------------------
   Func
-----------------------------------------------*/
void Init_value(void)
{
    i2cWrData = 0x0F;

    writeBuffer[0] = i2cWrData;


   
}



#ifndef MYVALUE_H
#define MYVALUE_H
/*-----------------------------------------------
   include func
-----------------------------------------------*/
#include "MyHeader.h"
#define SLAVE_ADDR 0x40  //PMBUS
#define EEPROM_ADDR 0xA0 //EEPROM 
#define startAddress 0x0000
/*-----------------------------------------------
   pmbus exponent
-----------------------------------------------*/
/*Vac*/
#define VAC_ARR_EXPONENT				3
#define VAC_ARR_SIZE						(0x0001 << VAC_ARR_EXPONENT)

/*Vdc 12V*/
#define VDC_ARR_EXPONENT				3
#define VDC_ARR_SIZE						(0x0001 << VDC_ARR_EXPONENT)

/*Temp_Amb*/
#define TEMP_AMB_ARR_EXPONENT			3
#define TEMP_AMB_ARR_SIZE				(0x0001 << TEMP_AMB_ARR_EXPONENT)

/*Temp_Spot*/
#define TEMP_SPOT_EXPONENT				3
#define TEMP_SPOT_SIZE					(0x0001 << TEMP_SPOT_EXPONENT)


/*Pin*/
#define PIN_ARR_EXPONENT				3
#define PIN_ARR_SIZE						(0x0001 << PIN_ARR_EXPONENT)

/*Pout*/
#define POUT_ARR_EXPONENT				3
#define POUT_ARR_SIZE					(0x0001 << POUT_ARR_EXPONENT)
/*-----------------------------------------------
   struct enum 
-----------------------------------------------*/



/*-----------------------------------------------
   var delc
-----------------------------------------------*/
extern uint8_t i2cWrData;
extern uint8_t writeBuffer[3];
// uint16_t timeOut, slaveTimeOut;
extern uint8_t EEPROM_TEST[16];
/*-----------------------------------------------
   public func delc
-----------------------------------------------*/
void Init_value(void);

















#ifdef __cplusplus
extern "C"
{
#endif
#ifdef __cplusplus
}
#endif

#endif /* TEMPLATE_H */

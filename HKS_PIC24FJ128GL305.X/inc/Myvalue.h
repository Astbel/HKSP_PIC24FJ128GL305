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
   pmbus exponent GuildLine Read Dell SPEC
-----------------------------------------------*/
/*Vac*/
#define VAC_ARR_EXPONENT				3
#define VAC_ARR_SIZE						(0x0001 << VAC_ARR_EXPONENT)

/*Vdc 12V*/
#define VDC_ARR_EXPONENT				9
#define VDC_ARR_SIZE						(0x0001 << VDC_ARR_EXPONENT)

/*Temp*/
#define TEMP_EXPONENT			      1
#define TEMP_SIZE				         (0x0001 << TEMP_EXPONENT)

/*Pin*/
#define PIN_ARR_EXPONENT				1
#define PIN_ARR_SIZE						(0x0001 << PIN_ARR_EXPONENT)

/*Pout*/
#define POUT_ARR_EXPONENT				1
#define POUT_ARR_SIZE					(0x0001 << POUT_ARR_EXPONENT)

/*Fan_RPM*/
#define FAN_RPM_EXPONENT				1
#define FAN_RPM_SIZE					   (0x0001 << FAN_RPM_EXPONENT)

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

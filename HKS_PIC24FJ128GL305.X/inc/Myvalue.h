#ifndef MYVALUE_H
#define MYVALUE_H
/*-----------------------------------------------
   include func
-----------------------------------------------*/
#include "MyHeader.h"
#define SLAVE_ADDR 0x40 

/*-----------------------------------------------
   struct enum 
-----------------------------------------------*/



/*-----------------------------------------------
   var delc
-----------------------------------------------*/
extern uint8_t i2cWrData;
extern uint8_t writeBuffer[3];
// uint16_t timeOut, slaveTimeOut;

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

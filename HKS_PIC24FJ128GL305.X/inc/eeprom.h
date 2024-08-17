#ifndef EEPROM_H
#define	EEPROM_H

#include "../mcc_generated_files/i2c2.h"
#include "../inc/Gernirc_Type.h"

void EEPROM_Write(uint8_t deviceAddress, uint16_t memAddress, uint8_t data);
uint8_t EEPROM_Read(uint8_t deviceAddress, uint16_t memAddress);
void EEPROM_PageErase(uint8_t deviceAddress, uint16_t pageAddress, uint16_t pageSize);
// void EEPROM_Erase(uint8_t deviceAddress, uint16_t startAddress, uint16_t length);
















#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TEMPLATE_H */
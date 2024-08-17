
#include "../inc/eeprom.h"



void EEPROM_Write(uint8_t deviceAddress, uint16_t memAddress, uint8_t data)
{
    I2C2_MESSAGE_STATUS status;
    uint8_t writeData[3];

    writeData[0] = (memAddress >> 8) & 0xFF; // 高位地址
    writeData[1] = memAddress & 0xFF;        // 低位地址
    writeData[2] = data;                     // 寫入的資料

    I2C2_MasterWrite(writeData, 3, deviceAddress, &status);

    while (status == I2C2_MESSAGE_PENDING); // 等待操作完成
}


uint8_t EEPROM_Read(uint8_t deviceAddress, uint16_t memAddress)
{
    I2C2_MESSAGE_STATUS status;
    uint8_t writeData[2];
    uint8_t readData;

    writeData[0] = (memAddress >> 8) & 0xFF; // 高位地址
    writeData[1] = memAddress & 0xFF;        // 低位地址

    I2C2_MasterWrite(writeData, 2, deviceAddress, &status);
    while (status == I2C2_MESSAGE_PENDING); // 等待地址寫入完成

    I2C2_MasterRead(&readData, 1, deviceAddress, &status);
    while (status == I2C2_MESSAGE_PENDING); // 等待讀取完成

    return readData;
}


void EEPROM_Erase(uint8_t deviceAddress, uint16_t startAddress, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
    {
        EEPROM_Write(deviceAddress, startAddress + i, 0xFF); // 將數據寫為 0xFF
    }
}


void EEPROM_PageErase(uint8_t deviceAddress, uint16_t pageAddress, uint16_t pageSize)
{
    for (uint16_t i = 0; i < pageSize; i++)
    {
        EEPROM_Write(deviceAddress, pageAddress + i, 0xFF); // 擦除一整頁
    }
}



/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "eeprom.h"

void saveWord(uint16 data, uint8 address){ 
    EEPROM_1_WriteByte((data >> 8), address);
    EEPROM_1_WriteByte((data & 0x00ff), address + 1);
}

uint16 loadWord(uint8 address){
    uint8 tmp1, tmp2;
    
    tmp1 = EEPROM_1_ReadByte(address);
    tmp2 = EEPROM_1_ReadByte(address + 1);
    
    uint16 res = (tmp1<<8) + tmp2;
    
    return res;
}

void setBit(bool value, uint8 bit, uint8 address){
    uint8 tmp = EEPROM_1_ReadByte(address);
    if(value){
        if(!(tmp & (1 << bit))){
            EEPROM_1_WriteByte(tmp | (1 << bit), address);
        }
    } else {
        if(tmp & (1 << bit)){
            EEPROM_1_WriteByte(tmp & ~(1 << bit), address);
        }
    }
}

bool testBit(uint8 bit, uint8 address){
    uint8 tmp = EEPROM_1_ReadByte(address);
    return (tmp & (1 << bit));
}

/* [] END OF FILE */

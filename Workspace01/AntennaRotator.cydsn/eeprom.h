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
#ifndef EEEPROM_H
#define EEEPROM_H
    
#include "project.h"
#include <stdbool.h>
   
    void saveWord(uint16 data, uint8 address);
    uint16 loadWord(uint8 address);
    void setBit(bool value, uint8 bit, uint8 address);
    bool testBit(uint8 bit, uint8 address);
    
#endif
/* [] END OF FILE */

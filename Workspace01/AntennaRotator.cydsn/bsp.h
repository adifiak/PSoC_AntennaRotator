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
#ifndef BSP_H
#define BSP_H

#include "stdbool.h"
#include "project.h"
    
void listSaveSlot();
    
bool testSaveSlot(uint8 id);

void saveToSaveSlot(uint8 id);

void moveToSaveSlot(uint8 id);
    
#endif
/* [] END OF FILE */

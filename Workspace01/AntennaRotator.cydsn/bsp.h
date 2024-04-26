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
    
//Service functions
    
void ReadHomePosition();
void ReadHomeOnRestart();
void ReadActualPosition();
void ReadDesiredPosition();
void ReadSignalOnStart();
void WriteHomePosition(uint16 x, uint16 y);
void WriteHomeOnRestart(uint16 b);
void WriteDesiredPosition(uint16 x, uint16 y);
void WriteSignalOnStart(uint16 b);
void MoveToHome();
    
//Auxilary functions
    
void listSaveSlots();
    
bool testSaveSlot(uint8 id);

void saveSlotDetails(uint8 id);

void saveToSaveSlot(uint8 id);

void moveToSaveSlot(uint8 id);
    
#endif
/* [] END OF FILE */

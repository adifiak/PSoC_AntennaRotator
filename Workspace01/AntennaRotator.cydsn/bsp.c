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
#include "bsp.h"
#include "eeprom.h"
#include "main.h"
#include <stdio.h>
    
bool testSaveSlot(uint8 id){
    uint16 tmp = loadWord(0x05);
    return (tmp & (1 << (id - 1)));
}

void listSaveSlots(){
    uint16 tmp = loadWord(0x05);
    uint16 mask = 1;
    for(int i = 1; i <= 16; i++){
        char str[10];
        sprintf(str, "%2d.: %d\r\n", i, ((0 != (tmp & mask)) ? 1 : 0));
        UART_PutString(str);
        mask = mask << 1;
    }
}

void saveSlotDetails(uint8 id){   
    if(testSaveSlot(id)){
        id -= 1;
        uint16 x = loadWord(0x06 + id*4);
        uint16 y = loadWord(0x06 + id*4 + 0x02);
        
        char str[32];
        sprintf(str, "Home: X=%d Y=%d\r\n", (int)AS5600_TO_ANGULAR(x), (int)AS5600_TO_ANGULAR(y));
        UART_PutString(str);
    } else {
        UART_PutString("Save slot empty.");
    }               
    
}

void saveToSaveSlot(uint8 id){
    id -= 1;
    saveWord(rotator_state.x_des, 0x06 + id*4);
    saveWord(rotator_state.y_des, 0x06 + id*4 + 0x02);
    if(!testSaveSlot(id+1)){
        uint16 tmp = loadWord(0x05);
        tmp = tmp + (1 << id);
        saveWord(tmp, 0x05);
    }
}

void moveToSaveSlot(uint8 id){
    if(testSaveSlot(id)){
        id -= 1;
        rotator_state.x_des = loadWord(0x06 + id*4);
        rotator_state.y_des = loadWord(0x06 + id*4 + 0x02);
    } else {
        UART_PutString("Save slot empty.");
    }
}

/* [] END OF FILE */

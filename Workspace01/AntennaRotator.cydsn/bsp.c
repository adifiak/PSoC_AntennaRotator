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
#include "rotation.h"
#include <stdio.h>

//Service functions

void ReadHomePosition(){
    uint16 x = loadWord(0x01);
    uint16 y = loadWord(0x03);
                
    char str[32];
    sprintf(str, "Home: X=%d Y=%d\r\n", (int)AS5600_TO_ANGULAR(x), (int)AS5600_TO_ANGULAR(y));
    UART_PutString(str);
}

void ReadHomeOnRestart(){
    bool tmp;
    tmp = testBit(0, 0x00);
                
    char str[32];
    sprintf(str, "Home on restart: %d\r\n", tmp);
    UART_PutString(str);
}

void ReadActualPosition(){
    ROTATOR_STATE rotator_state = getRotation();
    char str[32];
    sprintf(str, "Actual position: X=%d Y=%d\r\n",  (int)AS5600_TO_ANGULAR(rotator_state.x_act), (int)AS5600_TO_ANGULAR(rotator_state.y_act));
    UART_PutString(str);
}

void ReadDesiredPosition(){
    ROTATOR_STATE rotator_state = getRotation();
    char str[32];
    sprintf(str, "Desired position: X=%d Y=%d\r\n",  (int)AS5600_TO_ANGULAR(rotator_state.x_des), (int)AS5600_TO_ANGULAR(rotator_state.y_des));
    UART_PutString(str);
}

void ReadSignalOnStart(){
    bool tmp;
    tmp = testBit(1, 0x00);
                
    char str[32];
    sprintf(str, "Signal on restart: %d\r\n", tmp);
    UART_PutString(str);
}

void WriteHomePosition(uint16 x, uint16 y){
    if(x > 360) {x = 360;}
    x = AS5600_FROM_ANGULAR(x);
    saveWord(x, 0x01);
                
    if(y > 180) {y = 180;}
    y = AS5600_FROM_ANGULAR(y);
    saveWord(y, 0x03);
}

void WriteHomeOnRestart(uint16 b){
    setBit((b > 0), 0, 0x00);
}

void WriteDesiredPosition(uint16 x, uint16 y){
    if(x >360) {x = 360;}
    if(y >180) {y = 180;}        
    setRotation(AS5600_FROM_ANGULAR(x), AS5600_FROM_ANGULAR(y));       
}

void WriteSignalOnStart(uint16 b){
    setBit((b > 0), 1, 0x00);
}

void MoveToHome(){
    uint16 x = loadWord(0x01);
    uint16 y = loadWord(0x03);
    setRotation(x, y);       
}

//Auxilary functions

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
    ROTATOR_STATE rotator_state = getRotation();
    saveWord(rotator_state.x_des, 0x06 + (id - 1) * 4);
    saveWord(rotator_state.y_des, 0x06 + (id - 1) * 4 + 0x02);
    if(!testSaveSlot(id+1)){
        uint16 tmp = loadWord(0x05);
        tmp = tmp + (1 << id);
        saveWord(tmp, 0x05);
    }
}

void moveToSaveSlot(uint8 id){
    if(testSaveSlot(id)){
        setRotation(loadWord(0x06 + (id-1)*4), loadWord(0x06 + (id-1)*4 + 0x02));
    } else {
        UART_PutString("Save slot empty.");
    }
}

/* [] END OF FILE */

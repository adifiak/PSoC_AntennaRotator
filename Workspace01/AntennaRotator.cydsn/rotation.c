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
#include "rotation.h"
#include "project.h"

static ROTATOR_STATE rotator_state;

ROTATOR_STATE getRotation(){
    return rotator_state;
}

void setRotation(int x, int y){
    if(x < 0){x = 0;} else if(x > 4095){x = 4095;}
    if(y < 0){y = 0;} else if(y > 2047){y = 2047;}
    rotator_state.x_des = x;
    rotator_state.y_des = y;
}

void refreshRotation(){
    uint8 buf[2];
    uint8 status = 0;
    
    //X
    I2C_X_MasterClearStatus();
    status = I2C_X_MasterSendStart(ENCODER_ADDRESS, 0);
    if(I2C_X_MSTR_NO_ERROR == status) /* Check if transfer completed without errors */
    {
        /* Read array of 5 bytes */
        I2C_X_MasterWriteByte(ENCODER_POS_REG);
        I2C_X_MasterSendRestart(ENCODER_ADDRESS, 1);
        buf[0] = I2C_X_MasterReadByte(I2C_X_ACK_DATA);
        buf[1] = I2C_X_MasterReadByte(I2C_X_NAK_DATA);
                
        rotator_state.x_act = ((buf[0])<<8) + (buf[1]);
    }
    I2C_X_MasterSendStop(); /* Send Stop */
    
    //Y
    I2C_Y_MasterClearStatus();
    status = I2C_Y_MasterSendStart(ENCODER_ADDRESS, 0);
    if(I2C_Y_MSTR_NO_ERROR == status) /* Check if transfer completed without errors */
    {
        /* Read array of 5 bytes */
        I2C_Y_MasterWriteByte(ENCODER_POS_REG);
        I2C_Y_MasterSendRestart(ENCODER_ADDRESS, 1);
        buf[0] = I2C_Y_MasterReadByte(I2C_X_ACK_DATA);
        buf[1] = I2C_Y_MasterReadByte(I2C_X_NAK_DATA);
                
        rotator_state.y_act = (((buf[0])<<8) + (buf[1]))/2;// /2 is neccessary because the sensor on this axies is faulty.
    }
    I2C_Y_MasterSendStop(); /* Send Stop */
}

/* [] END OF FILE */

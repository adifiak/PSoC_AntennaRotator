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
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "RotatorHorizon.h"	
#include "main.h"
#include "cli.h"
#include "util.h"

#define STEPPING_TRESHOLD 4
#define ENCODER_ADDRESS 0x36
#define ENCODER_POS_REG 0x0E

bool refresh_display = false;
bool refresh_rotation = false;

CY_ISR( DISPLAY_REFRESH_Handler ){
    refresh_display = true;
}

CY_ISR( MOTOR_CONTROLL_RISEING_EDGE_Handler ){
    X_Dir_Pin_Write(rotator_state.x_act < rotator_state.x_des);
    Y_Dir_Pin_Write(rotator_state.y_act < rotator_state.y_des);
    
    if(abs(rotator_state.x_act - rotator_state.x_des) > STEPPING_TRESHOLD) {
        X_Step_Pin_Write(1);
    }
    if(abs(rotator_state.y_act - rotator_state.y_des) > STEPPING_TRESHOLD) {
        Y_Step_Pin_Write(1);
    }
}

CY_ISR( MOTOR_CONTROLL_FALLING_EDGE_Handler ){
    X_Step_Pin_Write(0);
    Y_Step_Pin_Write(0);
    refresh_rotation = true;
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */      
    rotator_state.x_des = AS5600_FROM_ANGULAR(245);
    rotator_state.x_act = 0;
    rotator_state.y_des = AS5600_FROM_ANGULAR(180);
    rotator_state.y_act = 0;
    
    CLI_Init();
    
    UART_Start();
    I2C_OLED_Start();
    PWM_1_Start();
    Display_Refresh_Timer_Start();
    I2C_X_Start();
    I2C_Y_Start();
    EEPROM_1_Start();
    
    refreshRotation(&rotator_state);
    
    initHorizon();
    renderHorizon(&rotator_state);
    
    Display_Refresh_Timer_Int_StartEx(DISPLAY_REFRESH_Handler);
    MotorControlRiseingEdge_StartEx(MOTOR_CONTROLL_RISEING_EDGE_Handler);
    MotorControlFallingEdge_StartEx(MOTOR_CONTROLL_FALLING_EDGE_Handler);
    
    Motor_Enable_Write(1);
  
    for(;;)
    {
        //Refresh rotation data
        if(refresh_rotation){
            refresh_rotation = false;
            refreshRotation(&rotator_state);
        }
        //Refresh display
        if(refresh_display){
            refresh_display = false;
            renderHorizon(&rotator_state);
        }
        //Input processing
        CLI_Update();
        
        LED_Pin_Write(SW_UP_Pin_Read() && SW_DOWN_Pin_Read() && SW_LEFT_Pin_Read() && SW_RIGHT_Pin_Read());
    }
}

void refreshRotation(ROTATOR_STATE* rotator_state){
    //uint8 dev_addr = 0x36;
    //uint8 reg_addr = 0x0E;
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
                
        rotator_state->x_act = ((buf[0])<<8) + (buf[1]);
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
                
        rotator_state->y_act = ((buf[0])<<8) + (buf[1]);
    }
    I2C_Y_MasterSendStop(); /* Send Stop */
}

/* [] END OF FILE */

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
#include "eeprom.h"

#define STEPPING_TRESHOLD 4
#define ENCODER_ADDRESS 0x36
#define ENCODER_POS_REG 0x0E

bool refresh_display = false;
bool refresh_buttons = false;
bool refresh_rotation = false;

CY_ISR( DISPLAY_REFRESH_Handler ){
    refresh_display = true;
}

CY_ISR( BUTTON_REFRESH_Handler ){
    refresh_buttons = true;
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
    
    //Start internal peripherials
    EEPROM_1_Start();   
    UART_Start();
    I2C_OLED_Start();
    PWM_1_Start();
    Display_Refresh_Timer_Start();
    Button_Refresh_Timer_Start();
    I2C_X_Start();
    I2C_Y_Start();
    
    //Get rotator state
    refreshRotation(&rotator_state);
    
    //Init external peripherials
    CLI_Init();
    Horizon_Init();
    Horizon_Render(&rotator_state);
    
    //Home on restart
    if(testBit(0, 0x00)){
        rotator_state.x_des = loadWord(0x01);
        rotator_state.y_des = loadWord(0x03);
    } else {
        rotator_state.x_des = rotator_state.x_act;
        rotator_state.y_des = rotator_state.y_act;
    }
    
    //Register interrupt service handlers
    Display_Refresh_Timer_Int_StartEx(DISPLAY_REFRESH_Handler);
    Button_Refresh_Timer_Int_StartEx(BUTTON_REFRESH_Handler);
    MotorControlRiseingEdge_StartEx(MOTOR_CONTROLL_RISEING_EDGE_Handler);
    MotorControlFallingEdge_StartEx(MOTOR_CONTROLL_FALLING_EDGE_Handler);
    
    //Enable the movement of the motors
    Motor_Enable_Write(1);
    
    //Signal on restart
    if(testBit(1, 0x00)){
        UART_PutString("System started.");
    }
    
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
            Horizon_Render(&rotator_state);
        }
        //Refresh buttons
        if(refresh_buttons){
            refresh_buttons = false;
            
            bool up_button = SW_UP_Pin_Read();
            bool down_button = SW_DOWN_Pin_Read();
            bool left_button = SW_LEFT_Pin_Read();
            bool right_button = SW_RIGHT_Pin_Read();
            
            //X
            if(left_button && !right_button){
                if(rotator_state.x_des >= 4) {rotator_state.x_des -= 4;}
            }
            if(!left_button && right_button){
                if(rotator_state.x_des <= 4091) {rotator_state.x_des += 4;}
            }
            
            //Y
            if(up_button && !down_button){
                if(rotator_state.y_des >= 4) {rotator_state.y_des -= 4;}
            }
            if(!up_button && down_button){
                if(rotator_state.y_des <= 4091) {rotator_state.y_des += 4;}
            }
        }
        //Input processing
        CLI_Update();
        
        LED_Pin_Write(SW_UP_Pin_Read() && SW_DOWN_Pin_Read() && SW_LEFT_Pin_Read() && SW_RIGHT_Pin_Read());
    }
}

void refreshRotation(ROTATOR_STATE* rotator_state){
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

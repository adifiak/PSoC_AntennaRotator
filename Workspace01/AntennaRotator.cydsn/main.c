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
#include "cli.h"
#include "util.h"
#include "eeprom.h"

#define STEPPING_TRESHOLD 4

bool refresh_display = false;
bool refresh_buttons = false;
bool refresh_rotation = false;

/**
 * @brief Interrupt service routine for DISPLAY_REFRESH.
 * 
 * This function is called when the DISPLAY_REFRESH interrupt occurs. It sets the refresh_display flag to true, indicating that the display needs to be refreshed.
 */
CY_ISR(DISPLAY_REFRESH_Handler) {
    refresh_display = true;
}

/**
 * @brief Interrupt service routine for BUTTON_REFRESH.
 * 
 * This function is called when the BUTTON_REFRESH interrupt occurs. It sets the refresh_buttons flag to true, indicating that the buttons need to be refreshed.
 */
CY_ISR( DISPLAY_REFRESH_Handler ){
    refresh_display = true;
}

/**
 * @brief Interrupt service routine for BUTTON_REFRESH.
 * 
 * This function is called when the BUTTON_REFRESH interrupt occurs. It sets the refresh_buttons flag to true, indicating that the buttons need to be refreshed.
 */
CY_ISR( BUTTON_REFRESH_Handler ){
    refresh_buttons = true;
}

/**
 * @brief Handle stepping the motors.
 * 
 * This function gets the current rotation data from the rotation module. Computes weather it neads to step the motors,sets the desired directions and issues a step if neccessary.
 */
CY_ISR( MOTOR_CONTROLL_RISEING_EDGE_Handler ){
    ROTATOR_STATE rotator_state = getRotation();
    
    X_Dir_Pin_Write(rotator_state.x_act < rotator_state.x_des);
    Y_Dir_Pin_Write(rotator_state.y_act < rotator_state.y_des);
    
    if(abs(rotator_state.x_act - rotator_state.x_des) > STEPPING_TRESHOLD) {
        X_Step_Pin_Write(1);
    }
    if(abs(rotator_state.y_act - rotator_state.y_des) > STEPPING_TRESHOLD) {
        Y_Step_Pin_Write(1);
    }
}

/**
 * @brief Finishes stepping the motors. And signals a refresh rotation event
 * 
 * This function creates the falling edge of the stepping signal. It sets the refresh_rotation flag to true, indicating that the buttons need to be refreshed.
 */
CY_ISR( MOTOR_CONTROLL_FALLING_EDGE_Handler ){
    X_Step_Pin_Write(0);
    Y_Step_Pin_Write(0);
    refresh_rotation = true;
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
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
    refreshRotation();
    
    //Init external peripherials
    CLI_Init();
    Horizon_Init();
    Horizon_Render();
    
    //Home on restart
    if(testBit(0, 0x00)){
        setRotation(loadWord(0x01), loadWord(0x03));
    } else {
        ROTATOR_STATE rotator_state = getRotation();
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
        UART_PutString("System started.\r\n");
    }
    
    for(;;)
    {
        //Refresh rotation data
        if(refresh_rotation){
            refresh_rotation = false;
            refreshRotation();
        }
        //Refresh display
        if(refresh_display){
            refresh_display = false;
            Horizon_Render();
        }
        //Refresh buttons
        if(refresh_buttons){
            refresh_buttons = false;
            
            bool up_button = SW_UP_Pin_Read();
            bool down_button = SW_DOWN_Pin_Read();
            bool left_button = SW_LEFT_Pin_Read();
            bool right_button = SW_RIGHT_Pin_Read();
            
            ROTATOR_STATE rotator_state = getRotation();
            int x = rotator_state.x_des;
            int y = rotator_state.y_des;
            
            //X
            if(left_button && !right_button){
                x -= 4;
            }
            if(!left_button && right_button){
                x += 4;
            }
            
            //Y
            if(up_button && !down_button){
                y -= 4;
            }
            if(!up_button && down_button){
                y += 4;
            }
            
            setRotation(x, y);
        }
        //Input processing
        CLI_Update();
        
        LED_Pin_Write(SW_UP_Pin_Read() && SW_DOWN_Pin_Read() && SW_LEFT_Pin_Read() && SW_RIGHT_Pin_Read());
    }
}

/* [] END OF FILE */

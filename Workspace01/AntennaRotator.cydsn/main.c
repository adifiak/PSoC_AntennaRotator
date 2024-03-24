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

typedef enum READ_STATE{
    CMD, ARG1, ARG2, ARG3
}READ_STATE;

typedef struct INPUT_BUFFER{
    char data[5];
    int cnt;
}INPUT_BUFFER;

bool ProcessCommand(struct INPUT_BUFFER* cmd, struct INPUT_BUFFER* arg1, struct INPUT_BUFFER* arg2, struct INPUT_BUFFER* arg3);
void ResetInput(enum READ_STATE* readState, struct INPUT_BUFFER* cmd, struct INPUT_BUFFER* arg1, struct INPUT_BUFFER* arg2, struct INPUT_BUFFER* arg3);
bool AddArgumentDigit(char c, struct INPUT_BUFFER* arg);
bool AddCommandChar(char c, struct INPUT_BUFFER* cmd);

bool refresh_display = false;

int x_des = 0;
int y_des = 0;
int x_act = 0;
int y_act = 0;

CY_ISR( X_ADC_Handler ){
    x_act = ADC_SAR_X_GetResult16();
}

CY_ISR( DISPLAY_REFRESH_Handler ){
    refresh_display = true;
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */      
    enum READ_STATE readState = CMD;
    
    struct INPUT_BUFFER cmd;
    struct INPUT_BUFFER arg1;
    struct INPUT_BUFFER arg2;
    struct INPUT_BUFFER arg3;
    
    UART_Start();
    I2C_OLED_Start();
    ADC_SAR_X_Start();
    PWM_1_Start();
    Display_Refresh_Timer_Start();
    
    LED_Pin_Write(1);
    
    X_ADC_Int_StartEx(X_ADC_Handler);
    Display_Refresh_Timer_Int_StartEx(DISPLAY_REFRESH_Handler);
  
    
    
    initHorizon();
    renderHorizon(x_des, x_act, y_des, y_act);
    UART_PutString("Hello World!\n");
    
    ResetInput(&readState, &cmd, &arg1, &arg2, &arg3);
    
    for(;;)
    {
        //Refresh display
        if(refresh_display){
            refresh_display = false;
            renderHorizon(x_des, x_act, y_des, y_act);
        }
        //Input processing
        char inChar = UART_GetChar();
        if(inChar != 0){
            bool error = false;
            switch(inChar){
                case 13:
                    readState = CMD;
                    error = ProcessCommand(&cmd, &arg1, &arg2, &arg3);
                    if(!error){
                        ResetInput(&readState, &cmd, &arg1, &arg2, &arg3);
                    }
                    break;
                case 32:
                    switch(readState){
                        case CMD:
                            readState = ARG1;
                            break;
                        case ARG1:
                            readState = ARG2;
                            break;
                        case ARG2:
                            readState = ARG3;
                            break;
                        case ARG3:
                            error = true;
                            break;
                    }
                    break;
                default:
                    switch(readState){
                        case CMD:
                            error = AddCommandChar(inChar, &cmd);
                            break;
                        case ARG1:
                            error = AddArgumentDigit(inChar, &arg1);
                            break;
                        case ARG2:
                            error = AddArgumentDigit(inChar, &arg1);
                            break;
                        case ARG3:
                            error = AddArgumentDigit(inChar, &arg1);
                            break;
                    }
                    break;
            }
            /*char str[5];
            sprintf(str, "%d", inChar);
            UART_PutString(strcat(str, " "));*/
            
            //UART_PutChar(inChar);
            
            /*char str[32];
            sprintf(str, "asd %d ", 271);
            UART_PutString(str);*/
            
            if(error){
                ResetInput(&readState, &cmd, &arg1, &arg2, &arg3);
                UART_PutString("Error, resetting input processor.");
            }
        }
        LED_Pin_Write(SW_UP_Pin_Read() && SW_DOWN_Pin_Read() && SW_LEFT_Pin_Read() && SW_RIGHT_Pin_Read());
    }
}

bool ProcessCommand(struct INPUT_BUFFER* cmd, struct INPUT_BUFFER* arg1, struct INPUT_BUFFER* arg2, struct INPUT_BUFFER* arg3){
    if(cmd->cnt == 4) {
        if(!strcmp(cmd->data, "rhom")){
            UART_PutString("Medve feladat 1");
        } else if(!strcmp(cmd->data, "rhor")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "ract")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "rpos")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "rsos")){
            UART_PutString("Medve feladat 2");
        }else if(!strcmp(cmd->data, "whom")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "whor")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "wpos")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "wsos")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "wpoi")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "mhom")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "mact")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "mpoi")){
            UART_PutString("Medve feladat 2");
        } else if(!strcmp(cmd->data, "rpoi")){
            UART_PutString("Medve feladat 2");
        } else {
            return true;
        }
    }
    return false;
}

void ResetInput(enum READ_STATE* readState, struct INPUT_BUFFER* cmd, struct INPUT_BUFFER* arg1, struct INPUT_BUFFER* arg2, struct INPUT_BUFFER* arg3){
    *readState = CMD;
    cmd->cnt = 0;
    arg1->cnt = 0;
    arg2->cnt = 0;
    arg3->cnt = 0;
    for(int i = 0; i < 5; i++){
        cmd->data[i] = 0;
        arg1->data[i] = 0;
        arg2->data[i] = 0;
        arg3->data[i] = 0;
    }
    
}

bool AddArgumentDigit(char c, struct INPUT_BUFFER* arg){
    if(isdigit(c)){
        if(arg->cnt <= 3){
            arg->data[arg->cnt++] = c;
        }
        return false;
    }
    return true;
}

bool AddCommandChar(char c, struct INPUT_BUFFER* cmd){
    if(cmd->cnt <= 3){
            cmd->data[cmd->cnt++] = c;
            return false;
    }
    return true;
}

/* [] END OF FILE */

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

typedef enum READ_STATE{
    CMD, ARG1, ARG2, ARG3
}READ_STATE;

typedef struct INPUT_BUFFER{
    char data[5];
    int cnt;
}INPUT_BUFFER;

void ProcessCommand(struct INPUT_BUFFER* cmd, struct INPUT_BUFFER* arg1, struct INPUT_BUFFER* arg2, struct INPUT_BUFFER* arg3);
void ResetInput(enum READ_STATE* readState, struct INPUT_BUFFER* cmd, struct INPUT_BUFFER* arg1, struct INPUT_BUFFER* arg2, struct INPUT_BUFFER* arg3);
bool AddArgumentDigit(char c, struct INPUT_BUFFER* arg);
bool AddCommandChar(char c, struct INPUT_BUFFER* cmd);


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    UART_Start();
    UART_PutString("Hello World!");
    
    enum READ_STATE readState = CMD;
    
    struct INPUT_BUFFER cmd;
    struct INPUT_BUFFER arg1;
    struct INPUT_BUFFER arg2;
    struct INPUT_BUFFER arg3;
    
    ResetInput(&readState, &cmd, &arg1, &arg2, &arg3);
    
    for(;;)
    {
        //Input processing
        char inChar = UART_GetChar();
        if(inChar != 0){
            bool error = false;
            switch(inChar){
                case 13:
                    readState = CMD;
                    ProcessCommand(&cmd, &arg1, &arg2, &arg3);
                    ResetInput(&readState, &cmd, &arg1, &arg2, &arg3);
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

void ProcessCommand(struct INPUT_BUFFER* cmd, struct INPUT_BUFFER* arg1, struct INPUT_BUFFER* arg2, struct INPUT_BUFFER* arg3){
    
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

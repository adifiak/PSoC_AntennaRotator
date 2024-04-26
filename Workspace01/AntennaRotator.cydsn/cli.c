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
#include "cli.h"
#include "eeprom.h"
#include "bsp.h"
#include "rotation.h"

enum READ_STATE readState = CMD;

void CLI_Init(){
    ResetInput(&readState, &cmd, &arg1, &arg2, &arg3);
}

void CLI_Update(){
    char inChar = UART_GetChar();
        if(inChar != 0){
            UART_PutChar(inChar);
            bool error = false;
            switch(inChar){
                case 27:
                    UART_PutString("\r\n");
                    ResetInput();
                    break;
                case 13:
                    UART_PutString("\r\n");
                    readState = CMD;
                    error = ProcessCommand();
                    if(!error){
                        ResetInput();
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
                            error = AddArgumentDigit(inChar, &arg2);
                            break;
                        case ARG3:
                            error = AddArgumentDigit(inChar, &arg3);
                            break;
                    }
                    break;
            }
         
            if(error){
                ResetInput();
                UART_PutString("Error, resetting input processor.\r\n");
            }
        }
}

bool ProcessCommand(){
    if(cmd.cnt == 4) {
        if(!strcmp(cmd.data, "rhom")){
            if(isNoArgFnc()){
                ReadHomePosition();
                return false;
            }
        } else if(!strcmp(cmd.data, "rhor")){
            if(isNoArgFnc()){
                ReadHomeOnRestart();
                return false;
            }
        } else if(!strcmp(cmd.data, "ract")){
            if(isNoArgFnc()){
                ReadActualPosition();
                return false;
            }
        } else if(!strcmp(cmd.data, "rpos")){
            if(isNoArgFnc()){
                ReadDesiredPosition();
                return false;
            }            
        } else if(!strcmp(cmd.data, "rsos")){
            if(isNoArgFnc()){
                ReadSignalOnStart();
                return false;
            }    
        }else if(!strcmp(cmd.data, "whom")){
            if(isTwoArgFnc()){              
                uint16 x = ParseArgument(&arg1);
                uint16 y = ParseArgument(&arg2);
                WriteHomePosition(x, y);
                return false;
            }   
        } else if(!strcmp(cmd.data, "whor")){
            if(isOneArgFnc()){
                WriteHomeOnRestart(ParseArgument(&arg1));
                return false;
            }
        } else if(!strcmp(cmd.data, "wpos")){
            if(isTwoArgFnc()){            
                uint16 x = ParseArgument(&arg1);
                uint16 y = ParseArgument(&arg2);
                WriteDesiredPosition(x, y);
                return false;
            }
        } else if(!strcmp(cmd.data, "wsos")){
            if(isOneArgFnc()){
                WriteSignalOnStart(ParseArgument(&arg1));
                return false;
            }
        } else if(!strcmp(cmd.data, "wpoi")){
            if(isOneArgFnc()){
                uint8 id = ParseArgument(&arg1);
                if(1 <= id && 16 >= id){
                    saveToSaveSlot(id);
                    return false;
                }
                UART_PutString("Invalid ID.");
            }
        } else if(!strcmp(cmd.data, "mhom")){
            if(isNoArgFnc()){
                MoveToHome();
                return false;
            }
        } else if(!strcmp(cmd.data, "mpoi")){
            if(isOneArgFnc()){
                uint8 id = ParseArgument(&arg1);
                if(1 <= id && 16 >= id){
                    moveToSaveSlot(id);
                    return false;
                }
                UART_PutString("Invalid ID.");
            }
        } else if(!strcmp(cmd.data, "rpoi")){
            if(isNoArgFnc()){
                listSaveSlots();
                return false;
            } else if(isOneArgFnc()){
                uint8 id = ParseArgument(&arg1);
                if(1 <= id && 16 >= id){
                    saveSlotDetails(id);
                    return false;
                }
                UART_PutString("Invalid ID.");
            }
        }
    }
    return true;
}

void ResetInput(){
    readState = CMD;
    cmd.cnt = 0;
    arg1.cnt = 0;
    arg2.cnt = 0;
    arg3.cnt = 0;
    for(int i = 0; i < 5; i++){
        cmd.data[i] = 0;
        arg1.data[i] = 0;
        arg2.data[i] = 0;
        arg3.data[i] = 0;
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

int ParseArgument(struct INPUT_BUFFER* arg){
    int res = 0;
    for(int i = 0; i < arg->cnt; i++){
        res *= 10;
        res += arg->data[i] - '0';
    }
    return res;
}

bool isNoArgFnc(){return arg1.cnt == 0 && arg2.cnt == 0 && arg3.cnt == 0;}
bool isOneArgFnc(){return arg1.cnt > 0 && arg2.cnt == 0 && arg3.cnt == 0;}
bool isTwoArgFnc(){return arg1.cnt > 0 && arg2.cnt > 0 && arg3.cnt == 0;}
bool isThreeArgFnc(){return arg1.cnt > 0 && arg2.cnt > 0 && arg3.cnt > 0;}

/* [] END OF FILE */

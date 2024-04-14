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
#include "main.h"

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
                case 13:
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
            
            if(arg1.cnt == 0 && arg2.cnt == 0 && arg3.cnt == 0){
                uint8 tmp1, tmp2;
                
                tmp1 = EEPROM_1_ReadByte(0x01);
                tmp2 = EEPROM_1_ReadByte(0x02);
                uint16 x = (tmp1<<8) + tmp2;
                
                tmp1 = EEPROM_1_ReadByte(0x03);
                tmp2 = EEPROM_1_ReadByte(0x04);
                uint16 y = (tmp1<<8) + tmp2;
                
                char str[32];
                sprintf(str, "Home: X=%d Y=%d\r\n", (int)AS5600_TO_ANGULAR(x), (int)AS5600_TO_ANGULAR(y));
                UART_PutString(str);
                return false;
            }
            return true;
            
        } else if(!strcmp(cmd.data, "rhor")){
            
            if(arg1.cnt == 0 && arg2.cnt == 0 && arg3.cnt == 0){
                uint8 tmp;
                tmp = EEPROM_1_ReadByte(0x00);
                
                char str[32];
                sprintf(str, "Home on restart: %d\r\n", (0 != (tmp & (1 << 0))));
                UART_PutString(str);
                return false;
            }
            return true;
            
        } else if(!strcmp(cmd.data, "ract")){
            
            if(arg1.cnt == 0 && arg2.cnt == 0 && arg3.cnt == 0){
                char str[32];
                sprintf(str, "Home: X=%d Y=%d\r\n",  (int)AS5600_TO_ANGULAR(rotator_state.x_act), (int)AS5600_TO_ANGULAR(rotator_state.y_act));
                UART_PutString(str);
                return false;
            }
            return true;
            
        } else if(!strcmp(cmd.data, "rpos")){
            
            if(arg1.cnt == 0 && arg2.cnt == 0 && arg3.cnt == 0){
                char str[32];
                sprintf(str, "Home: X=%d Y=%d\r\n",  (int)AS5600_TO_ANGULAR(rotator_state.x_des), (int)AS5600_TO_ANGULAR(rotator_state.y_des));
                UART_PutString(str);
                return false;
            }
            return true;
            
        } else if(!strcmp(cmd.data, "rsos")){
            
            if(arg1.cnt == 0 && arg2.cnt == 0 && arg3.cnt == 0){
                uint8 tmp;
                tmp = EEPROM_1_ReadByte(0x00);
                
                char str[32];
                sprintf(str, "Signal on restart: %d\r\n", (0 != (tmp & (1 << 1))));
                UART_PutString(str);
                return false;
            }
            return true;
            
        }else if(!strcmp(cmd.data, "whom")){
            
            if(arg1.cnt > 0 && arg2.cnt > 0 && arg3.cnt == 0){
                uint16 tmp;
                
                tmp = ParseArgument(&arg1);
                if(tmp > 360) {tmp = 360;}
                tmp = AS5600_FROM_ANGULAR(tmp);
                EEPROM_1_WriteByte((tmp >> 8), 0x01);
                EEPROM_1_WriteByte((tmp & 0x00ff), 0x02);
                
                tmp = ParseArgument(&arg2);
                if(tmp > 360) {tmp = 360;}
                tmp = AS5600_FROM_ANGULAR(tmp);
                EEPROM_1_WriteByte((tmp >> 8), 0x03);
                EEPROM_1_WriteByte((tmp & 0x00ff), 0x04);
                
                return false;
            }
            return true;
            
        } else if(!strcmp(cmd.data, "whor")){
            
            if(arg1.cnt > 0 && arg2.cnt == 0 && arg3.cnt == 0){
                uint8 tmp = EEPROM_1_ReadByte(0x00);
                if(ParseArgument(&arg1) > 0){
                    EEPROM_1_WriteByte(tmp | (1 << 0), 0x00);
                } else {
                    EEPROM_1_WriteByte(tmp & ~(1 << 0), 0x00);
                }
                return false;
            }
            return true;
            
        } else if(!strcmp(cmd.data, "wpos")){
            
            if(arg1.cnt > 0 && arg2.cnt > 0 && arg3.cnt == 0){
                uint16 tmp1, tmp2;
                
                tmp1 = ParseArgument(&arg1);
                tmp2 = ParseArgument(&arg2);
                
                if(tmp1 >360) {tmp1 = 360;}
                if(tmp2 >360) {tmp2 = 360;}
                
                rotator_state.x_des = AS5600_FROM_ANGULAR(tmp1);
                rotator_state.y_des = AS5600_FROM_ANGULAR(tmp2);
                
                return false;
            }
            return true;
            
        } else if(!strcmp(cmd.data, "wsos")){
            
            if(arg1.cnt > 0 && arg2.cnt == 0 && arg3.cnt == 0){
                uint8 tmp = EEPROM_1_ReadByte(0x00);
                if(ParseArgument(&arg1) > 0){
                    EEPROM_1_WriteByte(tmp | (1 << 1), 0x00);
                } else {
                    EEPROM_1_WriteByte(tmp & ~(1 << 1), 0x00);
                }
                return false;
            }
            return true;
            
        } else if(!strcmp(cmd.data, "wpoi")){
            UART_PutString("Medve feladat 2\r\n");
        } else if(!strcmp(cmd.data, "mhom")){
            
            if(arg1.cnt == 0 && arg2.cnt == 0 && arg3.cnt == 0){
                uint8 tmp1, tmp2;
                
                tmp1 = EEPROM_1_ReadByte(0x01);
                tmp2 = EEPROM_1_ReadByte(0x02);
                uint16 x = (tmp1<<8) + tmp2;
                
                tmp1 = EEPROM_1_ReadByte(0x03);
                tmp2 = EEPROM_1_ReadByte(0x04);
                uint16 y = (tmp1<<8) + tmp2;
                
                rotator_state.x_des = x;
                rotator_state.y_des = y;
                
                return false;
            }
            return true;
            
        } else if(!strcmp(cmd.data, "mact")){
            
            //FELESLEGES PARANCS
            return true;
            
        } else if(!strcmp(cmd.data, "mpoi")){
            UART_PutString("Medve feladat 2\r\n");
        } else if(!strcmp(cmd.data, "rpoi")){
            UART_PutString("Medve feladat 2\r\n");
        } else {
            return true;
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

/* [] END OF FILE */

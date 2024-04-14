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
#ifndef CLI_H
#define CLI_H

#include "project.h"
#include <stdbool.h>
#include "main.h"
#include <stdio.h>

typedef enum READ_STATE{
    CMD, ARG1, ARG2, ARG3
}READ_STATE;

typedef struct INPUT_BUFFER{
    char data[5];
    int cnt;
}INPUT_BUFFER;

extern enum READ_STATE readState;
    
struct INPUT_BUFFER cmd;
struct INPUT_BUFFER arg1;
struct INPUT_BUFFER arg2;
struct INPUT_BUFFER arg3;

void CLI_Init();
void CLI_Update();

bool ProcessCommand();
void ResetInput();
bool AddArgumentDigit(char c, struct INPUT_BUFFER* arg);
bool AddCommandChar(char c, struct INPUT_BUFFER* cmd);

int ParseArgument(struct INPUT_BUFFER* arg);

#endif
/* [] END OF FILE */

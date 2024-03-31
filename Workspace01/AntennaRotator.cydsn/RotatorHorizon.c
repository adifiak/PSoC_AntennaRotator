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
#include <project.h>
#include "RotatorHorizon.h"
#include "ssd1306.h"
#include <stdio.h>

#define DISPLAY_ADDRESS 0x3C // 011110+SA0+RW - 0x3C or 0x3D	

void initHorizon(){
    display_init(DISPLAY_ADDRESS);
    display_clear();    
    display_update(); 
}

void renderHorizon(ROTATOR_STATE* rotator_state){
    char str[32];
    display_clear();    
        
    gfx_setTextSize(1);
    gfx_setTextColor(WHITE);
    gfx_setCursor(0,0);

    // text display
    gfx_setTextSize(1);
    gfx_setTextColor(WHITE);
    gfx_setCursor(0,0);
    sprintf(str, "X : %3.2f : %3.2f", AS5600_TO_ANGULAR(rotator_state->x_des), AS5600_TO_ANGULAR(rotator_state->x_act));
    gfx_println(str); 
    gfx_setTextColor(WHITE);
    sprintf(str, "Y : %3.2f : %3.2f", AS5600_TO_ANGULAR(rotator_state->y_des), AS5600_TO_ANGULAR(rotator_state->y_act));
    gfx_setCursor(0,8);
    gfx_println(str); 
    display_update();
    
}

/* [] END OF FILE */

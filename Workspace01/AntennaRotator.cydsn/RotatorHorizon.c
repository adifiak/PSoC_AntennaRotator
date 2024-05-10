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
#include "rotation.h"
#include <stdio.h>
#include <math.h>

#define DISPLAY_ADDRESS 0x3C // 011110+SA0+RW - 0x3C or 0x3D	

void Horizon_Init(){
    display_init(DISPLAY_ADDRESS);
    display_clear();    
    display_update(); 
    gfx_setTextSize(1);
    gfx_setTextColor(WHITE);
    gfx_setCursor(0,0);
}

void Horizon_Render(){
    ROTATOR_STATE rotator_state = getRotation();
    
    display_clear();    
        
    DrawDial( 0, "XD", AS5600_TO_ANGULAR(rotator_state.x_des));
    DrawDial(32, "XA", AS5600_TO_ANGULAR(rotator_state.x_act));
    DrawDial(64, "YD", AS5600_TO_ANGULAR(rotator_state.y_des));
    DrawDial(96, "YA", AS5600_TO_ANGULAR(rotator_state.y_act));

    display_update();
    
}

void DrawDial(uint16_t horizontalOffset, const char* label, float degree){
    gfx_setCursor(horizontalOffset, 0);
    gfx_println(label);
    gfx_drawCircle( horizontalOffset + 16, 16, 12, WHITE);
    gfx_drawLine( horizontalOffset + 16, 15, horizontalOffset + 16 + cos(degree/360.0f*2*3.14f)*12, 16 + sin(degree/360.0f*2*3.14f)*12, WHITE);
}

/* [] END OF FILE */

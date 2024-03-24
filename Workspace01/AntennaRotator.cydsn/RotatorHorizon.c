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

#define DISPLAY_ADDRESS 0x3C // 011110+SA0+RW - 0x3C or 0x3D	

void initHorizon(){
    display_init(DISPLAY_ADDRESS);
    display_clear();    
    display_update(); 
}

void renderHorizon(){
    display_clear();    
    display_update(); 
        
    gfx_setTextSize(1);
    gfx_setTextColor(WHITE);
    gfx_setCursor(0,0);

    // text display
    gfx_setTextSize(1);
    gfx_setTextColor(WHITE);
    gfx_setCursor(0,0);
    gfx_println("PSoC PL5"); 
    gfx_setTextColor(WHITE);
    gfx_setCursor(8,8);
    gfx_println("PSoC PL5"); 
    display_update();
    
    // drawing a pixel
    /*gfx_drawPixel(10, 10, WHITE);
    gfx_drawPixel(11, 11, WHITE);
    gfx_drawPixel(12, 12, BLACK);
    gfx_drawPixel(13, 13, BLACK);*/
    display_update(); 
}

/* [] END OF FILE */

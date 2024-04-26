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

#ifndef ROTATION_H
#define ROTATION_H
    
#define ENCODER_ADDRESS 0x36
#define ENCODER_POS_REG 0x0E

#define AS5600_FROM_ANGULAR(x) (uint16)(((float)(1 << 12) / 360.0f) * x)
#define AS5600_TO_ANGULAR(x) (x / ((float)(1 << 12) / 360.0f))

typedef struct ROTATOR_STATE{
    int x_des;
    int y_des;
    int x_act;
    int y_act;
}ROTATOR_STATE;

void setRotation(int x, int y);

ROTATOR_STATE getRotation();

void refreshRotation();
    
#endif
/* [] END OF FILE */

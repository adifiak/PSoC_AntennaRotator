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
#ifndef MAIN_H
#define MAIN_H
    
#define AS5600_FROM_ANGULAR(x) (uint16)(((float)(1 << 12) / 360.0f) * x)
#define AS5600_TO_ANGULAR(x) (x / ((float)(1 << 12) / 360.0f))

typedef struct ROTATOR_STATE{
    int x_des;
    int y_des;
    int x_act;
    int y_act;
}ROTATOR_STATE;

struct ROTATOR_STATE rotator_state;

void refreshRotation(ROTATOR_STATE* rotator_state);

#endif /*MAIN_H*/
/* [] END OF FILE */

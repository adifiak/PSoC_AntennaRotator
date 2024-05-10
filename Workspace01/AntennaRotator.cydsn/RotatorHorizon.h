#ifndef ROTATOR_HORIZON_H
#define ROTATOR_HORIZON_H
    
#include "project.h"

/**
 * @brief Initializes the horizon module.
 * 
 * This function initializes the horizon module and any necessary resources.
 * It should be called before using any other functions in this module.
 */
void Horizon_Init();

/**
 * @brief Renders the horizon.
 * 
 * This function renders the horizon based on the current rotation state.
 * It should be called periodically to update the horizon display.
 */
void Horizon_Render();

void DrawDial(uint16_t horizontalOffset, const char* label, float degree);

#endif
/* [] END OF FILE */

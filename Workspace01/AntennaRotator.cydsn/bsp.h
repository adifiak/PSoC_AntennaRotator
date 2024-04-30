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

#ifndef BSP_H
#define BSP_H

#include "stdbool.h"
#include "project.h"

/**
 * @brief Reads the home position from the EEPROM.
 */
void ReadHomePosition();

/**
 * @brief Reads if it has to home in the case of system restart from the EEPROM.
 */
void ReadHomeOnRestart();

/**
 * @brief Reads the actual position and displays it to user.
 */
void ReadActualPosition();

/**
 * @brief Reads the desired position and displays it to user.
 */
void ReadDesiredPosition();

/**
 * @brief Reads if it has to send a startup signal in the case of system restart from the EEPROM.
 */
void ReadSignalOnStart();

/**
 * @brief Writes the home position.
 * @param x The x-coordinate of the home position.
 * @param y The y-coordinate of the home position.
 */
void WriteHomePosition(uint16 x, uint16 y);

/**
 * @brief Writes the home position on restart.
 * @param b The value to write.
 */
void WriteHomeOnRestart(uint16 b);

/**
 * @brief Writes the desired position.
 * @param x The x-coordinate of the desired position.
 * @param y The y-coordinate of the desired position.
 */
void WriteDesiredPosition(uint16 x, uint16 y);

/**
 * @brief Sets the signal on start option in the EEPROM.
 * @param b The value to write.
 */
void WriteSignalOnStart(uint16 b);

/**
 * @brief Moves to the home position.
 */
void MoveToHome();

/**
 * @brief Lists the save slots.
 */
void listSaveSlots();

/**
 * @brief Tests the save slot.
 * @param id The ID of the save slot to test.
 * @return True if the save slot is in use, false otherwise.
 */
bool testSaveSlot(uint8 id);

/**
 * @brief Saves the slot details.
 * @param id The ID of the save slot.
 */
void saveSlotDetails(uint8 id);

/**
 * @brief Saves the actual position to the specified save slot.
 * @param id The ID of the save slot.
 */
void saveToSaveSlot(uint8 id);

/**
 * @brief Moves to the position stored in the save slot.
 * @param id The ID of the save slot.
 */
void moveToSaveSlot(uint8 id);

#endif

/* [] END OF FILE */

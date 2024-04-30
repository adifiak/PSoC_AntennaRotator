/**
 * @file eeprom.h
 * @brief Header file for EEPROM operations.
 *
 * This file contains the function prototypes for saving and loading data from EEPROM,
 * as well as setting and testing individual bits in EEPROM.
 */

#ifndef EEEPROM_H
#define EEEPROM_H
    
#include "project.h"
#include <stdbool.h>
   
/**
 * @brief Save a 16-bit word to EEPROM at the specified address.
 *
 * This function saves a 16-bit word to the EEPROM at the specified address.
 *
 * @param data The 16-bit word to be saved.
 * @param address The address in EEPROM where the word should be saved.
 */
void saveWord(uint16 data, uint8 address);

/**
 * @brief Load a 16-bit word from EEPROM at the specified address.
 *
 * This function loads a 16-bit word from the EEPROM at the specified address.
 *
 * @param address The address in EEPROM from where the word should be loaded.
 * @return The 16-bit word loaded from EEPROM.
 */
uint16 loadWord(uint8 address);

/**
 * @brief Set a specific bit in EEPROM at the specified address.
 *
 * This function sets a specific bit in EEPROM at the specified address to the given value.
 *
 * @param value The value to set the bit to (true or false).
 * @param bit The bit position to set (0-7).
 * @param address The address in EEPROM where the bit should be set.
 */
void setBit(bool value, uint8 bit, uint8 address);

/**
 * @brief Test a specific bit in EEPROM at the specified address.
 *
 * This function tests a specific bit in EEPROM at the specified address and returns its value.
 *
 * @param bit The bit position to test (0-7).
 * @param address The address in EEPROM where the bit should be tested.
 * @return The value of the tested bit (true or false).
 */
bool testBit(uint8 bit, uint8 address);
    
#endif

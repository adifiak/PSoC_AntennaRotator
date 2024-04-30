/**
 * @file cli.h
 * @brief Header file for the Command Line Interface (CLI) module.
 *
 * This file contains the declarations of functions and data structures used in the CLI module.
 * The CLI module provides functionality for processing commands and arguments entered through a command line interface.
 */

#ifndef CLI_H
#define CLI_H

#include "project.h"
#include <stdbool.h>
#include <stdio.h>

#define NO_ERROR false
#define ERROR    true

/**
 * @brief Enumeration representing the different states of reading input.
 */
typedef enum READ_STATE{
    CMD, /**< Command state */
    ARG1, /**< First argument state */
    ARG2, /**< Second argument state */
    ARG3 /**< Third argument state */
}READ_STATE;

/**
 * @brief Structure representing an input buffer.
 */
typedef struct INPUT_BUFFER{
    char data[5]; /**< Array to store input data */
    int cnt; /**< Counter for the number of characters in the buffer */
}INPUT_BUFFER;

extern enum READ_STATE readState; /**< Global variable representing the current read state */

struct INPUT_BUFFER cmd; /**< Global variable representing the command buffer */
struct INPUT_BUFFER arg1; /**< Global variable representing the first argument buffer */
struct INPUT_BUFFER arg2; /**< Global variable representing the second argument buffer */
struct INPUT_BUFFER arg3; /**< Global variable representing the third argument buffer */

/**
 * @brief Initializes the CLI module.
 */
void CLI_Init();

/**
 * @brief Updates the CLI module.
 *
 * This function should be called periodically to process input and execute commands.
 */
void CLI_Update();

/**
 * @brief Processes the current command and arguments.
 *
 * @return ERROR if the command was processed successfully, NO_ERROR otherwise.
 */
bool ProcessCommand();

/**
 * @brief Resets the input buffers.
 */
void ResetInput();

/**
 * @brief Adds a digit to the specified argument buffer.
 *
 * @param c The digit character to add.
 * @param arg The argument buffer to add the digit to.
 * @return ERROR if the digit was added successfully, NO_ERROR if the argument buffer is full.
 */
bool AddArgumentDigit(char c, struct INPUT_BUFFER* arg);

/**
 * @brief Adds a character to the specified command buffer.
 *
 * @param c The character to add.
 * @param cmd The command buffer to add the character to.
 * @return ERROR if the character was added successfully, NO_ERROR if the command buffer is full.
 */
bool AddCommandChar(char c, struct INPUT_BUFFER* cmd);

/**
 * @brief Parses the specified argument buffer and returns the parsed integer value.
 *
 * @param arg The argument buffer to parse.
 * @return The parsed integer value.
 */
int ParseArgument(struct INPUT_BUFFER* arg);

/**
 * @brief Checks if the current command is a no-argument function.
 *
 * @return ERROR if the current command is a no-argument function, NO_ERROR otherwise.
 */
bool isNoArgFnc();

/**
 * @brief Checks if the current command is a one-argument function.
 *
 * @return ERROR if the current command is a one-argument function, NO_ERROR otherwise.
 */
bool isOneArgFnc();

/**
 * @brief Checks if the current command is a two-argument function.
 *
 * @return ERROR if the current command is a two-argument function, NO_ERROR otherwise.
 */
bool isTwoArgFnc();

/**
 * @brief Checks if the current command is a three-argument function.
 *
 * @return ERROR if the current command is a three-argument function, NO_ERROR otherwise.
 */
bool isThreeArgFnc();

#endif
/* [] END OF FILE */
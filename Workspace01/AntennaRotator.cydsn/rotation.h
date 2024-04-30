/**
 * @file rotation.h
 * @brief Header file containing the declarations for the rotation module.
 *
 * This file contains the declarations for the rotation module, which provides functions
 * for controlling the rotation of an antenna. It also defines constants and a structure
 * for storing the rotation state.
 */

#ifndef ROTATION_H
#define ROTATION_H
    
#define ENCODER_ADDRESS 0x36 /**< I2C address of the encoder */
#define ENCODER_POS_REG 0x0E /**< Register address for reading the encoder position */

/**
 * @brief Macro to convert an angular value to the corresponding encoder value.
 *
 * This macro takes an angular value in degrees and converts it to the corresponding
 * encoder value. The encoder value is a 16-bit unsigned integer.
 *
 * @param x The angular value in degrees.
 * @return The corresponding encoder value.
 */
#define AS5600_FROM_ANGULAR(x) (uint16)(((float)(1 << 12) / 360.0f) * x)

/**
 * @brief Macro to convert an encoder value to the corresponding angular value.
 *
 * This macro takes an encoder value and converts it to the corresponding angular value
 * in degrees. The encoder value is a 16-bit unsigned integer.
 *
 * @param x The encoder value.
 * @return The corresponding angular value in degrees.
 */
#define AS5600_TO_ANGULAR(x) (x / ((float)(1 << 12) / 360.0f))

/**
 * @struct ROTATOR_STATE
 * @brief Structure for storing the rotation state.
 *
 * This structure stores the desired and actual rotation values in the x and y axes.
 */
typedef struct ROTATOR_STATE{
    int x_des; /**< Desired rotation value in the x axis */
    int y_des; /**< Desired rotation value in the y axis */
    int x_act; /**< Actual rotation value in the x axis */
    int y_act; /**< Actual rotation value in the y axis */
}ROTATOR_STATE;

/**
 * @brief Sets the desired rotation values.
 *
 * This function sets the desired rotation values for the x and y axes.
 *
 * @param x The desired rotation value in the x axis.
 * @param y The desired rotation value in the y axis.
 */
void setRotation(int x, int y);

/**
 * @brief Gets the current rotation state.
 *
 * This function returns the current rotation state, including the desired and actual
 * rotation values in the x and y axes.
 *
 * @return The current rotation state.
 */
ROTATOR_STATE getRotation();

/**
 * @brief Refreshes the rotation state.
 *
 * This function refreshes the rotation state by updating the actual rotation values
 * based on the current sensor readings.
 */
void refreshRotation();
    
#endif
/* [] END OF FILE */
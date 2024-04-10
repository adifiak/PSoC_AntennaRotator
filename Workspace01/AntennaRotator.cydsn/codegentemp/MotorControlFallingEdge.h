/*******************************************************************************
* File Name: MotorControlFallingEdge.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_MotorControlFallingEdge_H)
#define CY_ISR_MotorControlFallingEdge_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void MotorControlFallingEdge_Start(void);
void MotorControlFallingEdge_StartEx(cyisraddress address);
void MotorControlFallingEdge_Stop(void);

CY_ISR_PROTO(MotorControlFallingEdge_Interrupt);

void MotorControlFallingEdge_SetVector(cyisraddress address);
cyisraddress MotorControlFallingEdge_GetVector(void);

void MotorControlFallingEdge_SetPriority(uint8 priority);
uint8 MotorControlFallingEdge_GetPriority(void);

void MotorControlFallingEdge_Enable(void);
uint8 MotorControlFallingEdge_GetState(void);
void MotorControlFallingEdge_Disable(void);

void MotorControlFallingEdge_SetPending(void);
void MotorControlFallingEdge_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the MotorControlFallingEdge ISR. */
#define MotorControlFallingEdge_INTC_VECTOR            ((reg32 *) MotorControlFallingEdge__INTC_VECT)

/* Address of the MotorControlFallingEdge ISR priority. */
#define MotorControlFallingEdge_INTC_PRIOR             ((reg8 *) MotorControlFallingEdge__INTC_PRIOR_REG)

/* Priority of the MotorControlFallingEdge interrupt. */
#define MotorControlFallingEdge_INTC_PRIOR_NUMBER      MotorControlFallingEdge__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable MotorControlFallingEdge interrupt. */
#define MotorControlFallingEdge_INTC_SET_EN            ((reg32 *) MotorControlFallingEdge__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the MotorControlFallingEdge interrupt. */
#define MotorControlFallingEdge_INTC_CLR_EN            ((reg32 *) MotorControlFallingEdge__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the MotorControlFallingEdge interrupt state to pending. */
#define MotorControlFallingEdge_INTC_SET_PD            ((reg32 *) MotorControlFallingEdge__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the MotorControlFallingEdge interrupt. */
#define MotorControlFallingEdge_INTC_CLR_PD            ((reg32 *) MotorControlFallingEdge__INTC_CLR_PD_REG)


#endif /* CY_ISR_MotorControlFallingEdge_H */


/* [] END OF FILE */

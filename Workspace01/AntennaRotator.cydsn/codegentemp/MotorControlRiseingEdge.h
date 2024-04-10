/*******************************************************************************
* File Name: MotorControlRiseingEdge.h
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
#if !defined(CY_ISR_MotorControlRiseingEdge_H)
#define CY_ISR_MotorControlRiseingEdge_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void MotorControlRiseingEdge_Start(void);
void MotorControlRiseingEdge_StartEx(cyisraddress address);
void MotorControlRiseingEdge_Stop(void);

CY_ISR_PROTO(MotorControlRiseingEdge_Interrupt);

void MotorControlRiseingEdge_SetVector(cyisraddress address);
cyisraddress MotorControlRiseingEdge_GetVector(void);

void MotorControlRiseingEdge_SetPriority(uint8 priority);
uint8 MotorControlRiseingEdge_GetPriority(void);

void MotorControlRiseingEdge_Enable(void);
uint8 MotorControlRiseingEdge_GetState(void);
void MotorControlRiseingEdge_Disable(void);

void MotorControlRiseingEdge_SetPending(void);
void MotorControlRiseingEdge_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the MotorControlRiseingEdge ISR. */
#define MotorControlRiseingEdge_INTC_VECTOR            ((reg32 *) MotorControlRiseingEdge__INTC_VECT)

/* Address of the MotorControlRiseingEdge ISR priority. */
#define MotorControlRiseingEdge_INTC_PRIOR             ((reg8 *) MotorControlRiseingEdge__INTC_PRIOR_REG)

/* Priority of the MotorControlRiseingEdge interrupt. */
#define MotorControlRiseingEdge_INTC_PRIOR_NUMBER      MotorControlRiseingEdge__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable MotorControlRiseingEdge interrupt. */
#define MotorControlRiseingEdge_INTC_SET_EN            ((reg32 *) MotorControlRiseingEdge__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the MotorControlRiseingEdge interrupt. */
#define MotorControlRiseingEdge_INTC_CLR_EN            ((reg32 *) MotorControlRiseingEdge__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the MotorControlRiseingEdge interrupt state to pending. */
#define MotorControlRiseingEdge_INTC_SET_PD            ((reg32 *) MotorControlRiseingEdge__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the MotorControlRiseingEdge interrupt. */
#define MotorControlRiseingEdge_INTC_CLR_PD            ((reg32 *) MotorControlRiseingEdge__INTC_CLR_PD_REG)


#endif /* CY_ISR_MotorControlRiseingEdge_H */


/* [] END OF FILE */

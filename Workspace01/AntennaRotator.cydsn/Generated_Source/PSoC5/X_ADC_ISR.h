/*******************************************************************************
* File Name: X_ADC_ISR.h
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
#if !defined(CY_ISR_X_ADC_ISR_H)
#define CY_ISR_X_ADC_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void X_ADC_ISR_Start(void);
void X_ADC_ISR_StartEx(cyisraddress address);
void X_ADC_ISR_Stop(void);

CY_ISR_PROTO(X_ADC_ISR_Interrupt);

void X_ADC_ISR_SetVector(cyisraddress address);
cyisraddress X_ADC_ISR_GetVector(void);

void X_ADC_ISR_SetPriority(uint8 priority);
uint8 X_ADC_ISR_GetPriority(void);

void X_ADC_ISR_Enable(void);
uint8 X_ADC_ISR_GetState(void);
void X_ADC_ISR_Disable(void);

void X_ADC_ISR_SetPending(void);
void X_ADC_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the X_ADC_ISR ISR. */
#define X_ADC_ISR_INTC_VECTOR            ((reg32 *) X_ADC_ISR__INTC_VECT)

/* Address of the X_ADC_ISR ISR priority. */
#define X_ADC_ISR_INTC_PRIOR             ((reg8 *) X_ADC_ISR__INTC_PRIOR_REG)

/* Priority of the X_ADC_ISR interrupt. */
#define X_ADC_ISR_INTC_PRIOR_NUMBER      X_ADC_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable X_ADC_ISR interrupt. */
#define X_ADC_ISR_INTC_SET_EN            ((reg32 *) X_ADC_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the X_ADC_ISR interrupt. */
#define X_ADC_ISR_INTC_CLR_EN            ((reg32 *) X_ADC_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the X_ADC_ISR interrupt state to pending. */
#define X_ADC_ISR_INTC_SET_PD            ((reg32 *) X_ADC_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the X_ADC_ISR interrupt. */
#define X_ADC_ISR_INTC_CLR_PD            ((reg32 *) X_ADC_ISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_X_ADC_ISR_H */


/* [] END OF FILE */

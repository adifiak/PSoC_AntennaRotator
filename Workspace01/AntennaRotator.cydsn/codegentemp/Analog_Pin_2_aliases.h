/*******************************************************************************
* File Name: Analog_Pin_2.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Analog_Pin_2_ALIASES_H) /* Pins Analog_Pin_2_ALIASES_H */
#define CY_PINS_Analog_Pin_2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Analog_Pin_2_0			(Analog_Pin_2__0__PC)
#define Analog_Pin_2_0_INTR	((uint16)((uint16)0x0001u << Analog_Pin_2__0__SHIFT))

#define Analog_Pin_2_INTR_ALL	 ((uint16)(Analog_Pin_2_0_INTR))

#endif /* End Pins Analog_Pin_2_ALIASES_H */


/* [] END OF FILE */

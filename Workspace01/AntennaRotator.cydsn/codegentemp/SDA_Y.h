/*******************************************************************************
* File Name: SDA_Y.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SDA_Y_H) /* Pins SDA_Y_H */
#define CY_PINS_SDA_Y_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SDA_Y_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SDA_Y__PORT == 15 && ((SDA_Y__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SDA_Y_Write(uint8 value);
void    SDA_Y_SetDriveMode(uint8 mode);
uint8   SDA_Y_ReadDataReg(void);
uint8   SDA_Y_Read(void);
void    SDA_Y_SetInterruptMode(uint16 position, uint16 mode);
uint8   SDA_Y_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SDA_Y_SetDriveMode() function.
     *  @{
     */
        #define SDA_Y_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SDA_Y_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SDA_Y_DM_RES_UP          PIN_DM_RES_UP
        #define SDA_Y_DM_RES_DWN         PIN_DM_RES_DWN
        #define SDA_Y_DM_OD_LO           PIN_DM_OD_LO
        #define SDA_Y_DM_OD_HI           PIN_DM_OD_HI
        #define SDA_Y_DM_STRONG          PIN_DM_STRONG
        #define SDA_Y_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SDA_Y_MASK               SDA_Y__MASK
#define SDA_Y_SHIFT              SDA_Y__SHIFT
#define SDA_Y_WIDTH              1u

/* Interrupt constants */
#if defined(SDA_Y__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SDA_Y_SetInterruptMode() function.
     *  @{
     */
        #define SDA_Y_INTR_NONE      (uint16)(0x0000u)
        #define SDA_Y_INTR_RISING    (uint16)(0x0001u)
        #define SDA_Y_INTR_FALLING   (uint16)(0x0002u)
        #define SDA_Y_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SDA_Y_INTR_MASK      (0x01u) 
#endif /* (SDA_Y__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SDA_Y_PS                     (* (reg8 *) SDA_Y__PS)
/* Data Register */
#define SDA_Y_DR                     (* (reg8 *) SDA_Y__DR)
/* Port Number */
#define SDA_Y_PRT_NUM                (* (reg8 *) SDA_Y__PRT) 
/* Connect to Analog Globals */                                                  
#define SDA_Y_AG                     (* (reg8 *) SDA_Y__AG)                       
/* Analog MUX bux enable */
#define SDA_Y_AMUX                   (* (reg8 *) SDA_Y__AMUX) 
/* Bidirectional Enable */                                                        
#define SDA_Y_BIE                    (* (reg8 *) SDA_Y__BIE)
/* Bit-mask for Aliased Register Access */
#define SDA_Y_BIT_MASK               (* (reg8 *) SDA_Y__BIT_MASK)
/* Bypass Enable */
#define SDA_Y_BYP                    (* (reg8 *) SDA_Y__BYP)
/* Port wide control signals */                                                   
#define SDA_Y_CTL                    (* (reg8 *) SDA_Y__CTL)
/* Drive Modes */
#define SDA_Y_DM0                    (* (reg8 *) SDA_Y__DM0) 
#define SDA_Y_DM1                    (* (reg8 *) SDA_Y__DM1)
#define SDA_Y_DM2                    (* (reg8 *) SDA_Y__DM2) 
/* Input Buffer Disable Override */
#define SDA_Y_INP_DIS                (* (reg8 *) SDA_Y__INP_DIS)
/* LCD Common or Segment Drive */
#define SDA_Y_LCD_COM_SEG            (* (reg8 *) SDA_Y__LCD_COM_SEG)
/* Enable Segment LCD */
#define SDA_Y_LCD_EN                 (* (reg8 *) SDA_Y__LCD_EN)
/* Slew Rate Control */
#define SDA_Y_SLW                    (* (reg8 *) SDA_Y__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SDA_Y_PRTDSI__CAPS_SEL       (* (reg8 *) SDA_Y__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SDA_Y_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SDA_Y__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SDA_Y_PRTDSI__OE_SEL0        (* (reg8 *) SDA_Y__PRTDSI__OE_SEL0) 
#define SDA_Y_PRTDSI__OE_SEL1        (* (reg8 *) SDA_Y__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SDA_Y_PRTDSI__OUT_SEL0       (* (reg8 *) SDA_Y__PRTDSI__OUT_SEL0) 
#define SDA_Y_PRTDSI__OUT_SEL1       (* (reg8 *) SDA_Y__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SDA_Y_PRTDSI__SYNC_OUT       (* (reg8 *) SDA_Y__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SDA_Y__SIO_CFG)
    #define SDA_Y_SIO_HYST_EN        (* (reg8 *) SDA_Y__SIO_HYST_EN)
    #define SDA_Y_SIO_REG_HIFREQ     (* (reg8 *) SDA_Y__SIO_REG_HIFREQ)
    #define SDA_Y_SIO_CFG            (* (reg8 *) SDA_Y__SIO_CFG)
    #define SDA_Y_SIO_DIFF           (* (reg8 *) SDA_Y__SIO_DIFF)
#endif /* (SDA_Y__SIO_CFG) */

/* Interrupt Registers */
#if defined(SDA_Y__INTSTAT)
    #define SDA_Y_INTSTAT            (* (reg8 *) SDA_Y__INTSTAT)
    #define SDA_Y_SNAP               (* (reg8 *) SDA_Y__SNAP)
    
	#define SDA_Y_0_INTTYPE_REG 		(* (reg8 *) SDA_Y__0__INTTYPE)
#endif /* (SDA_Y__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SDA_Y_H */


/* [] END OF FILE */

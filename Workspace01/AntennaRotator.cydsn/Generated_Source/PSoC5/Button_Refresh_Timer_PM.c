/*******************************************************************************
* File Name: Button_Refresh_Timer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Button_Refresh_Timer.h"

static Button_Refresh_Timer_backupStruct Button_Refresh_Timer_backup;


/*******************************************************************************
* Function Name: Button_Refresh_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Button_Refresh_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Button_Refresh_Timer_SaveConfig(void) 
{
    #if (!Button_Refresh_Timer_UsingFixedFunction)
        Button_Refresh_Timer_backup.TimerUdb = Button_Refresh_Timer_ReadCounter();
        Button_Refresh_Timer_backup.InterruptMaskValue = Button_Refresh_Timer_STATUS_MASK;
        #if (Button_Refresh_Timer_UsingHWCaptureCounter)
            Button_Refresh_Timer_backup.TimerCaptureCounter = Button_Refresh_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Button_Refresh_Timer_UDB_CONTROL_REG_REMOVED)
            Button_Refresh_Timer_backup.TimerControlRegister = Button_Refresh_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Button_Refresh_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Button_Refresh_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Button_Refresh_Timer_RestoreConfig(void) 
{   
    #if (!Button_Refresh_Timer_UsingFixedFunction)

        Button_Refresh_Timer_WriteCounter(Button_Refresh_Timer_backup.TimerUdb);
        Button_Refresh_Timer_STATUS_MASK =Button_Refresh_Timer_backup.InterruptMaskValue;
        #if (Button_Refresh_Timer_UsingHWCaptureCounter)
            Button_Refresh_Timer_SetCaptureCount(Button_Refresh_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Button_Refresh_Timer_UDB_CONTROL_REG_REMOVED)
            Button_Refresh_Timer_WriteControlRegister(Button_Refresh_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Button_Refresh_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Button_Refresh_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Button_Refresh_Timer_Sleep(void) 
{
    #if(!Button_Refresh_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Button_Refresh_Timer_CTRL_ENABLE == (Button_Refresh_Timer_CONTROL & Button_Refresh_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Button_Refresh_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Button_Refresh_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Button_Refresh_Timer_Stop();
    Button_Refresh_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Button_Refresh_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Button_Refresh_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Button_Refresh_Timer_Wakeup(void) 
{
    Button_Refresh_Timer_RestoreConfig();
    #if(!Button_Refresh_Timer_UDB_CONTROL_REG_REMOVED)
        if(Button_Refresh_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Button_Refresh_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

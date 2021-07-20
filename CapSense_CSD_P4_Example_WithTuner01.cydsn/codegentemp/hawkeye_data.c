/*******************************************************************************
* File Name: hawkeye_data.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "hawkeye_data.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        hawkeye_data_PC =   (hawkeye_data_PC & \
                                (uint32)(~(uint32)(hawkeye_data_DRIVE_MODE_IND_MASK << (hawkeye_data_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (hawkeye_data_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: hawkeye_data_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void hawkeye_data_Write(uint8 value) 
{
    uint8 drVal = (uint8)(hawkeye_data_DR & (uint8)(~hawkeye_data_MASK));
    drVal = (drVal | ((uint8)(value << hawkeye_data_SHIFT) & hawkeye_data_MASK));
    hawkeye_data_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: hawkeye_data_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  hawkeye_data_DM_STRONG     Strong Drive 
*  hawkeye_data_DM_OD_HI      Open Drain, Drives High 
*  hawkeye_data_DM_OD_LO      Open Drain, Drives Low 
*  hawkeye_data_DM_RES_UP     Resistive Pull Up 
*  hawkeye_data_DM_RES_DWN    Resistive Pull Down 
*  hawkeye_data_DM_RES_UPDWN  Resistive Pull Up/Down 
*  hawkeye_data_DM_DIG_HIZ    High Impedance Digital 
*  hawkeye_data_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void hawkeye_data_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(hawkeye_data__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: hawkeye_data_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro hawkeye_data_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 hawkeye_data_Read(void) 
{
    return (uint8)((hawkeye_data_PS & hawkeye_data_MASK) >> hawkeye_data_SHIFT);
}


/*******************************************************************************
* Function Name: hawkeye_data_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 hawkeye_data_ReadDataReg(void) 
{
    return (uint8)((hawkeye_data_DR & hawkeye_data_MASK) >> hawkeye_data_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(hawkeye_data_INTSTAT) 

    /*******************************************************************************
    * Function Name: hawkeye_data_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 hawkeye_data_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(hawkeye_data_INTSTAT & hawkeye_data_MASK);
		hawkeye_data_INTSTAT = maskedStatus;
        return maskedStatus >> hawkeye_data_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

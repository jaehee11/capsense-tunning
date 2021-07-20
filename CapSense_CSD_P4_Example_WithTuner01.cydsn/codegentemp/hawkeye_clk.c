/*******************************************************************************
* File Name: hawkeye_clk.c  
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
#include "hawkeye_clk.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        hawkeye_clk_PC =   (hawkeye_clk_PC & \
                                (uint32)(~(uint32)(hawkeye_clk_DRIVE_MODE_IND_MASK << (hawkeye_clk_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (hawkeye_clk_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: hawkeye_clk_Write
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
void hawkeye_clk_Write(uint8 value) 
{
    uint8 drVal = (uint8)(hawkeye_clk_DR & (uint8)(~hawkeye_clk_MASK));
    drVal = (drVal | ((uint8)(value << hawkeye_clk_SHIFT) & hawkeye_clk_MASK));
    hawkeye_clk_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: hawkeye_clk_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  hawkeye_clk_DM_STRONG     Strong Drive 
*  hawkeye_clk_DM_OD_HI      Open Drain, Drives High 
*  hawkeye_clk_DM_OD_LO      Open Drain, Drives Low 
*  hawkeye_clk_DM_RES_UP     Resistive Pull Up 
*  hawkeye_clk_DM_RES_DWN    Resistive Pull Down 
*  hawkeye_clk_DM_RES_UPDWN  Resistive Pull Up/Down 
*  hawkeye_clk_DM_DIG_HIZ    High Impedance Digital 
*  hawkeye_clk_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void hawkeye_clk_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(hawkeye_clk__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: hawkeye_clk_Read
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
*  Macro hawkeye_clk_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 hawkeye_clk_Read(void) 
{
    return (uint8)((hawkeye_clk_PS & hawkeye_clk_MASK) >> hawkeye_clk_SHIFT);
}


/*******************************************************************************
* Function Name: hawkeye_clk_ReadDataReg
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
uint8 hawkeye_clk_ReadDataReg(void) 
{
    return (uint8)((hawkeye_clk_DR & hawkeye_clk_MASK) >> hawkeye_clk_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(hawkeye_clk_INTSTAT) 

    /*******************************************************************************
    * Function Name: hawkeye_clk_ClearInterrupt
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
    uint8 hawkeye_clk_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(hawkeye_clk_INTSTAT & hawkeye_clk_MASK);
		hawkeye_clk_INTSTAT = maskedStatus;
        return maskedStatus >> hawkeye_clk_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

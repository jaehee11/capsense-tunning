/*******************************************************************************
* File Name: UnUsedPin_11.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "UnUsedPin_11.h"

static UnUsedPin_11_BACKUP_STRUCT  UnUsedPin_11_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: UnUsedPin_11_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet UnUsedPin_11_SUT.c usage_UnUsedPin_11_Sleep_Wakeup
*******************************************************************************/
void UnUsedPin_11_Sleep(void)
{
    #if defined(UnUsedPin_11__PC)
        UnUsedPin_11_backup.pcState = UnUsedPin_11_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            UnUsedPin_11_backup.usbState = UnUsedPin_11_CR1_REG;
            UnUsedPin_11_USB_POWER_REG |= UnUsedPin_11_USBIO_ENTER_SLEEP;
            UnUsedPin_11_CR1_REG &= UnUsedPin_11_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UnUsedPin_11__SIO)
        UnUsedPin_11_backup.sioState = UnUsedPin_11_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        UnUsedPin_11_SIO_REG &= (uint32)(~UnUsedPin_11_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: UnUsedPin_11_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to UnUsedPin_11_Sleep() for an example usage.
*******************************************************************************/
void UnUsedPin_11_Wakeup(void)
{
    #if defined(UnUsedPin_11__PC)
        UnUsedPin_11_PC = UnUsedPin_11_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            UnUsedPin_11_USB_POWER_REG &= UnUsedPin_11_USBIO_EXIT_SLEEP_PH1;
            UnUsedPin_11_CR1_REG = UnUsedPin_11_backup.usbState;
            UnUsedPin_11_USB_POWER_REG &= UnUsedPin_11_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UnUsedPin_11__SIO)
        UnUsedPin_11_SIO_REG = UnUsedPin_11_backup.sioState;
    #endif
}


/* [] END OF FILE */

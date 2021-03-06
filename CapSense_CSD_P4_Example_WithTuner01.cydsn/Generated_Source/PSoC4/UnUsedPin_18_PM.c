/*******************************************************************************
* File Name: UnUsedPin_18.c  
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
#include "UnUsedPin_18.h"

static UnUsedPin_18_BACKUP_STRUCT  UnUsedPin_18_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: UnUsedPin_18_Sleep
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
*  \snippet UnUsedPin_18_SUT.c usage_UnUsedPin_18_Sleep_Wakeup
*******************************************************************************/
void UnUsedPin_18_Sleep(void)
{
    #if defined(UnUsedPin_18__PC)
        UnUsedPin_18_backup.pcState = UnUsedPin_18_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            UnUsedPin_18_backup.usbState = UnUsedPin_18_CR1_REG;
            UnUsedPin_18_USB_POWER_REG |= UnUsedPin_18_USBIO_ENTER_SLEEP;
            UnUsedPin_18_CR1_REG &= UnUsedPin_18_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UnUsedPin_18__SIO)
        UnUsedPin_18_backup.sioState = UnUsedPin_18_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        UnUsedPin_18_SIO_REG &= (uint32)(~UnUsedPin_18_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: UnUsedPin_18_Wakeup
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
*  Refer to UnUsedPin_18_Sleep() for an example usage.
*******************************************************************************/
void UnUsedPin_18_Wakeup(void)
{
    #if defined(UnUsedPin_18__PC)
        UnUsedPin_18_PC = UnUsedPin_18_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            UnUsedPin_18_USB_POWER_REG &= UnUsedPin_18_USBIO_EXIT_SLEEP_PH1;
            UnUsedPin_18_CR1_REG = UnUsedPin_18_backup.usbState;
            UnUsedPin_18_USB_POWER_REG &= UnUsedPin_18_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UnUsedPin_18__SIO)
        UnUsedPin_18_SIO_REG = UnUsedPin_18_backup.sioState;
    #endif
}


/* [] END OF FILE */

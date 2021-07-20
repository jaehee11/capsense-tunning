/*******************************************************************************
* File Name: hawkeye_data.c  
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
#include "hawkeye_data.h"

static hawkeye_data_BACKUP_STRUCT  hawkeye_data_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: hawkeye_data_Sleep
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
*  \snippet hawkeye_data_SUT.c usage_hawkeye_data_Sleep_Wakeup
*******************************************************************************/
void hawkeye_data_Sleep(void)
{
    #if defined(hawkeye_data__PC)
        hawkeye_data_backup.pcState = hawkeye_data_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            hawkeye_data_backup.usbState = hawkeye_data_CR1_REG;
            hawkeye_data_USB_POWER_REG |= hawkeye_data_USBIO_ENTER_SLEEP;
            hawkeye_data_CR1_REG &= hawkeye_data_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(hawkeye_data__SIO)
        hawkeye_data_backup.sioState = hawkeye_data_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        hawkeye_data_SIO_REG &= (uint32)(~hawkeye_data_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: hawkeye_data_Wakeup
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
*  Refer to hawkeye_data_Sleep() for an example usage.
*******************************************************************************/
void hawkeye_data_Wakeup(void)
{
    #if defined(hawkeye_data__PC)
        hawkeye_data_PC = hawkeye_data_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            hawkeye_data_USB_POWER_REG &= hawkeye_data_USBIO_EXIT_SLEEP_PH1;
            hawkeye_data_CR1_REG = hawkeye_data_backup.usbState;
            hawkeye_data_USB_POWER_REG &= hawkeye_data_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(hawkeye_data__SIO)
        hawkeye_data_SIO_REG = hawkeye_data_backup.sioState;
    #endif
}


/* [] END OF FILE */

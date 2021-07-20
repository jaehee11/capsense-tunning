/*******************************************************************************
* File Name: SCB_PM.c
* Version 3.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCB.h"
#include "SCB_PVT.h"

#if(SCB_SCB_MODE_I2C_INC)
    #include "SCB_I2C_PVT.h"
#endif /* (SCB_SCB_MODE_I2C_INC) */

#if(SCB_SCB_MODE_EZI2C_INC)
    #include "SCB_EZI2C_PVT.h"
#endif /* (SCB_SCB_MODE_EZI2C_INC) */

#if(SCB_SCB_MODE_SPI_INC || SCB_SCB_MODE_UART_INC)
    #include "SCB_SPI_UART_PVT.h"
#endif /* (SCB_SCB_MODE_SPI_INC || SCB_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(SCB_SCB_MODE_UNCONFIG_CONST_CFG || \
   (SCB_SCB_MODE_I2C_CONST_CFG   && (!SCB_I2C_WAKE_ENABLE_CONST))   || \
   (SCB_SCB_MODE_EZI2C_CONST_CFG && (!SCB_EZI2C_WAKE_ENABLE_CONST)) || \
   (SCB_SCB_MODE_SPI_CONST_CFG   && (!SCB_SPI_WAKE_ENABLE_CONST))   || \
   (SCB_SCB_MODE_UART_CONST_CFG  && (!SCB_UART_WAKE_ENABLE_CONST)))

    SCB_BACKUP_STRUCT SCB_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: SCB_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB_Sleep(void)
{
#if(SCB_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SCB_SCB_WAKE_ENABLE_CHECK)
    {
        if(SCB_SCB_MODE_I2C_RUNTM_CFG)
        {
            SCB_I2CSaveConfig();
        }
        else if(SCB_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SCB_EzI2CSaveConfig();
        }
    #if(!SCB_CY_SCBIP_V1)
        else if(SCB_SCB_MODE_SPI_RUNTM_CFG)
        {
            SCB_SpiSaveConfig();
        }
        else if(SCB_SCB_MODE_UART_RUNTM_CFG)
        {
            SCB_UartSaveConfig();
        }
    #endif /* (!SCB_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        SCB_backup.enableState = (uint8) SCB_GET_CTRL_ENABLED;

        if(0u != SCB_backup.enableState)
        {
            SCB_Stop();
        }
    }

#else

    #if (SCB_SCB_MODE_I2C_CONST_CFG && SCB_I2C_WAKE_ENABLE_CONST)
        SCB_I2CSaveConfig();

    #elif (SCB_SCB_MODE_EZI2C_CONST_CFG && SCB_EZI2C_WAKE_ENABLE_CONST)
        SCB_EzI2CSaveConfig();

    #elif (SCB_SCB_MODE_SPI_CONST_CFG && SCB_SPI_WAKE_ENABLE_CONST)
        SCB_SpiSaveConfig();

    #elif (SCB_SCB_MODE_UART_CONST_CFG && SCB_UART_WAKE_ENABLE_CONST)
        SCB_UartSaveConfig();

    #else

        SCB_backup.enableState = (uint8) SCB_GET_CTRL_ENABLED;

        if(0u != SCB_backup.enableState)
        {
            SCB_Stop();
        }

    #endif /* defined (SCB_SCB_MODE_I2C_CONST_CFG) && (SCB_I2C_WAKE_ENABLE_CONST) */

#endif /* (SCB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB_Wakeup(void)
{
#if(SCB_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SCB_SCB_WAKE_ENABLE_CHECK)
    {
        if(SCB_SCB_MODE_I2C_RUNTM_CFG)
        {
            SCB_I2CRestoreConfig();
        }
        else if(SCB_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SCB_EzI2CRestoreConfig();
        }
    #if(!SCB_CY_SCBIP_V1)
        else if(SCB_SCB_MODE_SPI_RUNTM_CFG)
        {
            SCB_SpiRestoreConfig();
        }
        else if(SCB_SCB_MODE_UART_RUNTM_CFG)
        {
            SCB_UartRestoreConfig();
        }
    #endif /* (!SCB_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != SCB_backup.enableState)
        {
            SCB_Enable();
        }
    }

#else

    #if (SCB_SCB_MODE_I2C_CONST_CFG  && SCB_I2C_WAKE_ENABLE_CONST)
        SCB_I2CRestoreConfig();

    #elif (SCB_SCB_MODE_EZI2C_CONST_CFG && SCB_EZI2C_WAKE_ENABLE_CONST)
        SCB_EzI2CRestoreConfig();

    #elif (SCB_SCB_MODE_SPI_CONST_CFG && SCB_SPI_WAKE_ENABLE_CONST)
        SCB_SpiRestoreConfig();

    #elif (SCB_SCB_MODE_UART_CONST_CFG && SCB_UART_WAKE_ENABLE_CONST)
        SCB_UartRestoreConfig();

    #else

        if(0u != SCB_backup.enableState)
        {
            SCB_Enable();
        }

    #endif /* (SCB_I2C_WAKE_ENABLE_CONST) */

#endif /* (SCB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */

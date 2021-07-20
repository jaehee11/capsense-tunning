/*******************************************************************************
* File Name: EzI2C_1_PM.c
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

#include "EzI2C_1.h"
#include "EzI2C_1_PVT.h"

#if(EzI2C_1_SCB_MODE_I2C_INC)
    #include "EzI2C_1_I2C_PVT.h"
#endif /* (EzI2C_1_SCB_MODE_I2C_INC) */

#if(EzI2C_1_SCB_MODE_EZI2C_INC)
    #include "EzI2C_1_EZI2C_PVT.h"
#endif /* (EzI2C_1_SCB_MODE_EZI2C_INC) */

#if(EzI2C_1_SCB_MODE_SPI_INC || EzI2C_1_SCB_MODE_UART_INC)
    #include "EzI2C_1_SPI_UART_PVT.h"
#endif /* (EzI2C_1_SCB_MODE_SPI_INC || EzI2C_1_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG || \
   (EzI2C_1_SCB_MODE_I2C_CONST_CFG   && (!EzI2C_1_I2C_WAKE_ENABLE_CONST))   || \
   (EzI2C_1_SCB_MODE_EZI2C_CONST_CFG && (!EzI2C_1_EZI2C_WAKE_ENABLE_CONST)) || \
   (EzI2C_1_SCB_MODE_SPI_CONST_CFG   && (!EzI2C_1_SPI_WAKE_ENABLE_CONST))   || \
   (EzI2C_1_SCB_MODE_UART_CONST_CFG  && (!EzI2C_1_UART_WAKE_ENABLE_CONST)))

    EzI2C_1_BACKUP_STRUCT EzI2C_1_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: EzI2C_1_Sleep
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
void EzI2C_1_Sleep(void)
{
#if(EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(EzI2C_1_SCB_WAKE_ENABLE_CHECK)
    {
        if(EzI2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            EzI2C_1_I2CSaveConfig();
        }
        else if(EzI2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            EzI2C_1_EzI2CSaveConfig();
        }
    #if(!EzI2C_1_CY_SCBIP_V1)
        else if(EzI2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            EzI2C_1_SpiSaveConfig();
        }
        else if(EzI2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            EzI2C_1_UartSaveConfig();
        }
    #endif /* (!EzI2C_1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        EzI2C_1_backup.enableState = (uint8) EzI2C_1_GET_CTRL_ENABLED;

        if(0u != EzI2C_1_backup.enableState)
        {
            EzI2C_1_Stop();
        }
    }

#else

    #if (EzI2C_1_SCB_MODE_I2C_CONST_CFG && EzI2C_1_I2C_WAKE_ENABLE_CONST)
        EzI2C_1_I2CSaveConfig();

    #elif (EzI2C_1_SCB_MODE_EZI2C_CONST_CFG && EzI2C_1_EZI2C_WAKE_ENABLE_CONST)
        EzI2C_1_EzI2CSaveConfig();

    #elif (EzI2C_1_SCB_MODE_SPI_CONST_CFG && EzI2C_1_SPI_WAKE_ENABLE_CONST)
        EzI2C_1_SpiSaveConfig();

    #elif (EzI2C_1_SCB_MODE_UART_CONST_CFG && EzI2C_1_UART_WAKE_ENABLE_CONST)
        EzI2C_1_UartSaveConfig();

    #else

        EzI2C_1_backup.enableState = (uint8) EzI2C_1_GET_CTRL_ENABLED;

        if(0u != EzI2C_1_backup.enableState)
        {
            EzI2C_1_Stop();
        }

    #endif /* defined (EzI2C_1_SCB_MODE_I2C_CONST_CFG) && (EzI2C_1_I2C_WAKE_ENABLE_CONST) */

#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EzI2C_1_Wakeup
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
void EzI2C_1_Wakeup(void)
{
#if(EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(EzI2C_1_SCB_WAKE_ENABLE_CHECK)
    {
        if(EzI2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            EzI2C_1_I2CRestoreConfig();
        }
        else if(EzI2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            EzI2C_1_EzI2CRestoreConfig();
        }
    #if(!EzI2C_1_CY_SCBIP_V1)
        else if(EzI2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            EzI2C_1_SpiRestoreConfig();
        }
        else if(EzI2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            EzI2C_1_UartRestoreConfig();
        }
    #endif /* (!EzI2C_1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != EzI2C_1_backup.enableState)
        {
            EzI2C_1_Enable();
        }
    }

#else

    #if (EzI2C_1_SCB_MODE_I2C_CONST_CFG  && EzI2C_1_I2C_WAKE_ENABLE_CONST)
        EzI2C_1_I2CRestoreConfig();

    #elif (EzI2C_1_SCB_MODE_EZI2C_CONST_CFG && EzI2C_1_EZI2C_WAKE_ENABLE_CONST)
        EzI2C_1_EzI2CRestoreConfig();

    #elif (EzI2C_1_SCB_MODE_SPI_CONST_CFG && EzI2C_1_SPI_WAKE_ENABLE_CONST)
        EzI2C_1_SpiRestoreConfig();

    #elif (EzI2C_1_SCB_MODE_UART_CONST_CFG && EzI2C_1_UART_WAKE_ENABLE_CONST)
        EzI2C_1_UartRestoreConfig();

    #else

        if(0u != EzI2C_1_backup.enableState)
        {
            EzI2C_1_Enable();
        }

    #endif /* (EzI2C_1_I2C_WAKE_ENABLE_CONST) */

#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */

/*******************************************************************************
* File Name: EzI2C_1.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "EzI2C_1_PVT.h"

#if (EzI2C_1_SCB_MODE_I2C_INC)
    #include "EzI2C_1_I2C_PVT.h"
#endif /* (EzI2C_1_SCB_MODE_I2C_INC) */

#if (EzI2C_1_SCB_MODE_EZI2C_INC)
    #include "EzI2C_1_EZI2C_PVT.h"
#endif /* (EzI2C_1_SCB_MODE_EZI2C_INC) */

#if (EzI2C_1_SCB_MODE_SPI_INC || EzI2C_1_SCB_MODE_UART_INC)
    #include "EzI2C_1_SPI_UART_PVT.h"
#endif /* (EzI2C_1_SCB_MODE_SPI_INC || EzI2C_1_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 EzI2C_1_scbMode = EzI2C_1_SCB_MODE_UNCONFIG;
    uint8 EzI2C_1_scbEnableWake;
    uint8 EzI2C_1_scbEnableIntr;

    /* I2C configuration variables */
    uint8 EzI2C_1_mode;
    uint8 EzI2C_1_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * EzI2C_1_rxBuffer;
    uint8  EzI2C_1_rxDataBits;
    uint32 EzI2C_1_rxBufferSize;

    volatile uint8 * EzI2C_1_txBuffer;
    uint8  EzI2C_1_txDataBits;
    uint32 EzI2C_1_txBufferSize;

    /* EZI2C configuration variables */
    uint8 EzI2C_1_numberOfAddr;
    uint8 EzI2C_1_subAddrSize;
#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 EzI2C_1_initVar = 0u;

#if (EzI2C_1_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_EzI2C_1_CUSTOM_INTR_HANDLER)
    void (*EzI2C_1_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_EzI2C_1_CUSTOM_INTR_HANDLER) */
#endif /* (EzI2C_1_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void EzI2C_1_ScbEnableIntr(void);
static void EzI2C_1_ScbModeStop(void);
static void EzI2C_1_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: EzI2C_1_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EzI2C_1_Init(void)
{
#if (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    if (EzI2C_1_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        EzI2C_1_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (EzI2C_1_SCB_MODE_I2C_CONST_CFG)
    EzI2C_1_I2CInit();

#elif (EzI2C_1_SCB_MODE_SPI_CONST_CFG)
    EzI2C_1_SpiInit();

#elif (EzI2C_1_SCB_MODE_UART_CONST_CFG)
    EzI2C_1_UartInit();

#elif (EzI2C_1_SCB_MODE_EZI2C_CONST_CFG)
    EzI2C_1_EzI2CInit();

#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EzI2C_1_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EzI2C_1_Enable(void)
{
#if (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!EzI2C_1_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        EzI2C_1_CTRL_REG |= EzI2C_1_CTRL_ENABLED;

        EzI2C_1_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        EzI2C_1_ScbModePostEnable();
    }
#else
    EzI2C_1_CTRL_REG |= EzI2C_1_CTRL_ENABLED;

    EzI2C_1_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    EzI2C_1_ScbModePostEnable();
#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EzI2C_1_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EzI2C_1_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void EzI2C_1_Start(void)
{
    if (0u == EzI2C_1_initVar)
    {
        EzI2C_1_Init();
        EzI2C_1_initVar = 1u; /* Component was initialized */
    }

    EzI2C_1_Enable();
}


/*******************************************************************************
* Function Name: EzI2C_1_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*  It also disables all TX interrupt sources so as not to cause an unexpected
*  interrupt trigger because after the component is enabled, the TX FIFO 
*  is empty.
*
* Parameters:
*  None
*
* Return:
*  None
* 
*******************************************************************************/
void EzI2C_1_Stop(void)
{
#if (EzI2C_1_SCB_IRQ_INTERNAL)
    EzI2C_1_DisableInt();
#endif /* (EzI2C_1_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    EzI2C_1_ScbModeStop();

    /* Disable SCB IP */
    EzI2C_1_CTRL_REG &= (uint32) ~EzI2C_1_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    EzI2C_1_SetTxInterruptMode(EzI2C_1_NO_INTR_SOURCES);

#if (EzI2C_1_SCB_IRQ_INTERNAL)
    EzI2C_1_ClearPendingInt();
#endif /* (EzI2C_1_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: EzI2C_1_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void EzI2C_1_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = EzI2C_1_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~EzI2C_1_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (EzI2C_1_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    EzI2C_1_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: EzI2C_1_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void EzI2C_1_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = EzI2C_1_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~EzI2C_1_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (EzI2C_1_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    EzI2C_1_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (EzI2C_1_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: EzI2C_1_SetCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EzI2C_1_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_EzI2C_1_CUSTOM_INTR_HANDLER)
        EzI2C_1_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_EzI2C_1_CUSTOM_INTR_HANDLER) */
    }
#endif /* (EzI2C_1_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: EzI2C_1_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void EzI2C_1_ScbEnableIntr(void)
{
#if (EzI2C_1_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != EzI2C_1_scbEnableIntr)
        {
            EzI2C_1_EnableInt();
        }

    #else
        EzI2C_1_EnableInt();

    #endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (EzI2C_1_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: EzI2C_1_ScbModePostEnable
********************************************************************************
*
* Summary:
*  Calls the PostEnable function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void EzI2C_1_ScbModePostEnable(void)
{
#if (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!EzI2C_1_CY_SCBIP_V1)
    if (EzI2C_1_SCB_MODE_SPI_RUNTM_CFG)
    {
        EzI2C_1_SpiPostEnable();
    }
    else if (EzI2C_1_SCB_MODE_UART_RUNTM_CFG)
    {
        EzI2C_1_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!EzI2C_1_CY_SCBIP_V1) */

#elif (EzI2C_1_SCB_MODE_SPI_CONST_CFG)
    EzI2C_1_SpiPostEnable();

#elif (EzI2C_1_SCB_MODE_UART_CONST_CFG)
    EzI2C_1_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EzI2C_1_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void EzI2C_1_ScbModeStop(void)
{
#if (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    if (EzI2C_1_SCB_MODE_I2C_RUNTM_CFG)
    {
        EzI2C_1_I2CStop();
    }
    else if (EzI2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        EzI2C_1_EzI2CStop();
    }
#if (!EzI2C_1_CY_SCBIP_V1)
    else if (EzI2C_1_SCB_MODE_SPI_RUNTM_CFG)
    {
        EzI2C_1_SpiStop();
    }
    else if (EzI2C_1_SCB_MODE_UART_RUNTM_CFG)
    {
        EzI2C_1_UartStop();
    }
#endif /* (!EzI2C_1_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (EzI2C_1_SCB_MODE_I2C_CONST_CFG)
    EzI2C_1_I2CStop();

#elif (EzI2C_1_SCB_MODE_EZI2C_CONST_CFG)
    EzI2C_1_EzI2CStop();

#elif (EzI2C_1_SCB_MODE_SPI_CONST_CFG)
    EzI2C_1_SpiStop();

#elif (EzI2C_1_SCB_MODE_UART_CONST_CFG)
    EzI2C_1_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: EzI2C_1_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EzI2C_1_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [EzI2C_1_SCB_PINS_NUMBER];
        uint32 pinsDm   [EzI2C_1_SCB_PINS_NUMBER];

    #if (!EzI2C_1_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!EzI2C_1_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < EzI2C_1_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = EzI2C_1_HSIOM_DEF_SEL;
            pinsDm[i]    = EzI2C_1_PIN_DM_ALG_HIZ;
        }

        if ((EzI2C_1_SCB_MODE_I2C   == mode) ||
           (EzI2C_1_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[EzI2C_1_RX_SCL_MOSI_PIN_INDEX] = EzI2C_1_HSIOM_I2C_SEL;
            hsiomSel[EzI2C_1_TX_SDA_MISO_PIN_INDEX] = EzI2C_1_HSIOM_I2C_SEL;

            pinsDm[EzI2C_1_RX_SCL_MOSI_PIN_INDEX] = EzI2C_1_PIN_DM_OD_LO;
            pinsDm[EzI2C_1_TX_SDA_MISO_PIN_INDEX] = EzI2C_1_PIN_DM_OD_LO;
        }
    #if (!EzI2C_1_CY_SCBIP_V1)
        else if (EzI2C_1_SCB_MODE_SPI == mode)
        {
            hsiomSel[EzI2C_1_RX_SCL_MOSI_PIN_INDEX] = EzI2C_1_HSIOM_SPI_SEL;
            hsiomSel[EzI2C_1_TX_SDA_MISO_PIN_INDEX] = EzI2C_1_HSIOM_SPI_SEL;
            hsiomSel[EzI2C_1_SCLK_PIN_INDEX] = EzI2C_1_HSIOM_SPI_SEL;

            if (EzI2C_1_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[EzI2C_1_RX_SCL_MOSI_PIN_INDEX] = EzI2C_1_PIN_DM_DIG_HIZ;
                pinsDm[EzI2C_1_TX_SDA_MISO_PIN_INDEX] = EzI2C_1_PIN_DM_STRONG;
                pinsDm[EzI2C_1_SCLK_PIN_INDEX] = EzI2C_1_PIN_DM_DIG_HIZ;

            #if (EzI2C_1_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[EzI2C_1_SS0_PIN_INDEX] = EzI2C_1_HSIOM_SPI_SEL;
                pinsDm  [EzI2C_1_SS0_PIN_INDEX] = EzI2C_1_PIN_DM_DIG_HIZ;
            #endif /* (EzI2C_1_SS0_PIN) */

            #if (EzI2C_1_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= EzI2C_1_TX_SDA_MISO_PIN_MASK;
            #endif /* (EzI2C_1_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[EzI2C_1_RX_SCL_MOSI_PIN_INDEX] = EzI2C_1_PIN_DM_STRONG;
                pinsDm[EzI2C_1_TX_SDA_MISO_PIN_INDEX] = EzI2C_1_PIN_DM_DIG_HIZ;
                pinsDm[EzI2C_1_SCLK_PIN_INDEX] = EzI2C_1_PIN_DM_STRONG;

            #if (EzI2C_1_SS0_PIN)
                hsiomSel [EzI2C_1_SS0_PIN_INDEX] = EzI2C_1_HSIOM_SPI_SEL;
                pinsDm   [EzI2C_1_SS0_PIN_INDEX] = EzI2C_1_PIN_DM_STRONG;
                pinsInBuf |= EzI2C_1_SS0_PIN_MASK;
            #endif /* (EzI2C_1_SS0_PIN) */

            #if (EzI2C_1_SS1_PIN)
                hsiomSel [EzI2C_1_SS1_PIN_INDEX] = EzI2C_1_HSIOM_SPI_SEL;
                pinsDm   [EzI2C_1_SS1_PIN_INDEX] = EzI2C_1_PIN_DM_STRONG;
                pinsInBuf |= EzI2C_1_SS1_PIN_MASK;
            #endif /* (EzI2C_1_SS1_PIN) */

            #if (EzI2C_1_SS2_PIN)
                hsiomSel [EzI2C_1_SS2_PIN_INDEX] = EzI2C_1_HSIOM_SPI_SEL;
                pinsDm   [EzI2C_1_SS2_PIN_INDEX] = EzI2C_1_PIN_DM_STRONG;
                pinsInBuf |= EzI2C_1_SS2_PIN_MASK;
            #endif /* (EzI2C_1_SS2_PIN) */

            #if (EzI2C_1_SS3_PIN)
                hsiomSel [EzI2C_1_SS3_PIN_INDEX] = EzI2C_1_HSIOM_SPI_SEL;
                pinsDm   [EzI2C_1_SS3_PIN_INDEX] = EzI2C_1_PIN_DM_STRONG;
                pinsInBuf |= EzI2C_1_SS3_PIN_MASK;
            #endif /* (EzI2C_1_SS3_PIN) */

                /* Disable input buffers */
            #if (EzI2C_1_RX_SCL_MOSI_PIN)
                pinsInBuf |= EzI2C_1_RX_SCL_MOSI_PIN_MASK;
            #endif /* (EzI2C_1_RX_SCL_MOSI_PIN) */

             #if (EzI2C_1_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= EzI2C_1_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (EzI2C_1_RX_WAKE_SCL_MOSI_PIN) */

            #if (EzI2C_1_SCLK_PIN)
                pinsInBuf |= EzI2C_1_SCLK_PIN_MASK;
            #endif /* (EzI2C_1_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (EzI2C_1_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[EzI2C_1_TX_SDA_MISO_PIN_INDEX] = EzI2C_1_HSIOM_UART_SEL;
                pinsDm  [EzI2C_1_TX_SDA_MISO_PIN_INDEX] = EzI2C_1_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (EzI2C_1_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[EzI2C_1_RX_SCL_MOSI_PIN_INDEX] = EzI2C_1_HSIOM_UART_SEL;
                    pinsDm  [EzI2C_1_RX_SCL_MOSI_PIN_INDEX] = EzI2C_1_PIN_DM_DIG_HIZ;
                }

                if (0u != (EzI2C_1_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[EzI2C_1_TX_SDA_MISO_PIN_INDEX] = EzI2C_1_HSIOM_UART_SEL;
                    pinsDm  [EzI2C_1_TX_SDA_MISO_PIN_INDEX] = EzI2C_1_PIN_DM_STRONG;

                #if (EzI2C_1_TX_SDA_MISO_PIN)
                     pinsInBuf |= EzI2C_1_TX_SDA_MISO_PIN_MASK;
                #endif /* (EzI2C_1_TX_SDA_MISO_PIN) */
                }

            #if !(EzI2C_1_CY_SCBIP_V0 || EzI2C_1_CY_SCBIP_V1)
                if (EzI2C_1_UART_MODE_STD == subMode)
                {
                    if (0u != (EzI2C_1_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[EzI2C_1_SCLK_PIN_INDEX] = EzI2C_1_HSIOM_UART_SEL;
                        pinsDm  [EzI2C_1_SCLK_PIN_INDEX] = EzI2C_1_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (EzI2C_1_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[EzI2C_1_SS0_PIN_INDEX] = EzI2C_1_HSIOM_UART_SEL;
                        pinsDm  [EzI2C_1_SS0_PIN_INDEX] = EzI2C_1_PIN_DM_STRONG;

                    #if (EzI2C_1_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= EzI2C_1_SS0_PIN_MASK;
                    #endif /* (EzI2C_1_SS0_PIN) */
                    }
                }
            #endif /* !(EzI2C_1_CY_SCBIP_V0 || EzI2C_1_CY_SCBIP_V1) */
            }
        }
    #endif /* (!EzI2C_1_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (EzI2C_1_RX_WAKE_SCL_MOSI_PIN)
        EzI2C_1_SET_HSIOM_SEL(EzI2C_1_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       EzI2C_1_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       EzI2C_1_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[EzI2C_1_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        EzI2C_1_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[EzI2C_1_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        EzI2C_1_SET_INP_DIS(EzI2C_1_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     EzI2C_1_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & EzI2C_1_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        EzI2C_1_SET_INCFG_TYPE(EzI2C_1_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        EzI2C_1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        EzI2C_1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        EzI2C_1_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (EzI2C_1_RX_WAKE_SCL_MOSI_PIN) */

    #if (EzI2C_1_RX_SCL_MOSI_PIN)
        EzI2C_1_SET_HSIOM_SEL(EzI2C_1_RX_SCL_MOSI_HSIOM_REG,
                                       EzI2C_1_RX_SCL_MOSI_HSIOM_MASK,
                                       EzI2C_1_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[EzI2C_1_RX_SCL_MOSI_PIN_INDEX]);

        EzI2C_1_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[EzI2C_1_RX_SCL_MOSI_PIN_INDEX]);

    #if (!EzI2C_1_CY_SCBIP_V1)
        EzI2C_1_SET_INP_DIS(EzI2C_1_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     EzI2C_1_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & EzI2C_1_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!EzI2C_1_CY_SCBIP_V1) */
    #endif /* (EzI2C_1_RX_SCL_MOSI_PIN) */

    #if (EzI2C_1_TX_SDA_MISO_PIN)
        EzI2C_1_SET_HSIOM_SEL(EzI2C_1_TX_SDA_MISO_HSIOM_REG,
                                       EzI2C_1_TX_SDA_MISO_HSIOM_MASK,
                                       EzI2C_1_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[EzI2C_1_TX_SDA_MISO_PIN_INDEX]);

        EzI2C_1_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[EzI2C_1_TX_SDA_MISO_PIN_INDEX]);

    #if (!EzI2C_1_CY_SCBIP_V1)
        EzI2C_1_SET_INP_DIS(EzI2C_1_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     EzI2C_1_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & EzI2C_1_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!EzI2C_1_CY_SCBIP_V1) */
    #endif /* (EzI2C_1_RX_SCL_MOSI_PIN) */

    #if (EzI2C_1_SCLK_PIN)
        EzI2C_1_SET_HSIOM_SEL(EzI2C_1_SCLK_HSIOM_REG,
                                       EzI2C_1_SCLK_HSIOM_MASK,
                                       EzI2C_1_SCLK_HSIOM_POS,
                                       hsiomSel[EzI2C_1_SCLK_PIN_INDEX]);

        EzI2C_1_spi_sclk_SetDriveMode((uint8) pinsDm[EzI2C_1_SCLK_PIN_INDEX]);

        EzI2C_1_SET_INP_DIS(EzI2C_1_spi_sclk_INP_DIS,
                                     EzI2C_1_spi_sclk_MASK,
                                     (0u != (pinsInBuf & EzI2C_1_SCLK_PIN_MASK)));
    #endif /* (EzI2C_1_SCLK_PIN) */

    #if (EzI2C_1_SS0_PIN)
        EzI2C_1_SET_HSIOM_SEL(EzI2C_1_SS0_HSIOM_REG,
                                       EzI2C_1_SS0_HSIOM_MASK,
                                       EzI2C_1_SS0_HSIOM_POS,
                                       hsiomSel[EzI2C_1_SS0_PIN_INDEX]);

        EzI2C_1_spi_ss0_SetDriveMode((uint8) pinsDm[EzI2C_1_SS0_PIN_INDEX]);

        EzI2C_1_SET_INP_DIS(EzI2C_1_spi_ss0_INP_DIS,
                                     EzI2C_1_spi_ss0_MASK,
                                     (0u != (pinsInBuf & EzI2C_1_SS0_PIN_MASK)));
    #endif /* (EzI2C_1_SS0_PIN) */

    #if (EzI2C_1_SS1_PIN)
        EzI2C_1_SET_HSIOM_SEL(EzI2C_1_SS1_HSIOM_REG,
                                       EzI2C_1_SS1_HSIOM_MASK,
                                       EzI2C_1_SS1_HSIOM_POS,
                                       hsiomSel[EzI2C_1_SS1_PIN_INDEX]);

        EzI2C_1_spi_ss1_SetDriveMode((uint8) pinsDm[EzI2C_1_SS1_PIN_INDEX]);

        EzI2C_1_SET_INP_DIS(EzI2C_1_spi_ss1_INP_DIS,
                                     EzI2C_1_spi_ss1_MASK,
                                     (0u != (pinsInBuf & EzI2C_1_SS1_PIN_MASK)));
    #endif /* (EzI2C_1_SS1_PIN) */

    #if (EzI2C_1_SS2_PIN)
        EzI2C_1_SET_HSIOM_SEL(EzI2C_1_SS2_HSIOM_REG,
                                       EzI2C_1_SS2_HSIOM_MASK,
                                       EzI2C_1_SS2_HSIOM_POS,
                                       hsiomSel[EzI2C_1_SS2_PIN_INDEX]);

        EzI2C_1_spi_ss2_SetDriveMode((uint8) pinsDm[EzI2C_1_SS2_PIN_INDEX]);

        EzI2C_1_SET_INP_DIS(EzI2C_1_spi_ss2_INP_DIS,
                                     EzI2C_1_spi_ss2_MASK,
                                     (0u != (pinsInBuf & EzI2C_1_SS2_PIN_MASK)));
    #endif /* (EzI2C_1_SS2_PIN) */

    #if (EzI2C_1_SS3_PIN)
        EzI2C_1_SET_HSIOM_SEL(EzI2C_1_SS3_HSIOM_REG,
                                       EzI2C_1_SS3_HSIOM_MASK,
                                       EzI2C_1_SS3_HSIOM_POS,
                                       hsiomSel[EzI2C_1_SS3_PIN_INDEX]);

        EzI2C_1_spi_ss3_SetDriveMode((uint8) pinsDm[EzI2C_1_SS3_PIN_INDEX]);

        EzI2C_1_SET_INP_DIS(EzI2C_1_spi_ss3_INP_DIS,
                                     EzI2C_1_spi_ss3_MASK,
                                     (0u != (pinsInBuf & EzI2C_1_SS3_PIN_MASK)));
    #endif /* (EzI2C_1_SS3_PIN) */
    }

#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (EzI2C_1_CY_SCBIP_V0 || EzI2C_1_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: EzI2C_1_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EzI2C_1_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (EzI2C_1_CTRL_REG & EzI2C_1_CTRL_EC_AM_MODE)) &&
            (0u == (EzI2C_1_I2C_CTRL_REG & EzI2C_1_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            EzI2C_1_CTRL_REG &= ~EzI2C_1_CTRL_EC_AM_MODE;
            EzI2C_1_CTRL_REG |=  EzI2C_1_CTRL_EC_AM_MODE;
        }

        EzI2C_1_I2C_SLAVE_CMD_REG = EzI2C_1_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (EzI2C_1_CY_SCBIP_V0 || EzI2C_1_CY_SCBIP_V1) */


/* [] END OF FILE */

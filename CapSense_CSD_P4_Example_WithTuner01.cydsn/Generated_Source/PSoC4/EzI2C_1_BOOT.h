/*******************************************************************************
* File Name: EzI2C_1_BOOT.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_EzI2C_1_H)
#define CY_SCB_BOOT_EzI2C_1_H

#include "EzI2C_1_PVT.h"

#if (EzI2C_1_SCB_MODE_I2C_INC)
    #include "EzI2C_1_I2C.h"
#endif /* (EzI2C_1_SCB_MODE_I2C_INC) */

#if (EzI2C_1_SCB_MODE_EZI2C_INC)
    #include "EzI2C_1_EZI2C.h"
#endif /* (EzI2C_1_SCB_MODE_EZI2C_INC) */

#if (EzI2C_1_SCB_MODE_SPI_INC || EzI2C_1_SCB_MODE_UART_INC)
    #include "EzI2C_1_SPI_UART.h"
#endif /* (EzI2C_1_SCB_MODE_SPI_INC || EzI2C_1_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define EzI2C_1_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_EzI2C_1) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (EzI2C_1_SCB_MODE_I2C_INC)
    #define EzI2C_1_I2C_BTLDR_COMM_ENABLED     (EzI2C_1_BTLDR_COMM_ENABLED && \
                                                            (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             EzI2C_1_I2C_SLAVE_CONST))
#else
     #define EzI2C_1_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (EzI2C_1_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (EzI2C_1_SCB_MODE_EZI2C_INC)
    #define EzI2C_1_EZI2C_BTLDR_COMM_ENABLED   (EzI2C_1_BTLDR_COMM_ENABLED && \
                                                         EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define EzI2C_1_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (EzI2C_1_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (EzI2C_1_SCB_MODE_SPI_INC)
    #define EzI2C_1_SPI_BTLDR_COMM_ENABLED     (EzI2C_1_BTLDR_COMM_ENABLED && \
                                                            (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             EzI2C_1_SPI_SLAVE_CONST))
#else
        #define EzI2C_1_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (EzI2C_1_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (EzI2C_1_SCB_MODE_UART_INC)
       #define EzI2C_1_UART_BTLDR_COMM_ENABLED    (EzI2C_1_BTLDR_COMM_ENABLED && \
                                                            (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (EzI2C_1_UART_RX_DIRECTION && \
                                                              EzI2C_1_UART_TX_DIRECTION)))
#else
     #define EzI2C_1_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (EzI2C_1_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define EzI2C_1_BTLDR_COMM_MODE_ENABLED    (EzI2C_1_I2C_BTLDR_COMM_ENABLED   || \
                                                     EzI2C_1_SPI_BTLDR_COMM_ENABLED   || \
                                                     EzI2C_1_EZI2C_BTLDR_COMM_ENABLED || \
                                                     EzI2C_1_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void EzI2C_1_I2CCyBtldrCommStart(void);
    void EzI2C_1_I2CCyBtldrCommStop (void);
    void EzI2C_1_I2CCyBtldrCommReset(void);
    cystatus EzI2C_1_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus EzI2C_1_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (EzI2C_1_SCB_MODE_I2C_CONST_CFG)
        #define EzI2C_1_CyBtldrCommStart   EzI2C_1_I2CCyBtldrCommStart
        #define EzI2C_1_CyBtldrCommStop    EzI2C_1_I2CCyBtldrCommStop
        #define EzI2C_1_CyBtldrCommReset   EzI2C_1_I2CCyBtldrCommReset
        #define EzI2C_1_CyBtldrCommRead    EzI2C_1_I2CCyBtldrCommRead
        #define EzI2C_1_CyBtldrCommWrite   EzI2C_1_I2CCyBtldrCommWrite
    #endif /* (EzI2C_1_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void EzI2C_1_EzI2CCyBtldrCommStart(void);
    void EzI2C_1_EzI2CCyBtldrCommStop (void);
    void EzI2C_1_EzI2CCyBtldrCommReset(void);
    cystatus EzI2C_1_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus EzI2C_1_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (EzI2C_1_SCB_MODE_EZI2C_CONST_CFG)
        #define EzI2C_1_CyBtldrCommStart   EzI2C_1_EzI2CCyBtldrCommStart
        #define EzI2C_1_CyBtldrCommStop    EzI2C_1_EzI2CCyBtldrCommStop
        #define EzI2C_1_CyBtldrCommReset   EzI2C_1_EzI2CCyBtldrCommReset
        #define EzI2C_1_CyBtldrCommRead    EzI2C_1_EzI2CCyBtldrCommRead
        #define EzI2C_1_CyBtldrCommWrite   EzI2C_1_EzI2CCyBtldrCommWrite
    #endif /* (EzI2C_1_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void EzI2C_1_SpiCyBtldrCommStart(void);
    void EzI2C_1_SpiCyBtldrCommStop (void);
    void EzI2C_1_SpiCyBtldrCommReset(void);
    cystatus EzI2C_1_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus EzI2C_1_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (EzI2C_1_SCB_MODE_SPI_CONST_CFG)
        #define EzI2C_1_CyBtldrCommStart   EzI2C_1_SpiCyBtldrCommStart
        #define EzI2C_1_CyBtldrCommStop    EzI2C_1_SpiCyBtldrCommStop
        #define EzI2C_1_CyBtldrCommReset   EzI2C_1_SpiCyBtldrCommReset
        #define EzI2C_1_CyBtldrCommRead    EzI2C_1_SpiCyBtldrCommRead
        #define EzI2C_1_CyBtldrCommWrite   EzI2C_1_SpiCyBtldrCommWrite
    #endif /* (EzI2C_1_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void EzI2C_1_UartCyBtldrCommStart(void);
    void EzI2C_1_UartCyBtldrCommStop (void);
    void EzI2C_1_UartCyBtldrCommReset(void);
    cystatus EzI2C_1_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus EzI2C_1_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (EzI2C_1_SCB_MODE_UART_CONST_CFG)
        #define EzI2C_1_CyBtldrCommStart   EzI2C_1_UartCyBtldrCommStart
        #define EzI2C_1_CyBtldrCommStop    EzI2C_1_UartCyBtldrCommStop
        #define EzI2C_1_CyBtldrCommReset   EzI2C_1_UartCyBtldrCommReset
        #define EzI2C_1_CyBtldrCommRead    EzI2C_1_UartCyBtldrCommRead
        #define EzI2C_1_CyBtldrCommWrite   EzI2C_1_UartCyBtldrCommWrite
    #endif /* (EzI2C_1_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_BTLDR_COMM_ENABLED)
    #if (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void EzI2C_1_CyBtldrCommStart(void);
        void EzI2C_1_CyBtldrCommStop (void);
        void EzI2C_1_CyBtldrCommReset(void);
        cystatus EzI2C_1_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus EzI2C_1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_EzI2C_1)
        #define CyBtldrCommStart    EzI2C_1_CyBtldrCommStart
        #define CyBtldrCommStop     EzI2C_1_CyBtldrCommStop
        #define CyBtldrCommReset    EzI2C_1_CyBtldrCommReset
        #define CyBtldrCommWrite    EzI2C_1_CyBtldrCommWrite
        #define CyBtldrCommRead     EzI2C_1_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_EzI2C_1) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_1_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define EzI2C_1_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define EzI2C_1_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define EzI2C_1_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define EzI2C_1_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef EzI2C_1_SPI_BYTE_TO_BYTE
    #define EzI2C_1_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef EzI2C_1_UART_BYTE_TO_BYTE
    #define EzI2C_1_UART_BYTE_TO_BYTE  (2500u)
#endif /* EzI2C_1_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_EzI2C_1_H) */


/* [] END OF FILE */

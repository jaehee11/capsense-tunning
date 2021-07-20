/*******************************************************************************
* File Name: EzI2C_1_EZI2C.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  the EZI2C mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_EZI2C_EzI2C_1_H)
#define CY_SCB_EZI2C_EzI2C_1_H

#include "EzI2C_1.h"


/***************************************
*   Initial Parameter Constants
****************************************/

#define EzI2C_1_EZI2C_CLOCK_STRETCHING         (1u)
#define EzI2C_1_EZI2C_MEDIAN_FILTER_ENABLE     (1u)
#define EzI2C_1_EZI2C_NUMBER_OF_ADDRESSES      (0u)
#define EzI2C_1_EZI2C_PRIMARY_SLAVE_ADDRESS    (79u)
#define EzI2C_1_EZI2C_SECONDARY_SLAVE_ADDRESS  (9u)
#define EzI2C_1_EZI2C_SUB_ADDRESS_SIZE         (0u)
#define EzI2C_1_EZI2C_WAKE_ENABLE              (0u)
#define EzI2C_1_EZI2C_DATA_RATE                (400u)
#define EzI2C_1_EZI2C_SLAVE_ADDRESS_MASK       (254u)
#define EzI2C_1_EZI2C_BYTE_MODE_ENABLE         (0u)


/***************************************
*  Conditional Compilation Parameters
****************************************/

#if(EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    #define EzI2C_1_SUB_ADDRESS_SIZE16             (0u != EzI2C_1_subAddrSize)
    #define EzI2C_1_SECONDARY_ADDRESS_ENABLE       (0u != EzI2C_1_numberOfAddr)

    #define EzI2C_1_EZI2C_EC_AM_ENABLE         (0u != (EzI2C_1_CTRL_REG & \
                                                                EzI2C_1_CTRL_EC_AM_MODE))
    #define EzI2C_1_EZI2C_SCL_STRETCH_ENABLE   (0u != (EzI2C_1_GetSlaveInterruptMode() & \
                                                                EzI2C_1_INTR_SLAVE_I2C_ADDR_MATCH))
    #define EzI2C_1_EZI2C_SCL_STRETCH_DISABLE       (!EzI2C_1_EZI2C_SCL_STRETCH_ENABLE)

    #define EzI2C_1_SECONDARY_ADDRESS_ENABLE_CONST  (1u)
    #define EzI2C_1_SUB_ADDRESS_SIZE16_CONST        (1u)
    #define EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST  (1u)
    #define EzI2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST (1u)
    #define EzI2C_1_EZI2C_WAKE_ENABLE_CONST         (1u)

    #if (EzI2C_1_CY_SCBIP_V0 || EzI2C_1_CY_SCBIP_V1)
        #define EzI2C_1_EZI2C_FIFO_SIZE    (EzI2C_1_FIFO_SIZE)
    #else
        #define EzI2C_1_EZI2C_FIFO_SIZE    (EzI2C_1_GET_FIFO_SIZE(EzI2C_1_CTRL_REG & \
                                                                                    EzI2C_1_CTRL_BYTE_MODE))
    #endif /* (EzI2C_1_CY_SCBIP_V0 || EzI2C_1_CY_SCBIP_V1) */

#else

    #define EzI2C_1_SUB_ADDRESS_SIZE16         (0u != EzI2C_1_EZI2C_SUB_ADDRESS_SIZE)
    #define EzI2C_1_SUB_ADDRESS_SIZE16_CONST   (EzI2C_1_SUB_ADDRESS_SIZE16)

    #define EzI2C_1_SECONDARY_ADDRESS_ENABLE        (0u != EzI2C_1_EZI2C_NUMBER_OF_ADDRESSES)
    #define EzI2C_1_SECONDARY_ADDRESS_ENABLE_CONST  (EzI2C_1_SECONDARY_ADDRESS_ENABLE)

    #define EzI2C_1_EZI2C_SCL_STRETCH_ENABLE        (0u != EzI2C_1_EZI2C_CLOCK_STRETCHING)
    #define EzI2C_1_EZI2C_SCL_STRETCH_DISABLE       (!EzI2C_1_EZI2C_SCL_STRETCH_ENABLE)
    #define EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST  (EzI2C_1_EZI2C_SCL_STRETCH_ENABLE)
    #define EzI2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST (EzI2C_1_EZI2C_SCL_STRETCH_DISABLE)

    #define EzI2C_1_EZI2C_WAKE_ENABLE_CONST         (0u != EzI2C_1_EZI2C_WAKE_ENABLE)
    #define EzI2C_1_EZI2C_EC_AM_ENABLE              (0u != EzI2C_1_EZI2C_WAKE_ENABLE)

    #if (EzI2C_1_CY_SCBIP_V0 || EzI2C_1_CY_SCBIP_V1)
       #define EzI2C_1_EZI2C_FIFO_SIZE    (EzI2C_1_FIFO_SIZE)

    #else
        #define EzI2C_1_EZI2C_FIFO_SIZE \
                                            EzI2C_1_GET_FIFO_SIZE(EzI2C_1_EZI2C_BYTE_MODE_ENABLE)
    #endif /* (EzI2C_1_CY_SCBIP_V0 || EzI2C_1_CY_SCBIP_V1) */

#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint32 enableClockStretch;
    uint32 enableMedianFilter;
    uint32 numberOfAddresses;
    uint32 primarySlaveAddr;
    uint32 secondarySlaveAddr;
    uint32 subAddrSize;
    uint32 enableWake;
    uint8  enableByteMode;
} EzI2C_1_EZI2C_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

#if(EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    void EzI2C_1_EzI2CInit(const EzI2C_1_EZI2C_INIT_STRUCT *config);
#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

uint32 EzI2C_1_EzI2CGetActivity(void);

void   EzI2C_1_EzI2CSetAddress1(uint32 address);
uint32 EzI2C_1_EzI2CGetAddress1(void);
void   EzI2C_1_EzI2CSetBuffer1(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer);
void   EzI2C_1_EzI2CSetReadBoundaryBuffer1(uint32 rwBoundary);

#if(EzI2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
    void   EzI2C_1_EzI2CSetAddress2(uint32 address);
    uint32 EzI2C_1_EzI2CGetAddress2(void);
    void   EzI2C_1_EzI2CSetBuffer2(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer);
    void   EzI2C_1_EzI2CSetReadBoundaryBuffer2(uint32 rwBoundary);
#endif /* (EzI2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */

#if(EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
    CY_ISR_PROTO(EzI2C_1_EZI2C_STRETCH_ISR);
#endif /* (EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

#if(EzI2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST)
    CY_ISR_PROTO(EzI2C_1_EZI2C_NO_STRETCH_ISR);
#endif /* (EzI2C_1_EZI2C_SCL_STRETCH_DISABLE) */


/***************************************
*            API Constants
***************************************/

/* Configuration structure constants */
#define EzI2C_1_EZI2C_ONE_ADDRESS      (0u)
#define EzI2C_1_EZI2C_TWO_ADDRESSES    (1u)

#define EzI2C_1_EZI2C_PRIMARY_ADDRESS  (0u)
#define EzI2C_1_EZI2C_BOTH_ADDRESSES   (1u)

#define EzI2C_1_EZI2C_SUB_ADDR8_BITS   (0u)
#define EzI2C_1_EZI2C_SUB_ADDR16_BITS  (1u)

/* EzI2C_1_EzI2CGetActivity() return constants */
#define EzI2C_1_EZI2C_STATUS_SECOND_OFFSET (1u)
#define EzI2C_1_EZI2C_STATUS_READ1     ((uint32) (EzI2C_1_INTR_SLAVE_I2C_NACK))        /* Bit [1]   */
#define EzI2C_1_EZI2C_STATUS_WRITE1    ((uint32) (EzI2C_1_INTR_SLAVE_I2C_WRITE_STOP))  /* Bit [3]   */
#define EzI2C_1_EZI2C_STATUS_READ2     ((uint32) (EzI2C_1_INTR_SLAVE_I2C_NACK >> \
                                                           EzI2C_1_EZI2C_STATUS_SECOND_OFFSET)) /* Bit [0]   */
#define EzI2C_1_EZI2C_STATUS_WRITE2    ((uint32) (EzI2C_1_INTR_SLAVE_I2C_WRITE_STOP >> \
                                                           EzI2C_1_EZI2C_STATUS_SECOND_OFFSET)) /* Bit [2]   */
#define EzI2C_1_EZI2C_STATUS_ERR       ((uint32) (0x10u))                                       /* Bit [4]   */
#define EzI2C_1_EZI2C_STATUS_BUSY      ((uint32) (0x20u))                                       /* Bit [5]   */
#define EzI2C_1_EZI2C_CLEAR_STATUS     ((uint32) (0x1Fu))                                       /* Bits [0-4]*/
#define EzI2C_1_EZI2C_CMPLT_INTR_MASK  ((uint32) (EzI2C_1_INTR_SLAVE_I2C_NACK | \
                                                           EzI2C_1_INTR_SLAVE_I2C_WRITE_STOP))


/***************************************
*     Vars with External Linkage
***************************************/

#if(EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const EzI2C_1_EZI2C_INIT_STRUCT EzI2C_1_configEzI2C;
#endif /* (EzI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*           FSM states
***************************************/

/* Returns to master when there is no data to transmit */
#define EzI2C_1_EZI2C_OVFL_RETURN  (0xFFu)

/* States of EZI2C Slave FSM */
#define EzI2C_1_EZI2C_FSM_OFFSET_HI8 ((uint8) (0x02u)) /* Idle state for 1 addr: waits for high byte offset */
#define EzI2C_1_EZI2C_FSM_OFFSET_LO8 ((uint8) (0x00u)) /* Idle state for 2 addr: waits for low byte offset  */
#define EzI2C_1_EZI2C_FSM_BYTE_WRITE ((uint8) (0x01u)) /* Data byte write state: byte by byte mode          */
#define EzI2C_1_EZI2C_FSM_WAIT_STOP  ((uint8) (0x03u)) /* Discards written bytes as they do not match write
                                                                   criteria */
#define EzI2C_1_EZI2C_FSM_WRITE_MASK ((uint8) (0x01u)) /* Incorporates write states: EZI2C_FSM_BYTE_WRITE and
                                                                   EZI2C_FSM_WAIT_STOP  */

#define EzI2C_1_EZI2C_FSM_IDLE     ((EzI2C_1_SUB_ADDRESS_SIZE16) ?      \
                                                (EzI2C_1_EZI2C_FSM_OFFSET_HI8) : \
                                                (EzI2C_1_EZI2C_FSM_OFFSET_LO8))

#define EzI2C_1_EZI2C_CONTINUE_TRANSFER    (1u)
#define EzI2C_1_EZI2C_COMPLETE_TRANSFER    (0u)

#define EzI2C_1_EZI2C_NACK_RECEIVED_ADDRESS  (0u)
#define EzI2C_1_EZI2C_ACK_RECEIVED_ADDRESS   (1u)

#define EzI2C_1_EZI2C_ACTIVE_ADDRESS1  (0u)
#define EzI2C_1_EZI2C_ACTIVE_ADDRESS2  (1u)


/***************************************
*       Macro Definitions
***************************************/

/* Access to global variables */
#if(EzI2C_1_SECONDARY_ADDRESS_ENABLE_CONST)

    #define EzI2C_1_EZI2C_UPDATE_LOC_STATUS(activeAddress, locStatus) \
            do{ \
                (locStatus) >>= (activeAddress); \
            }while(0)

    #define EzI2C_1_EZI2C_GET_INDEX(activeAddress) \
            ((EzI2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) ? \
                ((uint32) EzI2C_1_indexBuf1) :                    \
                ((uint32) EzI2C_1_indexBuf2))

    #define EzI2C_1_EZI2C_GET_OFFSET(activeAddress) \
            ((EzI2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) ? \
                ((uint32) EzI2C_1_offsetBuf1) :                   \
                ((uint32) EzI2C_1_offsetBuf2))

    #define EzI2C_1_EZI2C_SET_INDEX(activeAddress, locIndex) \
            do{ \
                if(EzI2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) \
                {    \
                    EzI2C_1_indexBuf1 = (uint16) (locIndex); \
                }    \
                else \
                {    \
                    EzI2C_1_indexBuf2 = (uint16) (locIndex); \
                }    \
            }while(0)

    #define EzI2C_1_EZI2C_SET_OFFSET(activeAddress, locOffset) \
            do{ \
                if(EzI2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) \
                {    \
                    EzI2C_1_offsetBuf1 = (uint8) (locOffset); \
                }    \
                else \
                {    \
                    EzI2C_1_offsetBuf2 = (uint8) (locOffset); \
                }    \
            }while(0)
#else
    #define EzI2C_1_EZI2C_UPDATE_LOC_STATUS(activeAddress, locStatus)  do{ /* Empty*/ }while(0)

    #define EzI2C_1_EZI2C_GET_INDEX(activeAddress)  ((uint32) (EzI2C_1_indexBuf1))

    #define EzI2C_1_EZI2C_GET_OFFSET(activeAddress) ((uint32) (EzI2C_1_offsetBuf1))

    #define EzI2C_1_EZI2C_SET_INDEX(activeAddress, locIndex) \
            do{ \
                EzI2C_1_indexBuf1 = (uint16) (locIndex); \
            }while(0)

    #define EzI2C_1_EZI2C_SET_OFFSET(activeAddress, locOffset) \
            do{ \
                EzI2C_1_offsetBuf1 = (uint8) (locOffset); \
            }while(0)

#endif  /* (EzI2C_1_SUB_ADDRESS_SIZE16_CONST) */


/* This macro only applicable for EZI2C slave without clock stretching.
* It should not be used for other pusposes. */
#define EzI2C_1_EZI2C_TX_FIFO_CTRL_SET   (EzI2C_1_EZI2C_TX_FIFO_CTRL | \
                                                   EzI2C_1_TX_FIFO_CTRL_CLEAR)
#define EzI2C_1_EZI2C_TX_FIFO_CTRL_CLEAR (EzI2C_1_EZI2C_TX_FIFO_CTRL)
#define EzI2C_1_FAST_CLEAR_TX_FIFO \
                            do{             \
                                EzI2C_1_TX_FIFO_CTRL_REG = EzI2C_1_EZI2C_TX_FIFO_CTRL_SET;   \
                                EzI2C_1_TX_FIFO_CTRL_REG = EzI2C_1_EZI2C_TX_FIFO_CTRL_CLEAR; \
                            }while(0)


/***************************************
*      Common Register Settings
***************************************/

#define EzI2C_1_CTRL_EZI2C     (EzI2C_1_CTRL_MODE_I2C)

#define EzI2C_1_EZI2C_CTRL     (EzI2C_1_I2C_CTRL_S_GENERAL_IGNORE | \
                                         EzI2C_1_I2C_CTRL_SLAVE_MODE)

#define EzI2C_1_EZI2C_CTRL_AUTO    (EzI2C_1_I2C_CTRL_S_READY_ADDR_ACK      | \
                                             EzI2C_1_I2C_CTRL_S_READY_DATA_ACK      | \
                                             EzI2C_1_I2C_CTRL_S_NOT_READY_ADDR_NACK | \
                                             EzI2C_1_I2C_CTRL_S_NOT_READY_DATA_NACK)

#define EzI2C_1_EZI2C_RX_CTRL  ((EzI2C_1_FIFO_SIZE - 1u)   | \
                                          EzI2C_1_RX_CTRL_MSB_FIRST | \
                                          EzI2C_1_RX_CTRL_ENABLED)

#define EzI2C_1_EZI2C_TX_FIFO_CTRL (2u)
#define EzI2C_1_TX_LOAD_SIZE       (2u)

#define EzI2C_1_EZI2C_TX_CTRL  ((EzI2C_1_FIFO_SIZE - 1u)   | \
                                          EzI2C_1_TX_CTRL_MSB_FIRST | \
                                          EzI2C_1_TX_CTRL_ENABLED)

#define EzI2C_1_EZI2C_INTR_SLAVE_MASK  (EzI2C_1_INTR_SLAVE_I2C_BUS_ERROR | \
                                                 EzI2C_1_INTR_SLAVE_I2C_ARB_LOST  | \
                                                 EzI2C_1_INTR_SLAVE_I2C_STOP)

#define EzI2C_1_INTR_SLAVE_COMPLETE    (EzI2C_1_INTR_SLAVE_I2C_STOP | \
                                                 EzI2C_1_INTR_SLAVE_I2C_NACK | \
                                                 EzI2C_1_INTR_SLAVE_I2C_WRITE_STOP)


/***************************************
*    Initialization Register Settings
***************************************/

#if(EzI2C_1_SCB_MODE_EZI2C_CONST_CFG)

    #define EzI2C_1_EZI2C_DEFAULT_CTRL \
                                (EzI2C_1_GET_CTRL_BYTE_MODE  (EzI2C_1_EZI2C_BYTE_MODE_ENABLE)    | \
                                 EzI2C_1_GET_CTRL_ADDR_ACCEPT(EzI2C_1_EZI2C_NUMBER_OF_ADDRESSES) | \
                                 EzI2C_1_GET_CTRL_EC_AM_MODE (EzI2C_1_EZI2C_WAKE_ENABLE))

    #if(EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        #define EzI2C_1_EZI2C_DEFAULT_I2C_CTRL (EzI2C_1_EZI2C_CTRL)
    #else
        #define EzI2C_1_EZI2C_DEFAULT_I2C_CTRL (EzI2C_1_EZI2C_CTRL_AUTO | EzI2C_1_EZI2C_CTRL)
    #endif /* (EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */


    #define EzI2C_1_EZI2C_DEFAULT_RX_MATCH \
                                (EzI2C_1_GET_I2C_8BIT_ADDRESS(EzI2C_1_EZI2C_PRIMARY_SLAVE_ADDRESS) | \
                                 EzI2C_1_GET_RX_MATCH_MASK   (EzI2C_1_EZI2C_SLAVE_ADDRESS_MASK))

    #define EzI2C_1_EZI2C_DEFAULT_RX_CTRL  (EzI2C_1_EZI2C_RX_CTRL)
    #define EzI2C_1_EZI2C_DEFAULT_TX_CTRL  (EzI2C_1_EZI2C_TX_CTRL)

    #define EzI2C_1_EZI2C_DEFAULT_RX_FIFO_CTRL (0u)
    #if(EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        #define EzI2C_1_EZI2C_DEFAULT_TX_FIFO_CTRL (0u)
    #else
        #define EzI2C_1_EZI2C_DEFAULT_TX_FIFO_CTRL (2u)
    #endif /* (EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

    /* Interrupt sources */
    #define EzI2C_1_EZI2C_DEFAULT_INTR_I2C_EC_MASK (EzI2C_1_NO_INTR_SOURCES)
    #define EzI2C_1_EZI2C_DEFAULT_INTR_SPI_EC_MASK (EzI2C_1_NO_INTR_SOURCES)
    #define EzI2C_1_EZI2C_DEFAULT_INTR_MASTER_MASK (EzI2C_1_NO_INTR_SOURCES)
    #define EzI2C_1_EZI2C_DEFAULT_INTR_TX_MASK     (EzI2C_1_NO_INTR_SOURCES)

    #if(EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        #define EzI2C_1_EZI2C_DEFAULT_INTR_RX_MASK     (EzI2C_1_NO_INTR_SOURCES)
        #define EzI2C_1_EZI2C_DEFAULT_INTR_SLAVE_MASK  (EzI2C_1_INTR_SLAVE_I2C_ADDR_MATCH | \
                                                                 EzI2C_1_EZI2C_INTR_SLAVE_MASK)
    #else
        #define EzI2C_1_EZI2C_DEFAULT_INTR_RX_MASK     (EzI2C_1_INTR_RX_NOT_EMPTY)
        #define EzI2C_1_EZI2C_DEFAULT_INTR_SLAVE_MASK  (EzI2C_1_INTR_SLAVE_I2C_START | \
                                                                 EzI2C_1_EZI2C_INTR_SLAVE_MASK)
    #endif /* (EzI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

#endif /* (EzI2C_1_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* (CY_SCB_EZI2C_EzI2C_1_H) */


/* [] END OF FILE */

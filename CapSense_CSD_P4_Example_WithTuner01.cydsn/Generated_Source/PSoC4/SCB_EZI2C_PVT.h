/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in _EZI2C mode.
*  Do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_EZI2C_PVT_SCB_H)
#define CY_SCB_EZI2C_PVT_SCB_H

#include "SCB_EZI2C.h"


/***************************************
*      EZI2C Private Vars
***************************************/

extern volatile uint8 SCB_curStatus;
extern uint8 SCB_fsmState;

/* Variables intended to be used with Buffer 1: Primary slave address */
extern volatile uint8 * SCB_dataBuffer1;
extern uint16 SCB_bufSizeBuf1;
extern uint16 SCB_protectBuf1;
extern uint16 SCB_offsetBuf1;
extern uint16 SCB_indexBuf1;

#if(SCB_SECONDARY_ADDRESS_ENABLE_CONST)
    extern uint8 SCB_addrBuf1;
    extern uint8 SCB_addrBuf2;

    /* Variables intended to be used with Buffer 2: Primary slave address */
    extern volatile uint8 * SCB_dataBuffer2;
    extern uint16 SCB_bufSizeBuf2;
    extern uint16 SCB_protectBuf2;
    extern uint16 SCB_offsetBuf2;
    extern uint16 SCB_indexBuf2;
#endif /* (SCB_SECONDARY_ADDRESS_ENABLE_CONST) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(SCB_SCB_MODE_EZI2C_CONST_CFG)
    void SCB_EzI2CInit(void);
#endif /* (SCB_SCB_MODE_EZI2C_CONST_CFG) */

void SCB_EzI2CStop(void);
#if(SCB_EZI2C_WAKE_ENABLE_CONST)
    void SCB_EzI2CSaveConfig(void);
    void SCB_EzI2CRestoreConfig(void);
#endif /* (SCB_EZI2C_WAKE_ENABLE_CONST) */

#endif /* (CY_SCB__EZI2C_PVT_SCB_H) */


/* [] END OF FILE */

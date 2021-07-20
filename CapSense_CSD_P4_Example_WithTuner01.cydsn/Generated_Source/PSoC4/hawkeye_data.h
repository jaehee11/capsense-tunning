/*******************************************************************************
* File Name: hawkeye_data.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_hawkeye_data_H) /* Pins hawkeye_data_H */
#define CY_PINS_hawkeye_data_H

#include "cytypes.h"
#include "cyfitter.h"
#include "hawkeye_data_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    hawkeye_data_Write(uint8 value) ;
void    hawkeye_data_SetDriveMode(uint8 mode) ;
uint8   hawkeye_data_ReadDataReg(void) ;
uint8   hawkeye_data_Read(void) ;
uint8   hawkeye_data_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define hawkeye_data_DRIVE_MODE_BITS        (3)
#define hawkeye_data_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - hawkeye_data_DRIVE_MODE_BITS))

#define hawkeye_data_DM_ALG_HIZ         (0x00u)
#define hawkeye_data_DM_DIG_HIZ         (0x01u)
#define hawkeye_data_DM_RES_UP          (0x02u)
#define hawkeye_data_DM_RES_DWN         (0x03u)
#define hawkeye_data_DM_OD_LO           (0x04u)
#define hawkeye_data_DM_OD_HI           (0x05u)
#define hawkeye_data_DM_STRONG          (0x06u)
#define hawkeye_data_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define hawkeye_data_MASK               hawkeye_data__MASK
#define hawkeye_data_SHIFT              hawkeye_data__SHIFT
#define hawkeye_data_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define hawkeye_data_PS                     (* (reg32 *) hawkeye_data__PS)
/* Port Configuration */
#define hawkeye_data_PC                     (* (reg32 *) hawkeye_data__PC)
/* Data Register */
#define hawkeye_data_DR                     (* (reg32 *) hawkeye_data__DR)
/* Input Buffer Disable Override */
#define hawkeye_data_INP_DIS                (* (reg32 *) hawkeye_data__PC2)


#if defined(hawkeye_data__INTSTAT)  /* Interrupt Registers */

    #define hawkeye_data_INTSTAT                (* (reg32 *) hawkeye_data__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define hawkeye_data_DRIVE_MODE_SHIFT       (0x00u)
#define hawkeye_data_DRIVE_MODE_MASK        (0x07u << hawkeye_data_DRIVE_MODE_SHIFT)


#endif /* End Pins hawkeye_data_H */


/* [] END OF FILE */

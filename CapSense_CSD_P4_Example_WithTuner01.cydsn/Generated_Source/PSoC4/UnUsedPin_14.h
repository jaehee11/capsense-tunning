/*******************************************************************************
* File Name: UnUsedPin_14.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_UnUsedPin_14_H) /* Pins UnUsedPin_14_H */
#define CY_PINS_UnUsedPin_14_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UnUsedPin_14_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} UnUsedPin_14_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   UnUsedPin_14_Read(void);
void    UnUsedPin_14_Write(uint8 value);
uint8   UnUsedPin_14_ReadDataReg(void);
#if defined(UnUsedPin_14__PC) || (CY_PSOC4_4200L) 
    void    UnUsedPin_14_SetDriveMode(uint8 mode);
#endif
void    UnUsedPin_14_SetInterruptMode(uint16 position, uint16 mode);
uint8   UnUsedPin_14_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void UnUsedPin_14_Sleep(void); 
void UnUsedPin_14_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(UnUsedPin_14__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define UnUsedPin_14_DRIVE_MODE_BITS        (3)
    #define UnUsedPin_14_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UnUsedPin_14_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the UnUsedPin_14_SetDriveMode() function.
         *  @{
         */
        #define UnUsedPin_14_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define UnUsedPin_14_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define UnUsedPin_14_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define UnUsedPin_14_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define UnUsedPin_14_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define UnUsedPin_14_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define UnUsedPin_14_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define UnUsedPin_14_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define UnUsedPin_14_MASK               UnUsedPin_14__MASK
#define UnUsedPin_14_SHIFT              UnUsedPin_14__SHIFT
#define UnUsedPin_14_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in UnUsedPin_14_SetInterruptMode() function.
     *  @{
     */
        #define UnUsedPin_14_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define UnUsedPin_14_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define UnUsedPin_14_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define UnUsedPin_14_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(UnUsedPin_14__SIO)
    #define UnUsedPin_14_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(UnUsedPin_14__PC) && (CY_PSOC4_4200L)
    #define UnUsedPin_14_USBIO_ENABLE               ((uint32)0x80000000u)
    #define UnUsedPin_14_USBIO_DISABLE              ((uint32)(~UnUsedPin_14_USBIO_ENABLE))
    #define UnUsedPin_14_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define UnUsedPin_14_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define UnUsedPin_14_USBIO_ENTER_SLEEP          ((uint32)((1u << UnUsedPin_14_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << UnUsedPin_14_USBIO_SUSPEND_DEL_SHIFT)))
    #define UnUsedPin_14_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << UnUsedPin_14_USBIO_SUSPEND_SHIFT)))
    #define UnUsedPin_14_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << UnUsedPin_14_USBIO_SUSPEND_DEL_SHIFT)))
    #define UnUsedPin_14_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(UnUsedPin_14__PC)
    /* Port Configuration */
    #define UnUsedPin_14_PC                 (* (reg32 *) UnUsedPin_14__PC)
#endif
/* Pin State */
#define UnUsedPin_14_PS                     (* (reg32 *) UnUsedPin_14__PS)
/* Data Register */
#define UnUsedPin_14_DR                     (* (reg32 *) UnUsedPin_14__DR)
/* Input Buffer Disable Override */
#define UnUsedPin_14_INP_DIS                (* (reg32 *) UnUsedPin_14__PC2)

/* Interrupt configuration Registers */
#define UnUsedPin_14_INTCFG                 (* (reg32 *) UnUsedPin_14__INTCFG)
#define UnUsedPin_14_INTSTAT                (* (reg32 *) UnUsedPin_14__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define UnUsedPin_14_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(UnUsedPin_14__SIO)
    #define UnUsedPin_14_SIO_REG            (* (reg32 *) UnUsedPin_14__SIO)
#endif /* (UnUsedPin_14__SIO_CFG) */

/* USBIO registers */
#if !defined(UnUsedPin_14__PC) && (CY_PSOC4_4200L)
    #define UnUsedPin_14_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define UnUsedPin_14_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define UnUsedPin_14_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define UnUsedPin_14_DRIVE_MODE_SHIFT       (0x00u)
#define UnUsedPin_14_DRIVE_MODE_MASK        (0x07u << UnUsedPin_14_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins UnUsedPin_14_H */


/* [] END OF FILE */

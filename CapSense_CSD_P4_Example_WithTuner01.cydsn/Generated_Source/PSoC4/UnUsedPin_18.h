/*******************************************************************************
* File Name: UnUsedPin_18.h  
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

#if !defined(CY_PINS_UnUsedPin_18_H) /* Pins UnUsedPin_18_H */
#define CY_PINS_UnUsedPin_18_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UnUsedPin_18_aliases.h"


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
} UnUsedPin_18_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   UnUsedPin_18_Read(void);
void    UnUsedPin_18_Write(uint8 value);
uint8   UnUsedPin_18_ReadDataReg(void);
#if defined(UnUsedPin_18__PC) || (CY_PSOC4_4200L) 
    void    UnUsedPin_18_SetDriveMode(uint8 mode);
#endif
void    UnUsedPin_18_SetInterruptMode(uint16 position, uint16 mode);
uint8   UnUsedPin_18_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void UnUsedPin_18_Sleep(void); 
void UnUsedPin_18_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(UnUsedPin_18__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define UnUsedPin_18_DRIVE_MODE_BITS        (3)
    #define UnUsedPin_18_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UnUsedPin_18_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the UnUsedPin_18_SetDriveMode() function.
         *  @{
         */
        #define UnUsedPin_18_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define UnUsedPin_18_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define UnUsedPin_18_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define UnUsedPin_18_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define UnUsedPin_18_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define UnUsedPin_18_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define UnUsedPin_18_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define UnUsedPin_18_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define UnUsedPin_18_MASK               UnUsedPin_18__MASK
#define UnUsedPin_18_SHIFT              UnUsedPin_18__SHIFT
#define UnUsedPin_18_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in UnUsedPin_18_SetInterruptMode() function.
     *  @{
     */
        #define UnUsedPin_18_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define UnUsedPin_18_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define UnUsedPin_18_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define UnUsedPin_18_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(UnUsedPin_18__SIO)
    #define UnUsedPin_18_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(UnUsedPin_18__PC) && (CY_PSOC4_4200L)
    #define UnUsedPin_18_USBIO_ENABLE               ((uint32)0x80000000u)
    #define UnUsedPin_18_USBIO_DISABLE              ((uint32)(~UnUsedPin_18_USBIO_ENABLE))
    #define UnUsedPin_18_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define UnUsedPin_18_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define UnUsedPin_18_USBIO_ENTER_SLEEP          ((uint32)((1u << UnUsedPin_18_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << UnUsedPin_18_USBIO_SUSPEND_DEL_SHIFT)))
    #define UnUsedPin_18_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << UnUsedPin_18_USBIO_SUSPEND_SHIFT)))
    #define UnUsedPin_18_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << UnUsedPin_18_USBIO_SUSPEND_DEL_SHIFT)))
    #define UnUsedPin_18_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(UnUsedPin_18__PC)
    /* Port Configuration */
    #define UnUsedPin_18_PC                 (* (reg32 *) UnUsedPin_18__PC)
#endif
/* Pin State */
#define UnUsedPin_18_PS                     (* (reg32 *) UnUsedPin_18__PS)
/* Data Register */
#define UnUsedPin_18_DR                     (* (reg32 *) UnUsedPin_18__DR)
/* Input Buffer Disable Override */
#define UnUsedPin_18_INP_DIS                (* (reg32 *) UnUsedPin_18__PC2)

/* Interrupt configuration Registers */
#define UnUsedPin_18_INTCFG                 (* (reg32 *) UnUsedPin_18__INTCFG)
#define UnUsedPin_18_INTSTAT                (* (reg32 *) UnUsedPin_18__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define UnUsedPin_18_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(UnUsedPin_18__SIO)
    #define UnUsedPin_18_SIO_REG            (* (reg32 *) UnUsedPin_18__SIO)
#endif /* (UnUsedPin_18__SIO_CFG) */

/* USBIO registers */
#if !defined(UnUsedPin_18__PC) && (CY_PSOC4_4200L)
    #define UnUsedPin_18_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define UnUsedPin_18_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define UnUsedPin_18_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define UnUsedPin_18_DRIVE_MODE_SHIFT       (0x00u)
#define UnUsedPin_18_DRIVE_MODE_MASK        (0x07u << UnUsedPin_18_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins UnUsedPin_18_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: header.h
*
* Version: 1.0
*
* Description:
*  This file provides function prototypes, constants and macros for the example
*  project.
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>

/***************************************
*         Function Prototypes
****************************************/

uint8 ExecuteCommand(uint32 cmd);


/***************************************
*            Constants
****************************************/

/* Buffer and packet size */
//#define READ_BUFFER_SIZE     (6u)
#define READ_BUFFER_SIZE     (8u)
#define WRITE_BUFFER_SIZE     (7u)

#define PACKET_SIZE     (WRITE_BUFFER_SIZE)
#define READ_ONLY_OFFSET (3u)

/* Packet positions */
#define PACKET_SOP_POS  (0u)
#define PACKET_CMD_POS  (1u)
#define PACKET_STS_POS  (PACKET_CMD_POS)
#define PACKET_EOP_POS  (2u)

/* Start and end of packet markers */
#define PACKET_SOP      (0x01u)
#define PACKET_EOP      (0x17u)

/* Command valid status */
#define STS_CMD_DONE    (0x00u)
#define STS_CMD_FAIL    (0xFFu)

/* Commands set */
#define CMD_SET_OFF     (0u)
#define CMD_SET_RED     (1u)
#define CMD_SET_GREEN   (2u)
#define CMD_SET_BLUE    (3u)




/* [] END OF FILE */

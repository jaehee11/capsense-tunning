/*******************************************************************************
* File Name: CapSense_CSD_MBX.c
* Version 2.20
*
* Description:
*  This file provides the source code of Tuner communication APIs for the 
*  CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense_CSD_MBX.h"

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START CapSense_CSD_MBX` */

/* `#END` */

#if (CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_MANUAL)
    /*******************************************************************************
    * Function Name: CapSense_CSD_InitCsdParams
    ********************************************************************************
    *
    * Summary:
    *  Configures the CSD parameters to match the parameters in the inbox.
    *  Used only in the manual tuning mode to apply new scanning parameters from the Tuner 
    *  GUI.
    *
    * Parameters:
    *  inbox:  Pointer to Inbox structure in RAM.
    *
    * Return:
    *  None. Contents of the structure are not modified.
    * 
    * Global Variables:
    *  CapSense_CSD_modulationIDAC[] 	  - stores modulation IDAC values.
	*  CapSense_CSD_compensationIDAC[] 	  - stores compensation IDAC values.
	*  CapSense_CSD_widgetResolution[] 	  - used to store the scan resolution values for each widget.
	*  CapSense_CSD_senseClkDividerVal[]  - used to store the sense clock divider values for each widget.
	*  CapSense_CSD_sampleClkDividerVal[] - used to store the sample clock divider values for each widget.
    *  CapSense_CSD_fingerThreshold[] 	  - used to store the finger threshold values for each widget.
    *  CapSense_CSD_noiseThreshold[] 	  - used to store the noise threshold values for each widget.
    *  CapSense_CSD_hysteresis[] 		  - used to store the hysteresis values for each widget.
    *  CapSense_CSD_debounce[] 			  - used to store the debounce values for each widget.
	* 
    *******************************************************************************/
    static void CapSense_CSD_InitCsdParams(volatile const CapSense_CSD_INBOX *inbox);
    static void CapSense_CSD_InitCsdParams(volatile const CapSense_CSD_INBOX *inbox)
    {
        /* Define widget sensor belongs to */
        uint8 sensor = inbox->sensorIndex;
        uint8 widget = CapSense_CSD_widgetNumber[sensor];
        
        /* Scanning parameters */
		#if(0u == CapSense_CSD_AUTOCALIBRATION_ENABLE)
			CapSense_CSD_modulationIDAC[sensor] = inbox->CapSense_CSD_inboxCsdCfg.modulatorIDAC; 

			#if (CapSense_CSD_IDAC_CNT == 2u)
				CapSense_CSD_compensationIDAC[sensor] = inbox->CapSense_CSD_inboxCsdCfg.compensationIDAC;
			#endif /* ( CapSense_CSD_IDAC_CNT == 2u ) */
		#endif /* (0u != CapSense_CSD_AUTOCALIBRATION_ENABLE) */

		CapSense_CSD_SetIDACRange((uint32)inbox->CapSense_CSD_inboxCsdCfg.idacRange);

        CapSense_CSD_widgetResolution[widget] =
		(uint32)(~(CapSense_CSD_RESOLUTION_16_BITS << inbox->CapSense_CSD_inboxCsdCfg.scanResolution));
                                                    
        CapSense_CSD_widgetResolution[widget] &= CapSense_CSD_RESOLUTION_16_BITS;
		
		#if (0u != CapSense_CSD_MULTIPLE_FREQUENCY_SET )
            CapSense_CSD_senseClkDividerVal[sensor] = inbox->CapSense_CSD_inboxCsdCfg.analogSwitchDivider;
            CapSense_CSD_sampleClkDividerVal[sensor] = inbox->CapSense_CSD_inboxCsdCfg.modulatorDivider;
        #else
            CapSense_CSD_senseClkDividerVal = inbox->CapSense_CSD_inboxCsdCfg.analogSwitchDivider;
            CapSense_CSD_sampleClkDividerVal = inbox->CapSense_CSD_inboxCsdCfg.modulatorDivider;
        #endif /* (0u != CapSense_CSD_MULTIPLE_FREQUENCY_SET ) */
		
		#if(0u != CapSense_CSD_CSHL_API_GENERATE)
	        #if (0u != CapSense_CSD_TOTAL_GENERICS_COUNT)
	            /* Exclude generic widget */
	            if(widget < CapSense_CSD_END_OF_WIDGETS_INDEX)
	            {
	        #endif  /* 0u != CapSense_CSD_TOTAL_GENERICS_COUNT */
	        
	            /* High level parameters */
	            CapSense_CSD_fingerThreshold[widget] = inbox->CapSense_CSD_inboxCsdCfg.fingerThreshold;
	            CapSense_CSD_noiseThreshold[widget]  = inbox->CapSense_CSD_inboxCsdCfg.noiseThreshold;
	            
	            CapSense_CSD_hysteresis[widget] = inbox->CapSense_CSD_inboxCsdCfg.hysteresis;
	            CapSense_CSD_debounce[widget]   = inbox->CapSense_CSD_inboxCsdCfg.debounce;
				
				#if(CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
					CapSense_CSD_centroidMult[widget] = (uint16)((inbox->CapSense_CSD_inboxCsdCfg.apiResolution *
															(uint32)CapSense_CSD_RES_MULT) / (uint32)CapSense_CSD_numberOfSensors[widget]);		
															
				#endif /* (CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */
	        
	        #if (0u != CapSense_CSD_TOTAL_GENERICS_COUNT)
	            /* Exclude generic widget */
	            }
	        #endif  /* 0u != CapSense_CSD_TOTAL_GENERICS_COUNT */

	        /* Re-Init baseline */
	        CapSense_CSD_InitializeAllBaselines();
		#endif /* (0u != CapSense_CSD_CSHL_API_GENERATE) */
    }
#endif  /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_MANUAL) */


    /*******************************************************************************
    * Function Name: CapSense_CSD_InitGesturesParams
    ********************************************************************************
    *
    * Summary:
    *  Configures the parameters of gestures to match the parameters in the inbox.
    *  Used only in the manual and auto tuning mode or if the gestures support is enabled. 
	*  Intended apply new scanning parameters from the Tuner GUI.
    *
    * Parameters:
    *  inbox:  Pointer to Inbox structure in RAM.
    *
    * Return:
    *  None. Contents of the structure are not modified.
	* 
    *******************************************************************************/
#if((CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) && (0u != CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT))
	static void CapSense_CSD_InitGesturesParams(volatile const CapSense_CSD_INBOX *inbox);
	static void CapSense_CSD_InitGesturesParams(volatile const CapSense_CSD_INBOX *inbox)
	{	
		#if(0u != CapSense_CSD_IS_ANY_GESTURES_EN)			
			#if(0u != CapSense_CSD_CLICK_GEST_ENABLED)
				CapSense_CSD_gesturesConfig.clickRadiusX			= (uint8)inbox->CapSense_CSD_inboxTmgCfg.clickRadiusX;
				CapSense_CSD_gesturesConfig.clickRadiusY			= (uint8)inbox->CapSense_CSD_inboxTmgCfg.clickRadiusY;
				CapSense_CSD_gesturesConfig.doubleClickRadius		= (uint8)inbox->CapSense_CSD_inboxTmgCfg.doubleClickRadius;
				CapSense_CSD_gesturesConfig.STDoubleClickTimeoutMax	= inbox->CapSense_CSD_inboxTmgCfg.stDoubleClickTimeoutMax;
				CapSense_CSD_gesturesConfig.STDoubleClickTimeoutMin	= inbox->CapSense_CSD_inboxTmgCfg.stDoubleClickTimeoutMin;
				CapSense_CSD_gesturesConfig.STClickTimeoutMax		= inbox->CapSense_CSD_inboxTmgCfg.stClickTimeoutMax;
				CapSense_CSD_gesturesConfig.STClickTimeoutMin		= inbox->CapSense_CSD_inboxTmgCfg.stClickTimeoutMin;
				CapSense_CSD_gesturesConfig.DTClickTimeoutMax		= inbox->CapSense_CSD_inboxTmgCfg.dtClickTimeoutMax;
				CapSense_CSD_gesturesConfig.DTClickTimeoutMin		= inbox->CapSense_CSD_inboxTmgCfg.dtClickTimeoutMin;
			#endif /* (0u != CapSense_CSD_CLICK_GEST_ENABLED) */
			
			#if(0u != CapSense_CSD_ZOOM_GEST_ENABLED)
				CapSense_CSD_gesturesConfig.dtScrollToZoomDebounce  = inbox->CapSense_CSD_inboxTmgCfg.dtPanToZoomDebounce;
				CapSense_CSD_gesturesConfig.DTZoomDebounce			= inbox->CapSense_CSD_inboxTmgCfg.dtZoomDebounce;
				CapSense_CSD_gesturesConfig.zoomActiveDistanceX		= inbox->CapSense_CSD_inboxTmgCfg.zoomActiveDistanceX;
				CapSense_CSD_gesturesConfig.zoomActiveDistanceY		= inbox->CapSense_CSD_inboxTmgCfg.zoomActiveDistanceY;
			#endif /* (0u != CapSense_CSD_ZOOM_GEST_ENABLED) */
			
			#if(0u != CapSense_CSD_ST_SCROLL_GEST_ENABLED)
				CapSense_CSD_gesturesConfig.stScrollDebounce		= inbox->CapSense_CSD_inboxTmgCfg.stScrDebounce;

				CapSense_CSD_gesturesConfig.stScrollThreshold1X		= inbox->CapSense_CSD_inboxTmgCfg.stScrThreshold1X;	
				CapSense_CSD_gesturesConfig.stScrollThreshold2X		= inbox->CapSense_CSD_inboxTmgCfg.stScrThreshold2X;
				CapSense_CSD_gesturesConfig.stScrollThreshold3X		= inbox->CapSense_CSD_inboxTmgCfg.stScrThreshold3X;
				CapSense_CSD_gesturesConfig.stScrollThreshold4X		= inbox->CapSense_CSD_inboxTmgCfg.stScrThreshold4X;
				CapSense_CSD_gesturesConfig.stScrollThreshold1Y		= inbox->CapSense_CSD_inboxTmgCfg.stScrThreshold1Y;
				CapSense_CSD_gesturesConfig.stScrollThreshold2Y		= inbox->CapSense_CSD_inboxTmgCfg.stScrThreshold2Y;
				CapSense_CSD_gesturesConfig.stScrollThreshold3Y		= inbox->CapSense_CSD_inboxTmgCfg.stScrThreshold3Y;
				CapSense_CSD_gesturesConfig.stScrollThreshold4Y		= inbox->CapSense_CSD_inboxTmgCfg.stScrThreshold4Y;
				CapSense_CSD_gesturesConfig.stScrollStep1			= inbox->CapSense_CSD_inboxTmgCfg.stScrStep1;
				CapSense_CSD_gesturesConfig.stScrollStep2			= inbox->CapSense_CSD_inboxTmgCfg.stScrStep2;
				CapSense_CSD_gesturesConfig.stScrollStep3			= inbox->CapSense_CSD_inboxTmgCfg.stScrStep3;
				CapSense_CSD_gesturesConfig.stScrollStep4			= inbox->CapSense_CSD_inboxTmgCfg.stScrStep4;
				CapSense_CSD_gesturesConfig.stInScrActiveDistanceX	= inbox->CapSense_CSD_inboxTmgCfg.stInScrActiveDistanceX;
				CapSense_CSD_gesturesConfig.stInScrActiveDistanceY	= inbox->CapSense_CSD_inboxTmgCfg.stInScrActiveDistanceY;
				CapSense_CSD_gesturesConfig.stInScrCountLevel	    = inbox->CapSense_CSD_inboxTmgCfg.stInScrCountLevel;
			#endif /* (0u != CapSense_CSD_ST_SCROLL_GEST_ENABLED) */
			
			#if(0u != CapSense_CSD_DT_SCROLL_GEST_ENABLED)
				CapSense_CSD_gesturesConfig.dtScrollDebounce		= inbox->CapSense_CSD_inboxTmgCfg.dtScrDebounce;
				CapSense_CSD_gesturesConfig.dtScrollThreshold1X		= inbox->CapSense_CSD_inboxTmgCfg.dtScrThreshold1X;	
				CapSense_CSD_gesturesConfig.dtScrollThreshold2X		= inbox->CapSense_CSD_inboxTmgCfg.dtScrThreshold2X;
				CapSense_CSD_gesturesConfig.dtScrollThreshold3X		= inbox->CapSense_CSD_inboxTmgCfg.dtScrThreshold3X;
				CapSense_CSD_gesturesConfig.dtScrollThreshold4X		= inbox->CapSense_CSD_inboxTmgCfg.dtScrThreshold4X;
				CapSense_CSD_gesturesConfig.dtScrollThreshold1Y		= inbox->CapSense_CSD_inboxTmgCfg.dtScrThreshold1Y;
				CapSense_CSD_gesturesConfig.dtScrollThreshold2Y		= inbox->CapSense_CSD_inboxTmgCfg.dtScrThreshold2Y;
				CapSense_CSD_gesturesConfig.dtScrollThreshold3Y		= inbox->CapSense_CSD_inboxTmgCfg.dtScrThreshold3Y;
				CapSense_CSD_gesturesConfig.dtScrollThreshold4Y		= inbox->CapSense_CSD_inboxTmgCfg.dtScrThreshold4Y;
				CapSense_CSD_gesturesConfig.dtScrollStep1			= inbox->CapSense_CSD_inboxTmgCfg.dtScrStep1;
				CapSense_CSD_gesturesConfig.dtScrollStep2			= inbox->CapSense_CSD_inboxTmgCfg.dtScrStep2;
				CapSense_CSD_gesturesConfig.dtScrollStep3			= inbox->CapSense_CSD_inboxTmgCfg.dtScrStep3;
				CapSense_CSD_gesturesConfig.dtScrollStep4			= inbox->CapSense_CSD_inboxTmgCfg.dtScrStep4;
				CapSense_CSD_gesturesConfig.dtInScrActiveDistanceX	= inbox->CapSense_CSD_inboxTmgCfg.dtInScrActiveDistanceX;
				CapSense_CSD_gesturesConfig.dtInScrActiveDistanceY	= inbox->CapSense_CSD_inboxTmgCfg.dtInScrActiveDistanceY;
				CapSense_CSD_gesturesConfig.dtInScrCountLevel	    = inbox->CapSense_CSD_inboxTmgCfg.dtInScrCountLevel;
			#endif /* (0u != CapSense_CSD_DT_SCROLL_GEST_ENABLED) */

			#if(0u != CapSense_CSD_FLICK_GEST_ENABLED)
				CapSense_CSD_gesturesConfig.flickSampleTime			= inbox->CapSense_CSD_inboxTmgCfg.flickSampleTime;
				CapSense_CSD_gesturesConfig.flickActiveDistanceX	= inbox->CapSense_CSD_inboxTmgCfg.flickActiveDistanceX;
				CapSense_CSD_gesturesConfig.flickActiveDistanceY	= inbox->CapSense_CSD_inboxTmgCfg.flickActiveDistanceY;
			#endif /* (0u != CapSense_CSD_FLICK_GEST_ENABLED) */
			
			#if(0u != CapSense_CSD_ROTATE_GEST_ENABLED)
				CapSense_CSD_gesturesConfig.rotateDebounce			= inbox->CapSense_CSD_inboxTmgCfg.rotateDebounce;
			#endif /* (0u != CapSense_CSD_ROTATE_GEST_ENABLED) */
			
			#if(0u != CapSense_CSD_EDGE_SWIPE_GEST_ENABLED)
				CapSense_CSD_gesturesConfig.edgeSwipeActiveDistance	= inbox->CapSense_CSD_inboxTmgCfg.edgeSwipeActiveDistance;
				CapSense_CSD_gesturesConfig.bottomAngleThreshold	= inbox->CapSense_CSD_inboxTmgCfg.bottomAngleThreshold;
				CapSense_CSD_gesturesConfig.edgeSwipeTimeout		= inbox->CapSense_CSD_inboxTmgCfg.edgeSwipeTime;
				CapSense_CSD_TMG_edgeSwipeCompleteTimeout			= inbox->CapSense_CSD_inboxTmgCfg.edgeSwipeCompleteTimeout;			
				CapSense_CSD_gesturesConfig.topAngleThreshold		= inbox->CapSense_CSD_inboxTmgCfg.topAngleThreshold;
				CapSense_CSD_gesturesConfig.widthOfDisambiguation	= inbox->CapSense_CSD_inboxTmgCfg.widthOfDisambiguation;
			#endif /* (0u != CapSense_CSD_EDGE_SWIPE_GEST_ENABLED) */
			
			CapSense_CSD_TMG_InitGestures(&CapSense_CSD_gesturesConfig);
		#endif /* (0u != CapSense_CSD_IS_ANY_GESTURES_EN) */
		
		#if(0u != CapSense_CSD_TP_GESTURE_POS_FILTERS_MASK)
			CapSense_CSD_posFiltersMask[CapSense_CSD_TRACKPAD__TPG] = inbox->CapSense_CSD_inboxTmgCfg.filtersMask;  
		#endif /* (0u != CapSense_CSD_TP_GESTURE_POS_FILTERS_MASK) */
		
		#if(0u != (CapSense_CSD_XY_ADAPTIVE_IIR_MASK & CapSense_CSD_TP_GESTURE_POS_FILTERS_MASK)) 
			CapSense_CSD_adpFltOptions.divVal     	= inbox->CapSense_CSD_inboxTmgCfg.filterDivisor;
		    CapSense_CSD_adpFltOptions.largeMovTh 	= inbox->CapSense_CSD_inboxTmgCfg.largeMovThreshold;
		    CapSense_CSD_adpFltOptions.littleMovTh	= inbox->CapSense_CSD_inboxTmgCfg.littleMovThreshold;
		    CapSense_CSD_adpFltOptions.maxK		= inbox->CapSense_CSD_inboxTmgCfg.maxFilterCoef;
		    CapSense_CSD_adpFltOptions.minK		= inbox->CapSense_CSD_inboxTmgCfg.minFilterCoef;
		    CapSense_CSD_adpFltOptions.noMovTh		= inbox->CapSense_CSD_inboxTmgCfg.noMovThreshold;
		#endif /* (0u != (CapSense_CSD_XY_ADAPTIVE_IIR_MASK & CapSense_CSD_TP_GESTURE_POS_FILTERS_MASK)) */	
	}
#endif /* ((CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) && (0u != CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT)) */


/*******************************************************************************
* Function Name: CapSense_CSD_InitMailbox
********************************************************************************
*
* Summary:
*  Initializes parameters of the mailbox structure.
*  Sets the type and size of the mailbox structure. 
*  Sets a check sum to check by the Tuner GUI and noReadMsg flag to indicate that this 
*  is the first communication packet.
*
* Parameters:
*  mbx:  Pointer to Mailbox structure in RAM.
*
* Return:
*  None. Modifies the contents of mbx and mbx->outbox.
*
* Global Variables:
*  None
* 
*******************************************************************************/
void CapSense_CSD_InitMailbox(volatile CapSense_CSD_MAILBOX *mbx)
{
    /* Restore TYPE_ID (clear busy flag) to indicate "action complete" */
    mbx->type = CapSense_CSD_TYPE_ID;
    /* Restore default value - clear "have_msg" */
    mbx->size = sizeof(CapSense_CSD_MAILBOX);
    
    /* Additional fields for async and reset handling */
    #if((CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) && (0u != CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
		(CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_MANUAL))
        mbx->outbox.noReadMessage = 1u;
    #endif  /* ((CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) && (0u != CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
		        (CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_MANUAL)) */
    
    mbx->outbox.checkSum = (uint16)(CapSense_CSD_CHECK_SUM);
}


/*******************************************************************************
* Function Name:  CapSense_CSD_PostMessage
********************************************************************************
*
* Summary:
*  This blocking function waits while the Tuner GUI reports that the mailbox content
*  could be modified (clears CapSense_CSD_BUSY_FLAG). Then loads the report 
*  data to the outbox and sets a busy flag.
*  In the manual tuning mode the report data is:
*    - raw data, baseline, signal;
*  In the auto tuning mode the added data is:
*    - fingerThreshold;
*    - noiseThreshold;
*    - scanResolution;
*    - idacValue;
*    - prescaler.
*
* Parameters:
*  mbx:  Pointer to Mailbox structure in RAM.
*
* Return:
*  None. Modifies the contents of mbx->outbox.
*
* Global Variables:
*  None
*
*******************************************************************************/
void CapSense_CSD_PostMessage(volatile CapSense_CSD_MAILBOX *mbx)
{
    uint8 i;
	
	#if ( CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_AUTO )
		uint8 tmpResolutionIndex;
		uint16 tmpResolutionValue;
	#endif /* ( CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_AUTO ) */	

    /* Check busy flag */
    while (mbx->type != CapSense_CSD_TYPE_ID){}

	/* Copy scan parameters */
	#if((CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_AUTO) || (0u != CapSense_CSD_AUTOCALIBRATION_ENABLE))
		/* Copy tuned idac values */
        for(i = 0u; i < CapSense_CSD_TOTAL_SENSOR_COUNT; i++)
        {
            mbx->outbox.modulationIDAC[i] = CapSense_CSD_modulationIDAC[i];
			#if (CapSense_CSD_IDAC_CNT == 2u)
            	mbx->outbox.compensationIDAC[i] = CapSense_CSD_compensationIDAC[i];
			#endif /* (CapSense_CSD_IDAC_CNT == 2u) */
        }
	#endif /* ((CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_AUTO) || (0u != CapSense_CSD_AUTOCALIBRATION_ENABLE)) */
	
    #if ( CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_AUTO )
        for(i = 0u; i < CapSense_CSD_TOTAL_SCANSLOT_COUNT; i++)
        {
            mbx->outbox.analogSwitchDivider[i] = CapSense_CSD_senseClkDividerVal[i];
            mbx->outbox.modulatorDivider[i] = CapSense_CSD_sampleClkDividerVal[i];
        }
		
		/* Widget resolution, take to account TP and MB */
        for(i = 0u; i < CapSense_CSD_WIDGET_RESOLUTION_PARAMETERS_COUNT; i++)
        {
			tmpResolutionValue = (uint16)(CapSense_CSD_widgetResolution[i] >> CapSense_CSD_MSB_RESOLUTION_OFFSET);
			tmpResolutionIndex = 0u;	
			
			while(0u != tmpResolutionValue)
			{
				tmpResolutionIndex++;
				tmpResolutionValue >>= 1u;
			}
			
            mbx->outbox.scanResolution[i] = tmpResolutionIndex;
        }
		
		#if(0u != CapSense_CSD_CSHL_API_GENERATE)
			/* Parameters are changed in run time */
	        for(i = 0u; i < CapSense_CSD_WIDGET_CSHL_PARAMETERS_COUNT; i++)
	        {
	            mbx->outbox.fingerThreshold[i] = CapSense_CSD_fingerThreshold[i];
	            mbx->outbox.noiseThreshold[i]  = CapSense_CSD_noiseThreshold[i];
				mbx->outbox.hysteresis[i]  	   = CapSense_CSD_hysteresis[i];
	        }
		#endif /* (0u != CapSense_CSD_CSHL_API_GENERATE) */
		
    #endif /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_AUTO) */
	
	
    /* Copy all data - Raw, Base, Signal, OnMask */
    for(i = 0u; i < CapSense_CSD_TOTAL_SENSOR_COUNT; i++)
    {
        mbx->outbox.rawData[i]  = CapSense_CSD_sensorRaw[i];
		#if(0u != CapSense_CSD_CSHL_API_GENERATE)
	        mbx->outbox.baseLine[i] = CapSense_CSD_sensorBaseline[i];
	        #if (CapSense_CSD_SIGNAL_SIZE == CapSense_CSD_SIGNAL_SIZE_UINT8)
	            mbx->outbox.sensorSignal[i]   = (uint8)CapSense_CSD_sensorSignal[i];
	        #else
	            mbx->outbox.sensorSignal[i]   = (uint16)CapSense_CSD_sensorSignal[i];
	        #endif  /* (CapSense_CSD_SIGNAL_SIZE == CapSense_CSD_SIGNAL_SIZE_UINT8) */
		#endif /* (0u != CapSense_CSD_CSHL_API_GENERATE) */
    }

    /* Set busy flag */
    mbx->type = CapSense_CSD_BUSY_FLAG;
}


#if ((CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) && (0u != CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
	 (CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_MANUAL))

    /*******************************************************************************
    * Function Name: CapSense_CSD_ReadMessage
    ********************************************************************************
    *
    * Summary:
    *  If CapSense_CSD_HAVE_MSG is found in the mailbox, the function initializes
    *	the component with parameters which are found in the inbox.
    *   Signal is DONE by overwriting the value in the mailbox size field.
    *  Only available in the manual tuning mode.
    *
    * Parameters:
    *  mbx:  Pointer to Mailbox structure in RAM.
    *
    * Return:
    *  None. Modifies the contents of mbx.
	*
    * Global Variables:
	*  None
	*
    *******************************************************************************/
    void CapSense_CSD_ReadMessage(volatile CapSense_CSD_MAILBOX *mbx)
    {
        volatile CapSense_CSD_INBOX *tmpInbox;
       
        /* Do we have a message waiting? */
        if ((mbx->size) == CapSense_CSD_HAVE_MSG)
        {
            tmpInbox = &(mbx->inbox);
            
			#if(CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_MANUAL)
				if(tmpInbox->sensorIndex != CapSense_CSD_MAX_UINT_8)
				{
	            	CapSense_CSD_InitCsdParams(tmpInbox);
				}
			#endif /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_MANUAL) */
			
			#if(0u != CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT)
				if(tmpInbox->sensorIndex == CapSense_CSD_MAX_UINT_8)
				{
					CapSense_CSD_InitGesturesParams(tmpInbox);
				}
			#endif /* (0u != CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT) */
    
            /* Notify host/tuner that we have consumed message */
            mbx->size = sizeof(CapSense_CSD_MAILBOX);
            
            /* Default settings were changed */
            mbx->outbox.noReadMessage = 0u;
			
			/* `#START CapSense_CSD_MBX_READ_MSG` */

			/* `#END` */
        }
    }
#endif  /* ((CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) && (0u != CapSense_CSD_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
		    (CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_MANUAL)) */


/* [] END OF FILE */

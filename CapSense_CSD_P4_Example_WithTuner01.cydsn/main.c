 /* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
// /* unit8 widget is in Widgets constants definition of CapSense_CSHL.h */

//<A1_Global_Multi>

#include <project.h>
#include <header.h>
#include "CapSense_CSHL.h"

#define Debug

#ifdef Debug
#define hawkeye
//#define CYDebug
#endif

#ifdef hawkeye
   extern void report_debug_data( void );
   unsigned char d = 0;
#endif
extern uint16 CapSense_SensorSignal[6u];
//extern uint16 CapSense_SensorSignal[CapSense_TOTAL_SENSOR_COUNT];
extern uint16 CapSense_sensorRaw[CapSense_TOTAL_SENSOR_COUNT];
extern uint16 CapSense_sensorBaseline[CapSense_TOTAL_SENSOR_COUNT];
//extern uint8 CapSense_sensorOnMask[(((CapSense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];
extern uint8 CapSense_sensorOnMask[1u];
/* Cypress Functions */
CY_ISR_PROTO (WDT_ISR);
uint32 ILODelayCycles_0 = 0;
uint32 ILODelayCycles_1 = 0;

//------------------------ User Value & Function ------------------------//

/* Initialize Baseline for filter with specific sensing count */
void CapSense_CSD_InitializeAllBaselines_Filtered(uint8 Repeat);
void CapSense_CSD_InitializeSensorBaseline_Filtered(uint32 sensor);
void CapSense_CSD_BaseInit_Filtered(uint32 sensor);
#define BaselineUpdateCount 16u
extern uint16 CapSense_rawFilterData1[CapSense_TOTAL_SENSOR_COUNT];

/* WDT */
#define wdt_ms 40u
void WDT_Clear(void);
void Clear_WDT_With_Flag(void);
void Set_WDT_Clear_Flag(uint8 value);
//void WDT_Init(uint16 WDTResetTime, uint16 WDTSleepTime);
void WDT_Init(uint8 IgnoreBit, uint16 Match);
void WDT_Match_Init(uint8 IgnoreBit, uint16 Match);
void Force_WDT_Reset(void);
uint8 WDT_Clear_Flag = 0u;
uint16 WDT_Ignore;  
uint16 WDT_Match;

/* SleepMode */
//#define WDT_RESET_TIME 2000u * 32 /* WDT reset time */    
//#define WDT_INTERRUPT_TIME 100 * 32  /* WDT Interrupt for sleep */
#define WDT_RESET_TIME 1 /* WDT reset time */    
#define WDT_INTERRUPT_TIME 20  /* WDT Interrupt for sleep */

unsigned char key_scan_count;
extern unsigned int temp[CapSense_TOTAL_SENSOR_COUNT];

#ifdef Debug
void CapSense_UpdateEnabledBaselines_Filter(void);
void CapSense_UpdateSensorBaseline_Filter(uint32 sensor);
void CapSense_UpdateBaselineNoThreshold_Filter(uint32 sensor);
uint16 Capsense_FilteredRawData[CapSense_TOTAL_SENSOR_COUNT];
uint16 Sub_Buff[CapSense_TOTAL_SENSOR_COUNT];
uint8 SignalBit_Debug = 0;
#endif
/*******************************************************************************
* Define Interrupt service routine and allocate an vector to the Interrupt
********************************************************************************/
CY_ISR(InterruptHandler)        //SimpleUX   Timer ISR 설정
{
    Timer_1_ClearInterrupt(Timer_1_INTR_MASK_CC_MATCH);
    
    Set_WDT_Clear_Flag(1);
}

void FirstSensingData(void);

#ifdef CYDebug
#define SW_UART_PORT        (3u)
#define SW_UART_PIN         (0u)
#endif

int main(void)
{
	/* Enable global interrupt */
	CyGlobalIntEnable;
    
    UnUsedPin_16_Write(0);
    UnUsedPin_9_Write(0);
    UnUsedPin_18_Write(0);
    UnUsedPin_10_Write(0);
    UnUsedPin_14_Write(0);
    UnUsedPin_15_Write(0);
    #ifndef CYDebug
    hawkeye_clk_Write(0);
    hawkeye_data_Write(0);
    #endif
        
    Clock_1_Enable();                           //SimpleUX
    
    /* Enable the Interrupt component connected to interrupt */
    TC_CC_ISR_StartEx(InterruptHandler);        //SimpleUX

	/* Start the components */
    Timer_1_Start();                            //SimpleUX
    
    #ifdef CYDebug
    uint8 buff[46];
    /* Configure SW_Tx_UART to use port and pin from defines above */
    SW_Tx_UART_StartEx(SW_UART_PORT, SW_UART_PIN);
    #endif
    
    //WDT_Init(WDT_RESET_TIME, WDT_INTERRUPT_TIME);   /* Initialize WDT Interval */
    
    CyDelay(20u);
    CyDelay(20u);
    
	/* Initialize and start the CapSense component */
	CapSense_Start();			
    
    FirstSensingData();
    
	/* Initialize Baseline using Adapted filter */
    CapSense_CSD_InitializeAllBaselines_Filtered(BaselineUpdateCount);
    
    
	while(1)	/* Sensor Scanning Loop */
	{      
		/* Start scanning all enabled sensors */
		CapSense_ScanEnabledWidgets();
		
        /* Wait for scanning to complete */
		while(CapSense_IsBusy() != 0)
        {
        }
        
		/* Update all baselines */
        #ifdef Debug
        CapSense_UpdateEnabledBaselines_Filter();
        #else
        CapSense_UpdateEnabledBaselines();    
        #endif
        
        /* Is any sensor active? */
        CapSense_CheckIsAnyWidgetActive();
        
        #ifdef CYDebug
        //Fill in output buffer by the sinValue
        buff[0]  = 0x0D;
        buff[1]  = 0x0a;
        #if 1
        buff[2]  = CapSense_SensorOnMask[0];
        buff[3]  = CapSense_SensorOnMask[1];
        
        for(SignalBit_Debug = 0; SignalBit_Debug < CapSense_TOTAL_SENSOR_COUNT; SignalBit_Debug++)
        {
            Sub_Buff[SignalBit_Debug] = (Capsense_FilteredRawData[SignalBit_Debug] > CapSense_SensorBaseline[SignalBit_Debug]) ? (Capsense_FilteredRawData[SignalBit_Debug] - CapSense_SensorBaseline[SignalBit_Debug]) : 0;
        }
        
        for(SignalBit_Debug = 0; SignalBit_Debug < CapSense_TOTAL_SENSOR_COUNT; SignalBit_Debug++)
        {
            buff[(SignalBit_Debug*2)+4] = Sub_Buff[SignalBit_Debug];
            buff[(SignalBit_Debug*2)+5] = Sub_Buff[SignalBit_Debug]>>8;
        }
        //Send data to host
        SW_Tx_UART_PutArray(buff, 27);
        #endif
        #if 0
        for(SignalBit_Debug = 0; SignalBit_Debug < CapSense_TOTAL_SENSOR_COUNT; SignalBit_Debug++)
        {
            //buff[(SignalBit_Debug*2)+2] = CapSense_SensorRaw[SignalBit_Debug];
            //buff[(SignalBit_Debug*2)+3] = CapSense_SensorRaw[SignalBit_Debug]>>8;
            buff[(SignalBit_Debug*2)+2] = Capsense_FilteredRawData[SignalBit_Debug];
            buff[(SignalBit_Debug*2)+3] = Capsense_FilteredRawData[SignalBit_Debug]>>8;
        }
        for(SignalBit_Debug = 0; SignalBit_Debug < CapSense_TOTAL_SENSOR_COUNT; SignalBit_Debug++)
        {
            buff[(SignalBit_Debug*2)+24] = CapSense_SensorBaseline[SignalBit_Debug];
            buff[(SignalBit_Debug*2)+25] = CapSense_SensorBaseline[SignalBit_Debug]>>8;
        }
        //Send data to host
        SW_Tx_UART_PutArray(buff, 46);
        /*
        if(debugflag == 1)
        {
            debugcnt = 0;
            debugflag = 0;
        }
        */
        #endif
        #endif
        
        #ifdef hawkeye
            for(SignalBit_Debug = 0; SignalBit_Debug < CapSense_TOTAL_SENSOR_COUNT; SignalBit_Debug++)
            {
                Sub_Buff[SignalBit_Debug] = (Capsense_FilteredRawData[SignalBit_Debug] > CapSense_SensorBaseline[SignalBit_Debug]) ? (Capsense_FilteredRawData[SignalBit_Debug] - CapSense_SensorBaseline[SignalBit_Debug]) : 0;
            }
            //temp[0] = sleep_flag;
            //temp[0] = CapSense_GetModulationIDAC(0);
            //temp[0] = CapSense_GetDebounce(25);
            //temp[0] = comm_err_flag;
            if(d < 2)
            {
                d++;
            }
            else
            {
                report_debug_data();       
                d = 0;
            }
        #endif
	}
}
#if 0
void Long_key_detect(void)
{
    unsigned char i = 0;
    uint8 flag = 0;
    
    for( i = 0; i < CapSense_TOTAL_SENSOR_COUNT; i++)
    {
        if(CapSense_SensorSignal[i] > CapSense_noiseThreshold[i])
        {
            flag = 1;
            break;
        }
        else
        {
        }
    }
    
    
    long_key_start = flag;
}

void Abnormal_Capsense_Detect(void)
{
    uint8 i = 0;
    
    for(i = 0; i < CapSense_TOTAL_SENSOR_COUNT; i++)
    {
        if((CapSense_SensorRaw[i] <= (uint16)(((uint32)Resolution_Max[i]*Abnormal_Capsense_detect_Low)/100) ) ||
           (CapSense_SensorRaw[i] >= (uint16)(((uint32)Resolution_Max[i]*Abnormal_Capsense_detect_High)/100) ) )
        {
            Abnormal_Capsense_Flag = 1;
            break;
        }
        else
        {
            Abnormal_Capsense_Flag = 0;
        }
    }
}

void baseline_check(void)
{
    unsigned char i = 0;
    for( i = 0; i < CapSense_TOTAL_SENSOR_COUNT ; i++)
    {
        if( (CapSense_sensorBaseline[i] > ((default_baseline[i]*12)/10)) && (CapSense_GetModulationIDAC(i) == IDAC_val[i]) ) 
        {
            CapSense_SetModulationIDAC(i,( (IDAC_val[i]*135)/100));
            CapSense_SetFingerThreshold(i,((F_thersholds[i]*85)/100));
            CapSense_SetNoiseThreshold(i, (((F_thersholds[i]*85)/100) - (CapSense_GetFingerHysteresis(i)) - 1));
            CapSense_InitializeSensorBaseline(i);
            CyDelay(5u);
        }
        else if( (CapSense_sensorBaseline[i] < ((default_baseline[i]*8)/10)) && (CapSense_GetModulationIDAC(i) == ((IDAC_val[i]*135)/100) ) )
        {
            CapSense_SetModulationIDAC(i,IDAC_val[i]);
            CapSense_SetFingerThreshold(i,F_thersholds[i]);
            CapSense_SetNoiseThreshold(i, (F_thersholds[i] - (CapSense_GetFingerHysteresis(i)) - 1));
            CapSense_InitializeSensorBaseline(i);
            CyDelay(5u);
        }  
        #ifdef hawkeye
            //temp[i] = CapSense_GetModulationIDAC(i);
            //temp[i] = CapSense_GetFingerThreshold(i);
        #endif
    }
}

void multikey_check(void)
{
    #if 1
    unsigned char i, a, count_multi_key = 0;
    
    //multikey_flag = 0;
    
    if(CapSense_SensorOnMask[1] & 0x04)
    {
        count_multi_key++;
    }
    
    for(i = 0 ; i < 2 ; i++)
    {
        a = (0x01 << i);
        if( (CapSense_SensorOnMask[0] & a) )
        {
            count_multi_key++;
        }
    }
    
    if( count_multi_key >= 2 )
    {        
        multikey_flag = 1;
    }
    
    if( (CapSense_SensorOnMask[0] == 0x00) && (CapSense_SensorOnMask[1] == 0x00) )
    {
        multikey_flag = 0;
    }
    #endif
}

void Power_key_control(void)
{
    //if(PowerKeyCnt < 40)    //Power key가 100ms 미만으로 눌림
    if(PowerKeyCnt < 80)    //Power key가 200ms 미만으로 눌림
    {
        Pin_Power_Write(1);
            
        if( (CapSense_SensorOnMask[1] & 0x04) && (multikey_flag == 0))
            PowerKeyFlag = 1;
        else
            PowerKeyFlag = 0;
    }
    //else if(PowerKeyCnt < 80) //Power key가 100ms 이상으로 눌림, 100ms 동안 LOW 유지
    else if(PowerKeyCnt < 120) //Power key가 100ms 이상으로 눌림, 100ms 동안 LOW 유지
    {        
        Pin_Power_Write(0);
    }
    else //Power key 가 100ms 눌린 후 Pin_Power_Write(0) 출력 하며 100ms 이상이 지남
    {
        if(CapSense_SensorOnMask[1] & 0x04)
            Pin_Power_Write(0); 
        else
        {
            Pin_Power_Write(1);             
            PowerKeyFlag = 0;
        }
    }
}

void SensorEnable(void)
{
    uint8 i = 0;
    
    /* Scan only the Button 10 sensor */
    CapSense_ScanSensor(CapSense_BUTTON10__BTN);
    /* Wait for scanning to complete */
    while(CapSense_IsBusy() != 0);
    /* Update the baseline of only the Button 10 sensor*/
   	CapSense_UpdateSensorBaseline(CapSense_BUTTON10__BTN);
    /* Check if the Button 10 sensor is active */
    bButtonTouchOnOffStatus = CapSense_CheckIsWidgetActive(CapSense_BUTTON10__BTN);
    
    
    for(i = 0; i < 10; i++)
    {
        CapSense_ScanSensor(i);
        while(CapSense_IsBusy() != 0);
        CapSense_UpdateSensorBaseline(i);
        CapSense_CheckIsWidgetActive(i);
    }
}
#endif

void WDT_Clear(void)
{
    //CySysWdtResetCounters(CY_SYS_WDT_COUNTER1_RESET);
    /* Watchdog Clear */
    CySysWdtClearInterrupt();   
}

void Clear_WDT_With_Flag(void)
{    
    if(WDT_Clear_Flag == 1)
    {
        WDT_Clear();
        WDT_Clear_Flag = 0;
    }
}

void Set_WDT_Clear_Flag(uint8 value)
{
    WDT_Clear_Flag = value;
}

/***********************************************************************/
/* For void CapSense_CSD_InitializeAllBaselines_Filtered(uint8 Repeat) */
/***********************************************************************/
/* Baseline Calibration using Filter */
void CapSense_CSD_InitializeAllBaselines_Filtered(uint8 Repeat)
{
    uint32 i;
    uint8 j;
    
    for(j=0u;j<Repeat;j++)    /* Repeat N Times */
    {
        for(i = 0u; i < CapSense_TOTAL_SCANSLOT_COUNT; i++)
        {
            CapSense_CSD_InitializeSensorBaseline_Filtered(i);
 
        }
    }
}

/* IIR 필터 사용 하기 위하여 RawCount를 측정 */
void CapSense_CSD_InitializeSensorBaseline_Filtered(uint32 sensor)
{
    /* Scan sensor */
#if 1
    CapSense_ScanSensor(sensor);
    while(CapSense_IsBusy() != 0u)
    { 
        /* Wait while sensor is busy */
    }
#endif

    /* Initialize Baseline, Signal and debounce counters */
    CapSense_CSD_BaseInit_Filtered(sensor);
}

/* 필터를 거친 값을 Baseline에 저장 */
void CapSense_CSD_BaseInit_Filtered(uint32 sensor)
{    
    uint16 filteredRawData;        
    
    #if ((CapSense_CSD_TOTAL_BUTTONS_COUNT) || (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT) || \
         (CapSense_CSD_TOTAL_GENERICS_COUNT))
        uint8 widget = CapSense_CSD_widgetNumber[sensor];
    #endif /* ((CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT) || (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT)) */

    #if (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT)
        uint8 debounceIndex;
    #endif  /* (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT) */

    #if (CapSense_CSD_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        if(widget < CapSense_CSD_END_OF_WIDGETS_INDEX)
        {
    #endif  /* CapSense_CSD_TOTAL_GENERICS_COUNT */
    
    /* Filtered RawCount */
    filteredRawData = CapSense_sensorRaw[sensor];
    
    filteredRawData = CapSense_IIR4Filter(filteredRawData, CapSense_rawFilterData1[sensor]);
    CapSense_rawFilterData1[sensor] = filteredRawData;

    
    /* Initialize Baseline */    
    CapSense_sensorBaseline[sensor] = CapSense_rawFilterData1[sensor];
    CapSense_sensorBaselineLow[sensor] = 0u;
    CapSense_sensorSignal[sensor] = 0u;

    //CapSense_CSD_debounceCounter0[widget] =  OnDebounce[widget];
    //CapSense_CSD_debounceCounter1[widget] =  OffDebounce[widget];
    
}
        
void FirstSensingData(void)
{
    uint32 i;
    
    for(i = 0u; i < CapSense_TOTAL_SCANSLOT_COUNT; i++)
    {
        CapSense_ScanSensor(i);
        
        while(CapSense_IsBusy() != 0u)
        { 
            /* Wait while sensor is busy */
        }
        
        CapSense_rawFilterData1[i] = CapSense_sensorRaw[i];
    }
}

#ifdef Debug
/***********************************************************************/
/* For void CapSense_UpdateEnabledBaselines_Filter */
/***********************************************************************/
void CapSense_UpdateEnabledBaselines_Filter(void)
{
    uint32 i;
    uint32 isSensorEnabled;

    for(i = 0u; i < CapSense_TOTAL_SENSOR_COUNT; i++)
    {
        isSensorEnabled = CapSense_GetBitValue(CapSense_sensorEnableMask, i);

        if(0u != isSensorEnabled)
        {
            //CapSense_UpdateSensorBaseline(i);
            CapSense_UpdateSensorBaseline_Filter(i);
        }
    }
}

 void CapSense_UpdateSensorBaseline_Filter(uint32 sensor)
{
    #if (CapSense_TOTAL_GENERICS_COUNT)
        uint32 widget;

        widget = CapSense_widgetNumber[sensor];

        /* Exclude generic widget */
        if(widget < CapSense_END_OF_WIDGETS_INDEX)
        {
    #endif  /* CapSense_TOTAL_GENERICS_COUNT */

    #if (CapSense_TUNING_METHOD == CapSense__TUNING_AUTO)
        CapSense_UpdateThresholds(sensor);
    #endif /* (CapSense_TUNING_METHOD == CapSense__TUNING_AUTO) */

    //CapSense_UpdateBaselineNoThreshold(sensor);
    CapSense_UpdateBaselineNoThreshold_Filter(sensor);

    #if (CapSense_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* CapSense_TOTAL_GENERICS_COUNT */
}

void CapSense_UpdateBaselineNoThreshold_Filter(uint32 sensor)
{
    uint32 calc;
    uint32 sign;
    uint16 tempRaw;
    uint16 AveragetempRaw;
    uint16 filteredRawData;
    uint8 widget = CapSense_widgetNumber[sensor];
    uint16 noiseThreshold;

    #if (CapSense_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        if(widget < CapSense_END_OF_WIDGETS_INDEX)
        {
    #endif  /* CapSense_TOTAL_GENERICS_COUNT */

    noiseThreshold = CapSense_noiseThreshold[widget];
    filteredRawData = CapSense_sensorRaw[sensor];

    #if (CapSense_RAW_FILTER_MASK != 0u)
    //if(CapSense_enableRawFilters != 0u)
    {
        #if (CapSense_RAW_FILTER_MASK & CapSense_MEDIAN_FILTER)
            tempRaw = filteredRawData;
            filteredRawData = CapSense_MedianFilter(filteredRawData, CapSense_rawFilterData1[sensor],
                                                            CapSense_rawFilterData2[sensor]);
            CapSense_rawFilterData2[sensor] = CapSense_rawFilterData1[sensor];
            CapSense_rawFilterData1[sensor] = tempRaw;

        #elif (CapSense_RAW_FILTER_MASK & CapSense_AVERAGING_FILTER)
            tempRaw = filteredRawData;
            filteredRawData = CapSense_AveragingFilter(filteredRawData, CapSense_rawFilterData1[sensor],
                                                               CapSense_rawFilterData2[sensor]);
            CapSense_rawFilterData2[sensor] = CapSense_rawFilterData1[sensor];
            CapSense_rawFilterData1[sensor] = tempRaw;

        #elif (CapSense_RAW_FILTER_MASK & CapSense_IIR2_FILTER)
            filteredRawData = CapSense_IIR2Filter(filteredRawData, CapSense_rawFilterData1[sensor]);
            CapSense_rawFilterData1[sensor] = filteredRawData;

        #elif (CapSense_RAW_FILTER_MASK & CapSense_IIR4_FILTER)
            filteredRawData = CapSense_IIR4Filter(filteredRawData, CapSense_rawFilterData1[sensor]);
            CapSense_rawFilterData1[sensor] = filteredRawData;
            Capsense_FilteredRawData[sensor] = filteredRawData;
                    
            #if 0
            /* Add AverageFilter */
            AveragetempRaw = filteredRawData;
            filteredRawData = CapSense_USER_AverageFilter(filteredRawData, CapSense_Aver_rawFilterData1[sensor],CapSense_Aver_rawFilterData2[sensor]);
            CapSense_Aver_rawFilterData2[sensor] = CapSense_Aver_rawFilterData1[sensor];
            CapSense_Aver_rawFilterData1[sensor] = AveragetempRaw;
            /* Add AverageFilter */

            /* Add MedianFilter */
            tempRaw = filteredRawData;
            filteredRawData = CapSense_USER_MEDIANFilter(filteredRawData, CapSense_rawFilterData1[sensor], CapSense_rawFilterData2[sensor],
                                                     CapSense_rawFilterData3[sensor], CapSense_rawFilterData4[sensor]);
            
            //CapSense_rawFilterData6[sensor] = CapSense_rawFilterData5[sensor];
            //CapSense_rawFilterData5[sensor] = CapSense_rawFilterData4[sensor];
            CapSense_rawFilterData4[sensor] = CapSense_rawFilterData3[sensor];
            CapSense_rawFilterData3[sensor] = CapSense_rawFilterData2[sensor];
            CapSense_rawFilterData2[sensor] = CapSense_rawFilterData1[sensor];
            CapSense_rawFilterData1[sensor] = tempRaw;
            /* Add MedianFilter */     
            #endif
            
        #elif (CapSense_RAW_FILTER_MASK & CapSense_JITTER_FILTER)
            filteredRawData = CapSense_JitterFilter(filteredRawData, CapSense_rawFilterData1[sensor]);
            CapSense_rawFilterData1[sensor] = filteredRawData;

        #elif (CapSense_RAW_FILTER_MASK & CapSense_IIR8_FILTER)
            filteredRawData = CapSense_IIR8Filter(filteredRawData, CapSense_rawFilterData1[sensor]);
            CapSense_rawFilterData1[sensor] = filteredRawData;

        #elif (CapSense_RAW_FILTER_MASK & CapSense_IIR16_FILTER)
            filteredRawData = CapSense_IIR16Filter(filteredRawData, CapSense_rawFilterData1[sensor]);
            CapSense_rawFilterData1[sensor] = filteredRawData;

        #else
            /* No Raw filters */
        #endif  /* (CapSense_RAW_FILTER_MASK & CapSense_MEDIAN_FILTER) */
    }
    #endif  /* (CapSense_RAW_FILTER_MASK != 0u) */

    #if (CapSense_TUNING_METHOD == CapSense__TUNING_AUTO)
        MeasureNoiseEnvelope_P4_v2_60(&CapSense_config, (uint8)sensor, CapSense_sensorRaw);
    #endif /* (CapSense_TUNING_METHOD == CapSense__TUNING_AUTO) */

    /* Baseline calculation */
    /* Calculate difference RawData[cur] - Baseline[prev] */
    if(filteredRawData >= CapSense_sensorBaseline[sensor])
    {
        CapSense_lowBaselineResetCnt[sensor] = 0u;
        tempRaw = filteredRawData - CapSense_sensorBaseline[sensor];
        sign = 1u;    /* Positive difference - Calculate the Signal */
    }
    else
    {
        tempRaw = CapSense_sensorBaseline[sensor] - filteredRawData;
        sign = 0u;    /* Negative difference - Do NOT calculate the Signal */
    }

    #if (CapSense_TUNING_METHOD != CapSense__TUNING_NONE)
    if((sign == 0u) && (tempRaw > (uint16) CapSense_negativeNoiseThreshold[widget]))
    #else
    if((sign == 0u) && (tempRaw > (uint16) CapSense_NEGATIVE_NOISE_THRESHOLD))
    #endif /* (CapSense_TUNING_METHOD != CapSense__TUNING_NONE) */
    {
        if(CapSense_lowBaselineResetCnt[sensor] >= CapSense_lowBaselineReset[sensor])
        {
            CapSense_BaseInit(sensor);
            CapSense_lowBaselineResetCnt[sensor] = 0u;
        }
        else
        {
            CapSense_lowBaselineResetCnt[sensor]++;
        }
    }
    else
    {
        #if (CapSense_AUTO_RESET == CapSense_AUTO_RESET_DISABLE)
        #if (CapSense_TUNING_METHOD != CapSense__TUNING_NONE)
            /* Update Baseline if lower than noiseThreshold */
            if ( (tempRaw <= noiseThreshold) ||
             ((tempRaw < (uint16) CapSense_negativeNoiseThreshold[widget])
               && (sign == 0u)))
            {
        #else
            /* Update Baseline if lower than noiseThreshold */
            if ( (tempRaw <= noiseThreshold) ||
                 ((tempRaw < (uint16) CapSense_NEGATIVE_NOISE_THRESHOLD)
                   && (sign == 0u)))
            {
        #endif /* (CapSense_TUNING_METHOD != CapSense__TUNING_NONE) */
        #endif /* (CapSense_AUTO_RESET == CapSense_AUTO_RESET_DISABLE) */
                /* Make full Baseline 23 bits */
                calc = (uint32) CapSense_sensorBaseline[sensor] << 8u;
                calc |= (uint32) CapSense_sensorBaselineLow[sensor];

                /* Add Raw Data to Baseline */
                calc += filteredRawData;

                /* Sub the high Baseline */
                calc -= CapSense_sensorBaseline[sensor];

                /* Put Baseline and BaselineLow */
                CapSense_sensorBaseline[sensor] = ((uint16) (calc >> 8u));
                CapSense_sensorBaselineLow[sensor] = ((uint8) calc);

                CapSense_lowBaselineResetCnt[sensor] = 0u;
        #if (CapSense_AUTO_RESET == CapSense_AUTO_RESET_DISABLE)
            }
        #endif /* (CapSense_AUTO_RESET == CapSense_AUTO_RESET_DISABLE) */
    }

    /* Calculate Signal if positive difference > noiseThreshold */
    if((tempRaw > (uint16) noiseThreshold) && (sign != 0u))
    {
        #if (CapSense_SIGNAL_SIZE == CapSense_SIGNAL_SIZE_UINT8)
            /* Over flow defence for uint8 */
            if (tempRaw > 0xFFu)
            {
                CapSense_sensorSignal[sensor] = 0xFFu;
            }
            else
            {
                CapSense_sensorSignal[sensor] = ((uint8) tempRaw);
            }
        #else
            CapSense_sensorSignal[sensor] = ((uint16) tempRaw);
        #endif  /* (CapSense_SIGNAL_SIZE == CapSense_SIGNAL_SIZE_UINT8) */
    }
    else
    {
        /* Signal is zero */
        CapSense_sensorSignal[sensor] = 0u;
    }

    #if (CapSense_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* CapSense_TOTAL_GENERICS_COUNT */
}
#endif
/********************************************************************************************/
/* WDT Initialize */
/********************************************************************************************/
void WDT_Init(uint8 IgnoreBit, uint16 Match_ms)
{
    WDT_Ignore = IgnoreBit; /* for Reset mode */
    WDT_Match = Match_ms;  /* for Match mode */
    
    /* Configure WDT ISR */
    isr_WDT_Stop();
    
    /* Once watchdog counter reaches match value interrupt is generated  */
    CySysWdtWriteMatch(65535);    

    /* Configure WDT to be 16-bit wraparound up-counter - 1 MSb is ignored */
    /* 0 = 4.91, 1 = 2.45, 2 = 1.225, 3 = 0.612, 4 = 0.306, 5 = 0.153 */
    
    CySysWdtWriteIgnoreBits(IgnoreBit);    // ILO = 40khz -50%~100% accuracy, IgnoreBit = 0 : 65535 * (1 / 40000) * 3 = 4.91ms, range : 2.45 ~ 9.82ms

    /* Start the WDT */
    CySysWdtEnable();

    /* Make sure that interrupt is forwarded to the CPU */
    CySysWdtUnmaskInterrupt();   
}

/********************************************************************************************/
/* WDT Match Interrupt initialize */
/********************************************************************************************/

void WDT_Match_Init(uint8 IgnoreBit, uint16 Match_ms)
{
    WDT_Ignore = IgnoreBit;
    WDT_Match = Match_ms;
    
    /* Configure WDT ISR */
    isr_WDT_StartEx(WDT_ISR);
    
    /* Once watchdog counter reaches match value interrupt is generated  */
    //50 = 1.04ms interval
    CySysWdtWriteMatch(CySysWdtReadMatch() + WDT_Match*wdt_ms);
    
    /* Configure WDT to be 16-bit wraparound up-counter - 1 MSb is ignored */
    /* 0 = 4.91, 1 = 2.45, 2 = 1.225, 3 = 0.612, 4 = 0.306, 5 = 0.153 */
    
    CySysWdtWriteIgnoreBits(IgnoreBit);    /* 1.63*3 = 4.91ms, 2.45 ~ 9.82ms */

    /* Start the WDT */
    CySysWdtEnable();

    /* Make sure that interrupt is forwarded to the CPU */
    CySysWdtUnmaskInterrupt();  
}
/********************************************************************************************/
/* Force WDT Reset */
/********************************************************************************************/
void Force_WDT_Reset(void)
{
    WDT_Init(5, WDT_INTERRUPT_TIME);   /* Initialize WDT Interval */
    
    while(1)
    {
    }
}


/******************************************************************************
* Function Name: WDT_ISR_Handler
*******************************************************************************
*
* Summary:
* Interrupt Service Routine for the watchdog timer interrupt. The periodicity 
* of the interrupt is depended on the match value written into the counter 
* register using API - CySysWdtWriteMatch().
*
******************************************************************************/
CY_ISR(WDT_ISR)
{
	/* Clear WDT interrupt */ 
    CySysWdtClearInterrupt();
    isr_WDT_ClearPending();
    /* WDT match value is updated in order to obtain periodic interrupts. */
    CySysWdtWriteMatch(CySysWdtReadMatch() + WDT_Match*wdt_ms); // ILO = 40Khz, 1000 means 25ms, but there is -50~100% tollerance so range is 20Khz ~ 80Khz, 12.5ms ~ 50ms          
}

/* [] END OF FILE */

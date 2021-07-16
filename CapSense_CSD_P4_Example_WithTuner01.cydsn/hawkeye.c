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

/*----------------------------------------------------------------------------
                                include files
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                include files
----------------------------------------------------------------------------*/
//#include <device.h>
//#include <header.h>
#include <project.h>

/*----------------------------------------------------------------------------
                                macro
----------------------------------------------------------------------------*/
/**
  * Utility macro for expanding port registers.
  */
#define JOIN( x, y ) x ## y
#define JOIN1( A, B, C ) A ## B ## C

/**
  * Macro to build register writes for controlling ports. The intermediate
  * JOIN macro is required for correct expansion of the args.
  */
#define REG( REGISTER, SIDE ) JOIN( REGISTER, SIDE )


/*----------------------------------------------------------------------------
                                prototypes
----------------------------------------------------------------------------*/
void report_debug_data( void );
void init_debug_if( void );

static void output_to_debugger( uint8_t *p, uint8_t count );
static void send_debug_byte( uint8_t data );

//extern uint16 avg_signal[QT_NUM_CHANNELS];

//extern char noise_counter[63];
extern uint16 CapSense_SensorSignal[CapSense_TOTAL_SENSOR_COUNT];
extern uint16 CapSense_sensorRaw[CapSense_TOTAL_SENSOR_COUNT];
extern uint16 CapSense_sensorBaseline[CapSense_TOTAL_SENSOR_COUNT];
extern uint8 CapSense_sensorOnMask[(((CapSense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];

/*----------------------------------------------------------------------------
                            manifest constants
----------------------------------------------------------------------------*/


/*============================================================================
Name    :   init_debug_if
------------------------------------------------------------------------------
Purpose :   report debug data to host
Input   :   n/a
Output  :   n/a
Notes   :   n/a
============================================================================*/
/*
void init_debug_if( void )
{
    // init port pins
    REG( DDR, DBG_DATA_PORT ) |= (1u << DBG_DATA_BIT );
    REG( DDR, DBG_CLK_PORT ) |= (1u << DBG_CLK_BIT );
}
*/
/*============================================================================
Name    :   send_debug_byte
------------------------------------------------------------------------------
Purpose :   transmit a byte over the debug interface
Input   :   data = byte to be transmitted
Output  :   n/a
Notes   :
============================================================================*/
static void send_debug_byte( uint8_t data )
{
    // hawkeye_data_Write(1);
    // hawkeye_clk_Write(0);
    
    uint8 i;

    for( i = 0u; i < 8u; i++ )
    {
        /*  set data    */
        if( data & 0x80u )
        {
            hawkeye_data_Write(1);
        }
        else
        {
            hawkeye_data_Write(0);
        }

        /*  data set up time before clock pulse */
        CyDelayCycles(1);

        /*  shift next bit up, ready for output */
        data = (uint8_t)( data << 1u );

        /*  clock pulse */
        hawkeye_clk_Write(1);

        CyDelayCycles(1);

        hawkeye_clk_Write(0);

        /*  delay before next bit   */
        CyDelayCycles(1);
    }

    /*  hold data low between bytes */
        hawkeye_data_Write(0);

    /*  inter-byte delay    */
        CyDelayCycles(2);
}

/*============================================================================
Name    :   output_to_debugger
------------------------------------------------------------------------------
Purpose :   transmit multiple bytes over the debug interface
Input   :   p = ptr to bytes to transmit
            count = number of bytes to transmit
Output  :   n/a
Notes   :
============================================================================*/
static void output_to_debugger( uint8_t *p, uint8_t count )
{
    uint8_t i;
    uint8_t data;

    for( i = 0u; i < count; i++ )
    {
        /*  get next byte to transmit   */
        data = *p;

        /*  transmit a byte over the debug interface    */
        send_debug_byte( data );

        /*  point to next byte to transmit  */
        p++;
    }
}

/*============================================================================
Name    :   report_debug_data
------------------------------------------------------------------------------
Purpose :   report debug data to host
Input   :   n/a
Output  :   n/a
Notes   :   n/a
============================================================================*/
static uint8_t frame_count;
unsigned int temp[25];

extern uint16 Capsense_FilteredRawData[CapSense_TOTAL_SENSOR_COUNT];
extern uint16 Sub_Buff[CapSense_TOTAL_SENSOR_COUNT];

void report_debug_data( void )
{


    output_to_debugger( (uint8_t *) &frame_count, (uint8_t) sizeof( frame_count ) );
    //output_to_debugger( (uint8_t *) &CapSense_sensorRaw[0], (uint8_t) sizeof( CapSense_sensorRaw ) ); 
    output_to_debugger( (uint8_t *) &Capsense_FilteredRawData[0], (uint8_t) sizeof( Capsense_FilteredRawData ) ); 
    output_to_debugger( (uint8_t *) &CapSense_sensorBaseline[0], (uint8_t) sizeof( CapSense_sensorBaseline ) );       
    //output_to_debugger( (uint8_t *) &CapSense_SensorSignal[0], (uint8_t) sizeof( CapSense_SensorSignal ) );  
    output_to_debugger( (uint8_t *) &Sub_Buff[0], (uint8_t) sizeof( Sub_Buff ) );  
    output_to_debugger( (uint8_t *) &CapSense_sensorOnMask[0], (uint8_t) sizeof(CapSense_sensorOnMask ) );  
    /*
    unsigned char i = 0;
    for(i = 0; i < 25; i++)
    {
        output_to_debugger( (uint8_t *) &temp[i], (uint8_t) sizeof(temp ) );  
    }
    */
    
    output_to_debugger( (uint8_t *) &temp[0], (uint8_t) sizeof(temp ) ); 
    //output_to_debugger( (uint8_t *) &temp[1], (uint8_t) sizeof(temp ) );  
    //output_to_debugger( (uint8_t *) &temp[2], (uint8_t) sizeof(temp ) ); 
    //output_to_debugger( (uint8_t *) &temp[3], (uint8_t) sizeof(temp ) );   
    //output_to_debugger( (uint8_t *) &temp[4], (uint8_t) sizeof(temp ) ); 
    //output_to_debugger( (uint8_t *) &temp[5], (uint8_t) sizeof(temp ) );  
    //output_to_debugger( (uint8_t *) &temp[6], (uint8_t) sizeof(temp ) ); 
    //output_to_debugger( (uint8_t *) &temp[7], (uint8_t) sizeof(temp ) );  
    
    /*
    output_to_debugger( (uint8_t *) &qt_measure_data.channel_references[0], (uint8_t) sizeof( qt_measure_data.channel_references ) );
    
    for( i = 0u; i < QT_NUM_CHANNELS; i++ )
    {
        sensor_delta = qt_measure_data.channel_references[i] - qt_measure_data.channel_signals[i];
        output_to_debugger( (uint8_t *) &sensor_delta, sizeof( int16_t ) );
    }
    
    output_to_debugger( (uint8_t *) &qt_measure_data.qt_touch_status, (uint8_t) sizeof( qt_measure_data.qt_touch_status.sensor_states ) );
    
    
    for( i = 0u; i < QT_MAX_NUM_ROTORS_SLIDERS; i++ )
    {
        output_to_debugger( (uint8_t *) &qt_measure_data.qt_touch_status.rotor_slider_values[i], sizeof( uint8_t ) );
        output_to_debugger( (uint8_t *) &zero, sizeof( uint8_t ) );
    }
   
    
    k = 100;

    output_to_debugger( (uint8_t *) &k, (uint8_t) sizeof(k ) );        
	 */
    
    frame_count++;
}
/* [] END OF FILE */


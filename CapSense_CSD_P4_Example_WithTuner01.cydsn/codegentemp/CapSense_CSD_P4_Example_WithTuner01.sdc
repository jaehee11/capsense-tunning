# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Public\touch\(NowC302)A1_Global_Multi_Creator4.1_hawkeye\CapSense_CSD_P4_Example_WithTuner01.cydsn\CapSense_CSD_P4_Example_WithTuner01.cyprj
# Date: Fri, 16 Jul 2021 05:20:38 GMT
#set_units -time ns
create_clock -name {CapSense_SampleClk(FFB)} -period 21250 -waveform {0 10625} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CapSense_SenseClk(FFB)} -period 21250 -waveform {0 10625} [list [get_pins {ClockBlock/ff_div_1}]]
create_clock -name {Clock_1(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {CyILO} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {CapSense_SampleClk} -source [get_pins {ClockBlock/hfclk}] -edges {1 255 511} [list]
create_generated_clock -name {CapSense_SenseClk} -source [get_pins {ClockBlock/hfclk}] -edges {1 255 511} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 2 3} [list]


# Component constraints for C:\Users\Public\touch\(NowC302)A1_Global_Multi_Creator4.1_hawkeye\CapSense_CSD_P4_Example_WithTuner01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Public\touch\(NowC302)A1_Global_Multi_Creator4.1_hawkeye\CapSense_CSD_P4_Example_WithTuner01.cydsn\CapSense_CSD_P4_Example_WithTuner01.cyprj
# Date: Fri, 16 Jul 2021 05:20:37 GMT
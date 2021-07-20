-- ======================================================================
-- CapSense_CSD_P4_Example_WithTuner01.ctl generated from CapSense_CSD_P4_Example_WithTuner01
-- 07/16/2021 at 14:20
-- This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
-- ======================================================================

-- TopDesign
-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-040 kit.
-- =============================================================================

-- === RGB LED ===
attribute port_location of LED_1(0) : label is "PORT(1,1)"; -- GREEN LED

-- === Slider ===
attribute port_location of \CapSense_CSD:Cmod(0)\ : label is "PORT(0,4)";
attribute port_location of \CapSense_CSD:Sns(0)\ : label is "PORT(1,4)";
attribute port_location of \CapSense_CSD:Sns(1)\ : label is "PORT(1,5)";
attribute port_location of \CapSense_CSD:Sns(2)\ : label is "PORT(1,6)";
attribute port_location of \CapSense_CSD:Sns(3)\ : label is "PORT(1,0)";
attribute port_location of \CapSense_CSD:Sns(4)\ : label is "PORT(1,7)";

-- === SCB ===
attribute port_location of \SCB:scl(0)\ : label is "PORT(1,2)";
attribute port_location of \SCB:sda(0)\ : label is "PORT(1,3)";
-- PSoC Clock Editor
-- Directives Editor
-- Analog Device Editor

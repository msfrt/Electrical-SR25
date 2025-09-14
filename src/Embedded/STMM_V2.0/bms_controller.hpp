#ifndef BMS_CONTROL_HPP
#define BMS_CONTROL_HPP

#include <EasyTimer.h>
// #include "temp/bms_hardware.h"
// #include "index.h"
// #include "LT_SPI.h"
#include "LTC681x.h"
#include "LTC6811.h"
// #include "LTC6811_daisy.h"
// #include <SPI.h>
#include "CAN/raptor_CAN2.hpp"
// #include "can_send.hpp"

#define ENABLED 1
#define DISABLED 0

// change when running a daisy chain config
#define TOTAL_IC 1

// ADC Command Configurations
const uint8_t ADC_OPT = ADC_OPT_DISABLED;          
const uint8_t ADC_CONVERSION_MODE = MD_7KHZ_3KHZ;  // MD_7KHZ_3KHZ; //MD_26HZ_2KHZ;//MD_7KHZ_3KHZ;
const uint8_t ADC_DCP = DCP_ENABLED;              // 0: disable s while measuring, 1: enable s while measuring
const uint8_t CELL_CH_TO_CONVERT = CELL_CH_ALL;
const uint8_t AUX_CH_TO_CONVERT = AUX_CH_ALL;
const uint8_t STAT_CH_TO_CONVERT = STAT_CH_ALL;

// const uint16_t MEASUREMENT_LOOP_TIME = 5 * 6000;  // milliseconds(mS)
// const uint16_t BALANCE_LOOP_TIME = 60000;         // milliseconds(mS)

// Loop Measurement Setup These Variables are ENABLED or DISABLED Remember ALL CAPS
// const uint8_t WRITE_CONFIG = DISABLED;  // This is ENABLED or DISABLED
// const uint8_t READ_CONFIG = DISABLED;   // This is ENABLED or DISABLED
// const uint8_t MEASURE_CELL = ENABLED;   // This is ENABLED or DISABLED
// const uint8_t MEASURE_AUX = DISABLED;   // This is ENABLED or DISABLED
// const uint8_t MEASURE_STAT = DISABLED;  // This is ENABLED or DISABLED
// const uint8_t PRINT_PEC = DISABLED;     // This is ENABLED or DISABLED

// global variables for each temperature signal -- populates mod_temps vector
float module_temp_voltage_0;
float module_temp_voltage_1;
float module_temp_voltage_2;
float module_temp_voltage_3;
float module_temp_voltage_4;
float module_temp_voltage_5;
float module_temp_voltage_6;
float module_temp_voltage_7;
float module_temp_voltage_8;
float module_temp_voltage_9;

float module_voltage_0;
float module_voltage_1;
float module_voltage_2;
float module_voltage_3;
float module_voltage_4;
float module_voltage_5;
float module_voltage_6;
float module_voltage_7;
float module_voltage_8;
float module_voltage_9;

// const int STMM = 2;

// state variable
static bool step = 0;

void discharge_cycle_a(cell_asic *bms_ic){
  wakeup_sleep(TOTAL_IC);
  LTC6811_set_discharge(1, TOTAL_IC, bms_ic); // module 1
  LTC6811_set_discharge(3, TOTAL_IC, bms_ic); // module 3
  LTC6811_set_discharge(5, TOTAL_IC, bms_ic); // module 5
  LTC6811_set_discharge(8, TOTAL_IC, bms_ic); // module 7
  LTC6811_set_discharge(10, TOTAL_IC, bms_ic); // module 9
  LTC6811_wrcfg(TOTAL_IC, bms_ic);
}

void discharge_cycle_b(cell_asic *bms_ic){
  wakeup_sleep(TOTAL_IC);
  LTC6811_set_discharge(2, TOTAL_IC, bms_ic); // module 2
  LTC6811_set_discharge(4, TOTAL_IC, bms_ic); // module 4
  LTC6811_set_discharge(7, TOTAL_IC, bms_ic); // module 6
  LTC6811_set_discharge(9, TOTAL_IC, bms_ic); // module 8
  LTC6811_set_discharge(11, TOTAL_IC, bms_ic); // module 10
  LTC6811_wrcfg(TOTAL_IC, bms_ic);
}

void measure_voltage(cell_asic *bms_ic){
  wakeup_sleep(TOTAL_IC);
  LTC6811_adcv(ADC_CONVERSION_MODE, ADC_DCP, CELL_CH_TO_CONVERT);
  LTC6811_pollAdc();
  wakeup_idle(TOTAL_IC);
  LTC6811_rdcv(0, TOTAL_IC, bms_ic); // returns -1 if PEC error
}

void measurement_loop(cell_asic *bms_ic, const int &STMM){
  
  // read the registers -- happens every second
  // updates the cell_temp values on its own timer, every ~1sec since we don't need fast aquisition for temp
  static EasyTimer temp_acquisition(1);
  if (temp_acquisition.isup()) {
    // int8_t error = 0; // error variable
    
    // reset the things
    clear_discharge(TOTAL_IC, bms_ic);
    wakeup_sleep(TOTAL_IC);
    LTC6811_wrcfg(TOTAL_IC, bms_ic);
    // Serial.println("All things disabled");

    // Serial.println("Module 1: ");
    // Serial.println(bms_ic[0].cells.c_codes[0]*0.0001);
    // Serial.println("Module 2: ");
    // Serial.println(bms_ic[0].cells.c_codes[1]*0.0001);
    // Serial.println("Module 3: ");
    // Serial.println(bms_ic[0].cells.c_codes[2]*0.0001);
    // Serial.println("Module 4: ");
    // Serial.println(bms_ic[0].cells.c_codes[3]*0.0001);
    // Serial.println("Module 5: ");
    // Serial.println(bms_ic[0].cells.c_codes[4]*0.0001);
    // // Serial.println("Cell 5: ");
    // // Serial.println(bms_ic[0].cells.c_codes[5]*0.0001);
    // Serial.println("Module 6: ");
    // Serial.println(bms_ic[0].cells.c_codes[6]*0.0001);
    // Serial.println("Module 7: ");
    // Serial.println(bms_ic[0].cells.c_codes[7]*0.0001);
    // Serial.println("Module 8: ");
    // Serial.println(bms_ic[0].cells.c_codes[8]*0.0001);
    // Serial.println("Module 9: ");
    // Serial.println(bms_ic[0].cells.c_codes[9]*0.0001);
    // Serial.println("Module 10: ");
    // Serial.println(bms_ic[0].cells.c_codes[10]*0.0001);
    // // Serial.println("Cell 11: ");
    // // Serial.println(bms_ic[0].cells.c_codes[11]*0.0001);
    // Serial.println(error);
    if (STMM == 1){

      switch(step){
        case 0:

          measure_voltage(bms_ic);
          // Serial.println("Module 1 VOLTAGE: ");
          // Serial.println(bms_ic[0].cells.c_codes[0]*0.0001);

          module_voltage_0 = bms_ic[0].cells.c_codes[0]*0.0001; // module 1
          module_voltage_2 = bms_ic[0].cells.c_codes[2]*0.0001; // module 3
          module_voltage_4 = bms_ic[0].cells.c_codes[4]*0.0001; // module 5
          module_voltage_6 = bms_ic[0].cells.c_codes[7]*0.0001; // module 7
          module_voltage_8 = bms_ic[0].cells.c_codes[9]*0.0001; // module 9

          discharge_cycle_a(bms_ic);
          delay_m(10); // capacitor discharge delay
          measure_voltage(bms_ic); // measures all cell channels

          module_temp_voltage_0 = bms_ic[0].cells.c_codes[0]*0.0001; // module 1
          module_temp_voltage_2 = bms_ic[0].cells.c_codes[2]*0.0001; // module 3
          module_temp_voltage_4 = bms_ic[0].cells.c_codes[4]*0.0001; // module 5
          module_temp_voltage_6 = bms_ic[0].cells.c_codes[7]*0.0001; // module 7
          module_temp_voltage_8 = bms_ic[0].cells.c_codes[9]*0.0001; // module 9
          
          // Serial.println("Module 1 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[0]*0.0001);

          // Serial.println("Module 3 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[2]*0.0001);

          // Serial.println("Module 5 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[4]*0.0001);

          // Serial.println("Module 7 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[7]*0.0001);

          // Serial.println("Module 9 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[9]*0.0001);

          step = 1; // change state
          break;
        
        case 1:

          measure_voltage(bms_ic);
          // Serial.println("Module 2 VOLTAGE: ");
          // Serial.println(bms_ic[0].cells.c_codes[1]*0.0001);

          module_voltage_1 = bms_ic[0].cells.c_codes[1]*0.0001; // module 2
          module_voltage_3 = bms_ic[0].cells.c_codes[3]*0.0001; // module 4
          module_voltage_5 = bms_ic[0].cells.c_codes[6]*0.0001; // module 6
          module_voltage_7 = bms_ic[0].cells.c_codes[8]*0.0001; // module 8
          module_voltage_9 = bms_ic[0].cells.c_codes[10]*0.0001; // module 10

          discharge_cycle_b(bms_ic);
          delay_m(10); // capacitor discharge delay
          measure_voltage(bms_ic); // measures all cell channels
          
          module_temp_voltage_1 = bms_ic[0].cells.c_codes[1]*0.0001; // module 2
          module_temp_voltage_3 = bms_ic[0].cells.c_codes[3]*0.0001; // module 4
          module_temp_voltage_5 = bms_ic[0].cells.c_codes[6]*0.0001; // module 6
          module_temp_voltage_7 = bms_ic[0].cells.c_codes[8]*0.0001; // module 8
          module_temp_voltage_9 = bms_ic[0].cells.c_codes[10]*0.0001; // module 10

          // Serial.println("Module 2 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[1]*0.0001);

          // Serial.println("Module 4 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[3]*0.0001);

          // Serial.println("Module 6 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[6]*0.0001);

          // Serial.println("Module 8 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[8]*0.0001);

          // Serial.println("Module 10 TEMP: ");
          // Serial.println(bms_ic[0].cells.c_codes[10]*0.0001);

          step = 0; // change state
          break;
      
      }
    } else  {
    
      if (STMM_segmentSync.value() == 0x00 && STMM_segmentSync.timeout_check()){
        
        measure_voltage(bms_ic);
        
        // Serial.println("Module 1p2 VOLTAGE: ");
        // Serial.println(bms_ic[0].cells.c_codes[0]*0.0001);

        module_voltage_0 = bms_ic[0].cells.c_codes[0]*0.0001; // module 1
        module_voltage_2 = bms_ic[0].cells.c_codes[2]*0.0001; // module 3
        module_voltage_4 = bms_ic[0].cells.c_codes[4]*0.0001; // module 5
        module_voltage_6 = bms_ic[0].cells.c_codes[7]*0.0001; // module 7
        module_voltage_8 = bms_ic[0].cells.c_codes[9]*0.0001; // module 9

        discharge_cycle_a(bms_ic);
        delay_m(10); // capacitor discharge delay
        measure_voltage(bms_ic); // measures all cell channels

        module_temp_voltage_0 = bms_ic[0].cells.c_codes[0]*0.0001; // module 1
        module_temp_voltage_2 = bms_ic[0].cells.c_codes[2]*0.0001; // module 3
        module_temp_voltage_4 = bms_ic[0].cells.c_codes[4]*0.0001; // module 5
        module_temp_voltage_6 = bms_ic[0].cells.c_codes[7]*0.0001; // module 7
        module_temp_voltage_8 = bms_ic[0].cells.c_codes[9]*0.0001; // module 9

        // Serial.println("Case 0 tang");
      
      } else if (STMM_segmentSync.value() == 0x01 && STMM_segmentSync.timeout_check()){

        measure_voltage(bms_ic);
        // Serial.println("Module 2 VOLTAGE: ");
        // Serial.println(bms_ic[0].cells.c_codes[1]*0.0001);

        // Serial.println("Module 1p2 VOLTAGE again: ");
        // Serial.println(bms_ic[0].cells.c_codes[0]*0.0001);

        module_voltage_1 = bms_ic[0].cells.c_codes[1]*0.0001; // module 2
        module_voltage_3 = bms_ic[0].cells.c_codes[3]*0.0001; // module 4
        module_voltage_5 = bms_ic[0].cells.c_codes[6]*0.0001; // module 6
        module_voltage_7 = bms_ic[0].cells.c_codes[8]*0.0001; // module 8
        module_voltage_9 = bms_ic[0].cells.c_codes[10]*0.0001; // module 10

        discharge_cycle_b(bms_ic);
        delay_m(10); // capacitor discharge delay
        measure_voltage(bms_ic); // measures all cell channels
        
        module_temp_voltage_1 = bms_ic[0].cells.c_codes[1]*0.0001; // module 2
        module_temp_voltage_3 = bms_ic[0].cells.c_codes[3]*0.0001; // module 4
        module_temp_voltage_5 = bms_ic[0].cells.c_codes[6]*0.0001; // module 6
        module_temp_voltage_7 = bms_ic[0].cells.c_codes[8]*0.0001; // module 8
        module_temp_voltage_9 = bms_ic[0].cells.c_codes[10]*0.0001; // module 10

        // Serial.println("Case 1 tang");

      } 
    }
  }
}

#endif

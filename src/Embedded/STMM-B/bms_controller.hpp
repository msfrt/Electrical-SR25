#ifndef BMS_CONTROL_HPP
#define BMS_CONTROL_HPP

// #include <EasyTimer.h>
// #include "LT_SPI.h"
#include "LTC681x.h"
#include "LTC6811.h"
// #include "LTC6811_daisy.h"
// #include <SPI.h>
// #include "CAN/raptor_CAN2.hpp"
// #include "can_send.hpp"
#include "cyclic_id.hpp"

#define ENABLED 1
#define DISABLED 0

// change when running a daisy chain config
#define TOTAL_IC 1

// the amount of modules in each segment
#define CELLS_PER_SEG 10

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

float module_balancing_voltage_0;
float module_balancing_voltage_1;
float module_balancing_voltage_2;
float module_balancing_voltage_3;
float module_balancing_voltage_4;
float module_balancing_voltage_5;
float module_balancing_voltage_6;
float module_balancing_voltage_7;
float module_balancing_voltage_8;
float module_balancing_voltage_9;

// send out heartbeat to the STMMs
static bool step = 0; // make sure no 2 adjacent cells are being balanced 

/*
Scale everything up to all the modules in the pack pls
*/

void discharge_cycle_a(cell_asic *bms_ic){
  wakeup_sleep(TOTAL_IC);
  LTC6811_set_discharge(1, TOTAL_IC, bms_ic); // module 1
  LTC6811_set_discharge(3, TOTAL_IC, bms_ic); // module 3
  LTC6811_set_discharge(5, TOTAL_IC, bms_ic); // module 5
  LTC6811_set_discharge(7, TOTAL_IC, bms_ic); // module 7
  LTC6811_set_discharge(9, TOTAL_IC, bms_ic); // module 9
  LTC6811_wrcfg(TOTAL_IC, bms_ic);
}

void discharge_cycle_b(cell_asic *bms_ic){
  wakeup_sleep(TOTAL_IC);
  LTC6811_set_discharge(2, TOTAL_IC, bms_ic); // module 2
  LTC6811_set_discharge(4, TOTAL_IC, bms_ic); // module 4
  LTC6811_set_discharge(6, TOTAL_IC, bms_ic); // module 6
  LTC6811_set_discharge(8, TOTAL_IC, bms_ic); // module 8
  LTC6811_set_discharge(10, TOTAL_IC, bms_ic); // module 10
  LTC6811_wrcfg(TOTAL_IC, bms_ic);
}

void measure_voltage(cell_asic *bms_ic){
  wakeup_sleep(TOTAL_IC);
  LTC6811_adcv(ADC_CONVERSION_MODE, ADC_DCP, CELL_CH_TO_CONVERT);
  LTC6811_pollAdc();
  wakeup_idle(TOTAL_IC);
  LTC6811_rdcv(0, TOTAL_IC, bms_ic); // returns -1 if PEC error
}

// updates cell voltages in data structure
void update_mod_volts(cell_asic *bms_ic){
  // updates cell voltages in data structure
  for (int seg; seg < TOTAL_IC; seg++){
    for (int cell; cell < CELLS_PER_SEG - 1; cell++)
      get_mod_volts(seg).at(cell).second = bms_ic[seg].cells.c_codes[cell]*0.0001;
  }
}

// checks voltage limits
void check_voltage(cell_asic *bms_ic){

}

// checks current limits
// void check_current{}{

// }

// // perform a safety check to ensure voltages are within limits and such
// void safety_check(){


// }

// make 2 states - charging/balancing, and normal runtime
void measurement_loop(cell_asic *bms_ic){
  
  // updates the cell_temp values on its own timer, every ~1sec since we don't need fast aquisition for temp
  
  // int8_t error = 0; // error variable
  
  // reset the things
  LTC681x_clear_discharge(TOTAL_IC, bms_ic); // resets balancing switches
  wakeup_sleep(TOTAL_IC);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);
  // Serial.println("All things disabled");

  measure_voltage(bms_ic);
  // Serial.println("Module 1 VOLTAGE: ");
  // Serial.println(bms_ic[0].cells.c_codes[0]*0.0001);
  
  update_mod_volts(bms_ic);
  
  // module_voltage_0 = bms_ic[0].cells.c_codes[0]*0.0001; // module 1
  // module_voltage_2 = bms_ic[0].cells.c_codes[2]*0.0001; // module 3
  // module_voltage_4 = bms_ic[0].cells.c_codes[4]*0.0001; // module 5
  // module_voltage_6 = bms_ic[0].cells.c_codes[6]*0.0001; // module 7
  // module_voltage_8 = bms_ic[0].cells.c_codes[8]*0.0001; // module 9
  
  // module_voltage_1 = bms_ic[0].cells.c_codes[1]*0.0001; // module 2
  // module_voltage_3 = bms_ic[0].cells.c_codes[3]*0.0001; // module 4
  // module_voltage_5 = bms_ic[0].cells.c_codes[5]*0.0001; // module 6
  // module_voltage_7 = bms_ic[0].cells.c_codes[7]*0.0001; // module 8
  // module_voltage_9 = bms_ic[0].cells.c_codes[9]*0.0001; // module 10
  
}

void balancing_loop(cell_asic *bms_ic){

  LTC681x_clear_discharge(TOTAL_IC, bms_ic); // resets balancing switches
  wakeup_sleep(TOTAL_IC);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);

  switch(step){
    case 0:

      measure_voltage(bms_ic);
      // Serial.println("Module 1 VOLTAGE: ");
      // Serial.println(bms_ic[0].cells.c_codes[0]*0.0001);

      module_voltage_0 = bms_ic[0].cells.c_codes[0]*0.0001; // module 1
      module_voltage_2 = bms_ic[0].cells.c_codes[2]*0.0001; // module 3
      module_voltage_4 = bms_ic[0].cells.c_codes[4]*0.0001; // module 5
      module_voltage_6 = bms_ic[0].cells.c_codes[6]*0.0001; // module 7
      module_voltage_8 = bms_ic[0].cells.c_codes[8]*0.0001; // module 9

      discharge_cycle_a(bms_ic);
      delay_m(10); // capacitor discharge delay
      
      measure_voltage(bms_ic); // measures all cell channels

      module_balancing_voltage_0 = bms_ic[0].cells.c_codes[0]*0.0001; // module 1
      module_balancing_voltage_2 = bms_ic[0].cells.c_codes[2]*0.0001; // module 3
      module_balancing_voltage_4 = bms_ic[0].cells.c_codes[4]*0.0001; // module 5
      module_balancing_voltage_6 = bms_ic[0].cells.c_codes[6]*0.0001; // module 7
      module_balancing_voltage_8 = bms_ic[0].cells.c_codes[8]*0.0001; // module 9
      
      step = 1;
      break;
    
    case 1:
      
      measure_voltage(bms_ic);
      // Serial.println("Module 2 VOLTAGE: ");
      // Serial.println(bms_ic[0].cells.c_codes[1]*0.0001);

      module_voltage_1 = bms_ic[0].cells.c_codes[1]*0.0001; // module 2
      module_voltage_3 = bms_ic[0].cells.c_codes[3]*0.0001; // module 4
      module_voltage_5 = bms_ic[0].cells.c_codes[5]*0.0001; // module 6
      module_voltage_7 = bms_ic[0].cells.c_codes[7]*0.0001; // module 8
      module_voltage_9 = bms_ic[0].cells.c_codes[9]*0.0001; // module 10

      discharge_cycle_b(bms_ic);
      delay_m(10); // capacitor discharge delay
      measure_voltage(bms_ic); // measures all cell channels
      
      module_balancing_voltage_1 = bms_ic[0].cells.c_codes[1]*0.0001; // module 2
      module_balancing_voltage_3 = bms_ic[0].cells.c_codes[3]*0.0001; // module 4
      module_balancing_voltage_5 = bms_ic[0].cells.c_codes[5]*0.0001; // module 6
      module_balancing_voltage_7 = bms_ic[0].cells.c_codes[7]*0.0001; // module 8
      module_balancing_voltage_9 = bms_ic[0].cells.c_codes[9]*0.0001; // module 10
      
      step = 0;
      break;
  }

}

#endif

#ifndef BMS_CONTROL_HPP
#define BMS_CONTROL_HPP

#include <EasyTimer.h>
#include "bms_hardware.h"
#include "index.h"
#include "LT_SPI.h"
#include "LTC681x.h"
#include "LTC6811.h"

#define ENABLED 1
#define DISABLED 0

#define DATALOG_ENABLED 1
#define DATALOG_DISABLED 0

// ADC Command Configurations
const uint8_t ADC_OPT = ADC_OPT_DISABLED;          // See LTC6811_daisy.h for Options
const uint8_t ADC_CONVERSION_MODE = MD_7KHZ_3KHZ;  // MD_7KHZ_3KHZ; //MD_26HZ_2KHZ;//MD_7KHZ_3KHZ; // See LTC6811_daisy.h for Options
const uint8_t ADC_DCP = DCP_DISABLED;              // See LTC6811_daisy.h for Options ---- enable if this is what allows dc during measurement
const uint8_t CELL_CH_TO_CONVERT = CELL_CH_ALL;    // See LTC6811_daisy.h for Options
// const uint8_t AUX_CH_TO_CONVERT = AUX_CH_ALL;      // See LTC6811_daisy.h for Options
// const uint8_t STAT_CH_TO_CONVERT = STAT_CH_ALL;    // See LTC6811_daisy.h for Options

// const uint16_t MEASUREMENT_LOOP_TIME = 5 * 6000;  // milliseconds(mS)
// const uint16_t BALANCE_LOOP_TIME = 60000;         // milliseconds(mS)

// Loop Measurement Setup These Variables are ENABLED or DISABLED Remember ALL CAPS
const uint8_t WRITE_CONFIG = DISABLED;  // This is ENABLED or DISABLED
const uint8_t READ_CONFIG = DISABLED;   // This is ENABLED or DISABLED
const uint8_t MEASURE_CELL = ENABLED;   // This is ENABLED or DISABLED
const uint8_t MEASURE_AUX = DISABLED;   // This is ENABLED or DISABLED
const uint8_t MEASURE_STAT = DISABLED;  // This is ENABLED or DISABLED
const uint8_t PRINT_PEC = DISABLED;     // This is ENABLED or DISABLED

int segment_temp_0;
int segment_temp_1;
int segment_temp_2;
int segment_temp_3;
int segment_temp_4;
int segment_temp_5;
int segment_temp_6;
int segment_temp_7;
int segment_temp_8;
int segment_temp_9;

void read_voltage(cell_asic *bms_ic, const int &state) {
  
  int8_t error = 0;
  // default balancing switch state before switching again
  LTC6811_clear_discharge(TOTAL_IC, bms_ic);
  wakeup_sleep(TOTAL_IC);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);

  // half the aquisition cycle dedicated to "odds" and the other to "evens"
  // modified register bits, need to write to config register after
  switch(state){
    case 1: 
      LTC6811_set_discharge(1, TOTAL_IC, bms_ic);
      LTC6811_set_discharge(3, TOTAL_IC, bms_ic);
      LTC6811_set_discharge(5, TOTAL_IC, bms_ic);
      LTC6811_set_discharge(8, TOTAL_IC, bms_ic);
      LTC6811_set_discharge(10, TOTAL_IC, bms_ic);
      break;
      
    case 2:
      LTC6811_set_discharge(2, TOTAL_IC, bms_ic);
      LTC6811_set_discharge(4, TOTAL_IC, bms_ic);
      LTC6811_set_discharge(7, TOTAL_IC, bms_ic);
      LTC6811_set_discharge(9, TOTAL_IC, bms_ic);
      LTC6811_set_discharge(11, TOTAL_IC, bms_ic);
      break;
  }

  // wakeup before commanding register update
  wakeup_sleep(TOTAL_IC);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);

  // ADC commands already send directly over SPI, no need to write to registers after
  LTC6811_adcv(ADC_CONVERSION_MODE,ADC_DCP,CELL_CH_TO_CONVERT);
  LTC6811_pollAdc();
  error = LTC6811_rdcv(0, TOTAL_IC, bms_ic);
  // wakeup_idle();

  // values get updated on ADC poll?
  // need to see what units the voltages are in, gotta do processing
  // converting 
  segment_temp_0 = bms_ic[1].cells.c_codes[1] * 0.0001;
  segment_temp_1 = bms_ic[1].cells.c_codes[2] * 0.0001;
  segment_temp_2 = bms_ic[1].cells.c_codes[3] * 0.0001;
  segment_temp_3 = bms_ic[1].cells.c_codes[4] * 0.0001;
  segment_temp_4 = bms_ic[1].cells.c_codes[5] * 0.0001;
  segment_temp_5 = bms_ic[1].cells.c_codes[7] * 0.0001;
  segment_temp_6 = bms_ic[1].cells.c_codes[8] * 0.0001;
  segment_temp_7 = bms_ic[1].cells.c_codes[9] * 0.0001;
  segment_temp_8 = bms_ic[1].cells.c_codes[10] * 0.0001;
  segment_temp_9 = bms_ic[1].cells.c_codes[11] * 0.0001;

}



#endif

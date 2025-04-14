#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>

// turn this into an Arduino library eventually
#include "LTC6811.h"
#include "LTC681x.h"
#include "bms_hardware.h"
#include "LT_SPI.h"

#include "index.h"

#include <Adafruit_NeoPixel.h>

// bus and message definition
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> cbus2;
// CHECK TO SEE WHICH HARDWARE, PHYSICAL, CANBUS WE ARE USING
static CAN_message_t msg;
#define CAN2_BAUDRATE 1000000

// signal definitions
// #include "CAN/raptor_CAN1.hpp"
// #include "CAN/raptor_CAN2.hpp"

const int STMM = 1;   /* STMM Module Select 
                      1 = seg1 
                      2 = seg2
                      3 = seg3
                      4 = seg4
                      5 = seg5
                      6 = seg6
                      7 = seg7
                      8 = seg8
                      */

// sensor definitions
// #include "sensors.hpp"

// outgoing can message definitions
// #include "can_send.hpp"

// rainbow RGB
#include "rainbow_pixels.hpp"

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 10; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

#define ENABLED 1
#define DISABLED 0

#define DATALOG_ENABLED 1
#define DATALOG_DISABLED 0

// ADC Command Configurations
const uint8_t ADC_OPT = ADC_OPT_DISABLED;          // See LTC6811_daisy.h for Options
const uint8_t ADC_CONVERSION_MODE = MD_7KHZ_3KHZ;  // MD_7KHZ_3KHZ; //MD_26HZ_2KHZ;//MD_7KHZ_3KHZ; // See LTC6811_daisy.h for Options
const uint8_t ADC_DCP = DCP_DISABLED;              // See LTC6811_daisy.h for Options
const uint8_t CELL_CH_TO_CONVERT = CELL_CH_ALL;    // See LTC6811_daisy.h for Options
const uint8_t AUX_CH_TO_CONVERT = AUX_CH_ALL;      // See LTC6811_daisy.h for Options
const uint8_t STAT_CH_TO_CONVERT = STAT_CH_ALL;    // See LTC6811_daisy.h for Options

const uint16_t MEASUREMENT_LOOP_TIME = 5 * 6000;  // milliseconds(mS)
const uint16_t BALANCE_LOOP_TIME = 60000;         // milliseconds(mS)

// Loop Measurement Setup These Variables are ENABLED or DISABLED Remember ALL CAPS
const uint8_t WRITE_CONFIG = DISABLED;  // This is ENABLED or DISABLED
const uint8_t READ_CONFIG = DISABLED;   // This is ENABLED or DISABLED
const uint8_t MEASURE_CELL = ENABLED;   // This is ENABLED or DISABLED
const uint8_t MEASURE_AUX = DISABLED;   // This is ENABLED or DISABLED
const uint8_t MEASURE_STAT = DISABLED;  // This is ENABLED or DISABLED
const uint8_t PRINT_PEC = DISABLED;     // This is ENABLED or DISABLED

//Cycle ID logic
// #include "cyclic_id.hpp"

// cell data structure with a number of elements matching the number of ICs
cell_asic bms_ic[TOTAL_IC];

void EnableBalancingSwitches(int state) {
  // default balancing switch state before switching again
  
  LTC6811_clear_discharge(TOTAL_IC, bms_ic);
  
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

  wakeup_sleep(TOTAL_IC);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);
}

void ReadTemperature() {
  // activate the ICs
  wakeup_sleep(TOTAL_IC);
  // default balancing switch state before measuring
  LTC6811_clear_discharge(TOTAL_IC, bms_ic);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);

  // initialize everything to 0
  // saveCount = 0;
  // battery.min.voltage = bms_ic[0].cells.c_codes[0];
  // battery.min.IC = 0;
  // battery.min.cell = 0;

  // battery.max.voltage = bms_ic[0].cells.c_codes[0];
  // battery.max.IC = 0;
  // battery.max.cell = 0;
  // battery.sum = 0;

  // loop through all connected ICs (should only be one)
  for (int current_ic = 0; current_ic < TOTAL_IC; current_ic++) {
    // battery.pack[current_ic].sum = 0;
    // battery.pack[current_ic].min.voltage = bms_ic[current_ic].cells.c_codes[0];
    // battery.pack[current_ic].max.voltage = bms_ic[current_ic].cells.c_codes[0];

    // bms_ic[current_ic].cells.c_codes[0];
    
    // loop through all connected cells
    for (int i = 0; i < bms_ic[0].ic_reg.cell_channels; i++) {
      // EnableBalancingSwitches(1);
      // battery.pack[current_ic].cells[i] = bms_ic[current_ic].cells.c_codes[i];
      // battery.pack[current_ic].sum += battery.pack[current_ic].cells[i];
      Serial.println(bms_ic[current_ic].cells.c_codes[i]);
      
      // // set new minimum voltage for current IC
      // if (battery.pack[current_ic].cells[i] < battery.pack[current_ic].min.voltage) {
      //   battery.pack[current_ic].min.voltage = battery.pack[current_ic].cells[i];
      //   battery.pack[current_ic].min.IC = current_ic;
      //   battery.pack[current_ic].min.cell = i;
      // }

      // // set new maximum voltage for current IC
      // if (battery.pack[current_ic].cells[i] > battery.pack[current_ic].max.voltage) {
      //   battery.pack[current_ic].max.voltage = battery.pack[current_ic].cells[i];
      //   battery.pack[current_ic].max.IC = current_ic;
      //   battery.pack[current_ic].max.cell = i;
      // }
    }
    
    // // calculate average voltage for current IC
    // battery.pack[current_ic].average = battery.pack[current_ic].sum / bms_ic[0].ic_reg.cell_channels;
    // battery.sum += battery.pack[current_ic].sum;

    // // calculate minumum voltage for all ICs
    // if (battery.min.voltage > battery.pack[current_ic].min.voltage) {
    //   battery.min.voltage = battery.pack[current_ic].min.voltage;
    //   battery.min.IC = battery.pack[current_ic].min.IC;
    //   battery.min.cell = battery.pack[current_ic].min.cell;
    // }
    
    // // calculate maximum voltage for all ICs
    // if (battery.max.voltage < battery.pack[current_ic].max.voltage) {
    //   battery.max.voltage = battery.pack[current_ic].max.voltage;
    //   battery.max.IC = battery.pack[current_ic].max.IC;
    //   battery.max.cell = battery.pack[current_ic].max.cell;
    // }
  }

  // calculate average for all ICs
  // battery.average = battery.sum / (TOTAL_IC * bms_ic[0].ic_reg.cell_channels);

  // // save battery stats
  // BatteryStats.data[0] = battery.sum;
  // BatteryStats.BatteryStats.data[2] = battery.max.voltage;
  // BatteryStats.data[4] = battery.min.voltage;
}

void setup() {

  // begin Neopixel
  GLO_neopixel.begin();
  GLO_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
  GLO_neopixel.setPixelColor(0, 255, 0, 0); // red
  GLO_neopixel.show();

  // Initialize serial communication
  Serial.begin(112500);

  // initialize SPI communication
  SPI.begin();

  //initialize the CAN Bus and set its baud rate to 1Mb
  cbus2.begin();
  cbus2.setBaudRate(CAN2_BAUDRATE);

  // make a nice wrapper for the LTC6811 at some point
  LTC681x_init_cfg(TOTAL_IC, bms_ic);
  LTC6811_reset_crc_count(TOTAL_IC, bms_ic);
  LTC6811_init_reg_limits(TOTAL_IC, bms_ic);
  bms_ic->isospi_reverse = false;
  
  wakeup_sleep(TOTAL_IC);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);
}

void loop() {

  rainbow_pixels(GLO_neopixel);
  static EasyTimer loop_timer(1); // 1 Hz (100ms)
    if(loop_timer.isup()) {
      wakeup_sleep(TOTAL_IC);
      ReadTemperature();
    }
  
}
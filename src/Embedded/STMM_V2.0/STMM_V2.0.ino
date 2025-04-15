// legacy libs
#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>

// turn this into an Arduino library eventually
// BMS libs
#include "bms_control.hpp"

// cycle ID logic
#include "cyclic_id.hpp"

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
#include "can_send.hpp"

// rainbow RGB
#include "rainbow_pixels.hpp"

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 10; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

#define ENABLED 1
#define DISABLED 0

#define DATALOG_ENABLED 1
#define DATALOG_DISABLED 0

// cell data structure with a number of elements matching the number of ICs
cell_asic bms_ic[TOTAL_IC];

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
  LTC6811_init_cfg(TOTAL_IC, bms_ic);
  LTC6811_reset_crc_count(TOTAL_IC, bms_ic);
  LTC6811_init_reg_limits(TOTAL_IC, bms_ic);
  bms_ic->isospi_reverse = false;
  
  wakeup_sleep(TOTAL_IC);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);
}

void loop() {
  
  int8_t error = 0;
  rainbow_pixels(GLO_neopixel);
  
  // read the registers -- happens whenever we want to send a CAN message
  // updates the cell_temp values on its own timer, every ~1sec since we don't need fast aquisition for temp
  static EasyTimer temp_acquisition(1); // 1 Hz (1s)
  if (temp_acquisition.isup()) {
    wakeup_sleep(TOTAL_IC);
    LTC6811_rdcfg(TOTAL_IC, bms_ic);
    
    // below is the measurement loop, create a library to handle the sampling and stuff
    ltc6811_adcv(ADC_CONVERSION_MODE,ADC_DCP,CELL_CH_TO_CONVERT);
    ltc6811_pollAdc();
    wakeup_idle();
    error = ltc6811_rdcv(0, TOTAL_IC, bms_ic);
    // check_error(error);



  }

  // CAN timers are asynchronous with temperature acquition timers
  switch (STMM) {
    case 1:
      send_can_1();
      break;
    case 2:
      send_can_2();
      break;
    case 3:
      send_can_3();
      break;
    case 4:
      send_can_4();
      break;
    case 5:
      send_can_5();
      break;
    case 6:
      send_can_6();
      break;
    case 7:
      send_can_7();
      break;
    case 8:
      send_can_8();
      break;
  }
  
}
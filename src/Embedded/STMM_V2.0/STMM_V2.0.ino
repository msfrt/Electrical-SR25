// legacy libs
#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>
// #include "LTC6811_daisy.h"

#include <Arduino.h>
#include <SPI.h>
#include <stdint.h>

#include "LTC6811.h"
#include "LTC681x.h"
#include "LT_SPI.h"
#include "Linduino.h"
// #include "index.h"

#include "bms_hardware.h"

// turn this into an Arduino library eventually
// BMS libs
#include "bms_controller.hpp"

// cycle ID logic
#include "cyclic_id.hpp"

#include <Adafruit_NeoPixel.h>

// bus and message definition
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> cbus2;
// CHECK TO SEE WHICH HARDWARE, PHYSICAL, CANBUS WE ARE USING
static CAN_message_t msg; // tx msg
static CAN_message_t rxmsg; // rx msg
#define cbus2_BAUDRATE 1000000

// each bus has a total of 64 mailboxes
#define NUM_RX_STD_MAILBOXES 60
#define NUM_RX_EXT_MAILBOXES 2
#define NUM_TX_MAILBOXES 2
// limit the number of messages each bus can read for each loop cycle.
// Typically, only one message is recieved in the time that the loop can run,
// but a buildup can occur, and this limit can poll the bus to read messages
// while not getting stuck in an infinite loop
#define MAX_CAN_FRAME_READ_PER_CYCLE 5

// cell data structure with a number of elements matching the number of ICs
static cell_asic bms_ic[TOTAL_IC];

// signal definitions
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

const int STMM = 8;   /* STMM Module Select 
                      1 = seg1 
                      2 = seg2
                      3 = seg3
                      4 = seg4
                      5 = seg5
                      6 = seg6
                      7 = seg7
                      8 = seg8
                      */

// outgoing can message definitions
#include "can_send.hpp"

// rainbow RGB
#include "rainbow_pixels.hpp"

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 10; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

void setup() {

  // begin Neopixel
  GLO_neopixel.begin();
  GLO_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
  GLO_neopixel.setPixelColor(0, 255, 0, 0); // red
  GLO_neopixel.show();

  // Initialize serial communication
  Serial.begin(112500);
  
  //initialize the CAN Bus and set its baud rate to 1Mb
  cbus2.begin();
  cbus2.setBaudRate(cbus2_BAUDRATE);
  set_mailboxes();
  STMM_segmentSync.set_timeout_delay(10);

  // initialize SPI communication
  // make a nice wrapper for the LTC6811 at some point
  
  // sets up the CS pin n' stuff
  spi_enable();

  LTC681x_init_cfg(TOTAL_IC, bms_ic);
  LTC6811_reset_crc_count(TOTAL_IC, bms_ic);
  LTC6811_init_reg_limits(TOTAL_IC, bms_ic);
  bms_ic->isospi_reverse = false;
  wakeup_sleep(TOTAL_IC);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);
}

void loop() {
  
  rainbow_pixels(GLO_neopixel);
  
  measurement_loop(bms_ic, STMM);

  // CAN timers are asynchronous with temperature acquition timers
  switch (STMM) {
    case 1:
      send_can_1(1);
      send_step(step);
      break;
    case 2:
      send_can_2(2);
      readCan();
      // Serial.println("Seg 2 Step");
      // Serial.println(step);
      // Serial.println("Sync CAN");
      // Serial.println(STMM_segmentSync.value());
      break;
    case 3:
      send_can_3(3);
      readCan();
      break;
    case 4:
      send_can_4(4);
      readCan();
      break;
    case 5:
      send_can_5(5);
      readCan();
      break;
    case 6:
      send_can_6(6);
      readCan();
      break;
    case 7:
      send_can_7(7);
      readCan();
      break;
    case 8:
      send_can_8(8);
      readCan();
      break;
  }
  
}

void set_mailboxes() {
  // to view mailbox status, you can use the member function mailboxStatus().
  // Don't put it in a fast loop, though, because you may actually affect how
  // the chips moves things around

  // use all mailboxes of course
  cbus2.setMaxMB(64);

  for (int i = 0; i < NUM_RX_STD_MAILBOXES; i++) {
    cbus2.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }
  for (int i = NUM_RX_STD_MAILBOXES;
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES); i++) {
    cbus2.setMB((FLEXCAN_MAILBOX)i, RX, EXT);
  }
  for (int i = (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES);
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES + NUM_TX_MAILBOXES);
       i++) {
    cbus2.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }

  cbus2.setMBFilter(REJECT_ALL);
  cbus2.setMBFilter(MB0, STMM_segmentSync.get_msg_id());
  cbus2.setMBFilter(MB1, 0);
  cbus2.setMBFilter(MB2, 0);
  cbus2.setMBFilter(MB3, 0);
  cbus2.setMBFilter(MB4, 0);
  cbus2.setMBFilter(MB5, 0);
  cbus2.setMBFilter(MB6, 0);
  cbus2.setMBFilter(MB7, 0);
  cbus2.setMBFilter(MB8, 0);
  cbus2.setMBFilter(MB9, 0);
  cbus2.setMBFilter(MB10, 0);
  cbus2.setMBFilter(MB11, 0);
  cbus2.setMBFilter(MB12, 0);
  cbus2.setMBFilter(MB13, 0);
  cbus2.setMBFilter(MB14, 0);
}

void readCan() {
  int count = 0;

  count = 0;
  while (cbus2.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_raptor_CAN2(rxmsg);
    count++;
  }
}
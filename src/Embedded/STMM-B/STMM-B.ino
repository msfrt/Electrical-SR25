#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>

#include <Arduino.h>
#include <SPI.h>
#include <stdint.h>

#include "LTC6811.h"
#include "LTC681x.h"
#include "LT_SPI.h"
#include "Linduino.h"
#include <Adafruit_NeoPixel.h>

#include "bms_hardware.h"

#include "bms_controller.hpp"

#include "sensors.hpp"

// bus and message definition1
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> cbus1;
// CHECK TO SEE WHICH HARDWARE, PHYSICAL, CANBUS WE ARE USING
static CAN_message_t msg; // tx msg
static CAN_message_t rxmsg; // rx msg
#define cbus1_BAUDRATE 1000000

// bus and message definition2
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> cbus2;
#define cbus2_BAUDRATE 125000

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

// outgoing can message definitions
// #include "can_send.hpp"

// rainbow RGB
#include "rainbow_pixels.hpp"

// output pin that drives the shutdown circuit relay
const int BMS_status_pin = 20;

// default balancing state
int balancing = 0;

const int GLO_NeoPixel_teensy_pin = 7;
      int GLO_NeoPixel_brightness_percent = 10; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:

  // begin Neopixel
  GLO_neopixel.begin();
  GLO_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
  GLO_neopixel.setPixelColor(0, 255, 0, 0); // red
  GLO_neopixel.show();

  // initialize BMS status pin
  pinMode(BMS_status_pin, OUTPUT);
  // initialize the BMS status pin low before passing status checks
  digitalWrite(BMS_status_pin, LOW);

  // Initialize serial communication
  Serial.begin(112500);

  //initialize the CAN Bus and set its baud rate to 1Mb
  cbus1.begin();
  cbus2.begin();
  cbus1.setBaudRate(cbus1_BAUDRATE);
  cbus2.setBaudRate(cbus2_BAUDRATE);
  set_mailboxes();

  // initialize the ADC sensors
  initialize_ADCs();

  // initialize SPI communication
  // make a nice wrapper for the LTC6811 at some point
  
  // sets up the CS pin n' stuff
  spi_enable(); // should be okay with the ADCs SPI comms upon first glance

  LTC681x_init_cfg(TOTAL_IC, bms_ic);
  LTC6811_reset_crc_count(TOTAL_IC, bms_ic);
  LTC6811_init_reg_limits(TOTAL_IC, bms_ic);
  bms_ic->isospi_reverse = false;
  wakeup_sleep(TOTAL_IC);
  LTC6811_wrcfg(TOTAL_IC, bms_ic);

}

void loop() {
  // put your main code here, to run repeatedly:
  rainbow_pixels(GLO_neopixel);

  sample_ADCs();
  readCan();

  // find a good trigger that comes from the Elcon
  if (XXX.value() == 0x00 && XXX.timeout_check()){
    balancing = 1;
  } else {
    balancing = 0;
  }

  switch(balancing):
    case 0: // normal monitoring state
      
      static EasyTimer measurement_timer(10); // measure voltages every 100ms
      if (measurement_timer.isup()) {
        measurement_loop(bms_ic);
      }

      send_step();
      send_can_2();

      break;
    
    case 1: // charging state
      
      static EasyTimer balancing_timer(10); // balances every 100ms
      if (balancing_timer.isup()) {
        balancing_loop(bms_ic);
      }

      send_step();
      send_can_1();

      break;
    
}

void set_mailboxes() {
  // to view mailbox status, you can use the member function mailboxStatus().
  // Don't put it in a fast loop, though, because you may actually affect how
  // the chips moves things around

  // use all mailboxes of course
  cbus1.setMaxMB(64);
  cbus2.setMaxMB(64);

  // CAN 1
  for (int i = 0; i < NUM_RX_STD_MAILBOXES; i++) {
    cbus1.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }
  for (int i = NUM_RX_STD_MAILBOXES;
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES); i++) {
    cbus1.setMB((FLEXCAN_MAILBOX)i, RX, EXT);
  }
  for (int i = (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES);
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES + NUM_TX_MAILBOXES);
       i++) {
    cbus1.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }

  // CAN 2
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

  // put in msg id's that are being used below, or else none of ur wanted messages will get processed
  cbus1.setMBFilter(REJECT_ALL);
  cbus1.setMBFilter(MB0, 0);
  cbus1.setMBFilter(MB1, 0);
  cbus1.setMBFilter(MB2, 0);
  cbus1.setMBFilter(MB3, 0);
  cbus1.setMBFilter(MB4, 0);
  cbus1.setMBFilter(MB5, 0);
  cbus1.setMBFilter(MB6, 0);
  cbus1.setMBFilter(MB7, 0);
  cbus1.setMBFilter(MB8, 0);
  cbus1.setMBFilter(MB9, 0);
  cbus1.setMBFilter(MB10, 0);
  cbus1.setMBFilter(MB11, 0);
  cbus1.setMBFilter(MB12, 0);
  cbus1.setMBFilter(MB13, 0);
  cbus1.setMBFilter(MB14, 0);

  cbus2.setMBFilter(REJECT_ALL);
  cbus2.setMBFilter(MB0, 0);
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
  
  while (cbus1.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_raptor_CAN1(rxmsg);
    count++;
  }

  while (cbus2.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_raptor_CAN2(rxmsg);
    count++;
  }
}

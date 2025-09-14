#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>

#include <Adafruit_NeoPixel.h>

// bus and message definition
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> cbus2;
// CHECK TO SEE WHICH HARDWARE, PHYSICAL, CANBUS WE ARE USING
static CAN_message_t msg;
#define CAN2_BAUDRATE 1000000

// signal definitions
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

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
#include "sensors.hpp"

// outgoing can message definitions
#include "can_send.hpp"

// rainbow RGB
#include "rainbow_pixels.hpp"

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 10; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

//Cycle ID logic
#include "cyclic_id.hpp"

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

  //initialize ADCs
  initialize_ADCs();

}

void loop() {

  rainbow_pixels(GLO_neopixel);

  // segment #
  // 8 STMMs, each in charge of sending different messages
  switch (STMM)
  {
    case 1:
      sample_ADCs_1();
      send_can_1(STMM);
      break;

    case 2:
      sample_ADCs_2();
      send_can_2(STMM);
      break;

    case 3:
      sample_ADCs_3();
      send_can_3(STMM);
      break;

    case 4:
      sample_ADCs_4();
      send_can_4(STMM);
      break;

    case 5:
      sample_ADCs_5();
      send_can_5(STMM);
      break;

    case 6:
      sample_ADCs_6();
      send_can_6(STMM);
      break;

    case 7:
      sample_ADCs_7();
      send_can_7(STMM);
      break;

    case 8:
      sample_ADCs_8();
      send_can_8(STMM);
      break;
      
  }
}
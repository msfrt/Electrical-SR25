#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>

#include <Adafruit_NeoPixel.h>

// bus and message_t definition
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> cbus2;
// CHECK TO SEE WHICH HARDWARE, PHYSICAL, CANBUS WE ARE USING
static CAN_message_t msg;
#define CAN2_BAUDRATE 250000

// signal definitions
// #include "CAN/CAN1.hpp"
// #include "CAN/CAN2.hpp"
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
      int GLO_NeoPixel_brightness_percent = 100; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

//Cycle ID logic
#include "cyclic_id.hpp"

int counter_1 = 0;
int counter_2 = 0;
int counter_3 = 0;
int counter_4 = 0;
int counter_5 = 0;
int counter_6 = 0;
int counter_7 = 0;
int counter_8 = 0;

void setup() {

  // begin Neopixel
  GLO_neopixel.begin();
  GLO_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
  GLO_neopixel.setPixelColor(0, 255, 0, 0); // red
  GLO_neopixel.show();

  // Initialize serial communication
  Serial.begin(112500);

  // initialize SPI communication
  // SPI.begin();

  //initialize the CAN Bus and set its baud rate to 1Mb
  cbus2.begin();
  cbus2.setBaudRate(CAN2_BAUDRATE);

  //initialize ADCs
  // initialize_ADCs();

}

void loop() {

  msu_pixels(GLO_neopixel);

  // counter, segment

  switch (STMM)
  {
    case 1:
      // sample_ADCs_1();
      send_can_1(counter_1, 1);
      send_can_2(counter_2, 2);
      break;

    // case 2:
    //   sample_ADCs_2();
    //   send_can_2(counter_2, 2);
    //   break;

    // case 3:
    //   sample_ADCs_3();
    //   send_can_3(counter_3, 3);
    //   break;

    // case 4:
    //   sample_ADCs_4();
    //   send_can_4(counter_4, 4);
    //   break;

    // case 5:
    //   sample_ADCs_5();
    //   send_can_5(counter_5, 5);
    //   break;

    // case 6:
    //   sample_ADCs_6();
    //   send_can_6(counter_6, 6);
    //   break;

    // case 7:
    //   sample_ADCs_7();
    //   send_can_7(counter_7, 7);
    //   break;

    // case 8:
    //   sample_ADCs_8();
    //   send_can_8(counter_8, 8);
    //   break;
      
  }
}
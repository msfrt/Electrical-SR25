#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <FreqMeasureMulti.h>

// bus and message_t definition
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
#define CAN1_BAUDRATE 500000

// signal definitions
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

// sensor definitions
#include "sensors.hpp"

// outgoing can message definitions
#include "can_send.hpp"

// brake bias calculation for front ATCC
#include "bias_calc.hpp"

// rotor temp calculation for ATCC
#include "rotor_temp_calc.hpp"

// rainbow RGB
#include "rainbow_pixels.hpp"

// wheel speed calc
#include "wheel_speed.hpp"

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 100; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

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
  can1.begin();
  can1.setBaudRate(CAN1_BAUDRATE);

  //initialize ADCs
  initialize_ADCs();

  // turn neopixel green
  GLO_neopixel.setPixelColor(0, 0, 255, 0); // green
  GLO_neopixel.show();

  freq1.begin(freq_pin1);
  freq2.begin(freq_pin2);
  freq3.begin(freq_pin3);
  freq4.begin(freq_pin4);

}

void loop() {

  msu_pixels(GLO_neopixel);

  sample_ADCs();
  
  readWheelSpeed();

}

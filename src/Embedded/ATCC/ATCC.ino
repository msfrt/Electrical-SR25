#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <FreqMeasureMulti.h>

// bus and message_t definition
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> cbus2;
static CAN_message_t msg;
#define CAN1_BAUDRATE 1000000

// signal definitions
#include "CAN/CAN1.hpp"
#include "CAN/CAN2.hpp"

// ATCC Module Select - 0 front, 1 back
const int ATCCMS = 0;

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

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 100; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

FreqMeasureMulti freq1;
FreqMeasureMulti freq2;
FreqMeasureMulti freq3;
FreqMeasureMulti freq4;

#define freq_pin1 5
#define freq_pin2 6
#define freq_pin3 7
#define freq_pin4 8

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
  cbus2.setBaudRate(CAN1_BAUDRATE);

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

float sum1=0, sum2=0, sum3=0, sum4=0;
int count1=0, count2=0, count3=0, count4=0;
elapsedMillis timeout;

float frequencyToRPM(float freq, int teeth) {
  return (freq * 60.0) / teeth;
}

void loop() {

  msu_pixels(GLO_neopixel);

  switch (ATCCMS)
  {
    case 0:
      sample_ADCs_F();
      send_can_F();
      
      calculate_rotor_temp(ATCCF_rotorTempFL, ATCCF_rotorTempFR, ATCCR_rotorTempRL, ATCCR_rotorTempRR);
      calculate_brake_bias(ATCCF_brakePressureF, ATCCF_brakePressureR, ATCCF_brakeBias);
      break;
    case 1:
      sample_ADCs_R();
      send_can_R();
      break;
  }

  if (freq1.available()) {
    sum1 = sum1 + freq1.read();
    Serial.println(1);
    count1 = count1 + 1;
  }
  if (freq2.available()) {
    sum2 = sum2 + freq2.read();
    Serial.println(2);
    count2 = count2 + 1;
  }
  if (freq3.available()) {
    sum3 = sum3 + freq3.read();
    Serial.println(3);
    count3 = count3 + 1;
  }
  if (freq4.available()) {
    sum4 = sum4 + freq4.read();
    //Serial.println(4);
    count4 = count4 + 1;
  }
  // print results every half second
  if (timeout > 500) {
    if (count1 > 0) {
      float freq = freq1.countToFrequency(sum1 / count1);
      Serial.print(frequencyToRPM(freq, 40));
    } else {
      Serial.print("(no pulses)");
    }
    Serial.print(",  ");
    
    if (count2 > 0) {
      float freq = freq2.countToFrequency(sum2 / count2);
      Serial.print(frequencyToRPM(freq, 40));
    } else {
      Serial.print("(no pulses)");
    }
    Serial.print(",  ");
    
    if (count3 > 0) {
      float freq = freq3.countToFrequency(sum3 / count3);
      Serial.print(frequencyToRPM(freq, 40));
    } else {
      Serial.print("(no pulses)");
    }
    Serial.print(",  ");
    
    if (count4 > 0) {
      float freq = freq4.countToFrequency(sum4 / count4);
      Serial.print(frequencyToRPM(freq, 40));
    } else {
      Serial.print("(no pulses)");
    }
    Serial.println();

    // Reset for next interval
    sum1 = sum2 = sum3 = sum4 = 0;
    count1 = count2 = count3 = count4 = 0;
    timeout = 0;
  }


}

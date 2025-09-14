#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <FreqMeasureMulti.h>

#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"
#include "can_send.hpp"

// ATCC Module Select - 0 front, 1 back
const int ATCCMS = 1;

FreqMeasureMulti freq1;
FreqMeasureMulti freq2;
FreqMeasureMulti freq3;
FreqMeasureMulti freq4;

#define freq_pin1 3
#define freq_pin2 4
#define freq_pin3 5
#define freq_pin4 6

float sum1=0, sum2=0, sum3=0, sum4=0;
int count1=0, count2=0, count3=0, count4=0;
elapsedMillis timeout;

float frequencyToRPM(float freq, int teeth) {
  return (freq * 60.0) / teeth;
}

void readWheelSpeed () {

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

  send_can1();

}
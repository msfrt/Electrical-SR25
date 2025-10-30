#ifndef SENSORS_ATCC_HPP
#define SENSORS_ATCC_HPP

#include <ReadADC.h>
#include <EasyTimer.h>

// cooling temp calculation for ATCC
#include "cooling_temp_calc.hpp"

// ADC CS teensy pins
#define ADC1_CS 10
#define ADC2_CS 9
#define ADC3_CS 8

// ADCs
ADCChip adc1(ADC1_CS);
ADCChip adc2(ADC2_CS);
ADCChip adc3(ADC3_CS);

// whatr reads a right voltage 3,9 3,4

// rear sensors
ADCSensor coolant_temp_middle_sens(10, 0, 1000); // adc3
ADCSensor coolant_temp_outlet_sens(9, 0, 1000); // adc3
ADCSensor coolant_temp_inlet_sens(4, 0, 1000); // adc3 


void initialize_ADCs()
{
  adc1.begin();
  adc2.begin();
  adc3.begin();
}

void sample_ADCs_R()
{

  // 100 Hz
  static EasyTimer sample_timer_2(100);
  if (sample_timer_2.isup())
  {
    //adc2
    //adc2.sample();
    
  }

  // 100 Hz
  static EasyTimer sample_timer_3(100);
  if (sample_timer_3.isup())
  {

    //adc3
    adc3.sample(coolant_temp_middle_sens, coolant_temp_inlet_sens, coolant_temp_outlet_sens);
    Serial.print("coolant_temp_sens_voltage: ");
    Serial.println(coolant_temp_middle_sens.avg());
    Serial.print("coolant_temp_sens_voltage: ");
    Serial.println(coolant_temp_inlet_sens.avg());
    Serial.print("coolant_temp_sens_voltage: ");
    Serial.println(coolant_temp_outlet_sens.avg());

  }

}




#endif
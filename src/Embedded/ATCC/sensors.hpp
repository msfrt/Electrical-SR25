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

// rear sensors
ADCSensor coolant_temp_middle_sens(1, 0, 1000); // adc3
ADCSensor coolant_temp_outlet_sens(7, 0, 1000); // adc2
ADCSensor coolant_temp_inlet_sens(0, 0, 1000); // adc2

ADCSensor egt1_sens(2, 0, 100);
ADCSensor egt2_sens(0, 0, 100);
ADCSensor egt3_sens(1, 0, 100);
ADCSensor egt4_sens(3, 0, 100);


float voltage_to_NTC_M12_H_temp(float v){

  // calculated from the excel document.
  // fifth order because we don't really care about extrapolation here.
  return -0.8982 * pow(v, 5) +
          11.970 * pow(v, 4) -
          61.647 * pow(v, 3) +
          153.57 * pow(v, 2) -
          209.75 * pow(v, 1) +
          187.96;
}

float voltage_to_EGT_temp(float v){

  // calculated from the excel document.
  return 137.64 * pow(v, 3) -
         280.17 * pow(v, 2) +
         652.15 * pow(v, 1) -
         374.03;
}


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
    adc2.sample(coolant_temp_inlet_sens, coolant_temp_outlet_sens);
    //Serial.print("coolant_temp_sens_voltage: ");
    //Serial.println(voltage_to_temp(coolant_temp_inlet_sens.avg()));
    //Serial.print("coolant_temp_sens_voltage: ");
    //Serial.println(voltage_to_temp(coolant_temp_outlet_sens.avg()));
  }

  // 100 Hz
  static EasyTimer sample_timer_3(100);
  if (sample_timer_3.isup())
  {

    //adc3
    adc3.sample(coolant_temp_middle_sens);
    //Serial.print("coolant_temp_sens_voltage: ");
    //Serial.println(voltage_to_temp(coolant_temp_outlet_sens.avg()));

  }

}




#endif
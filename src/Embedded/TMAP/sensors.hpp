#ifndef SENSORS_STMM_HPP
#define SENSORS_STMM_HPP

#include <EasyTimer.h>
#include <ReadADC.h>

// ADC CS(Chip Select) teensy pins
#define ADC1_CS 10
#define ADC2_CS 9

// ADCs
ADCChip adc1(ADC1_CS);
ADCChip adc2(ADC2_CS); 

//Analog to Digital Convertor input signals
//seg_1_mod_0 = Segment 1, Module 1

ADCSensor tmap_temp_pre(0,0,1000); // 
ADCSensor tmap_pres_pre(1,0,1000);

ADCSensor tmap_temp_post(2,0,1000);
ADCSensor tmap_pres_post(3,0,1000);

// takes 1k pullup into account
float voltage_to_boschua_temp(float v) {
    return  -0.0722 * pow(v,4) -
            2.6887 * pow(v,3) +
            25.738 * pow(v,2) -
            93.071 * pow(v,1) +
            160.54;
}

float voltage_to_boschua_pres(float v) {
    return  ((v/5)-(-0.1/105))/(0.85/105); //pressure in kpa
}

void initialize_ADCs()
{
  adc1.begin();
//   adc2.begin();
}

// come back here to change which channels we are actually using on the ADCs

void sample_ADCs() {
    // static variable prevents object from deletion when out of scope
    static EasyTimer sample_timer_1(100); //100 Hz
    if(sample_timer_1.isup()) {
        adc1.sample(tmap_temp_pre, tmap_pres_pre, tmap_temp_post, tmap_pres_post);
        // adc2.sample();
    }
    
}

#endif
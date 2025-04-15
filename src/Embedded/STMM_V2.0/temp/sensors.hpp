#ifndef SENSORS_STMM2_HPP
#define SENSORS_STMM2_HPP

#include <EasyTimer.h>
#include <ReadADC.h>

// ADC CS(Chip Select) teensy pins
#define ADC1_CS 10

// ADCs
ADCChip adc1(ADC1_CS);

//Analog to Digital Convertor input signals
//seg_1_mod_0 = Segment 1, Module 1

ADCSensor seg_1_mod_0(0,0,1000);



/* 
ADC Sampling: For every cycle(of frequency mentioned in timer initialization), sample data from the ADC
Each Teensy controls 2 ADC chips, and handles 4 messages(i.e. 12 signals)
So, each ADC chip takes data for 6 signals
*/

void initialize_ADCs()
{
  adc1.begin();
}

// come back here to change which channels we are actually using on the ADCs

void sample_ADC() {
    // static variable prevents object from deletion when out of scope
    static EasyTimer sample_timer_1(100); //100 Hz
    if(sample_timer_1.isup()) {
        adc1.sample(seg_1_mod_0, seg_1_mod_1, seg_1_mod_2, seg_1_mod_3, seg_1_mod_4, seg_1_mod_5, seg_1_mod_6, seg_1_mod_7,
                    seg_1_mod_8, seg_1_mod_9);
    }
    
}

#endif
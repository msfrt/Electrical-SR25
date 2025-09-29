#ifndef SENSORS_STMMB_HPP
#define SENSORS_STMMB_HPP

#include <EasyTimer.h>
#include <ReadADC.h>

// ADC CS(Chip Select) teensy pins
#define ADC1_CS 9

// ADCs
ADCChip adc1(ADC1_CS);

ADCSensor curr_sense_1(0,0,1000);
ADCSensor curr_sense_2(1,0,1000);

// float voltage_to_ENEPAQ_cell_temp(float v) {
//     // return -740.85 * pow(v,5) + 
//     //         7056.8 * pow(v,4) +
//     //         -26800 * pow(v,3) +
//     //          50732 * pow(v,2) +
//     //         -47967 * pow(v,1) +
//     //         18213;
//     return  155.35203 * pow(v,4) -
//            1381.39248 * pow(v,3) +
//            4484.86765 * pow(v,2) -
//            6407.60322 * pow(v,1) +
//            3457.41389;
// }

// make the voltage to current correlation
float voltage_to_current(float v){
    return;
}

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

void sample_ADCs_1() {
    // static variable prevents object from deletion when out of scope
    static EasyTimer sample_timer_1(100); //100 Hz
    if(sample_timer_1.isup()) {
        adc1.sample(curr_sense_1, curr_sense_2);
    }
}

#endif
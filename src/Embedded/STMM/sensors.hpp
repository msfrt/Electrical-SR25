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

ADCSensor seg_1_mod_0(0,0,1000);
ADCSensor seg_1_mod_1(1,0,1000);
ADCSensor seg_1_mod_2(2,0,1000);
ADCSensor seg_1_mod_3(3,0,1000);
ADCSensor seg_1_mod_4(4,0,1000);
ADCSensor seg_1_mod_5(5,0,1000);
ADCSensor seg_1_mod_6(6,0,1000);
ADCSensor seg_1_mod_7(7,0,1000);
ADCSensor seg_1_mod_8(0,0,1000);
ADCSensor seg_1_mod_9(1,0,1000);
ADCSensor seg_1_mod_10(2,0,1000);
ADCSensor seg_1_mod_11(3,0,1000);
ADCSensor seg_2_mod_0(0,0,1000);
ADCSensor seg_2_mod_1(1,0,1000);
ADCSensor seg_2_mod_2(2,0,1000);
ADCSensor seg_2_mod_3(3,0,1000);
ADCSensor seg_2_mod_4(4,0,1000);
ADCSensor seg_2_mod_5(5,0,1000);
ADCSensor seg_2_mod_6(6,0,1000);
ADCSensor seg_2_mod_7(7,0,1000);
ADCSensor seg_2_mod_8(0,0,1000);
ADCSensor seg_2_mod_9(1,0,1000);
ADCSensor seg_2_mod_10(2,0,1000);
ADCSensor seg_2_mod_11(3,0,1000);
ADCSensor seg_3_mod_0(0,0,1000);
ADCSensor seg_3_mod_1(1,0,1000);
ADCSensor seg_3_mod_2(2,0,1000);
ADCSensor seg_3_mod_3(3,0,1000);
ADCSensor seg_3_mod_4(4,0,1000);
ADCSensor seg_3_mod_5(5,0,1000);
ADCSensor seg_3_mod_6(6,0,1000);
ADCSensor seg_3_mod_7(7,0,1000);
ADCSensor seg_3_mod_8(0,0,1000);
ADCSensor seg_3_mod_9(1,0,1000);
ADCSensor seg_3_mod_10(2,0,1000);
ADCSensor seg_3_mod_11(3,0,1000);
ADCSensor seg_4_mod_0(0,0,1000);
ADCSensor seg_4_mod_1(1,0,1000);
ADCSensor seg_4_mod_2(2,0,1000);
ADCSensor seg_4_mod_3(3,0,1000);
ADCSensor seg_4_mod_4(4,0,1000);
ADCSensor seg_4_mod_5(5,0,1000);
ADCSensor seg_4_mod_6(6,0,1000);
ADCSensor seg_4_mod_7(7,0,1000);
ADCSensor seg_4_mod_8(0,0,1000);
ADCSensor seg_4_mod_9(1,0,1000);
ADCSensor seg_4_mod_10(2,0,1000);
ADCSensor seg_4_mod_11(3,0,1000);
ADCSensor seg_5_mod_0(0,0,1000);
ADCSensor seg_5_mod_1(1,0,1000);
ADCSensor seg_5_mod_2(2,0,1000);
ADCSensor seg_5_mod_3(3,0,1000);
ADCSensor seg_5_mod_4(4,0,1000);
ADCSensor seg_5_mod_5(5,0,1000);
ADCSensor seg_5_mod_6(6,0,1000);
ADCSensor seg_5_mod_7(7,0,1000);
ADCSensor seg_5_mod_8(0,0,1000);
ADCSensor seg_5_mod_9(1,0,1000);
ADCSensor seg_5_mod_10(2,0,1000);
ADCSensor seg_5_mod_11(3,0,1000);
ADCSensor seg_6_mod_0(0,0,1000);
ADCSensor seg_6_mod_1(1,0,1000);
ADCSensor seg_6_mod_2(2,0,1000);
ADCSensor seg_6_mod_3(3,0,1000);
ADCSensor seg_6_mod_4(4,0,1000);
ADCSensor seg_6_mod_5(5,0,1000);
ADCSensor seg_6_mod_6(6,0,1000);
ADCSensor seg_6_mod_7(7,0,1000);
ADCSensor seg_6_mod_8(0,0,1000);
ADCSensor seg_6_mod_9(1,0,1000);
ADCSensor seg_6_mod_10(2,0,1000);
ADCSensor seg_6_mod_11(3,0,1000);
ADCSensor seg_7_mod_0(0,0,1000);
ADCSensor seg_7_mod_1(1,0,1000);
ADCSensor seg_7_mod_2(2,0,1000);
ADCSensor seg_7_mod_3(3,0,1000);
ADCSensor seg_7_mod_4(4,0,1000);
ADCSensor seg_7_mod_5(5,0,1000);
ADCSensor seg_7_mod_6(6,0,1000);
ADCSensor seg_7_mod_7(7,0,1000);
ADCSensor seg_7_mod_8(0,0,1000);
ADCSensor seg_7_mod_9(1,0,1000);
ADCSensor seg_7_mod_10(2,0,1000);
ADCSensor seg_7_mod_11(3,0,1000);
ADCSensor seg_8_mod_0(0,0,1000);
ADCSensor seg_8_mod_1(1,0,1000);
ADCSensor seg_8_mod_2(2,0,1000);
ADCSensor seg_8_mod_3(3,0,1000);
ADCSensor seg_8_mod_4(4,0,1000);
ADCSensor seg_8_mod_5(5,0,1000);
ADCSensor seg_8_mod_6(6,0,1000);
ADCSensor seg_8_mod_7(7,0,1000);
ADCSensor seg_8_mod_8(0,0,1000);
ADCSensor seg_8_mod_9(1,0,1000);
ADCSensor seg_8_mod_10(2,0,1000);
ADCSensor seg_8_mod_11(3,0,1000);

float voltage_to_ENEPAQ_cell_temp(float v) {
    // return -740.85 * pow(v,5) + 
    //         7056.8 * pow(v,4) +
    //         -26800 * pow(v,3) +
    //          50732 * pow(v,2) +
    //         -47967 * pow(v,1) +
    //         18213;
    return  155.35203 * pow(v,4) -
           1381.39248 * pow(v,3) +
           4484.86765 * pow(v,2) -
           6407.60322 * pow(v,1) +
           3457.41389;
}

/* 
ADC Sampling: For every cycle(of frequency mentioned in timer initialization), sample data from the ADC
Each Teensy controls 2 ADC chips, and handles 4 messages(i.e. 12 signals)
So, each ADC chip takes data for 6 signals
*/

void initialize_ADCs()
{
  adc1.begin();
  adc2.begin();
}

// come back here to change which channels we are actually using on the ADCs

void sample_ADCs_1() {
    // static variable prevents object from deletion when out of scope
    static EasyTimer sample_timer_1(100); //100 Hz
    if(sample_timer_1.isup()) {
        adc1.sample(seg_1_mod_0, seg_1_mod_1, seg_1_mod_2, seg_1_mod_3, seg_1_mod_4, seg_1_mod_5, seg_1_mod_6, seg_1_mod_7);
        adc2.sample(seg_1_mod_8, seg_1_mod_9, seg_1_mod_10, seg_1_mod_11);
    }
    
}

void sample_ADCs_2() {
    static EasyTimer sample_timer_2(100); //100 Hz
    if(sample_timer_2.isup()) {
        adc1.sample(seg_2_mod_0, seg_2_mod_1, seg_2_mod_2, seg_2_mod_3, seg_2_mod_4, seg_2_mod_5, seg_2_mod_6, seg_2_mod_7);
        adc2.sample(seg_2_mod_8, seg_2_mod_9, seg_2_mod_10, seg_2_mod_11);
    }
}

void sample_ADCs_3() {
    static EasyTimer sample_timer_3(100); //100 Hz
    if(sample_timer_3.isup()) {
        adc1.sample(seg_3_mod_0, seg_3_mod_1, seg_3_mod_2, seg_3_mod_3, seg_3_mod_4, seg_3_mod_5, seg_3_mod_6, seg_3_mod_7);
        adc2.sample(seg_3_mod_8, seg_3_mod_9, seg_3_mod_10, seg_3_mod_11);
    }
}

void sample_ADCs_4() {
    static EasyTimer sample_timer_4(100); //100 Hz
    if(sample_timer_4.isup()) {
        adc1.sample(seg_4_mod_0, seg_4_mod_1, seg_4_mod_2, seg_4_mod_3, seg_4_mod_4, seg_4_mod_5, seg_4_mod_6, seg_4_mod_7);
        adc2.sample(seg_4_mod_8, seg_4_mod_9, seg_4_mod_10, seg_4_mod_11);
    }
}

void sample_ADCs_5() {
    static EasyTimer sample_timer_5(100); //100 Hz
    if(sample_timer_5.isup()) {
        adc1.sample(seg_5_mod_0, seg_5_mod_1, seg_5_mod_2, seg_5_mod_3, seg_5_mod_4, seg_5_mod_5, seg_5_mod_6, seg_5_mod_7);
        adc2.sample(seg_5_mod_8, seg_5_mod_9, seg_5_mod_10, seg_5_mod_11);

        // Serial.println("Mod 1 (ADC): ");
        // Serial.println(seg_5_mod_0.read_value());
    }
}

void sample_ADCs_6() {
    static EasyTimer sample_timer_6(100); //100 Hz
    if(sample_timer_6.isup()) {
        adc1.sample(seg_6_mod_0, seg_6_mod_1, seg_6_mod_2, seg_6_mod_3, seg_6_mod_4, seg_6_mod_5, seg_6_mod_6, seg_6_mod_7);
        adc2.sample(seg_6_mod_8, seg_6_mod_9, seg_6_mod_10, seg_6_mod_11);
    }
}

void sample_ADCs_7() {
    static EasyTimer sample_timer_7(100); //100 Hz
    if(sample_timer_7.isup()) {
        adc1.sample(seg_7_mod_0, seg_7_mod_1, seg_7_mod_2, seg_7_mod_3, seg_7_mod_4, seg_7_mod_5, seg_7_mod_6, seg_7_mod_7);
        adc2.sample(seg_7_mod_8, seg_7_mod_9, seg_7_mod_10, seg_7_mod_11);
    }
}

void sample_ADCs_8() {
    static EasyTimer sample_timer_8(100); //100 Hz
    if(sample_timer_8.isup()) {
        adc1.sample(seg_8_mod_0, seg_8_mod_1, seg_8_mod_2, seg_8_mod_3, seg_8_mod_4, seg_8_mod_5, seg_8_mod_6, seg_8_mod_7);
        adc2.sample(seg_8_mod_8, seg_8_mod_9, seg_8_mod_10, seg_8_mod_11);
    }
}

#endif
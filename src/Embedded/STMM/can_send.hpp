#ifndef CAN_SEND_STMM_HPP
#define CAN_SEND_STMM_HPP

#include <EasyTimer.h>
#include <FlexCAN_T4.h>

// #include "CAN/CAN1.hpp"
// #include "CAN/CAN2.hpp"

#include "CAN/raptor_CAN2.hpp"
#include "sensors.hpp"

#include "cyclic_id.hpp"

// Address claim messages below

void send_STMM_18EEFF80(){
    
    msg.id = 418316160;
    // flag as extended id
    msg.flags.extended = 1;
    msg.len = 8;

    // msg.buf[0] = 0x80;      // address claim
    msg.buf[0] = 0xF3;      // address claim
    msg.buf[1] = 0x00;      // address claim
    msg.buf[2] = 0x80;      // address claim
    msg.buf[3] = 0xF3;      // destination (target address)
    msg.buf[4] = 0 << 3;    // thermistor module number << 3 (0x00)
    //msg.buf[4] = 0x00;
    msg.buf[5] = 0x40;      // constant 1
    msg.buf[6] = 0x1E;      // constant 2
    msg.buf[7] = 0x90;      // constant 3

    cbus2.write(msg);
}

void send_STMM_18EEFF81(){
    
    msg.id = 418316161;
    msg.flags.extended = 1;
    msg.len = 8;

    msg.buf[0] = 0xF3;      // address claim
    msg.buf[1] = 0x00;      // address claim
    msg.buf[2] = 0x81;      // address claim
    msg.buf[3] = 0xF3;      // destination (target address)
    msg.buf[4] = 1 << 3;    // thermistor module number << 3
    msg.buf[5] = 0x40;      // constant 1
    msg.buf[6] = 0x1E;      // constant 2
    msg.buf[7] = 0x90;      // constant 3

    cbus2.write(msg);
}

void send_STMM_1839F380(const int &seg) {

    msg.id = 406451072;
    // msg.id = 2553934720;
    // msg.id = 128;
    msg.flags.extended = 1;
    // msg.id = 128;
    // msg.flags.extended = 0;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    int min = static_cast<int>(get_min_temp(sorted_module_temps));
    int max = static_cast<int>(get_max_temp(sorted_module_temps));
    int avg = static_cast<int>(get_avg_temp(module_temps));
    int min_id = get_min_id(sorted_module_temps);
    int max_id = get_max_id(sorted_module_temps);
    int average = static_cast<int>(get_avg_temp(module_temps));

    // int teensy_id = counter;
    // int global_id = get_global_id(counter, module_temps);

    // Serial.println("global_id: ");
    // Serial.println(global_id);

    // Serial.println("module_temps: ");
    // Serial.println(get_module_temp(counter, module_temps));

    // Serial.println("min: ");
    // Serial.println(min);

    // Serial.println("min_id: ");
    // Serial.println(min_id);

    // Serial.println("max: ");
    // Serial.println(max);

    // Serial.println("max_id: ");
    // Serial.println(max_id);
    
    // test message --- works
    // msg.buf[0] = 0x00; // thermistor module number
    // msg.buf[1] = 0x01; // lowest thermistor value
    // msg.buf[2] = 0x11; // highest thermistor value
    // msg.buf[3] = 0x01; // average thermistor value
    // msg.buf[4] = 0x01; // number of thermistors enabled
    // msg.buf[5] = 0x01; // ID of the module with the highest raw value
    // msg.buf[6] = 0x00; // ID of the module with the lowest raw value
    // msg.buf[7] = 0x56; // checksum

    msg.buf[0] = 0x00; // thermistor module number
    msg.buf[1] = min; // lowest thermistor value
    msg.buf[2] = max; // highest thermistor value
    msg.buf[3] = avg; // average thermistor value
    msg.buf[4] = 0x0C; // number of thermistors enabled (12)
    msg.buf[5] = max_id; // ID of the module with the highest raw value
    msg.buf[6] = min_id; // ID of the module with the lowest raw value
    msg.buf[7] = msg.buf[0] + msg.buf[1] + msg.buf[2] + msg.buf[3] +
                msg.buf[4] + msg.buf[5] + msg.buf[6] + 0x39 + 0x08; // checksum

    cbus2.write(msg);
}

// do i need to remove the 1838F380 message?

// void send_STMM_1838F380(const int &seg){
    
//     msg.id = 406385536;
//     // flag as extended id
//     msg.flags.extended = 1;
//     msg.len = 8;

//     // msg.buf[0] = 0x80;      // address claim
//     msg.buf[0] = 0x00;      // thermistor ID relative to all modules #1
//     msg.buf[1] = 0x01;      // thermistor ID relative to all modules #2
//     msg.buf[2] = 0x42;      // current thermistor value
//     msg.buf[3] = 0x01;      // thermistor ID relative to current module
//     msg.buf[4] = 0x38;    // lowest thermistor value
//     //msg.buf[4] = 0x00;
//     msg.buf[5] = 0x45;      // highest thermistor value
//     msg.buf[6] = 0x01;      // highest thermistor ID on the module
//     msg.buf[7] = 0x01;      // lowest thermistor ID on the module

//     cbus2.write(msg);
// }

/*
////////////////////////////////////////////////////////////////////////////////////////
/ BELOW ARE THE MESSAGES THAT ARE BROADCASTED ON THE BUS TO MODULES OTHER THAN THE BMS /
////////////////////////////////////////////////////////////////////////////////////////
*/

void send_STMM_300() {
    // static definition - only defined once (like a global variable, but is local to this function only)
    static StateCounter ctr;

    // update per message
    msg.id = 300;
    msg.flags.extended = 0;
    msg.len = 8;

    // automatically does calcs
    STMM_segmentTemp100 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_0.avg());
    STMM_segmentTemp101 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_1.avg());
    STMM_segmentTemp102 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_2.avg());

    // load up the message buffer
    // Each message contains a counter and 3 signals
    // Each signal is 16 bits, so they take up two spots in the message, hence the 8-bit shift
    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp100.can_value();
    msg.buf[3] = STMM_segmentTemp100.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp101.can_value();
    msg.buf[5] = STMM_segmentTemp101.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp102.can_value();
    msg.buf[7] = STMM_segmentTemp102.can_value() >> 8;

    // send the message
    cbus2.write(msg);
}

void send_STMM_301() {
    static StateCounter ctr;

    msg.id = 301;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp103 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_3.avg());
    STMM_segmentTemp104 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_4.avg());
    STMM_segmentTemp105 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_5.avg());

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp103.can_value();
    msg.buf[3] = STMM_segmentTemp103.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp104.can_value();
    msg.buf[5] = STMM_segmentTemp104.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp105.can_value();
    msg.buf[7] = STMM_segmentTemp105.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_302() {
    static StateCounter ctr;

    msg.id = 302;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp106 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_6.avg());
    STMM_segmentTemp107 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_7.avg());
    STMM_segmentTemp108 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_8.avg());

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp106.can_value();
    msg.buf[3] = STMM_segmentTemp106.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp107.can_value();
    msg.buf[5] = STMM_segmentTemp107.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp108.can_value();
    msg.buf[7] = STMM_segmentTemp108.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_303() {
    static StateCounter ctr;

    msg.id = 303;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp109 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_9.avg());
    STMM_segmentTemp110 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_10.avg());
    STMM_segmentTemp111 = voltage_to_ENEPAQ_cell_temp(seg_1_mod_11.avg());

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp109.can_value();
    msg.buf[3] = STMM_segmentTemp109.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp110.can_value();
    msg.buf[5] = STMM_segmentTemp110.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp111.can_value();
    msg.buf[7] = STMM_segmentTemp111.can_value() >> 8;

    cbus2.write(msg);
}

void send_can_1(const int &seg) {
    // static EasyTimer STMM_18EEFF80_timer(5); // 5 Hz (200ms)
    // if (STMM_18EEFF80_timer.isup()){
    //     send_STMM_18EEFF80();
    // }
    
    static EasyTimer STMM_1839F380_timer(10); // 10 Hz (100ms)
    if(STMM_1839F380_timer.isup()) {
        send_STMM_1839F380(seg);
        // send_STMM_1838F380(seg);
        // here so that overflow doesn't become an issue for whatever reason
        // if I keep this here, that means having the modulus operator is unnecessarily redundant
        // if (counter_1 >= 11) {
        //     counter_1 = 0;
        // } else {
        //     counter_1 += 1;
        // }
    }

    static EasyTimer STMM_300_timer(1); // 1Hz
    if(STMM_300_timer.isup()) {
        send_STMM_300();
    }

    static EasyTimer STMM_301_timer(1);
    if(STMM_301_timer.isup()) {
        send_STMM_301();
    }

    static EasyTimer STMM_302_timer(1);
    if(STMM_302_timer.isup()) {
        send_STMM_302();
    }

    static EasyTimer STMM_303_timer(1);
    if(STMM_303_timer.isup()) {
        send_STMM_303();
    }
}

void send_can_2(const int &seg) {
    static EasyTimer STMM_18EEFF81_timer(5); // 5 Hz (200ms)
    if (STMM_18EEFF81_timer.isup()){
        send_STMM_18EEFF81();
    }
    
    // static EasyTimer STMM_1838F381_timer(10);
    // if(STMM_1838F381_timer.isup()) {
    //     send_STMM_1838F381(counter_2, seg);
    //     // if (counter_2 >= 11) {
    //     //     counter_2 = 0;
    //     // } else {
    //     //     counter_2 += 1;
    //     // }
    // }

    // static EasyTimer STMM_304_timer(1);
    // if(STMM_304_timer.isup()) {
    //     send_STMM_304();
    // }

    // static EasyTimer STMM_305_timer(1);
    // if(STMM_305_timer.isup()) {
    //     send_STMM_305();
    // }

    // static EasyTimer STMM_306_timer(1);
    // if(STMM_306_timer.isup()) {
    //     send_STMM_306();
    // }

    // static EasyTimer STMM_307_timer(1);
    // if(STMM_307_timer.isup()) {
    //     send_STMM_307();
    // }
}

#endif

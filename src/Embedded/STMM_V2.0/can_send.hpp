#ifndef CAN_SEND_HPP
#define CAN_SEND_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

#include "cyclic_id.hpp"

/*
///////////////////////////////////////////////////////////////////
/ BELOW ARE THE MESSAGES THAT ARE UNICASTED ON THE BUS TO THE BMS /
///////////////////////////////////////////////////////////////////
*/

void send_STMM_1839F380(const int &seg) {

    msg.id = 406451072;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    STMM_seg1ThermModNum = 0x00;
    STMM_seg1ThermValLow = clamp(get_min_temp(sorted_module_temps));
    STMM_seg1ThermValHigh = clamp(get_max_temp(sorted_module_temps));
    STMM_seg1ThermValAvg = clamp(get_avg_temp(module_temps));
    STMM_seg1ThermsEnabled = 0x0A;
    STMM_seg1ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg1ThermIDLow = get_min_id(sorted_module_temps);
    
    // // test message --- works
    // msg.buf[0] = 0x00; // thermistor module number
    // msg.buf[1] = 0x01; // lowest thermistor value
    // msg.buf[2] = 0x11; // highest thermistor value
    // msg.buf[3] = 0x01; // average thermistor value
    // msg.buf[4] = 0x01; // number of thermistors enabled
    // msg.buf[5] = 0x01; // ID of the module with the highest raw value
    // msg.buf[6] = 0x00; // ID of the module with the lowest raw value
    // msg.buf[7] = 0x56; // checksum

    msg.buf[0] = STMM_seg1ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg1ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg1ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg1ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg1ThermsEnabled.can_value(); // number of thermistors enabled (10)
    msg.buf[5] = STMM_seg1ThermIDHigh.can_value(); // ID of the module with the highest raw value
    msg.buf[6] = STMM_seg1ThermIDLow.can_value(); // ID of the module with the lowest raw value
    msg.buf[7] = msg.buf[0] + msg.buf[1] + msg.buf[2] + msg.buf[3] +
                msg.buf[4] + msg.buf[5] + msg.buf[6] + 0x39 + 0x08; // checksum

    cbus2.write(msg);
}

void send_STMM_1839F381(const int &seg) {

    msg.id = 406451073;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    STMM_seg2ThermModNum = 0x01;
    STMM_seg2ThermValLow = clamp(get_min_temp(sorted_module_temps));
    STMM_seg2ThermValHigh = clamp(get_max_temp(sorted_module_temps));
    STMM_seg2ThermValAvg = clamp(get_avg_temp(module_temps));
    STMM_seg2ThermsEnabled = 0x0A;
    STMM_seg2ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg2ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg2ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg2ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg2ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg2ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg2ThermsEnabled.can_value(); // number of thermistors enabled (10)
    msg.buf[5] = STMM_seg2ThermIDHigh.can_value(); // ID of the module with the highest raw value
    msg.buf[6] = STMM_seg2ThermIDLow.can_value(); // ID of the module with the lowest raw value
    msg.buf[7] = msg.buf[0] + msg.buf[1] + msg.buf[2] + msg.buf[3] +
                msg.buf[4] + msg.buf[5] + msg.buf[6] + 0x39 + 0x08; // checksum

    cbus2.write(msg);
}

void send_STMM_1839F382(const int &seg) {

    msg.id = 406451074;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    STMM_seg3ThermModNum = 0x02;
    STMM_seg3ThermValLow = clamp(get_min_temp(sorted_module_temps));
    STMM_seg3ThermValHigh = clamp(get_max_temp(sorted_module_temps));
    STMM_seg3ThermValAvg = clamp(get_avg_temp(module_temps));
    STMM_seg3ThermsEnabled = 0x0A;
    STMM_seg3ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg3ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg3ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg3ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg3ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg3ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg3ThermsEnabled.can_value(); // number of thermistors enabled (10)
    msg.buf[5] = STMM_seg3ThermIDHigh.can_value(); // ID of the module with the highest raw value
    msg.buf[6] = STMM_seg3ThermIDLow.can_value(); // ID of the module with the lowest raw value
    msg.buf[7] = msg.buf[0] + msg.buf[1] + msg.buf[2] + msg.buf[3] +
                msg.buf[4] + msg.buf[5] + msg.buf[6] + 0x39 + 0x08; // checksum

    cbus2.write(msg);
}

void send_STMM_1839F383(const int &seg) {

    msg.id = 406451075;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    STMM_seg4ThermModNum = 0x03;
    STMM_seg4ThermValLow = clamp(get_min_temp(sorted_module_temps));
    STMM_seg4ThermValHigh = clamp(get_max_temp(sorted_module_temps));
    STMM_seg4ThermValAvg = clamp(get_avg_temp(module_temps));
    STMM_seg4ThermsEnabled = 0x0A;
    STMM_seg4ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg4ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg4ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg4ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg4ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg4ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg4ThermsEnabled.can_value(); // number of thermistors enabled (10)
    msg.buf[5] = STMM_seg4ThermIDHigh.can_value(); // ID of the module with the highest raw value
    msg.buf[6] = STMM_seg4ThermIDLow.can_value(); // ID of the module with the lowest raw value
    msg.buf[7] = msg.buf[0] + msg.buf[1] + msg.buf[2] + msg.buf[3] +
                msg.buf[4] + msg.buf[5] + msg.buf[6] + 0x39 + 0x08; // checksum

    cbus2.write(msg);
}

void send_STMM_1839F384(const int &seg) {

    msg.id = 406451076;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    STMM_seg5ThermModNum = 0x04;
    STMM_seg5ThermValLow = clamp(get_min_temp(sorted_module_temps));
    STMM_seg5ThermValHigh = clamp(get_max_temp(sorted_module_temps));
    STMM_seg5ThermValAvg = clamp(get_avg_temp(module_temps));
    STMM_seg5ThermsEnabled = 0x0A;
    STMM_seg5ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg5ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg5ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg5ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg5ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg5ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg5ThermsEnabled.can_value(); // number of thermistors enabled (10)
    msg.buf[5] = STMM_seg5ThermIDHigh.can_value(); // ID of the module with the highest raw value
    msg.buf[6] = STMM_seg5ThermIDLow.can_value(); // ID of the module with the lowest raw value
    msg.buf[7] = msg.buf[0] + msg.buf[1] + msg.buf[2] + msg.buf[3] +
                msg.buf[4] + msg.buf[5] + msg.buf[6] + 0x39 + 0x08; // checksum

    cbus2.write(msg);
}

void send_STMM_1839F385(const int &seg) {

    msg.id = 406451077;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    STMM_seg6ThermModNum = 0x05;
    STMM_seg6ThermValLow = clamp(get_min_temp(sorted_module_temps));
    STMM_seg6ThermValHigh = clamp(get_max_temp(sorted_module_temps));
    STMM_seg6ThermValAvg = clamp(get_avg_temp(module_temps));
    STMM_seg6ThermsEnabled = 0x0A;
    STMM_seg6ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg6ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg6ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg6ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg6ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg6ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg6ThermsEnabled.can_value(); // number of thermistors enabled (10)
    msg.buf[5] = STMM_seg6ThermIDHigh.can_value(); // ID of the module with the highest raw value
    msg.buf[6] = STMM_seg6ThermIDLow.can_value(); // ID of the module with the lowest raw value
    msg.buf[7] = msg.buf[0] + msg.buf[1] + msg.buf[2] + msg.buf[3] +
                msg.buf[4] + msg.buf[5] + msg.buf[6] + 0x39 + 0x08; // checksum

    cbus2.write(msg);
}

void send_STMM_1839F386(const int &seg) {

    msg.id = 406451078;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    STMM_seg7ThermModNum = 0x06;
    STMM_seg7ThermValLow = clamp(get_min_temp(sorted_module_temps));
    STMM_seg7ThermValHigh = clamp(get_max_temp(sorted_module_temps));
    STMM_seg7ThermValAvg = clamp(get_avg_temp(module_temps));
    STMM_seg7ThermsEnabled = 0x0A;
    STMM_seg7ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg7ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg7ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg7ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg7ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg7ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg7ThermsEnabled.can_value(); // number of thermistors enabled (10)
    msg.buf[5] = STMM_seg7ThermIDHigh.can_value(); // ID of the module with the highest raw value
    msg.buf[6] = STMM_seg7ThermIDLow.can_value(); // ID of the module with the lowest raw value
    msg.buf[7] = msg.buf[0] + msg.buf[1] + msg.buf[2] + msg.buf[3] +
                msg.buf[4] + msg.buf[5] + msg.buf[6] + 0x39 + 0x08; // checksum

    cbus2.write(msg);
}

void send_STMM_1839F387(const int &seg) {

    msg.id = 406451079;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    STMM_seg8ThermModNum = 0x07;
    STMM_seg8ThermValLow = clamp(get_min_temp(sorted_module_temps));
    STMM_seg8ThermValHigh = clamp(get_max_temp(sorted_module_temps));
    STMM_seg8ThermValAvg = clamp(get_avg_temp(module_temps));
    STMM_seg8ThermsEnabled = 0x0A;
    STMM_seg8ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg8ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg8ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg8ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg8ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg8ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg8ThermsEnabled.can_value(); // number of thermistors enabled (10)
    msg.buf[5] = STMM_seg8ThermIDHigh.can_value(); // ID of the module with the highest raw value
    msg.buf[6] = STMM_seg8ThermIDLow.can_value(); // ID of the module with the lowest raw value
    msg.buf[7] = msg.buf[0] + msg.buf[1] + msg.buf[2] + msg.buf[3] +
                msg.buf[4] + msg.buf[5] + msg.buf[6] + 0x39 + 0x08; // checksum

    cbus2.write(msg);
}

/*
////////////////////////////////////////////////////////////////////////////////////////
/ BELOW ARE THE MESSAGES THAT ARE BROADCASTED ON THE BUS TO MODULES OTHER THAN THE BMS /
////////////////////////////////////////////////////////////////////////////////////////
*/

void send_STMM_299(bool &step){
    static StateCounter ctr;

    msg.id = 299;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentSync = step;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentSync.can_value();
    msg.buf[3] = 0x00;
    msg.buf[4] = 0x00;
    msg.buf[5] = 0x00;
    msg.buf[6] = 0x00;
    msg.buf[7] = 0x00;

    cbus2.write(msg);
}

void send_STMM_300(const int &seg) {
    // static definition - only defined once (like a global variable, but is local to this function only)
    static StateCounter ctr;

    // update per message
    msg.id = 300;
    msg.flags.extended = 0;
    msg.len = 8;

    // automatically does calcs
    STMM_segmentTemp100 = get_mod_temps(seg).at(0).second;
    STMM_segmentTemp101 = get_mod_temps(seg).at(1).second;
    STMM_segmentTemp102 = get_mod_temps(seg).at(2).second;

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

    // Serial.println("Mod 0: ");
    // Serial.println(STMM_segmentTemp100.value());
    // Serial.println("Mod 1: ");
    // Serial.println(STMM_segmentTemp101.value());
    // Serial.println("Mod 2: ");
    // Serial.println(STMM_segmentTemp102.value());

    // send the message
    cbus2.write(msg);
}

void send_STMM_301(const int &seg) {
    static StateCounter ctr;

    msg.id = 301;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp103 = get_mod_temps(seg).at(3).second;
    STMM_segmentTemp104 = get_mod_temps(seg).at(4).second;
    STMM_segmentTemp105 = get_mod_temps(seg).at(5).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp103.can_value();
    msg.buf[3] = STMM_segmentTemp103.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp104.can_value();
    msg.buf[5] = STMM_segmentTemp104.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp105.can_value();
    msg.buf[7] = STMM_segmentTemp105.can_value() >> 8;

    // Serial.println("Mod 3: ");
    // Serial.println(STMM_segmentTemp103.value());
    // Serial.println("Mod 4: ");
    // Serial.println(STMM_segmentTemp104.value());
    // Serial.println("Mod 5: ");
    // Serial.println(STMM_segmentTemp105.value());

    cbus2.write(msg);
}

void send_STMM_302(const int &seg) {
    static StateCounter ctr;

    msg.id = 302;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp106 = get_mod_temps(seg).at(6).second;
    STMM_segmentTemp107 = get_mod_temps(seg).at(7).second;
    STMM_segmentTemp108 = get_mod_temps(seg).at(8).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp106.can_value();
    msg.buf[3] = STMM_segmentTemp106.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp107.can_value();
    msg.buf[5] = STMM_segmentTemp107.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp108.can_value();
    msg.buf[7] = STMM_segmentTemp108.can_value() >> 8;

    // Serial.println("Mod 6: ");
    // Serial.println(STMM_segmentTemp106.value());
    // Serial.println("Mod 7: ");
    // Serial.println(STMM_segmentTemp107.value());
    // Serial.println("Mod 8: ");
    // Serial.println(STMM_segmentTemp108.value());

    cbus2.write(msg);
}

void send_STMM_303(const int &seg) {
    static StateCounter ctr;

    msg.id = 303;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp109 = get_mod_temps(seg).at(9).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp109.can_value();
    msg.buf[3] = STMM_segmentTemp109.can_value() >> 8;
    msg.buf[4] = 0x00;
    msg.buf[5] = 0x00;
    msg.buf[6] = 0x00;
    msg.buf[7] = 0x00;

    // Serial.println("Mod 9: ");
    // Serial.println(STMM_segmentTemp109.value());

    cbus2.write(msg);
}

void send_STMM_304(const int &seg) {
    static StateCounter ctr;

    msg.id = 304;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp200 = get_mod_temps(seg).at(0).second;
    STMM_segmentTemp201 = get_mod_temps(seg).at(1).second;
    STMM_segmentTemp202 = get_mod_temps(seg).at(2).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp200.can_value();
    msg.buf[3] = STMM_segmentTemp200.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp201.can_value();
    msg.buf[5] = STMM_segmentTemp201.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp202.can_value();
    msg.buf[7] = STMM_segmentTemp202.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_305(const int &seg) {
    static StateCounter ctr;

    msg.id = 305;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp203 = get_mod_temps(seg).at(3).second;
    STMM_segmentTemp204 = get_mod_temps(seg).at(4).second;
    STMM_segmentTemp205 = get_mod_temps(seg).at(5).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp203.can_value();
    msg.buf[3] = STMM_segmentTemp203.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp204.can_value();
    msg.buf[5] = STMM_segmentTemp204.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp205.can_value();
    msg.buf[7] = STMM_segmentTemp205.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_306(const int &seg) {
    static StateCounter ctr;

    msg.id = 306;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp206 = get_mod_temps(seg).at(6).second;
    STMM_segmentTemp207 = get_mod_temps(seg).at(7).second;
    STMM_segmentTemp208 = get_mod_temps(seg).at(8).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp206.can_value();
    msg.buf[3] = STMM_segmentTemp206.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp207.can_value();
    msg.buf[5] = STMM_segmentTemp207.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp208.can_value();
    msg.buf[7] = STMM_segmentTemp208.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_307(const int &seg) {
    static StateCounter ctr;

    msg.id = 307;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp209 = get_mod_temps(seg).at(9).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp209.can_value();
    msg.buf[3] = STMM_segmentTemp209.can_value() >> 8;
    msg.buf[4] = 0x00;
    msg.buf[5] = 0x00;
    msg.buf[6] = 0x00;
    msg.buf[7] = 0x00;

    cbus2.write(msg);
}

void send_STMM_308(const int &seg) {
    static StateCounter ctr;

    msg.id = 308;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp300 = get_mod_temps(seg).at(0).second;
    STMM_segmentTemp301 = get_mod_temps(seg).at(1).second;
    STMM_segmentTemp302 = get_mod_temps(seg).at(2).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp300.can_value();
    msg.buf[3] = STMM_segmentTemp300.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp301.can_value();
    msg.buf[5] = STMM_segmentTemp301.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp302.can_value();
    msg.buf[7] = STMM_segmentTemp302.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_309(const int &seg) {
    static StateCounter ctr;

    msg.id = 309;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp303 = get_mod_temps(seg).at(3).second;
    STMM_segmentTemp304 = get_mod_temps(seg).at(4).second;
    STMM_segmentTemp305 = get_mod_temps(seg).at(5).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp303.can_value();
    msg.buf[3] = STMM_segmentTemp303.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp304.can_value();
    msg.buf[5] = STMM_segmentTemp304.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp305.can_value();
    msg.buf[7] = STMM_segmentTemp305.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_310(const int &seg) {
    static StateCounter ctr;

    msg.id = 310;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp306 = get_mod_temps(seg).at(6).second;
    STMM_segmentTemp307 = get_mod_temps(seg).at(7).second;
    STMM_segmentTemp308 = get_mod_temps(seg).at(8).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp306.can_value();
    msg.buf[3] = STMM_segmentTemp306.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp307.can_value();
    msg.buf[5] = STMM_segmentTemp307.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp308.can_value();
    msg.buf[7] = STMM_segmentTemp308.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_311(const int &seg) {
    static StateCounter ctr;

    msg.id = 311;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp309 = get_mod_temps(seg).at(9).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp309.can_value();
    msg.buf[3] = STMM_segmentTemp309.can_value() >> 8;
    msg.buf[4] = 0x00;
    msg.buf[5] = 0x00;
    msg.buf[6] = 0x00;
    msg.buf[7] = 0x00;

    cbus2.write(msg);
}

void send_STMM_312(const int &seg) {
    static StateCounter ctr;

    msg.id = 312;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp400 = get_mod_temps(seg).at(0).second;
    STMM_segmentTemp401 = get_mod_temps(seg).at(1).second;
    STMM_segmentTemp402 = get_mod_temps(seg).at(2).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp400.can_value();
    msg.buf[3] = STMM_segmentTemp400.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp401.can_value();
    msg.buf[5] = STMM_segmentTemp401.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp402.can_value();
    msg.buf[7] = STMM_segmentTemp402.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_313(const int &seg) {
    static StateCounter ctr;

    msg.id = 313;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp403 = get_mod_temps(seg).at(3).second;
    STMM_segmentTemp404 = get_mod_temps(seg).at(4).second;
    STMM_segmentTemp405 = get_mod_temps(seg).at(5).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp403.can_value();
    msg.buf[3] = STMM_segmentTemp403.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp404.can_value();
    msg.buf[5] = STMM_segmentTemp404.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp405.can_value();
    msg.buf[7] = STMM_segmentTemp405.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_314(const int &seg) {
    static StateCounter ctr;

    msg.id = 314;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp406 = get_mod_temps(seg).at(6).second;
    STMM_segmentTemp407 = get_mod_temps(seg).at(7).second;
    STMM_segmentTemp408 = get_mod_temps(seg).at(8).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp406.can_value();
    msg.buf[3] = STMM_segmentTemp406.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp407.can_value();
    msg.buf[5] = STMM_segmentTemp407.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp408.can_value();
    msg.buf[7] = STMM_segmentTemp408.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_315(const int &seg) {
    static StateCounter ctr;

    msg.id = 315;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp409 = get_mod_temps(seg).at(9).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp409.can_value();
    msg.buf[3] = STMM_segmentTemp409.can_value() >> 8;
    msg.buf[4] = 0x00;
    msg.buf[5] = 0x00;
    msg.buf[6] = 0x00;
    msg.buf[7] = 0x00;

    cbus2.write(msg);
}

void send_STMM_316(const int &seg) {
    static StateCounter ctr;

    msg.id = 316;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp500 = get_mod_temps(seg).at(0).second;
    STMM_segmentTemp501 = get_mod_temps(seg).at(1).second;
    STMM_segmentTemp502 = get_mod_temps(seg).at(2).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp500.can_value();
    msg.buf[3] = STMM_segmentTemp500.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp501.can_value();
    msg.buf[5] = STMM_segmentTemp501.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp502.can_value();
    msg.buf[7] = STMM_segmentTemp502.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_317(const int &seg) {
    static StateCounter ctr;

    msg.id = 317;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp503 = get_mod_temps(seg).at(3).second;
    STMM_segmentTemp504 = get_mod_temps(seg).at(4).second;
    STMM_segmentTemp505 = get_mod_temps(seg).at(5).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp503.can_value();
    msg.buf[3] = STMM_segmentTemp503.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp504.can_value();
    msg.buf[5] = STMM_segmentTemp504.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp505.can_value();
    msg.buf[7] = STMM_segmentTemp505.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_318(const int &seg) {
    static StateCounter ctr;

    msg.id = 318;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp506 = get_mod_temps(seg).at(6).second;
    STMM_segmentTemp507 = get_mod_temps(seg).at(7).second;
    STMM_segmentTemp508 = get_mod_temps(seg).at(8).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp506.can_value();
    msg.buf[3] = STMM_segmentTemp506.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp507.can_value();
    msg.buf[5] = STMM_segmentTemp507.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp508.can_value();
    msg.buf[7] = STMM_segmentTemp508.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_319(const int &seg) {
    static StateCounter ctr;

    msg.id = 319;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp509 = get_mod_temps(seg).at(9).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp509.can_value();
    msg.buf[3] = STMM_segmentTemp509.can_value() >> 8;
    msg.buf[4] = 0x00;
    msg.buf[5] = 0x00;
    msg.buf[6] = 0x00;
    msg.buf[7] = 0x00;

    cbus2.write(msg);
}

void send_STMM_320(const int &seg) {
    static StateCounter ctr;

    msg.id = 320;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp600 = get_mod_temps(seg).at(0).second;
    STMM_segmentTemp601 = get_mod_temps(seg).at(1).second;
    STMM_segmentTemp602 = get_mod_temps(seg).at(2).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp600.can_value();
    msg.buf[3] = STMM_segmentTemp600.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp601.can_value();
    msg.buf[5] = STMM_segmentTemp601.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp602.can_value();
    msg.buf[7] = STMM_segmentTemp602.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_321(const int &seg) {
    static StateCounter ctr;

    msg.id = 321;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp603 = get_mod_temps(seg).at(3).second;
    STMM_segmentTemp604 = get_mod_temps(seg).at(4).second;
    STMM_segmentTemp605 = get_mod_temps(seg).at(5).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp603.can_value();
    msg.buf[3] = STMM_segmentTemp603.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp604.can_value();
    msg.buf[5] = STMM_segmentTemp604.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp605.can_value();
    msg.buf[7] = STMM_segmentTemp605.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_322(const int &seg) {
    static StateCounter ctr;

    msg.id = 322;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp606 = get_mod_temps(seg).at(6).second;
    STMM_segmentTemp607 = get_mod_temps(seg).at(7).second;
    STMM_segmentTemp608 = get_mod_temps(seg).at(8).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp606.can_value();
    msg.buf[3] = STMM_segmentTemp606.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp607.can_value();
    msg.buf[5] = STMM_segmentTemp607.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp608.can_value();
    msg.buf[7] = STMM_segmentTemp608.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_323(const int &seg) {
    static StateCounter ctr;

    msg.id = 323;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp609 = get_mod_temps(seg).at(9).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp609.can_value();
    msg.buf[3] = STMM_segmentTemp609.can_value() >> 8;
    msg.buf[4] = 0x00;
    msg.buf[5] = 0x00;
    msg.buf[6] = 0x00;
    msg.buf[7] = 0x00;

    cbus2.write(msg);
}

void send_STMM_324(const int &seg) {
    static StateCounter ctr;

    msg.id = 324;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp700 = get_mod_temps(seg).at(0).second;
    STMM_segmentTemp701 = get_mod_temps(seg).at(1).second;
    STMM_segmentTemp702 = get_mod_temps(seg).at(2).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp700.can_value();
    msg.buf[3] = STMM_segmentTemp700.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp701.can_value();
    msg.buf[5] = STMM_segmentTemp701.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp702.can_value();
    msg.buf[7] = STMM_segmentTemp702.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_325(const int &seg) {
    static StateCounter ctr;

    msg.id = 325;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp703 = get_mod_temps(seg).at(3).second;
    STMM_segmentTemp704 = get_mod_temps(seg).at(4).second;
    STMM_segmentTemp705 = get_mod_temps(seg).at(5).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp703.can_value();
    msg.buf[3] = STMM_segmentTemp703.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp704.can_value();
    msg.buf[5] = STMM_segmentTemp704.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp705.can_value();
    msg.buf[7] = STMM_segmentTemp705.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_326(const int &seg) {
    static StateCounter ctr;

    msg.id = 326;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp706 = get_mod_temps(seg).at(6).second;
    STMM_segmentTemp707 = get_mod_temps(seg).at(7).second;
    STMM_segmentTemp708 = get_mod_temps(seg).at(8).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp706.can_value();
    msg.buf[3] = STMM_segmentTemp706.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp707.can_value();
    msg.buf[5] = STMM_segmentTemp707.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp708.can_value();
    msg.buf[7] = STMM_segmentTemp708.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_327(const int &seg) {
    static StateCounter ctr;

    msg.id = 327;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp709 = get_mod_temps(seg).at(9).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp709.can_value();
    msg.buf[3] = STMM_segmentTemp709.can_value() >> 8;
    msg.buf[4] = 0x00;
    msg.buf[5] = 0x00;
    msg.buf[6] = 0x00;
    msg.buf[7] = 0x00;

    cbus2.write(msg);
}

void send_STMM_328(const int &seg) {
    static StateCounter ctr;

    msg.id = 328;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp800 = get_mod_temps(seg).at(0).second;
    STMM_segmentTemp801 = get_mod_temps(seg).at(1).second;
    STMM_segmentTemp802 = get_mod_temps(seg).at(2).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp800.can_value();
    msg.buf[3] = STMM_segmentTemp800.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp801.can_value();
    msg.buf[5] = STMM_segmentTemp801.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp802.can_value();
    msg.buf[7] = STMM_segmentTemp802.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_329(const int &seg) {
    static StateCounter ctr;

    msg.id = 329;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp803 = get_mod_temps(seg).at(3).second;
    STMM_segmentTemp804 = get_mod_temps(seg).at(4).second;
    STMM_segmentTemp805 = get_mod_temps(seg).at(5).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp803.can_value();
    msg.buf[3] = STMM_segmentTemp803.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp804.can_value();
    msg.buf[5] = STMM_segmentTemp804.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp805.can_value();
    msg.buf[7] = STMM_segmentTemp805.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_330(const int &seg) {
    static StateCounter ctr;

    msg.id = 330;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp806 = get_mod_temps(seg).at(6).second;
    STMM_segmentTemp807 = get_mod_temps(seg).at(7).second;
    STMM_segmentTemp808 = get_mod_temps(seg).at(8).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp806.can_value();
    msg.buf[3] = STMM_segmentTemp806.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp807.can_value();
    msg.buf[5] = STMM_segmentTemp807.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp808.can_value();
    msg.buf[7] = STMM_segmentTemp808.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_331(const int &seg) {
    static StateCounter ctr;

    msg.id = 331;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp809 = get_mod_temps(seg).at(9).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp809.can_value();
    msg.buf[3] = STMM_segmentTemp809.can_value() >> 8;
    msg.buf[4] = 0x00;
    msg.buf[5] = 0x00;
    msg.buf[6] = 0x00;
    msg.buf[7] = 0x00;

    cbus2.write(msg);
}

void send_STMM_332(const int &seg) {
    static StateCounter ctr;

    msg.id = 332;
    msg.flags.extended = 0;
    msg.len = 8;

    // Serial.println(STMM_segmentVolt100.can_value());

    STMM_segmentVolt100 = module_voltage_0;
    STMM_segmentVolt101 = module_voltage_1;
    STMM_segmentVolt102 = module_voltage_2;

    // Serial.println(STMM_segmentVolt100.can_value());

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt100.can_value();
    msg.buf[3] = STMM_segmentVolt100.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt101.can_value();
    msg.buf[5] = STMM_segmentVolt101.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt102.can_value();
    msg.buf[7] = STMM_segmentVolt102.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_333(const int &seg) {
    static StateCounter ctr;

    msg.id = 333;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt103 = module_voltage_3;
    STMM_segmentVolt104 = module_voltage_4;
    STMM_segmentVolt105 = module_voltage_5;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt103.can_value();
    msg.buf[3] = STMM_segmentVolt103.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt104.can_value();
    msg.buf[5] = STMM_segmentVolt104.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt105.can_value();
    msg.buf[7] = STMM_segmentVolt105.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_334(const int &seg) {
    static StateCounter ctr;

    msg.id = 334;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt106 = module_voltage_6;
    STMM_segmentVolt107 = module_voltage_7;
    STMM_segmentVolt108 = module_voltage_8;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt106.can_value();
    msg.buf[3] = STMM_segmentVolt106.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt107.can_value();
    msg.buf[5] = STMM_segmentVolt107.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt108.can_value();
    msg.buf[7] = STMM_segmentVolt108.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_335(const int &seg) {
    static StateCounter ctr;

    msg.id = 335;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt109 = module_voltage_9;
    // STMM_segmentVolt110 = module_voltage_10;
    // STMM_segmentVolt111 = module_voltage_11;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt109.can_value();
    msg.buf[3] = STMM_segmentVolt109.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt110.can_value();
    msg.buf[5] = STMM_segmentVolt110.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt111.can_value();
    msg.buf[7] = STMM_segmentVolt111.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_336(const int &seg) {
    static StateCounter ctr;

    msg.id = 336;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt200 = module_voltage_0;
    STMM_segmentVolt201 = module_voltage_1;
    STMM_segmentVolt202 = module_voltage_2;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt200.can_value();
    msg.buf[3] = STMM_segmentVolt200.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt201.can_value();
    msg.buf[5] = STMM_segmentVolt201.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt202.can_value();
    msg.buf[7] = STMM_segmentVolt202.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_337(const int &seg) {
    static StateCounter ctr;

    msg.id = 337;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt203 = module_voltage_3;
    STMM_segmentVolt204 = module_voltage_4;
    STMM_segmentVolt205 = module_voltage_5;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt203.can_value();
    msg.buf[3] = STMM_segmentVolt203.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt204.can_value();
    msg.buf[5] = STMM_segmentVolt204.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt205.can_value();
    msg.buf[7] = STMM_segmentVolt205.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_338(const int &seg) {
    static StateCounter ctr;

    msg.id = 338;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt206 = module_voltage_6;
    STMM_segmentVolt207 = module_voltage_7;
    STMM_segmentVolt208 = module_voltage_8;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt206.can_value();
    msg.buf[3] = STMM_segmentVolt206.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt207.can_value();
    msg.buf[5] = STMM_segmentVolt207.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt208.can_value();
    msg.buf[7] = STMM_segmentVolt208.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_339(const int &seg) {
    static StateCounter ctr;

    msg.id = 339;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt209 = module_voltage_9;
    // STMM_segmentVolt210 = module_voltage_10;
    // STMM_segmentVolt211 = module_voltage_11;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt209.can_value();
    msg.buf[3] = STMM_segmentVolt209.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt210.can_value();
    msg.buf[5] = STMM_segmentVolt210.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt211.can_value();
    msg.buf[7] = STMM_segmentVolt211.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_340(const int &seg) {
    static StateCounter ctr;

    msg.id = 340;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt300 = module_voltage_0;
    STMM_segmentVolt301 = module_voltage_1;
    STMM_segmentVolt302 = module_voltage_2;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt300.can_value();
    msg.buf[3] = STMM_segmentVolt300.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt301.can_value();
    msg.buf[5] = STMM_segmentVolt301.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt302.can_value();
    msg.buf[7] = STMM_segmentVolt302.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_341(const int &seg) {
    static StateCounter ctr;

    msg.id = 341;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt303 = module_voltage_3;
    STMM_segmentVolt304 = module_voltage_4;
    STMM_segmentVolt305 = module_voltage_5;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt303.can_value();
    msg.buf[3] = STMM_segmentVolt303.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt304.can_value();
    msg.buf[5] = STMM_segmentVolt304.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt305.can_value();
    msg.buf[7] = STMM_segmentVolt305.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_342(const int &seg) {
    static StateCounter ctr;

    msg.id = 342;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt306 = module_voltage_6;
    STMM_segmentVolt307 = module_voltage_7;
    STMM_segmentVolt308 = module_voltage_8;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt306.can_value();
    msg.buf[3] = STMM_segmentVolt306.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt307.can_value();
    msg.buf[5] = STMM_segmentVolt307.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt308.can_value();
    msg.buf[7] = STMM_segmentVolt308.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_343(const int &seg) {
    static StateCounter ctr;

    msg.id = 343;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt309 = module_voltage_9;
    // STMM_segmentVolt310 = module_voltage_10;
    // STMM_segmentVolt311 = module_voltage_11;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt309.can_value();
    msg.buf[3] = STMM_segmentVolt309.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt310.can_value();
    msg.buf[5] = STMM_segmentVolt310.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt311.can_value();
    msg.buf[7] = STMM_segmentVolt311.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_344(const int &seg) {
    static StateCounter ctr;

    msg.id = 344;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt400 = module_voltage_0;
    STMM_segmentVolt401 = module_voltage_1;
    STMM_segmentVolt402 = module_voltage_2;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt400.can_value();
    msg.buf[3] = STMM_segmentVolt400.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt401.can_value();
    msg.buf[5] = STMM_segmentVolt401.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt402.can_value();
    msg.buf[7] = STMM_segmentVolt402.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_345(const int &seg) {
    static StateCounter ctr;

    msg.id = 345;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt403 = module_voltage_3;
    STMM_segmentVolt404 = module_voltage_4;
    STMM_segmentVolt405 = module_voltage_5;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt403.can_value();
    msg.buf[3] = STMM_segmentVolt403.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt404.can_value();
    msg.buf[5] = STMM_segmentVolt404.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt405.can_value();
    msg.buf[7] = STMM_segmentVolt405.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_346(const int &seg) {
    static StateCounter ctr;

    msg.id = 346;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt406 = module_voltage_6;
    STMM_segmentVolt407 = module_voltage_7;
    STMM_segmentVolt408 = module_voltage_8;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt406.can_value();
    msg.buf[3] = STMM_segmentVolt406.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt407.can_value();
    msg.buf[5] = STMM_segmentVolt407.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt408.can_value();
    msg.buf[7] = STMM_segmentVolt408.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_347(const int &seg) {
    static StateCounter ctr;

    msg.id = 347;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt409 = module_voltage_9;
    // STMM_segmentVolt410 = module_voltage_10;
    // STMM_segmentVolt411 = module_voltage_11;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt409.can_value();
    msg.buf[3] = STMM_segmentVolt409.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt410.can_value();
    msg.buf[5] = STMM_segmentVolt410.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt411.can_value();
    msg.buf[7] = STMM_segmentVolt411.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_348(const int &seg) {
    static StateCounter ctr;

    msg.id = 348;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt500 = module_voltage_0;
    STMM_segmentVolt501 = module_voltage_1;
    STMM_segmentVolt502 = module_voltage_2;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt500.can_value();
    msg.buf[3] = STMM_segmentVolt500.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt501.can_value();
    msg.buf[5] = STMM_segmentVolt501.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt502.can_value();
    msg.buf[7] = STMM_segmentVolt502.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_349(const int &seg) {
    static StateCounter ctr;

    msg.id = 349;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt503 = module_voltage_3;
    STMM_segmentVolt504 = module_voltage_4;
    STMM_segmentVolt505 = module_voltage_5;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt503.can_value();
    msg.buf[3] = STMM_segmentVolt503.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt504.can_value();
    msg.buf[5] = STMM_segmentVolt504.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt505.can_value();
    msg.buf[7] = STMM_segmentVolt505.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_350(const int &seg) {
    static StateCounter ctr;

    msg.id = 350;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt506 = module_voltage_6;
    STMM_segmentVolt507 = module_voltage_7;
    STMM_segmentVolt508 = module_voltage_8;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt506.can_value();
    msg.buf[3] = STMM_segmentVolt506.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt507.can_value();
    msg.buf[5] = STMM_segmentVolt507.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt508.can_value();
    msg.buf[7] = STMM_segmentVolt508.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_351(const int &seg) {
    static StateCounter ctr;

    msg.id = 351;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt509 = module_voltage_9;
    // STMM_segmentVolt510 = module_voltage_10;
    // STMM_segmentVolt511 = module_voltage_11;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt509.can_value();
    msg.buf[3] = STMM_segmentVolt509.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt510.can_value();
    msg.buf[5] = STMM_segmentVolt510.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt511.can_value();
    msg.buf[7] = STMM_segmentVolt511.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_352(const int &seg) {
    static StateCounter ctr;

    msg.id = 352;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt600 = module_voltage_0;
    STMM_segmentVolt601 = module_voltage_1;
    STMM_segmentVolt602 = module_voltage_2;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt600.can_value();
    msg.buf[3] = STMM_segmentVolt600.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt601.can_value();
    msg.buf[5] = STMM_segmentVolt601.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt602.can_value();
    msg.buf[7] = STMM_segmentVolt602.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_353(const int &seg) {
    static StateCounter ctr;

    msg.id = 353;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt603 = module_voltage_3;
    STMM_segmentVolt604 = module_voltage_4;
    STMM_segmentVolt605 = module_voltage_5;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt603.can_value();
    msg.buf[3] = STMM_segmentVolt603.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt604.can_value();
    msg.buf[5] = STMM_segmentVolt604.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt605.can_value();
    msg.buf[7] = STMM_segmentVolt605.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_354(const int &seg) {
    static StateCounter ctr;

    msg.id = 354;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt606 = module_voltage_6;
    STMM_segmentVolt607 = module_voltage_7;
    STMM_segmentVolt608 = module_voltage_8;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt606.can_value();
    msg.buf[3] = STMM_segmentVolt606.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt607.can_value();
    msg.buf[5] = STMM_segmentVolt607.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt608.can_value();
    msg.buf[7] = STMM_segmentVolt608.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_355(const int &seg) {
    static StateCounter ctr;

    msg.id = 355;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt609 = module_voltage_9;
    // STMM_segmentVolt610 = module_voltage_10;
    // STMM_segmentVolt611 = module_voltage_11;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt609.can_value();
    msg.buf[3] = STMM_segmentVolt609.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt610.can_value();
    msg.buf[5] = STMM_segmentVolt610.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt611.can_value();
    msg.buf[7] = STMM_segmentVolt611.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_356(const int &seg) {
    static StateCounter ctr;

    msg.id = 356;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt700 = module_voltage_0;
    STMM_segmentVolt701 = module_voltage_1;
    STMM_segmentVolt702 = module_voltage_2;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt700.can_value();
    msg.buf[3] = STMM_segmentVolt700.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt701.can_value();
    msg.buf[5] = STMM_segmentVolt701.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt702.can_value();
    msg.buf[7] = STMM_segmentVolt702.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_357(const int &seg) {
    static StateCounter ctr;

    msg.id = 357;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt703 = module_voltage_3;
    STMM_segmentVolt704 = module_voltage_4;
    STMM_segmentVolt705 = module_voltage_5;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt703.can_value();
    msg.buf[3] = STMM_segmentVolt703.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt704.can_value();
    msg.buf[5] = STMM_segmentVolt704.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt705.can_value();
    msg.buf[7] = STMM_segmentVolt705.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_358(const int &seg) {
    static StateCounter ctr;

    msg.id = 358;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt706 = module_voltage_6;
    STMM_segmentVolt707 = module_voltage_7;
    STMM_segmentVolt708 = module_voltage_8;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt706.can_value();
    msg.buf[3] = STMM_segmentVolt706.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt707.can_value();
    msg.buf[5] = STMM_segmentVolt707.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt708.can_value();
    msg.buf[7] = STMM_segmentVolt708.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_359(const int &seg) {
    static StateCounter ctr;

    msg.id = 359;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt709 = module_voltage_9;
    // STMM_segmentVolt710 = module_voltage_10;
    // STMM_segmentVolt711 = module_voltage_11;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt709.can_value();
    msg.buf[3] = STMM_segmentVolt709.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt710.can_value();
    msg.buf[5] = STMM_segmentVolt710.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt711.can_value();
    msg.buf[7] = STMM_segmentVolt711.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_360(const int &seg) {
    static StateCounter ctr;

    msg.id = 360;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt800 = module_voltage_0;
    STMM_segmentVolt801 = module_voltage_1;
    STMM_segmentVolt802 = module_voltage_2;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt800.can_value();
    msg.buf[3] = STMM_segmentVolt800.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt801.can_value();
    msg.buf[5] = STMM_segmentVolt801.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt802.can_value();
    msg.buf[7] = STMM_segmentVolt802.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_361(const int &seg) {
    static StateCounter ctr;

    msg.id = 361;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt803 = module_voltage_3;
    STMM_segmentVolt804 = module_voltage_4;
    STMM_segmentVolt805 = module_voltage_5;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt803.can_value();
    msg.buf[3] = STMM_segmentVolt803.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt804.can_value();
    msg.buf[5] = STMM_segmentVolt804.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt805.can_value();
    msg.buf[7] = STMM_segmentVolt805.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_362(const int &seg) {
    static StateCounter ctr;

    msg.id = 362;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt806 = module_voltage_6;
    STMM_segmentVolt807 = module_voltage_7;
    STMM_segmentVolt808 = module_voltage_8;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt806.can_value();
    msg.buf[3] = STMM_segmentVolt806.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt807.can_value();
    msg.buf[5] = STMM_segmentVolt807.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt808.can_value();
    msg.buf[7] = STMM_segmentVolt808.can_value() >> 8;

    cbus2.write(msg);
}

void send_STMM_363(const int &seg) {
    static StateCounter ctr;

    msg.id = 363;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentVolt809 = module_voltage_9;
    // STMM_segmentVolt810 = module_voltage_10;
    // STMM_segmentVolt811 = module_voltage_11;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentVolt809.can_value();
    msg.buf[3] = STMM_segmentVolt809.can_value() >> 8;
    msg.buf[4] = STMM_segmentVolt810.can_value();
    msg.buf[5] = STMM_segmentVolt810.can_value() >> 8;
    msg.buf[6] = STMM_segmentVolt811.can_value();
    msg.buf[7] = STMM_segmentVolt811.can_value() >> 8;

    cbus2.write(msg);
}

/*
////////////
/ SEND IT! /
////////////
*/

void send_step(bool &step) {
    static EasyTimer STMM_299_timer(100); // 100 Hz (10ms)
    if(STMM_299_timer.isup()) {
        send_STMM_299(step);
    }
}

void send_can_1(const int &seg) {
    static EasyTimer STMM_1839F380_timer(10); // 10 Hz (100ms)
    if(STMM_1839F380_timer.isup()) {
        send_STMM_1839F380(seg);
    }

    static EasyTimer STMM_300_timer(1); // 1Hz
    if(STMM_300_timer.isup()) {
        send_STMM_300(seg);
    }

    static EasyTimer STMM_301_timer(1);
    if(STMM_301_timer.isup()) {
        send_STMM_301(seg);
    }

    static EasyTimer STMM_302_timer(1);
    if(STMM_302_timer.isup()) {
        send_STMM_302(seg);
    }

    static EasyTimer STMM_303_timer(1);
    if(STMM_303_timer.isup()) {
        send_STMM_303(seg);
    }

    static EasyTimer STMM_332_timer(1);
    if(STMM_332_timer.isup()) {
        send_STMM_332(seg);
    }

    static EasyTimer STMM_333_timer(1);
    if(STMM_333_timer.isup()) {
        send_STMM_333(seg);
    }

    static EasyTimer STMM_334_timer(1);
    if(STMM_334_timer.isup()) {
        send_STMM_334(seg);
    }

    static EasyTimer STMM_335_timer(1);
    if(STMM_335_timer.isup()) {
        send_STMM_335(seg);
    }

}

void send_can_2(const int &seg) {
    static EasyTimer STMM_1839F381_timer(10); // 10 Hz (100ms)
    if(STMM_1839F381_timer.isup()) {
        send_STMM_1839F381(seg);
    }

    static EasyTimer STMM_304_timer(1); // 1Hz
    if(STMM_304_timer.isup()) {
        send_STMM_304(seg);
    }

    static EasyTimer STMM_305_timer(1);
    if(STMM_305_timer.isup()) {
        send_STMM_305(seg);
    }

    static EasyTimer STMM_306_timer(1);
    if(STMM_306_timer.isup()) {
        send_STMM_306(seg);
    }

    static EasyTimer STMM_307_timer(1);
    if(STMM_307_timer.isup()) {
        send_STMM_307(seg);
    }

    static EasyTimer STMM_336_timer(1);
    if(STMM_336_timer.isup()) {
        send_STMM_335(seg);
    }

    static EasyTimer STMM_337_timer(1);
    if(STMM_337_timer.isup()) {
        send_STMM_337(seg);
    }

    static EasyTimer STMM_338_timer(1);
    if(STMM_338_timer.isup()) {
        send_STMM_338(seg);
    }

    static EasyTimer STMM_339_timer(1);
    if(STMM_339_timer.isup()) {
        send_STMM_339(seg);
    }
}

void send_can_3(const int &seg) {
    static EasyTimer STMM_1839F382_timer(10); // 10 Hz (100ms)
    if(STMM_1839F382_timer.isup()) {
        send_STMM_1839F382(seg);
    }

    static EasyTimer STMM_308_timer(1); // 1Hz
    if(STMM_308_timer.isup()) {
        send_STMM_308(seg);
    }

    static EasyTimer STMM_309_timer(1);
    if(STMM_309_timer.isup()) {
        send_STMM_309(seg);
    }

    static EasyTimer STMM_310_timer(1);
    if(STMM_310_timer.isup()) {
        send_STMM_310(seg);
    }

    static EasyTimer STMM_311_timer(1);
    if(STMM_311_timer.isup()) {
        send_STMM_311(seg);
    }

    static EasyTimer STMM_340_timer(1);
    if(STMM_340_timer.isup()) {
        send_STMM_340(seg);
    }

    static EasyTimer STMM_341_timer(1);
    if(STMM_341_timer.isup()) {
        send_STMM_341(seg);
    }

    static EasyTimer STMM_342_timer(1);
    if(STMM_342_timer.isup()) {
        send_STMM_342(seg);
    }

    static EasyTimer STMM_343_timer(1);
    if(STMM_343_timer.isup()) {
        send_STMM_343(seg);
    }
}

void send_can_4(const int &seg) {
    static EasyTimer STMM_1839F383_timer(10); // 10 Hz (100ms)
    if(STMM_1839F383_timer.isup()) {
        send_STMM_1839F383(seg);
    }

    static EasyTimer STMM_312_timer(1); // 1Hz
    if(STMM_312_timer.isup()) {
        send_STMM_312(seg);
    }

    static EasyTimer STMM_313_timer(1);
    if(STMM_313_timer.isup()) {
        send_STMM_313(seg);
    }

    static EasyTimer STMM_314_timer(1);
    if(STMM_314_timer.isup()) {
        send_STMM_314(seg);
    }

    static EasyTimer STMM_315_timer(1);
    if(STMM_315_timer.isup()) {
        send_STMM_315(seg);
    }

    static EasyTimer STMM_344_timer(1);
    if(STMM_344_timer.isup()) {
        send_STMM_344(seg);
    }
    
    static EasyTimer STMM_345_timer(1);
    if(STMM_345_timer.isup()) {
        send_STMM_345(seg);
    }

    static EasyTimer STMM_346_timer(1);
    if(STMM_346_timer.isup()) {
        send_STMM_346(seg);
    }

    static EasyTimer STMM_347_timer(1);
    if(STMM_347_timer.isup()) {
        send_STMM_347(seg);
    }
}

void send_can_5(const int &seg) {
    static EasyTimer STMM_1839F384_timer(10); // 10 Hz (100ms)
    if(STMM_1839F384_timer.isup()) {
        send_STMM_1839F384(seg);
    }

    static EasyTimer STMM_316_timer(1); // 1Hz
    if(STMM_316_timer.isup()) {
        send_STMM_316(seg);
    }

    static EasyTimer STMM_317_timer(1);
    if(STMM_317_timer.isup()) {
        send_STMM_317(seg);
    }

    static EasyTimer STMM_318_timer(1);
    if(STMM_318_timer.isup()) {
        send_STMM_318(seg);
    }

    static EasyTimer STMM_319_timer(1);
    if(STMM_319_timer.isup()) {
        send_STMM_319(seg);
    }

    static EasyTimer STMM_348_timer(1);
    if(STMM_348_timer.isup()) {
        send_STMM_348(seg);
    }

    static EasyTimer STMM_349_timer(1);
    if(STMM_349_timer.isup()) {
        send_STMM_349(seg);
    }

    static EasyTimer STMM_350_timer(1);
    if(STMM_350_timer.isup()) {
        send_STMM_350(seg);
    }

    static EasyTimer STMM_351_timer(1);
    if(STMM_351_timer.isup()) {
        send_STMM_351(seg);
    }
}

void send_can_6(const int &seg) {
    static EasyTimer STMM_1839F385_timer(10); // 10 Hz (100ms)
    if(STMM_1839F385_timer.isup()) {
        send_STMM_1839F385(seg);
    }

    static EasyTimer STMM_320_timer(1); // 1Hz
    if(STMM_320_timer.isup()) {
        send_STMM_320(seg);
    }

    static EasyTimer STMM_321_timer(1);
    if(STMM_321_timer.isup()) {
        send_STMM_321(seg);
    }

    static EasyTimer STMM_322_timer(1);
    if(STMM_322_timer.isup()) {
        send_STMM_322(seg);
    }

    static EasyTimer STMM_323_timer(1);
    if(STMM_323_timer.isup()) {
        send_STMM_323(seg);
    }

    static EasyTimer STMM_352_timer(1);
    if(STMM_352_timer.isup()) {
        send_STMM_352(seg);
    }

    static EasyTimer STMM_353_timer(1);
    if(STMM_353_timer.isup()) {
        send_STMM_353(seg);
    }

    static EasyTimer STMM_354_timer(1);
    if(STMM_354_timer.isup()) {
        send_STMM_354(seg);
    }

    static EasyTimer STMM_355_timer(1);
    if(STMM_355_timer.isup()) {
        send_STMM_355(seg);
    }
}

void send_can_7(const int &seg) {
    static EasyTimer STMM_1839F386_timer(10); // 10 Hz (100ms)
    if(STMM_1839F386_timer.isup()) {
        send_STMM_1839F386(seg);
    }

    static EasyTimer STMM_324_timer(1); // 1Hz
    if(STMM_324_timer.isup()) {
        send_STMM_324(seg);
    }

    static EasyTimer STMM_325_timer(1);
    if(STMM_325_timer.isup()) {
        send_STMM_325(seg);
    }

    static EasyTimer STMM_326_timer(1);
    if(STMM_326_timer.isup()) {
        send_STMM_326(seg);
    }

    static EasyTimer STMM_327_timer(1);
    if(STMM_327_timer.isup()) {
        send_STMM_327(seg);
    }

    static EasyTimer STMM_356_timer(1);
    if(STMM_356_timer.isup()) {
        send_STMM_356(seg);
    }

    static EasyTimer STMM_357_timer(1);
    if(STMM_357_timer.isup()) {
        send_STMM_357(seg);
    }

    static EasyTimer STMM_358_timer(1);
    if(STMM_358_timer.isup()) {
        send_STMM_358(seg);
    }

    static EasyTimer STMM_359_timer(1);
    if(STMM_359_timer.isup()) {
        send_STMM_359(seg);
    }
}

void send_can_8(const int &seg) {
    static EasyTimer STMM_1839F387_timer(10); // 10 Hz (100ms)
    if(STMM_1839F387_timer.isup()) {
        send_STMM_1839F387(seg);
    }

    static EasyTimer STMM_328_timer(1); // 1Hz
    if(STMM_328_timer.isup()) {
        send_STMM_328(seg);
    }

    static EasyTimer STMM_329_timer(1);
    if(STMM_329_timer.isup()) {
        send_STMM_329(seg);
    }

    static EasyTimer STMM_330_timer(1);
    if(STMM_330_timer.isup()) {
        send_STMM_330(seg);
    }

    static EasyTimer STMM_331_timer(1);
    if(STMM_331_timer.isup()) {
        send_STMM_331(seg);
    }

    static EasyTimer STMM_360_timer(1);
    if(STMM_360_timer.isup()) {
        send_STMM_360(seg);
    }

    static EasyTimer STMM_361_timer(1);
    if(STMM_361_timer.isup()) {
        send_STMM_361(seg);
    }

    static EasyTimer STMM_362_timer(1);
    if(STMM_362_timer.isup()) {
        send_STMM_362(seg);
    }

    static EasyTimer STMM_363_timer(1);
    if(STMM_363_timer.isup()) {
        send_STMM_363(seg);
    }
}

#endif

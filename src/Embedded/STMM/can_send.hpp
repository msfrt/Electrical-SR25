#ifndef CAN_SEND_HPP
#define CAN_SEND_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"
#include "sensors.hpp"
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
    STMM_seg1ThermsEnabled = 0x0C;
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
    msg.buf[4] = STMM_seg1ThermsEnabled.can_value(); // number of thermistors enabled (12)
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
    STMM_seg2ThermsEnabled = 0x0C;
    STMM_seg2ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg2ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg2ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg2ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg2ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg2ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg2ThermsEnabled.can_value(); // number of thermistors enabled (12)
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
    STMM_seg3ThermsEnabled = 0x0C;
    STMM_seg3ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg3ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg3ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg3ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg3ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg3ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg3ThermsEnabled.can_value(); // number of thermistors enabled (12)
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
    STMM_seg4ThermsEnabled = 0x0C;
    STMM_seg4ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg4ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg4ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg4ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg4ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg4ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg4ThermsEnabled.can_value(); // number of thermistors enabled (12)
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
    STMM_seg5ThermsEnabled = 0x0C;
    STMM_seg5ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg5ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg5ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg5ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg5ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg5ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg5ThermsEnabled.can_value(); // number of thermistors enabled (12)
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
    STMM_seg6ThermsEnabled = 0x0C;
    STMM_seg6ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg6ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg6ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg6ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg6ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg6ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg6ThermsEnabled.can_value(); // number of thermistors enabled (12)
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
    STMM_seg7ThermsEnabled = 0x0C;
    STMM_seg7ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg7ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg7ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg7ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg7ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg7ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg7ThermsEnabled.can_value(); // number of thermistors enabled (12)
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
    STMM_seg8ThermsEnabled = 0x0C;
    STMM_seg8ThermIDHigh = get_max_id(sorted_module_temps);
    STMM_seg8ThermIDLow = get_min_id(sorted_module_temps);

    msg.buf[0] = STMM_seg8ThermModNum.can_value(); // thermistor module number
    msg.buf[1] = STMM_seg8ThermValLow.can_value(); // lowest thermistor value
    msg.buf[2] = STMM_seg8ThermValHigh.can_value(); // highest thermistor value
    msg.buf[3] = STMM_seg8ThermValAvg.can_value(); // average thermistor value
    msg.buf[4] = STMM_seg8ThermsEnabled.can_value(); // number of thermistors enabled (12)
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

    
    Serial.println("Mod 3 (CAN): ");
    Serial.println(STMM_segmentTemp103.value());
    Serial.println("Mod 4 (CAN): ");
    Serial.println(STMM_segmentTemp104.value());
    Serial.println("Mod 5 (CAN 2kHz): ");
    Serial.println(STMM_segmentTemp105.value());

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

    
    Serial.println("Mod 6 (CAN 20Hz): ");
    Serial.println(STMM_segmentTemp106.value());
    Serial.println("Mod 7 (CAN shielded): ");
    Serial.println(STMM_segmentTemp107.value());
    Serial.println("Mod 8 (CAN): ");
    Serial.println(STMM_segmentTemp108.value());

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
    STMM_segmentTemp110 = get_mod_temps(seg).at(10).second;
    STMM_segmentTemp111 = get_mod_temps(seg).at(11).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp109.can_value();
    msg.buf[3] = STMM_segmentTemp109.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp110.can_value();
    msg.buf[5] = STMM_segmentTemp110.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp111.can_value();
    msg.buf[7] = STMM_segmentTemp111.can_value() >> 8;

    // Serial.println("Mod 9: ");
    // Serial.println(STMM_segmentTemp109.value());
    // Serial.println("Mod 10: ");
    // Serial.println(STMM_segmentTemp110.value());
    // Serial.println("Mod 11: ");
    // Serial.println(STMM_segmentTemp111.value());

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
    STMM_segmentTemp210 = get_mod_temps(seg).at(10).second;
    STMM_segmentTemp211 = get_mod_temps(seg).at(11).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp209.can_value();
    msg.buf[3] = STMM_segmentTemp209.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp210.can_value();
    msg.buf[5] = STMM_segmentTemp210.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp211.can_value();
    msg.buf[7] = STMM_segmentTemp211.can_value() >> 8;

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
    STMM_segmentTemp310 = get_mod_temps(seg).at(10).second;
    STMM_segmentTemp311 = get_mod_temps(seg).at(11).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp309.can_value();
    msg.buf[3] = STMM_segmentTemp309.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp310.can_value();
    msg.buf[5] = STMM_segmentTemp310.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp311.can_value();
    msg.buf[7] = STMM_segmentTemp311.can_value() >> 8;

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
    STMM_segmentTemp410 = get_mod_temps(seg).at(10).second;
    STMM_segmentTemp411 = get_mod_temps(seg).at(11).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp409.can_value();
    msg.buf[3] = STMM_segmentTemp409.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp410.can_value();
    msg.buf[5] = STMM_segmentTemp410.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp411.can_value();
    msg.buf[7] = STMM_segmentTemp411.can_value() >> 8;

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

    // Serial.println("Mod 1 (CAN): ");
    // Serial.println(STMM_segmentTemp500.value());

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
    STMM_segmentTemp510 = get_mod_temps(seg).at(10).second;
    STMM_segmentTemp511 = get_mod_temps(seg).at(11).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp509.can_value();
    msg.buf[3] = STMM_segmentTemp509.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp510.can_value();
    msg.buf[5] = STMM_segmentTemp510.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp511.can_value();
    msg.buf[7] = STMM_segmentTemp511.can_value() >> 8;

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
    STMM_segmentTemp610 = get_mod_temps(seg).at(10).second;
    STMM_segmentTemp611 = get_mod_temps(seg).at(11).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp609.can_value();
    msg.buf[3] = STMM_segmentTemp609.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp610.can_value();
    msg.buf[5] = STMM_segmentTemp610.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp611.can_value();
    msg.buf[7] = STMM_segmentTemp611.can_value() >> 8;

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
    STMM_segmentTemp710 = get_mod_temps(seg).at(10).second;
    STMM_segmentTemp711 = get_mod_temps(seg).at(11).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp709.can_value();
    msg.buf[3] = STMM_segmentTemp709.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp710.can_value();
    msg.buf[5] = STMM_segmentTemp710.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp711.can_value();
    msg.buf[7] = STMM_segmentTemp711.can_value() >> 8;

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
    STMM_segmentTemp810 = get_mod_temps(seg).at(10).second;
    STMM_segmentTemp811 = get_mod_temps(seg).at(11).second;

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = STMM_segmentTemp809.can_value();
    msg.buf[3] = STMM_segmentTemp809.can_value() >> 8;
    msg.buf[4] = STMM_segmentTemp810.can_value();
    msg.buf[5] = STMM_segmentTemp810.can_value() >> 8;
    msg.buf[6] = STMM_segmentTemp811.can_value();
    msg.buf[7] = STMM_segmentTemp811.can_value() >> 8;

    cbus2.write(msg);
}

/*
////////////
/ SEND IT! /
////////////
*/

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
}

#endif

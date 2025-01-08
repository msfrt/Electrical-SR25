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
    STMM_seg1ThermValLow = get_min_temp(sorted_module_temps);
    STMM_seg1ThermValHigh = get_max_temp(sorted_module_temps);
    STMM_seg1ThermValAvg = get_avg_temp(module_temps);
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
    
    int min = static_cast<int>(get_min_temp(sorted_module_temps));
    int max = static_cast<int>(get_max_temp(sorted_module_temps));
    int avg = static_cast<int>(get_avg_temp(module_temps));
    int min_id = get_min_id(sorted_module_temps);
    int max_id = get_max_id(sorted_module_temps);

    msg.buf[0] = 0x01; // thermistor module number
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

void send_STMM_1839F382(const int &seg) {

    msg.id = 406451074;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    int min = static_cast<int>(get_min_temp(sorted_module_temps));
    int max = static_cast<int>(get_max_temp(sorted_module_temps));
    int avg = static_cast<int>(get_avg_temp(module_temps));
    int min_id = get_min_id(sorted_module_temps);
    int max_id = get_max_id(sorted_module_temps);

    msg.buf[0] = 0x02; // thermistor module number
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

void send_STMM_1839F383(const int &seg) {

    msg.id = 406451075;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    int min = static_cast<int>(get_min_temp(sorted_module_temps));
    int max = static_cast<int>(get_max_temp(sorted_module_temps));
    int avg = static_cast<int>(get_avg_temp(module_temps));
    int min_id = get_min_id(sorted_module_temps);
    int max_id = get_max_id(sorted_module_temps);

    msg.buf[0] = 0x03; // thermistor module number
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

void send_STMM_1839F384(const int &seg) {

    msg.id = 406451076;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    int min = static_cast<int>(get_min_temp(sorted_module_temps));
    int max = static_cast<int>(get_max_temp(sorted_module_temps));
    int avg = static_cast<int>(get_avg_temp(module_temps));
    int min_id = get_min_id(sorted_module_temps);
    int max_id = get_max_id(sorted_module_temps);

    msg.buf[0] = 0x04; // thermistor module number
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

void send_STMM_1839F385(const int &seg) {

    msg.id = 406451077;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    int min = static_cast<int>(get_min_temp(sorted_module_temps));
    int max = static_cast<int>(get_max_temp(sorted_module_temps));
    int avg = static_cast<int>(get_avg_temp(module_temps));
    int min_id = get_min_id(sorted_module_temps);
    int max_id = get_max_id(sorted_module_temps);

    msg.buf[0] = 0x05; // thermistor module number
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

void send_STMM_1839F386(const int &seg) {

    msg.id = 406451078;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    int min = static_cast<int>(get_min_temp(sorted_module_temps));
    int max = static_cast<int>(get_max_temp(sorted_module_temps));
    int avg = static_cast<int>(get_avg_temp(module_temps));
    int min_id = get_min_id(sorted_module_temps);
    int max_id = get_max_id(sorted_module_temps);

    msg.buf[0] = 0x06; // thermistor module number
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

void send_STMM_1839F387(const int &seg) {

    msg.id = 406451079;
    msg.flags.extended = 1;
    msg.len = 8;

    vector<pair<int, float>> module_temps = get_mod_temps(seg);
    vector<pair<int, float>> sorted_module_temps = sort_mod_temps(module_temps);
    
    int min = static_cast<int>(get_min_temp(sorted_module_temps));
    int max = static_cast<int>(get_max_temp(sorted_module_temps));
    int avg = static_cast<int>(get_avg_temp(module_temps));
    int min_id = get_min_id(sorted_module_temps);
    int max_id = get_max_id(sorted_module_temps);

    msg.buf[0] = 0x07; // thermistor module number
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

void send_STMM_304() {
    static StateCounter ctr;

    msg.id = 304;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp200 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_0.avg());
    STMM_segmentTemp201 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_1.avg());
    STMM_segmentTemp202 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_2.avg());

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

void send_STMM_305() {
    static StateCounter ctr;

    msg.id = 305;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp203 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_3.avg());
    STMM_segmentTemp204 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_4.avg());
    STMM_segmentTemp205 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_5.avg());

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

void send_STMM_306() {
    static StateCounter ctr;

    msg.id = 306;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp206 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_6.avg());
    STMM_segmentTemp207 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_7.avg());
    STMM_segmentTemp208 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_8.avg());

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

void send_STMM_307() {
    static StateCounter ctr;

    msg.id = 307;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp209 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_9.avg());
    STMM_segmentTemp210 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_10.avg());
    STMM_segmentTemp211 = voltage_to_ENEPAQ_cell_temp(seg_2_mod_11.avg());

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

void send_STMM_308() {
    static StateCounter ctr;

    msg.id = 308;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp300 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_0.avg());
    STMM_segmentTemp301 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_1.avg());
    STMM_segmentTemp302 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_2.avg());

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

void send_STMM_309() {
    static StateCounter ctr;

    msg.id = 309;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp303 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_3.avg());
    STMM_segmentTemp304 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_4.avg());
    STMM_segmentTemp305 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_5.avg());

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

void send_STMM_310() {
    static StateCounter ctr;

    msg.id = 310;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp306 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_6.avg());
    STMM_segmentTemp307 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_7.avg());
    STMM_segmentTemp308 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_8.avg());

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

void send_STMM_311() {
    static StateCounter ctr;

    msg.id = 311;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp309 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_9.avg());
    STMM_segmentTemp310 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_10.avg());
    STMM_segmentTemp311 = voltage_to_ENEPAQ_cell_temp(seg_3_mod_11.avg());

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

void send_STMM_312() {
    static StateCounter ctr;

    msg.id = 312;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp400 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_0.avg());
    STMM_segmentTemp401 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_1.avg());
    STMM_segmentTemp402 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_2.avg());

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

void send_STMM_313() {
    static StateCounter ctr;

    msg.id = 313;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp403 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_3.avg());
    STMM_segmentTemp404 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_4.avg());
    STMM_segmentTemp405 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_5.avg());

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

void send_STMM_314() {
    static StateCounter ctr;

    msg.id = 314;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp406 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_6.avg());
    STMM_segmentTemp407 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_7.avg());
    STMM_segmentTemp408 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_8.avg());

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

void send_STMM_315() {
    static StateCounter ctr;

    msg.id = 315;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp409 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_9.avg());
    STMM_segmentTemp410 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_10.avg());
    STMM_segmentTemp411 = voltage_to_ENEPAQ_cell_temp(seg_4_mod_11.avg());

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

void send_STMM_316() {
    static StateCounter ctr;

    msg.id = 316;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp500 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_0.avg());
    STMM_segmentTemp501 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_1.avg());
    STMM_segmentTemp502 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_2.avg());

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

void send_STMM_317() {
    static StateCounter ctr;

    msg.id = 317;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp503 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_3.avg());
    STMM_segmentTemp504 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_4.avg());
    STMM_segmentTemp505 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_5.avg());

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

void send_STMM_318() {
    static StateCounter ctr;

    msg.id = 318;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp506 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_6.avg());
    STMM_segmentTemp507 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_7.avg());
    STMM_segmentTemp508 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_8.avg());

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

void send_STMM_319() {
    static StateCounter ctr;

    msg.id = 319;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp509 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_9.avg());
    STMM_segmentTemp510 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_10.avg());
    STMM_segmentTemp511 = voltage_to_ENEPAQ_cell_temp(seg_5_mod_11.avg());

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

void send_STMM_320() {
    static StateCounter ctr;

    msg.id = 320;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp600 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_0.avg());
    STMM_segmentTemp601 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_1.avg());
    STMM_segmentTemp602 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_2.avg());

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

void send_STMM_321() {
    static StateCounter ctr;

    msg.id = 321;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp603 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_3.avg());
    STMM_segmentTemp604 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_4.avg());
    STMM_segmentTemp605 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_5.avg());

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

void send_STMM_322() {
    static StateCounter ctr;

    msg.id = 322;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp606 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_6.avg());
    STMM_segmentTemp607 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_7.avg());
    STMM_segmentTemp608 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_8.avg());

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

void send_STMM_323() {
    static StateCounter ctr;

    msg.id = 323;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp609 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_9.avg());
    STMM_segmentTemp610 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_10.avg());
    STMM_segmentTemp611 = voltage_to_ENEPAQ_cell_temp(seg_6_mod_11.avg());

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

void send_STMM_324() {
    static StateCounter ctr;

    msg.id = 324;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp700 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_0.avg());
    STMM_segmentTemp701 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_1.avg());
    STMM_segmentTemp702 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_2.avg());

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

void send_STMM_325() {
    static StateCounter ctr;

    msg.id = 325;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp703 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_3.avg());
    STMM_segmentTemp704 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_4.avg());
    STMM_segmentTemp705 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_5.avg());

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

void send_STMM_326() {
    static StateCounter ctr;

    msg.id = 326;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp706 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_6.avg());
    STMM_segmentTemp707 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_7.avg());
    STMM_segmentTemp708 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_8.avg());

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

void send_STMM_327() {
    static StateCounter ctr;

    msg.id = 327;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp709 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_9.avg());
    STMM_segmentTemp710 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_10.avg());
    STMM_segmentTemp711 = voltage_to_ENEPAQ_cell_temp(seg_7_mod_11.avg());

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

void send_STMM_328() {
    static StateCounter ctr;

    msg.id = 328;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp800 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_0.avg());
    STMM_segmentTemp801 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_1.avg());
    STMM_segmentTemp802 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_2.avg());

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

void send_STMM_329() {
    static StateCounter ctr;

    msg.id = 329;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp803 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_3.avg());
    STMM_segmentTemp804 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_4.avg());
    STMM_segmentTemp805 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_5.avg());

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

void send_STMM_330() {
    static StateCounter ctr;

    msg.id = 330;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp806 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_6.avg());
    STMM_segmentTemp807 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_7.avg());
    STMM_segmentTemp808 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_8.avg());

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

void send_STMM_331() {
    static StateCounter ctr;

    msg.id = 331;
    msg.flags.extended = 0;
    msg.len = 8;

    STMM_segmentTemp809 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_9.avg());
    STMM_segmentTemp810 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_10.avg());
    STMM_segmentTemp811 = voltage_to_ENEPAQ_cell_temp(seg_8_mod_11.avg());

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
    static EasyTimer STMM_1839F381_timer(10); // 10 Hz (100ms)
    if(STMM_1839F381_timer.isup()) {
        send_STMM_1839F381(seg);
    }

    static EasyTimer STMM_304_timer(1); // 1Hz
    if(STMM_304_timer.isup()) {
        send_STMM_304();
    }

    static EasyTimer STMM_305_timer(1);
    if(STMM_305_timer.isup()) {
        send_STMM_305();
    }

    static EasyTimer STMM_306_timer(1);
    if(STMM_306_timer.isup()) {
        send_STMM_306();
    }

    static EasyTimer STMM_307_timer(1);
    if(STMM_307_timer.isup()) {
        send_STMM_307();
    }
}

void send_can_3(const int &seg) {
    static EasyTimer STMM_1839F382_timer(10); // 10 Hz (100ms)
    if(STMM_1839F382_timer.isup()) {
        send_STMM_1839F382(seg);
    }

    static EasyTimer STMM_308_timer(1); // 1Hz
    if(STMM_308_timer.isup()) {
        send_STMM_308();
    }

    static EasyTimer STMM_309_timer(1);
    if(STMM_309_timer.isup()) {
        send_STMM_309();
    }

    static EasyTimer STMM_310_timer(1);
    if(STMM_310_timer.isup()) {
        send_STMM_310();
    }

    static EasyTimer STMM_311_timer(1);
    if(STMM_311_timer.isup()) {
        send_STMM_311();
    }
}

void send_can_4(const int &seg) {
    static EasyTimer STMM_1839F383_timer(10); // 10 Hz (100ms)
    if(STMM_1839F383_timer.isup()) {
        send_STMM_1839F383(seg);
    }

    static EasyTimer STMM_312_timer(1); // 1Hz
    if(STMM_312_timer.isup()) {
        send_STMM_312();
    }

    static EasyTimer STMM_313_timer(1);
    if(STMM_313_timer.isup()) {
        send_STMM_313();
    }

    static EasyTimer STMM_314_timer(1);
    if(STMM_314_timer.isup()) {
        send_STMM_314();
    }

    static EasyTimer STMM_315_timer(1);
    if(STMM_315_timer.isup()) {
        send_STMM_315();
    }
}

void send_can_5(const int &seg) {
    static EasyTimer STMM_1839F384_timer(10); // 10 Hz (100ms)
    if(STMM_1839F384_timer.isup()) {
        send_STMM_1839F384(seg);
    }

    static EasyTimer STMM_316_timer(1); // 1Hz
    if(STMM_316_timer.isup()) {
        send_STMM_316();
    }

    static EasyTimer STMM_317_timer(1);
    if(STMM_317_timer.isup()) {
        send_STMM_317();
    }

    static EasyTimer STMM_318_timer(1);
    if(STMM_318_timer.isup()) {
        send_STMM_318();
    }

    static EasyTimer STMM_319_timer(1);
    if(STMM_319_timer.isup()) {
        send_STMM_319();
    }
}

void send_can_6(const int &seg) {
    static EasyTimer STMM_1839F385_timer(10); // 10 Hz (100ms)
    if(STMM_1839F385_timer.isup()) {
        send_STMM_1839F385(seg);
    }

    static EasyTimer STMM_320_timer(1); // 1Hz
    if(STMM_320_timer.isup()) {
        send_STMM_320();
    }

    static EasyTimer STMM_321_timer(1);
    if(STMM_321_timer.isup()) {
        send_STMM_321();
    }

    static EasyTimer STMM_322_timer(1);
    if(STMM_322_timer.isup()) {
        send_STMM_322();
    }

    static EasyTimer STMM_323_timer(1);
    if(STMM_323_timer.isup()) {
        send_STMM_323();
    }
}

void send_can_7(const int &seg) {
    static EasyTimer STMM_1839F386_timer(10); // 10 Hz (100ms)
    if(STMM_1839F386_timer.isup()) {
        send_STMM_1839F386(seg);
    }

    static EasyTimer STMM_324_timer(1); // 1Hz
    if(STMM_324_timer.isup()) {
        send_STMM_324();
    }

    static EasyTimer STMM_325_timer(1);
    if(STMM_325_timer.isup()) {
        send_STMM_325();
    }

    static EasyTimer STMM_326_timer(1);
    if(STMM_326_timer.isup()) {
        send_STMM_326();
    }

    static EasyTimer STMM_327_timer(1);
    if(STMM_327_timer.isup()) {
        send_STMM_327();
    }
}

void send_can_8(const int &seg) {
    static EasyTimer STMM_1839F387_timer(10); // 10 Hz (100ms)
    if(STMM_1839F387_timer.isup()) {
        send_STMM_1839F387(seg);
    }

    static EasyTimer STMM_328_timer(1); // 1Hz
    if(STMM_328_timer.isup()) {
        send_STMM_328();
    }

    static EasyTimer STMM_329_timer(1);
    if(STMM_329_timer.isup()) {
        send_STMM_329();
    }

    static EasyTimer STMM_330_timer(1);
    if(STMM_330_timer.isup()) {
        send_STMM_330();
    }

    static EasyTimer STMM_331_timer(1);
    if(STMM_331_timer.isup()) {
        send_STMM_331();
    }
}

#endif

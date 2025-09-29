#ifndef CAN_SEND_HPP
#define CAN_SEND_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

// #include "cyclic_id.hpp"

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

void send_STMM_332(const int &seg) {
    static StateCounter ctr;

    msg.id = 332;
    msg.flags.extended = 0;
    msg.len = 8;

    // Serial.println(STMM_segmentVolt100.can_value());

    STMM_segmentVolt100 = get_mod_volts(1).at(0).second;
    STMM_segmentVolt101 = get_mod_volts(1).at(1).second;
    STMM_segmentVolt102 = get_mod_volts(1).at(2).second;

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

// void send_STMM_333(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 333;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt103 = module_voltage_3;
//     STMM_segmentVolt104 = module_voltage_4;
//     STMM_segmentVolt105 = module_voltage_5;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt103.can_value();
//     msg.buf[3] = STMM_segmentVolt103.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt104.can_value();
//     msg.buf[5] = STMM_segmentVolt104.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt105.can_value();
//     msg.buf[7] = STMM_segmentVolt105.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_334(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 334;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt106 = module_voltage_6;
//     STMM_segmentVolt107 = module_voltage_7;
//     STMM_segmentVolt108 = module_voltage_8;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt106.can_value();
//     msg.buf[3] = STMM_segmentVolt106.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt107.can_value();
//     msg.buf[5] = STMM_segmentVolt107.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt108.can_value();
//     msg.buf[7] = STMM_segmentVolt108.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_335(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 335;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt109 = module_voltage_9;
//     // STMM_segmentVolt110 = module_voltage_10;
//     // STMM_segmentVolt111 = module_voltage_11;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt109.can_value();
//     msg.buf[3] = STMM_segmentVolt109.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt110.can_value();
//     msg.buf[5] = STMM_segmentVolt110.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt111.can_value();
//     msg.buf[7] = STMM_segmentVolt111.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_336(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 336;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt200 = module_voltage_0;
//     STMM_segmentVolt201 = module_voltage_1;
//     STMM_segmentVolt202 = module_voltage_2;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt200.can_value();
//     msg.buf[3] = STMM_segmentVolt200.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt201.can_value();
//     msg.buf[5] = STMM_segmentVolt201.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt202.can_value();
//     msg.buf[7] = STMM_segmentVolt202.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_337(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 337;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt203 = module_voltage_3;
//     STMM_segmentVolt204 = module_voltage_4;
//     STMM_segmentVolt205 = module_voltage_5;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt203.can_value();
//     msg.buf[3] = STMM_segmentVolt203.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt204.can_value();
//     msg.buf[5] = STMM_segmentVolt204.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt205.can_value();
//     msg.buf[7] = STMM_segmentVolt205.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_338(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 338;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt206 = module_voltage_6;
//     STMM_segmentVolt207 = module_voltage_7;
//     STMM_segmentVolt208 = module_voltage_8;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt206.can_value();
//     msg.buf[3] = STMM_segmentVolt206.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt207.can_value();
//     msg.buf[5] = STMM_segmentVolt207.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt208.can_value();
//     msg.buf[7] = STMM_segmentVolt208.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_339(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 339;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt209 = module_voltage_9;
//     // STMM_segmentVolt210 = module_voltage_10;
//     // STMM_segmentVolt211 = module_voltage_11;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt209.can_value();
//     msg.buf[3] = STMM_segmentVolt209.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt210.can_value();
//     msg.buf[5] = STMM_segmentVolt210.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt211.can_value();
//     msg.buf[7] = STMM_segmentVolt211.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_340(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 340;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt300 = module_voltage_0;
//     STMM_segmentVolt301 = module_voltage_1;
//     STMM_segmentVolt302 = module_voltage_2;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt300.can_value();
//     msg.buf[3] = STMM_segmentVolt300.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt301.can_value();
//     msg.buf[5] = STMM_segmentVolt301.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt302.can_value();
//     msg.buf[7] = STMM_segmentVolt302.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_341(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 341;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt303 = module_voltage_3;
//     STMM_segmentVolt304 = module_voltage_4;
//     STMM_segmentVolt305 = module_voltage_5;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt303.can_value();
//     msg.buf[3] = STMM_segmentVolt303.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt304.can_value();
//     msg.buf[5] = STMM_segmentVolt304.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt305.can_value();
//     msg.buf[7] = STMM_segmentVolt305.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_342(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 342;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt306 = module_voltage_6;
//     STMM_segmentVolt307 = module_voltage_7;
//     STMM_segmentVolt308 = module_voltage_8;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt306.can_value();
//     msg.buf[3] = STMM_segmentVolt306.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt307.can_value();
//     msg.buf[5] = STMM_segmentVolt307.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt308.can_value();
//     msg.buf[7] = STMM_segmentVolt308.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_343(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 343;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt309 = module_voltage_9;
//     // STMM_segmentVolt310 = module_voltage_10;
//     // STMM_segmentVolt311 = module_voltage_11;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt309.can_value();
//     msg.buf[3] = STMM_segmentVolt309.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt310.can_value();
//     msg.buf[5] = STMM_segmentVolt310.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt311.can_value();
//     msg.buf[7] = STMM_segmentVolt311.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_344(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 344;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt400 = module_voltage_0;
//     STMM_segmentVolt401 = module_voltage_1;
//     STMM_segmentVolt402 = module_voltage_2;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt400.can_value();
//     msg.buf[3] = STMM_segmentVolt400.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt401.can_value();
//     msg.buf[5] = STMM_segmentVolt401.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt402.can_value();
//     msg.buf[7] = STMM_segmentVolt402.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_345(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 345;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt403 = module_voltage_3;
//     STMM_segmentVolt404 = module_voltage_4;
//     STMM_segmentVolt405 = module_voltage_5;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt403.can_value();
//     msg.buf[3] = STMM_segmentVolt403.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt404.can_value();
//     msg.buf[5] = STMM_segmentVolt404.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt405.can_value();
//     msg.buf[7] = STMM_segmentVolt405.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_346(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 346;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt406 = module_voltage_6;
//     STMM_segmentVolt407 = module_voltage_7;
//     STMM_segmentVolt408 = module_voltage_8;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt406.can_value();
//     msg.buf[3] = STMM_segmentVolt406.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt407.can_value();
//     msg.buf[5] = STMM_segmentVolt407.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt408.can_value();
//     msg.buf[7] = STMM_segmentVolt408.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_347(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 347;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt409 = module_voltage_9;
//     // STMM_segmentVolt410 = module_voltage_10;
//     // STMM_segmentVolt411 = module_voltage_11;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt409.can_value();
//     msg.buf[3] = STMM_segmentVolt409.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt410.can_value();
//     msg.buf[5] = STMM_segmentVolt410.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt411.can_value();
//     msg.buf[7] = STMM_segmentVolt411.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_348(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 348;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt500 = module_voltage_0;
//     STMM_segmentVolt501 = module_voltage_1;
//     STMM_segmentVolt502 = module_voltage_2;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt500.can_value();
//     msg.buf[3] = STMM_segmentVolt500.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt501.can_value();
//     msg.buf[5] = STMM_segmentVolt501.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt502.can_value();
//     msg.buf[7] = STMM_segmentVolt502.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_349(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 349;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt503 = module_voltage_3;
//     STMM_segmentVolt504 = module_voltage_4;
//     STMM_segmentVolt505 = module_voltage_5;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt503.can_value();
//     msg.buf[3] = STMM_segmentVolt503.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt504.can_value();
//     msg.buf[5] = STMM_segmentVolt504.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt505.can_value();
//     msg.buf[7] = STMM_segmentVolt505.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_350(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 350;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt506 = module_voltage_6;
//     STMM_segmentVolt507 = module_voltage_7;
//     STMM_segmentVolt508 = module_voltage_8;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt506.can_value();
//     msg.buf[3] = STMM_segmentVolt506.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt507.can_value();
//     msg.buf[5] = STMM_segmentVolt507.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt508.can_value();
//     msg.buf[7] = STMM_segmentVolt508.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_351(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 351;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt509 = module_voltage_9;
//     // STMM_segmentVolt510 = module_voltage_10;
//     // STMM_segmentVolt511 = module_voltage_11;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt509.can_value();
//     msg.buf[3] = STMM_segmentVolt509.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt510.can_value();
//     msg.buf[5] = STMM_segmentVolt510.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt511.can_value();
//     msg.buf[7] = STMM_segmentVolt511.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_352(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 352;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt600 = module_voltage_0;
//     STMM_segmentVolt601 = module_voltage_1;
//     STMM_segmentVolt602 = module_voltage_2;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt600.can_value();
//     msg.buf[3] = STMM_segmentVolt600.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt601.can_value();
//     msg.buf[5] = STMM_segmentVolt601.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt602.can_value();
//     msg.buf[7] = STMM_segmentVolt602.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_353(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 353;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt603 = module_voltage_3;
//     STMM_segmentVolt604 = module_voltage_4;
//     STMM_segmentVolt605 = module_voltage_5;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt603.can_value();
//     msg.buf[3] = STMM_segmentVolt603.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt604.can_value();
//     msg.buf[5] = STMM_segmentVolt604.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt605.can_value();
//     msg.buf[7] = STMM_segmentVolt605.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_354(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 354;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt606 = module_voltage_6;
//     STMM_segmentVolt607 = module_voltage_7;
//     STMM_segmentVolt608 = module_voltage_8;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt606.can_value();
//     msg.buf[3] = STMM_segmentVolt606.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt607.can_value();
//     msg.buf[5] = STMM_segmentVolt607.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt608.can_value();
//     msg.buf[7] = STMM_segmentVolt608.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_355(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 355;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt609 = module_voltage_9;
//     // STMM_segmentVolt610 = module_voltage_10;
//     // STMM_segmentVolt611 = module_voltage_11;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt609.can_value();
//     msg.buf[3] = STMM_segmentVolt609.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt610.can_value();
//     msg.buf[5] = STMM_segmentVolt610.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt611.can_value();
//     msg.buf[7] = STMM_segmentVolt611.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_356(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 356;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt700 = module_voltage_0;
//     STMM_segmentVolt701 = module_voltage_1;
//     STMM_segmentVolt702 = module_voltage_2;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt700.can_value();
//     msg.buf[3] = STMM_segmentVolt700.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt701.can_value();
//     msg.buf[5] = STMM_segmentVolt701.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt702.can_value();
//     msg.buf[7] = STMM_segmentVolt702.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_357(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 357;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt703 = module_voltage_3;
//     STMM_segmentVolt704 = module_voltage_4;
//     STMM_segmentVolt705 = module_voltage_5;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt703.can_value();
//     msg.buf[3] = STMM_segmentVolt703.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt704.can_value();
//     msg.buf[5] = STMM_segmentVolt704.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt705.can_value();
//     msg.buf[7] = STMM_segmentVolt705.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_358(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 358;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt706 = module_voltage_6;
//     STMM_segmentVolt707 = module_voltage_7;
//     STMM_segmentVolt708 = module_voltage_8;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt706.can_value();
//     msg.buf[3] = STMM_segmentVolt706.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt707.can_value();
//     msg.buf[5] = STMM_segmentVolt707.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt708.can_value();
//     msg.buf[7] = STMM_segmentVolt708.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_359(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 359;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt709 = module_voltage_9;
//     // STMM_segmentVolt710 = module_voltage_10;
//     // STMM_segmentVolt711 = module_voltage_11;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt709.can_value();
//     msg.buf[3] = STMM_segmentVolt709.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt710.can_value();
//     msg.buf[5] = STMM_segmentVolt710.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt711.can_value();
//     msg.buf[7] = STMM_segmentVolt711.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_360(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 360;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt800 = module_voltage_0;
//     STMM_segmentVolt801 = module_voltage_1;
//     STMM_segmentVolt802 = module_voltage_2;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt800.can_value();
//     msg.buf[3] = STMM_segmentVolt800.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt801.can_value();
//     msg.buf[5] = STMM_segmentVolt801.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt802.can_value();
//     msg.buf[7] = STMM_segmentVolt802.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_361(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 361;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt803 = module_voltage_3;
//     STMM_segmentVolt804 = module_voltage_4;
//     STMM_segmentVolt805 = module_voltage_5;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt803.can_value();
//     msg.buf[3] = STMM_segmentVolt803.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt804.can_value();
//     msg.buf[5] = STMM_segmentVolt804.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt805.can_value();
//     msg.buf[7] = STMM_segmentVolt805.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_362(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 362;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt806 = module_voltage_6;
//     STMM_segmentVolt807 = module_voltage_7;
//     STMM_segmentVolt808 = module_voltage_8;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt806.can_value();
//     msg.buf[3] = STMM_segmentVolt806.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt807.can_value();
//     msg.buf[5] = STMM_segmentVolt807.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt808.can_value();
//     msg.buf[7] = STMM_segmentVolt808.can_value() >> 8;

//     cbus2.write(msg);
// }

// void send_STMM_363(const int &seg) {
//     static StateCounter ctr;

//     msg.id = 363;
//     msg.flags.extended = 0;
//     msg.len = 8;

//     STMM_segmentVolt809 = module_voltage_9;
//     // STMM_segmentVolt810 = module_voltage_10;
//     // STMM_segmentVolt811 = module_voltage_11;

//     msg.buf[0] = ctr.value();
//     msg.buf[1] = 0;
//     msg.buf[2] = STMM_segmentVolt809.can_value();
//     msg.buf[3] = STMM_segmentVolt809.can_value() >> 8;
//     msg.buf[4] = STMM_segmentVolt810.can_value();
//     msg.buf[5] = STMM_segmentVolt810.can_value() >> 8;
//     msg.buf[6] = STMM_segmentVolt811.can_value();
//     msg.buf[7] = STMM_segmentVolt811.can_value() >> 8;

//     cbus2.write(msg);
// }

/*
////////////
/ SEND IT! /
////////////
*/

// STMM heartbeat
void send_step(bool &step) {
    static EasyTimer STMM_299_timer(100); // 100 Hz (10ms)
    if(STMM_299_timer.isup()) {
        send_STMM_299(step);
    }
}

// send the charger messages
void send_can_1() {
    return;
}

// voltage tap values, current sense values, BMS status
void send_can_2() {

    static EasyTimer STMM_332_timer(1);
    if(STMM_332_timer.isup()) {
        send_STMM_332(seg);
    }

    // static EasyTimer STMM_333_timer(1);
    // if(STMM_333_timer.isup()) {
    //     send_STMM_333(seg);
    // }

    // static EasyTimer STMM_334_timer(1);
    // if(STMM_334_timer.isup()) {
    //     send_STMM_334(seg);
    // }

    // static EasyTimer STMM_335_timer(1);
    // if(STMM_335_timer.isup()) {
    //     send_STMM_335(seg);
    // }

    // static EasyTimer STMM_336_timer(1);
    // if(STMM_336_timer.isup()) {
    //     send_STMM_336(seg);
    // }

    // static EasyTimer STMM_337_timer(1);
    // if(STMM_337_timer.isup()) {
    //     send_STMM_337(seg);
    // }

    // static EasyTimer STMM_338_timer(1);
    // if(STMM_338_timer.isup()) {
    //     send_STMM_338(seg);
    // }

    // static EasyTimer STMM_339_timer(1);
    // if(STMM_339_timer.isup()) {
    //     send_STMM_339(seg);
    // }

    // static EasyTimer STMM_340_timer(1);
    // if(STMM_340_timer.isup()) {
    //     send_STMM_340(seg);
    // }

    // static EasyTimer STMM_341_timer(1);
    // if(STMM_341_timer.isup()) {
    //     send_STMM_341(seg);
    // }

    // static EasyTimer STMM_342_timer(1);
    // if(STMM_342_timer.isup()) {
    //     send_STMM_342(seg);
    // }

    // static EasyTimer STMM_343_timer(1);
    // if(STMM_343_timer.isup()) {
    //     send_STMM_343(seg);
    // }

    // static EasyTimer STMM_344_timer(1);
    // if(STMM_344_timer.isup()) {
    //     send_STMM_344(seg);
    // }
    
    // static EasyTimer STMM_345_timer(1);
    // if(STMM_345_timer.isup()) {
    //     send_STMM_345(seg);
    // }

    // static EasyTimer STMM_346_timer(1);
    // if(STMM_346_timer.isup()) {
    //     send_STMM_346(seg);
    // }

    // static EasyTimer STMM_347_timer(1);
    // if(STMM_347_timer.isup()) {
    //     send_STMM_347(seg);
    // }

    // static EasyTimer STMM_348_timer(1);
    // if(STMM_348_timer.isup()) {
    //     send_STMM_348(seg);
    // }

    // static EasyTimer STMM_349_timer(1);
    // if(STMM_349_timer.isup()) {
    //     send_STMM_349(seg);
    // }

    // static EasyTimer STMM_350_timer(1);
    // if(STMM_350_timer.isup()) {
    //     send_STMM_350(seg);
    // }

    // static EasyTimer STMM_351_timer(1);
    // if(STMM_351_timer.isup()) {
    //     send_STMM_351(seg);
    // }

    // static EasyTimer STMM_352_timer(1);
    // if(STMM_352_timer.isup()) {
    //     send_STMM_352(seg);
    // }

    // static EasyTimer STMM_353_timer(1);
    // if(STMM_353_timer.isup()) {
    //     send_STMM_353(seg);
    // }

    // static EasyTimer STMM_354_timer(1);
    // if(STMM_354_timer.isup()) {
    //     send_STMM_354(seg);
    // }

    // static EasyTimer STMM_355_timer(1);
    // if(STMM_355_timer.isup()) {
    //     send_STMM_355(seg);
    // }

    //     static EasyTimer STMM_356_timer(1);
    // if(STMM_356_timer.isup()) {
    //     send_STMM_356(seg);
    // }

    // static EasyTimer STMM_357_timer(1);
    // if(STMM_357_timer.isup()) {
    //     send_STMM_357(seg);
    // }

    // static EasyTimer STMM_358_timer(1);
    // if(STMM_358_timer.isup()) {
    //     send_STMM_358(seg);
    // }

    // static EasyTimer STMM_359_timer(1);
    // if(STMM_359_timer.isup()) {
    //     send_STMM_359(seg);
    // }
    // static EasyTimer STMM_360_timer(1);
    // if(STMM_360_timer.isup()) {
    //     send_STMM_360(seg);
    // }

    // static EasyTimer STMM_361_timer(1);
    // if(STMM_361_timer.isup()) {
    //     send_STMM_361(seg);
    // }

    // static EasyTimer STMM_362_timer(1);
    // if(STMM_362_timer.isup()) {
    //     send_STMM_362(seg);
    // }

    // static EasyTimer STMM_363_timer(1);
    // if(STMM_363_timer.isup()) {
    //     send_STMM_363(seg);
    // }
}

#endif

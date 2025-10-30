#ifndef CAN_SEND_HPP
#define CAN_SEND_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
// #include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"
#include "sensors.hpp"

void send_TMAP_500() {
    // static definition - only defined once (like a global variable, but is local to this function only)
    static StateCounter ctr;

    // update per message
    msg.id = 500;
    msg.flags.extended = 0;
    msg.len = 8;

    // automatically does calcs
    RAND_preRadTemp = tmap_temp_pre.avg();
    RAND_preRadPres = tmap_pres_pre.avg();

    // load up the message buffer
    // Each message contains a counter and 3 signals
    // Each signal is 16 bits, so they take up two spots in the message, hence the 8-bit shift
    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = RAND_preRadTemp.can_value();
    msg.buf[3] = RAND_preRadTemp.can_value() >> 8;
    msg.buf[4] = RAND_preRadPres.can_value();
    msg.buf[5] = RAND_preRadPres.can_value() >> 8;
    msg.buf[6] = 0;
    msg.buf[7] = 0;

    Serial.println("Temp: ");
    Serial.println(tmap_temp_pre.avg());

    Serial.println("Pres: ");
    Serial.println(tmap_pres_pre.avg());

    // send the message
    cbus2.write(msg);
}

void send_TMAP_501() {
    // static definition - only defined once (like a global variable, but is local to this function only)
    static StateCounter ctr;

    // update per message
    msg.id = 501;
    msg.flags.extended = 0;
    msg.len = 8;

    // automatically does calcs
    RAND_postRadTemp = tmap_temp_post.avg();
    RAND_postRadPres = tmap_pres_post.avg();

    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = RAND_postRadTemp.can_value();
    msg.buf[3] = RAND_postRadTemp.can_value() >> 8;
    msg.buf[4] = RAND_postRadPres.can_value();
    msg.buf[5] = RAND_postRadPres.can_value() >> 8;
    msg.buf[6] = 0;
    msg.buf[7] = 0;

    // send the message
    cbus2.write(msg);
}

/*
////////////
/ SEND IT! /
////////////
*/

void send_can() {

    static EasyTimer TMAP_500_timer(10); // 10Hz
    if(TMAP_500_timer.isup()) {
        send_TMAP_500();
    }

    static EasyTimer TMAP_501_timer(10); // 10Hz
    if(TMAP_501_timer.isup()) {
        send_TMAP_501();
    }

}

#endif

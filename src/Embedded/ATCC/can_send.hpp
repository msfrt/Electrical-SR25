#ifndef CAN_SEND_ATCC_HPP
#define CAN_SEND_ATCC_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

#include "sensors.hpp"

static CAN_message_t msg;

// message definitions below

void send_ATCC_300(){
  static StateCounter ctr;

  msg.id = 300;
  msg.len = 8;

  ATCC_boardTemp = 0; //board_temp.value();
  ATCC_teensyTemp = tempmonGetTemp();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCC_boardTemp.can_value();
  msg.buf[3] = ATCC_boardTemp.can_value() >> 8;
  msg.buf[4] = ATCC_teensyTemp.can_value();
  msg.buf[5] = ATCC_teensyTemp.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1

void send_ATCC_301(){
  static StateCounter ctr;

  msg.id = 301;
  msg.len = 8;

  ATCC_angularWheelFreqFL = ATCC_angularWheelFreqFL.value();
  ATCC_angularWheelFreqFR = ATCC_angularWheelFreqFR.value();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCC_angularWheelFreqFL.can_value();
  msg.buf[3] = ATCC_angularWheelFreqFL.can_value() >> 8;
  msg.buf[4] = ATCC_angularWheelFreqFR.can_value();
  msg.buf[5] = ATCC_angularWheelFreqFR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1

void send_ATCC_302(){
  static StateCounter ctr;

  msg.id = 302;
  msg.len = 8;

  ATCC_angularWheelFreqRL = ATCC_angularWheelFreqFL.value();
  ATCC_angularWheelFreqRR = ATCC_angularWheelFreqFR.value();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCC_angularWheelFreqRL.can_value();
  msg.buf[3] = ATCC_angularWheelFreqRL.can_value() >> 8;
  msg.buf[4] = ATCC_angularWheelFreqRR.can_value();
  msg.buf[5] = ATCC_angularWheelFreqRR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1

void send_ATCC_303(){
  static StateCounter ctr;
  Serial.println("sendingATCC303");

  msg.id = 302;
  msg.len = 8;

  ATCC_coolantTempMotorIn = 0; //voltage_to_NTC_M12_H_temp(ATCC_coolantTempMotorIn.avg());
  ATCC_coolantTempInverterIn = 0; //voltage_to_NTC_M12_H_temp(ATCC_coolantTempInverterIn.avg());
  ATCC_coolantTempInverterOut = 0; //voltage_to_NTC_M12_H_temp(ATCC_coolantTempInverterOut.avg());

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCC_coolantTempMotorIn.can_value();
  msg.buf[3] = ATCC_coolantTempMotorIn.can_value() >> 8;
  msg.buf[4] = ATCC_coolantTempInverterIn.can_value();
  msg.buf[5] = ATCC_coolantTempInverterIn.can_value() >> 8;
  msg.buf[6] = ATCC_coolantTempInverterIn.can_value();
  msg.buf[7] = ATCC_coolantTempInverterIn.can_value() >> 8;

  can1.write(msg);
} // can1

void send_can1(){

  static EasyTimer ATCC_300_timer(1); // 200Hz
  if (ATCC_300_timer.isup()){
    send_ATCC_300();
  }

  static EasyTimer ATCC_301_timer(1); // 200Hz
  if (ATCC_301_timer.isup()){
    send_ATCC_301();
  }

  static EasyTimer ATCC_302_timer(1); // 200Hz
  if (ATCC_302_timer.isup()){
    send_ATCC_302();
  }

  static EasyTimer ATCC_303_timer(1); // 200Hz
  if (ATCC_303_timer.isup()){
    send_ATCC_303();
  }

}

#endif

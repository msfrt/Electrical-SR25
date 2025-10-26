#ifndef CAN_SEND_ATCC_HPP
#define CAN_SEND_ATCC_HPP

#include <FlexCAN_T4.h>
#include <math.h>
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

#include "sensors.hpp"
// message definitions belo

void send_STMM_302() {
  static StateCounter ctr;

  msg.id = 211;
  msg.flags.extended = 0;
  msg.len = 8;
  Serial.println("SENDING TIRE TEMP COOLING TEMP");

  /*
    // automatically does calcs
    ATCC_coolantTempMotorIn = voltage_to_temp(ATCC_coolantTempMotorIn.avg());
    ATCC_coolantTempInverterIn = voltage_to_temp(ATCC_coolantTempInverterIn.avg());
    ATCC_coolantTempInverterOut = voltage_to_temp(ATCC_coolantTempInverterOut.avg());
  */

    VCU_tireTempRRI = voltage_to_temp(coolant_temp_inlet_sens.avg());
    VCU_tireTempRRM = voltage_to_temp(coolant_temp_outlet_sens.avg());
    VCU_tireTempRRO = voltage_to_temp(coolant_temp_outlet_sens.avg());

    // load up the message buffer
    msg.buf[0] = ctr.value();
    msg.buf[1] = 0;
    msg.buf[2] = VCU_tireTempRRI.can_value();
    msg.buf[3] = VCU_tireTempRRI.can_value() >> 8;
    msg.buf[4] = VCU_tireTempRRM.can_value();
    msg.buf[5] = VCU_tireTempRRM.can_value() >> 8;
    msg.buf[6] = VCU_tireTempRRO.can_value();
    msg.buf[7] = VCU_tireTempRRO.can_value() >> 8;

    Serial.println(VCU_tireTempRRO.value());
    Serial.println(VCU_tireTempRRO.value()); 
    Serial.println(VCU_tireTempRRO.value());

    cbus2.write(msg);
}

//Front ATCC
void send_ATCC_303(){
  // static definition - only defined once (like a global variable, but is local to this function only)
  static StateCounter ctr;

  // update per message
  msg.id = 303;
  msg.len = 8;
  Serial.println("sendingATCC303");

/*
  // automatically does calcs
  ATCC_coolantTempMotorIn = voltage_to_temp(ATCC_coolantTempMotorIn.avg());
  ATCC_coolantTempInverterIn = voltage_to_temp(ATCC_coolantTempInverterIn.avg());
  ATCC_coolantTempInverterOut = voltage_to_temp(ATCC_coolantTempInverterOut.avg());
*/

  ATCC_coolantTempMotorIn = voltage_to_temp(coolant_temp_inlet_sens.avg());
  ATCC_coolantTempInverterIn = voltage_to_temp(coolant_temp_outlet_sens.avg());
  ATCC_coolantTempInverterOut = voltage_to_temp(coolant_temp_outlet_sens.avg());

  // load up the message buffer
  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCC_coolantTempMotorIn.can_value();
  msg.buf[3] = ATCC_coolantTempMotorIn.can_value() >> 8;
  msg.buf[4] = ATCC_coolantTempInverterIn.can_value();
  msg.buf[5] = ATCC_coolantTempInverterIn.can_value() >> 8;
  msg.buf[6] = ATCC_coolantTempInverterOut.can_value();
  msg.buf[7] = ATCC_coolantTempInverterOut.can_value() >> 8;

  Serial.println(ATCC_coolantTempMotorIn.can_value());
  Serial.println(ATCC_coolantTempInverterIn.can_value()); 
  Serial.println(ATCC_coolantTempInverterOut.can_value());

  cbus1.write(msg);
}

void send_can_F(){

  static EasyTimer ATCC_303_timer(1); // 200Hz
  if (ATCC_303_timer.isup()){
    send_ATCC_303();
    send_STMM_302();
  }
}

#endif

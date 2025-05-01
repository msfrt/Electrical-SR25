#ifndef CAN_MESSAGES_HPP
#define CAN_MESSAGES_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"


// external definitions
extern int OBDFLAG_oil_pressure;
extern int OBDFLAG_oil_temp;
extern int OBDFLAG_fuel_pressure;


static CAN_message_t msg;

// send message definitions

/*
void send_PDM_400() {
  static StateCounter ctr;
  msg.id = 400;
  msg.len = 8;

  PDM_boardTemp = board_temp.value();
  PDM_brakelightVoltAvg = brakelight_volt_sens.avg();
  PDM_vehichleState = 0; // find sens refrence
  PDM_coolingOverideActive = 0;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_boardTemp.can_value();
  msg.buf[3] = PDM_boardTemp.can_value() >> 8;
  msg.buf[4] = PDM_brakelightVoltAvg.can_value();
  msg.buf[5] = PDM_brakelightVoltAvg.can_value() >> 8;
  msg.buf[6] = PDM_velichleState.can_value();
  msg.buf[7] = PDM_coolingOverrideActive.can_value();

  can2.send(msg);
}
*/

void send_PDM_401() {
  static StateCounter ctr;
  msg.id = 401;
  msg.len = 8;

  PDM_pdmCurrentAvg = pdm_current_sens.avg();
  PDM_pdmCurrentMax = pdm_current_sens.max();
  PDM_pdmCurrentMin = pdm_current_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_pdmCurrentMin.can_value();
  msg.buf[3] = PDM_pdmCurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_pdmCurrentMax.can_value();
  msg.buf[5] = PDM_pdmCurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_pdmCurrentMin.can_value();
  msg.buf[7] = PDM_pdmCurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_402() {
  static StateCounter ctr;
  msg.id = 402;
  msg.len = 8;

  PDM_pdmVoltAvg = pdm_volt_sens.avg();
  PDM_pdmVoltMax = pdm_volt_sens.max();
  PDM_pdmVoltMin = pdm_volt_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_pdmVoltAvg.can_value();
  msg.buf[3] = PDM_pdmVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_pdmVoltMax.can_value();
  msg.buf[5] = PDM_pdmVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_pdmVoltMin.can_value();
  msg.buf[7] = PDM_pdmVoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_403() {
  static StateCounter ctr;
  msg.id = 403;
  msg.len = 8;
  Serial.println("sendingPDM403");
  PDM_fanRightCurrentAvg = fanr_current_sens.avg();
  PDM_fanRightCurrentMax = fanr_current_sens.max();
  PDM_fanRightCurrentMin = fanr_current_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanRightCurrentAvg.can_value();
  msg.buf[3] = PDM_fanRightCurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_fanRightCurrentMax.can_value();
  msg.buf[5] = PDM_fanRightCurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_fanRightCurrentMin.can_value();
  msg.buf[7] = PDM_fanRightCurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_404(){
  static StateCounter ctr;
  msg.id = 404;
  msg.len = 8;

  PDM_fanRightVoltAvg = fanr_volt_sens.avg();
  PDM_fanRightVoltMax = fanr_volt_sens.max();
  PDM_fanRightVoltMin = fanr_volt_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanRightVoltAvg.can_value();
  msg.buf[3] = PDM_fanRightVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_fanRightVoltMax.can_value();
  msg.buf[5] = PDM_fanRightVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_fanRightVoltMin.can_value();
  msg.buf[7] = PDM_fanRightVoltMin.can_value() >> 8;

  can1.write(msg);
}

void send_PDM_405(){
  static StateCounter ctr;
  msg.id = 405;
  msg.len = 8;

  PDM_fanLeftCurrentAvg = fanl_current_sens.avg();
  PDM_fanLeftCurrentMax = fanl_current_sens.max();
  PDM_fanLeftCurrentMin = fanl_current_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanLeftCurrentAvg.can_value();
  msg.buf[3] = PDM_fanLeftCurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_fanLeftCurrentMax.can_value();
  msg.buf[5] = PDM_fanLeftCurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_fanLeftCurrentMin.can_value();
  msg.buf[7] = PDM_fanLeftCurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_406(){
  static StateCounter ctr;
  msg.id = 406;
  msg.len = 8;

  PDM_fanLeftVoltAvg = fanl_volt_sens.avg();
  PDM_fanLeftVoltMax = fanl_volt_sens.max();
  PDM_fanLeftVoltMin = fanl_volt_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanLeftVoltAvg.can_value();
  msg.buf[3] = PDM_fanLeftVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_fanLeftVoltMax.can_value();
  msg.buf[5] = PDM_fanLeftVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_fanLeftVoltMin.can_value();
  msg.buf[7] = PDM_fanLeftVoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_407(){
  static StateCounter ctr;
  msg.id = 407;
  msg.len = 8;

  PDM_wpCurrentAvg = wp_current_sens.avg();
  PDM_wpCurrentMax = wp_current_sens.max();
  PDM_wpCurrentMin = wp_current_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_wpCurrentAvg.can_value();
  msg.buf[3] = PDM_wpCurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_wpCurrentMax.can_value();
  msg.buf[5] = PDM_wpCurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_wpCurrentMin.can_value();
  msg.buf[7] = PDM_wpCurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_408(){
  static StateCounter ctr;
  msg.id = 408;
  msg.len = 8;

  PDM_wpVoltAvg = wp_volt_sens.avg();
  PDM_wpVoltMax = wp_volt_sens.max();
  PDM_wpVoltMin = wp_volt_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_wpVoltAvg.can_value();
  msg.buf[3] = PDM_wpVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_wpVoltMax.can_value();
  msg.buf[5] = PDM_wpVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_wpVoltMin.can_value();
  msg.buf[7] = PDM_wpVoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_409(){
  static StateCounter ctr;
  msg.id = 409;
  msg.len = 8;

  PDM_fanLeftDutyCycle = fan_left.actual();
  PDM_fanRightDutyCycle = fan_right.actual();
  PDM_wpDutyCycle = water_pump.actual();
  PDM_teensyTemp = tempmonGetTemp(); // built-in teensy function

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanLeftDutyCycle.can_value();
  msg.buf[3] = PDM_fanRightDutyCycle.can_value();
  msg.buf[4] = PDM_wpDutyCycle.can_value();
  msg.buf[5] = 0;
  msg.buf[6] = PDM_teensyTemp.can_value();
  msg.buf[7] = PDM_teensyTemp.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_410(){
  msg.id = 410;
  msg.len = 8;

  auto time = millis();
  msg.buf[1] = time;
  msg.buf[2] = time >> 8;
  msg.buf[3] = time >> 16;
  msg.buf[4] = time >> 24;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_PDM_412(){
  static StateCounter ctr;
  msg.id = 412;
  msg.len = 8;

  PDM_dataVoltAvg = data_volt_sens.avg();
  PDM_dataVoltMax = data_volt_sens.max();
  PDM_dataVoltMin = data_volt_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_dataVoltAvg.can_value();
  msg.buf[3] = PDM_dataVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_dataVoltMax.can_value();
  msg.buf[5] = PDM_dataVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_dataVoltMin.can_value();
  msg.buf[7] = PDM_dataVoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_413(){
  static StateCounter ctr;
  msg.id = 413;
  msg.len = 8;

  PDM_keepAliveVoltAvg = keepalive_volt_sens.avg();
  PDM_keepAliveVoltMax = keepalive_volt_sens.max();
  PDM_keepAliveVoltMin = keepalive_volt_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_keepAliveVoltAvg.can_value();
  msg.buf[3] = PDM_keepAliveVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_keepAliveVoltMax.can_value();
  msg.buf[5] = PDM_keepAliveVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_keepAliveVoltMin.can_value();
  msg.buf[7] = PDM_keepAliveVoltMin.can_value() >> 8;

  can2.write(msg);
}


void send_PDM_23(){
  static StateCounter ctr;
  msg.id = 273;
  msg.len = 8;

  PDM_boardTemp = board_temp.value();
  PDM_brakelightVoltAvg = brakelight_volt_sens.avg();
  //PDM_starterRelayVoltAvg = starter_volt_sens.avg();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_boardTemp.can_value();
  msg.buf[3] = PDM_boardTemp.can_value() >> 8;
  msg.buf[4] = PDM_brakelightVoltAvg.can_value();
  msg.buf[5] = PDM_brakelightVoltAvg.can_value() >> 8;
  msg.buf[6] = 0; //PDM_starterRelayVoltAvg.can_value();
  msg.buf[7] = 0; //PDM_starterRelayVoltAvg.can_value() >> 8;

  can2.write(msg);
}


void send_PDM_24(){
  static StateCounter ctr;
  Serial.println("sendingPDM24");
  msg.id = 274;
  msg.len = 8;

  PDM_fanLeftDutyCycle = fan_left.actual();
  PDM_fanRightDutyCycle = fan_right.actual();
  PDM_wpDutyCycle = water_pump.actual();
  PDM_teensyTemp = tempmonGetTemp(); // built-in teensy function

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanLeftDutyCycle.can_value();
  msg.buf[3] = PDM_fanRightDutyCycle.can_value();
  msg.buf[4] = PDM_wpDutyCycle.can_value();
  msg.buf[5] = 0;
  msg.buf[6] = PDM_teensyTemp.can_value();
  msg.buf[7] = PDM_teensyTemp.can_value() >> 8;

  can2.write(msg);
}



void send_PDM_25(){
  static StateCounter ctr;
  msg.id = 275;
  msg.len = 8;

  // eeprom.read(eeprom_engine_hours);
  // eeprom.read(eeprom_engine_minutes);
  // eeprom.read(eeprom_mileage);

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = eeprom_mileage.value();
  msg.buf[3] = eeprom_mileage.value() >> 8;
  msg.buf[4] = eeprom_engine_hours.value();
  msg.buf[5] = eeprom_engine_hours.value() >> 8;
  msg.buf[6] = eeprom_engine_minutes.value();
  msg.buf[7] = eeprom_engine_minutes.value() >> 8;

  can2.write(msg);
}

void send_can2(){

  /*
  static EasyTimer PDM_400_timer(10); // 10Hz
  if (PDM_400_timer.isup()){
    send_PDM_400();
  }
  */

  static EasyTimer PDM_401_timer(1); // 100Hz
  if (PDM_401_timer.isup()){
    send_PDM_401();
  }

  static EasyTimer PDM_402_timer(1); // 100Hz
  if (PDM_402_timer.isup()){
    send_PDM_402();
  }

  static EasyTimer PDM_403_timer(1); // 100Hz
  if (PDM_403_timer.isup()){
    send_PDM_403();
  }

  static EasyTimer PDM_404_timer(1); // 100Hz
  if (PDM_404_timer.isup()){
    send_PDM_404();
  }

  static EasyTimer PDM_405_timer(1); // 100Hz
  if (PDM_405_timer.isup()){
    send_PDM_405();
  }

  static EasyTimer PDM_406_timer(1); // 100Hz
  if (PDM_406_timer.isup()){
    send_PDM_406();
  }

  static EasyTimer PDM_407_timer(1); // 100Hz
  if (PDM_407_timer.isup()){
    send_PDM_407();
  }

  static EasyTimer PDM_408_timer(1); // 100Hz
  if (PDM_408_timer.isup()){
    send_PDM_408();
  }

  static EasyTimer PDM_409_timer(1); // 100Hz
  if (PDM_409_timer.isup()){
    send_PDM_409();
  }

  static EasyTimer PDM_410_timer(1); // 100Hz
  if (PDM_410_timer.isup()){
    send_PDM_410();
  }

  /*
  static EasyTimer PDM_411_timer(1); // 100Hz
  if (PDM_411_timer.isup()){
    send_PDM_411();
  }
  */

  static EasyTimer PDM_412_timer(1); // 100Hz
  if (PDM_412_timer.isup()){
    send_PDM_412();
  }

  static EasyTimer PDM_413_timer(1); // 50Hz
  if (PDM_413_timer.isup()){
    send_PDM_413();
  }

}

#endif

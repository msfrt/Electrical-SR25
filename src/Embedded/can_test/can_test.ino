// Dave Yonkers, 2022

#include <Adafruit_NeoPixel.h>
#include <BoardTemp.h>
#include <EasyTimer.h>
#include <FlexCAN_T4.h>
#include <StateCAN.h>

#include "Adafruit_GFX.h"
#include "ILI9341_t3n.h"
#include "SPI.h"
#include<string>
using std::string;
#define SPI0_DISP1

// can bus decleration
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;\
static CAN_message_t rxmsg;
// each bus has a total of 64 mailboxes
#define NUM_RX_STD_MAILBOXES 60
#define NUM_RX_EXT_MAILBOXES 2
#define NUM_TX_MAILBOXES 2
// limit the number of messages each bus can read for each loop cycle.
// Typically, only one message is recieved in the time that the loop can run,
// but a buildup can occur, and this limit can poll the bus to read messages
// while not getting stuck in an infinite loop
#define MAX_CAN_FRAME_READ_PER_CYCLE 5

// keep track of the time elapsed between loop iterations
unsigned long previousUpdateTime = 0;

// CAN message and read definitions
#include "CAN/raptor_CAN1.hpp"

EasyTimer debug(50);  // debugging timer

void setup() {

  // initilize CAN busses
  can1.begin();
  can1.setBaudRate(500000);
  set_mailboxes();

  // initialze serial coms
  Serial.begin(115200);

  previousUpdateTime = millis();

  debug.set_delay_millis(10000);

  can1.mailboxStatus();
}

void loop() {
  unsigned long elapsed = millis() - previousUpdateTime;
  previousUpdateTime = millis();

  // read any incoming CAN messages
  // Serial.println("Reading CAN:");
  readCan();
  // can1.events();

  static EasyTimer timer(1); // 50Hz
  if (timer.isup()){
    send_ATCC_303();
  }
}

void test_callback1(const CAN_message_t &imsg) {
  // Serial.println("Recieved 1");
  decode_raptor_CAN1(imsg);
}

void test_callback2(const CAN_message_t &imsg) {
  // Serial.println("Recieved 2");
  decode_raptor_CAN1(imsg);
}

void set_mailboxes() {
  // to view mailbox status, you can use the member function mailboxStatus().
  // Don't put it in a fast loop, though, because you may actually affect how
  // the chips moves things around

  can1.setMaxMB(64);  // use all mailboxes of course

  for (int i = 0; i < NUM_RX_STD_MAILBOXES; i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }
  for (int i = NUM_RX_STD_MAILBOXES;
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES); i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, RX, EXT);
  }
  for (int i = (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES);
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES + NUM_TX_MAILBOXES);
       i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }

  // be sure to assign at least one mailbox to each message that you want to
  // read. filtering allows us to avoid using clock cycles to read messages that
  // we have no interest in. it also reserves a slot for messages as they are
  // recieved.
  can1.setMBFilter(REJECT_ALL);
  can1.setMBFilter(MB0, C50_gpsSpeed.get_msg_id());
  can1.setMBFilter(MB1, PM_motorSpeed.get_msg_id());
  can1.setMBFilter(MB2, PM_motorTemp.get_msg_id());
  can1.setMBFilter(MB3, PM_dcBusVolt.get_msg_id());
  can1.setMBFilter(MB4, PM_commandedTorque.get_msg_id());
  can1.setMBFilter(MB5, VCU_radFanLDuty.get_msg_id());
  can1.setMBFilter(MB6, VCU_radFanRDuty.get_msg_id());
  can1.setMBFilter(MB7, ATCC_angularWheelFreqRR.get_msg_id());
  can1.setMBFilter(MB8, ATCC_coolantTempInverterOut.get_msg_id());
  can1.setMBFilter(MB9, ATCC_coolantTempInverterIn.get_msg_id());
  can1.setMBFilter(MB10, ATCC_coolantTempMotorIn.get_msg_id());
  can1.setMBFilter(MB11, 0);
  can1.setMBFilter(MB12, 0);
  can1.setMBFilter(MB13, 0);
  can1.setMBFilter(MB14, 0);
}

//Front ATCC
void send_ATCC_303(){
  // static definition - only defined once (like a global variable, but is local to this function only)
  static StateCounter ctr;

  // update per message
  rxmsg.id = 303;
  rxmsg.len = 8;
  Serial.println("sendingATCC303");

/*
  // automatically does calcs
  ATCC_coolantTempMotorIn = voltage_to_temp(ATCC_coolantTempMotorIn.avg());
  ATCC_coolantTempInverterIn = voltage_to_temp(ATCC_coolantTempInverterIn.avg());
  ATCC_coolantTempInverterOut = voltage_to_temp(ATCC_coolantTempInverterOut.avg());
*/

  ATCC_coolantTempMotorIn = 20;
  ATCC_coolantTempInverterIn = 20;
  ATCC_coolantTempInverterOut = 20;

  // load up the message buffer
  rxmsg.buf[0] = ctr.value();
  rxmsg.buf[1] = 0;
  rxmsg.buf[2] = ATCC_coolantTempMotorIn.can_value();
  rxmsg.buf[3] = ATCC_coolantTempMotorIn.can_value() >> 8;
  rxmsg.buf[4] = ATCC_coolantTempInverterIn.can_value();
  rxmsg.buf[5] = ATCC_coolantTempInverterIn.can_value() >> 8;
  rxmsg.buf[6] = ATCC_coolantTempInverterOut.can_value();
  rxmsg.buf[7] = ATCC_coolantTempInverterOut.can_value() >> 8;

  Serial.println(ATCC_coolantTempMotorIn.can_value());
  Serial.println(ATCC_coolantTempInverterIn.can_value()); 
  Serial.println(ATCC_coolantTempInverterOut.can_value());

  can1.write(rxmsg);
}

/**
 *  Reads a CAN message if available and then sends it to thr
 *  proper decoding funciton
 **/
void readCan() {
  int count = 0;
  while (can1.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_raptor_CAN1(rxmsg);
    count++;
  }

}

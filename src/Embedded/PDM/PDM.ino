#include <PWMControl.h>

// Dave Yonkers, 2022

#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <BoardTemp.h>
#include <EepromHelper.h>

// CAN Bus Declaration
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
static CAN_message_t rxmsg;

#define NUM_RX_STD_MAILBOXES 32
#define NUM_RX_EXT_MAILBOXES 2
#define NUM_TX_MAILBOXES 30
#define MAX_CAN_FRAME_READ_PER_CYCLE 5  // Limit per loop iteration

// Global Variable Definitions
const int GLO_read_resolution_bits = 12;
const int GLO_max_analog_write_pwm = 255;

const int GLO_brakelight_teensy_pin = 4;
const int VCU_brakelight = 0;
const int GLO_data_circuit_teensy_pin = 5;
const int GLO_NeoPixel_teensy_pin = 2;

int GLO_NeoPixel_brightness_percent = 10;
Adafruit_NeoPixel GLO_obd_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

BoardTempDiode board_temp(21, GLO_read_resolution_bits, 28.1, 594);
EasyTimer board_temp_sample_timer(50);

// EEPROM
const int eeprom_cs_pin = 9;
EEPROM_25LC128 eeprom(eeprom_cs_pin);

// Timer Definitions
EasyTimer engine_time_update_timer(1);
EasyTimer odometer_update_timer(2);

// EEPROM Signals
#include "EEPROM_sigs.hpp"

// Sensor Sampling Definitions
#include "sensors.hpp"

// Fan & Water Pump Control
#include "fans.hpp"

// CAN Message Definitions
#include "CAN/CAN1.hpp"
#include "CAN/CAN2.hpp"
#include "can_send.hpp"

// Miscellaneous Functions
#include "misc_fcns.hpp"

// On-Board Diagnostics
#include "obd.hpp"

// Debugging Timer
EasyTimer debug(2);
const bool GLO_debug = false;

<<<<<<< HEAD
// Global Fan Speed Signal (Controlled by CAN)
int fan_signal = 3; // Default value
=======
void setup() { //high 18 low 26

  analogReadResolution(GLO_read_resolution_bits);
  

  // begin OBD Neopixel
  GLO_obd_neopixel.begin();
  GLO_obd_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
  GLO_obd_neopixel.setPixelColor(0, 255, 0, 0); // red
  GLO_obd_neopixel.show();

  // Initialize serial communication
  Serial.begin(112500);

  //initialize the CAN Bus and set its baud rate to 1Mb
  can1.begin();
  // can1.setBaudRate(1000000);
  can1.setBaudRate(500000);
  can2.begin();
  can2.setBaudRate(1000000);
  set_mailboxes();

  // initialize the ADC sensors
  initialize_ADCs();

  // initialize SPI communication
  SPI.begin();

  // initialize the data circuit pin
  pinMode(GLO_data_circuit_teensy_pin, OUTPUT);
  // turn the data circuit on
  digitalWrite(GLO_data_circuit_teensy_pin, HIGH);
  // initialize brakelight pin
  pinMode(GLO_brakelight_teensy_pin, OUTPUT);

  // EEPROM
  // eeprom.begin();

  // write the eeprom variables that are not commented out in the write eeprom function in the EEPROM_sigs file
  // initialize_eeprom_variables();

  GLO_obd_neopixel.setPixelColor(0, 0, 255, 0); // green
  GLO_obd_neopixel.show();

  // board temp initialization
  board_temp.begin();

  // neat brakelight animation
  brakelight_startup();

  //initializes the fans off
  //CMD_fanLeftOverride = 0;
  //CMD_fanRightOverride = 0;
>>>>>>> origin/dev

// CAN Message Handler
void canReceiveHandler(const CAN_message_t &msg) {
    if (msg.id == 0x200) {  // Replace with actual CAN ID for fan control
        fan_signal = msg.buf[0];  // Extract fan speed value (0-100%)
        fan_signal = constrain(fan_signal, 0, 100);
    }
}

// placeholder function for undefined
void engine_timer(int hours, int minutes) {
    Serial.println("Engine timer update (placeholder function)");
}

void odometer(float speed, int mileage) {
    Serial.println("Odometer update (placeholder function)");
}

const bool testMode = true;
const int testNum = 2;

void setup() {
    // Initialize everything
    analogReadResolution(GLO_read_resolution_bits);
    Serial.begin(115200);
    SPI.begin();
  
    // begin OBD Neopixel
    GLO_obd_neopixel.begin();
    GLO_obd_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
    GLO_obd_neopixel.setPixelColor(0, 255, 0, 0); // red
    GLO_obd_neopixel.show();


    can1.begin();
    can1.setBaudRate(500000);
    can2.begin();
    can2.setBaudRate(1000000);

    set_mailboxes();

    can2.setMaxMB(16);
    can2.enableFIFO();
    can2.enableFIFOInterrupt();
    can2.onReceive(FIFO, canReceiveHandler);

    initialize_ADCs();
    pinMode(GLO_data_circuit_teensy_pin, OUTPUT);
    digitalWrite(GLO_data_circuit_teensy_pin, HIGH);
    //pinMode(GLO_brakelight_teensy_pin, OUTPUT);

    //board_temp.begin();
    brakelight_startup();

    GLO_obd_neopixel.setPixelColor(0, 0, 255, 0); // green
    GLO_obd_neopixel.show();

    CMD_fanLeftOverride = 0;
    CMD_fanRightOverride = 0;
}

void loop() {
    static unsigned long t_start = millis();
    float elapsed = (millis() - t_start) / 1000.0; // time in seconds

    if (testMode) {
      if (testNum == 1) {
        // Create a sine wave oscillation between 0 and 100
        // Adjust frequency (e.g. 0.1 Hz = one full cycle every 10 seconds)
        float frequency = 0.06;
        float amplitude = 50.0;
        float offset = 50.0;

        fan_signal = offset + amplitude * sin(2 * PI * frequency * elapsed);
      } else if (testNum == 2) {
        fan_signal = 5;
      }
    }

    updateFanSpeed(fan_signal);

    sample_ADCs();
    if (board_temp_sample_timer.isup()) {
        board_temp.sample();
    }

    brakelight_run();

    // **Fix: Pass 4 Parameters to set_pwm()**
    //fan_left.set_pwm(0, 0, 2, fan_signal);
    //fan_right.set_pwm(0, 0, 2, fan_signal);

    CMD_fanLeftOverride = fan_signal;
    CMD_fanRightOverride = fan_signal;

    fan_left.set_pwm(2);
    fan_right.set_pwm(2);

    delay(1000); 
}

void set_mailboxes() {
    can2.setMaxMB(64);
    can2.enableFIFO();
    can2.setMB(MB4, RX, STD);
    can2.setMB(MB5, RX, STD);
    can2.setMB(MB6, RX, STD);
    can2.setMB(MB7, RX, STD);
    can2.setMB(MB8, RX, STD);
    can2.setMB(MB9, RX, STD);
    can2.setMB(MB10, RX, STD);
    can2.setMB(MB11, RX, STD);
    can2.setMB(MB12, RX, EXT);
    can2.setMB(MB13, RX, EXT);
    can2.setMB(MB14, RX, EXT);
    can2.setMB(MB15, RX, EXT);

    can1.setMaxMB(64);
    can1.enableFIFO();
    can1.setMB(MB4, RX, STD);
    can1.setMB(MB5, RX, STD);
    can1.setMB(MB6, RX, STD);
    can1.setMB(MB7, RX, STD);
    can1.setMB(MB8, RX, STD);
    can1.setMB(MB9, RX, STD);
    can1.setMB(MB10, RX, STD);
    can1.setMB(MB11, RX, STD);
    can1.setMB(MB12, RX, STD);
    can1.setMB(MB13, RX, STD);
    can1.setMB(MB14, RX, STD);
    can1.setMB(MB15, RX, STD);
    can1.setMB(MB16, RX, EXT);
    can1.setMB(MB17, RX, EXT);
    can1.setMB(MB18, RX, EXT);
    can1.setMB(MB19, RX, EXT);
}

void read_CAN() {
    int count = 0;
    while (can1.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
        decode_CAN1(rxmsg);
        count++;
    }

    count = 0;
    while (can2.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
        decode_CAN2(rxmsg);
        count++;
    }
}

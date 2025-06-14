#ifndef BRAKELIGHT_STARTUP_HPP
#define BRAKELIGHT_STARTUP_HPP

#include <Arduino.h>

// Durations in milliseconds
const int dash = 400;
const int dot = 100;
const int gap = 200;  // Gap between signals

struct MorseStartup {
  const int* message;
  int length;
  int index = 0;
  bool led_on = false;
  unsigned long last_change = 0;
  bool active = false;
  unsigned int current_duration = 0;

  void begin(const int* msg, int len) {
    message = msg;
    length = len;
    index = 0;
    led_on = false;
    last_change = millis();
    active = true;
    current_duration = 0;
    analogWrite(GLO_brakelight_teensy_pin, 0);
    Serial.println("Startup Morse sequence beginning.");
  }

  void update() {
    if (!active) return;

    unsigned long now = millis();
    if (now - last_change >= current_duration) {
      last_change = now;

      if (led_on) {
        // Turn off LED
        analogWrite(GLO_brakelight_teensy_pin, 0);
        led_on = false;
        current_duration = gap;
        Serial.println("OFF");

        index++;
        if (index >= length) {
          active = false;
          Serial.println("Startup Morse sequence complete.");
        }
      } else {
        if (index < length) {
          led_on = true;
          current_duration = (message[index] == 1) ? dash : dot;
          analogWrite(GLO_brakelight_teensy_pin, 255);
          Serial.print((message[index] == 1) ? "Dash" : "Dot");
          Serial.print(" - ON for ");
          Serial.print(current_duration);
          Serial.println(" ms");
        }
      }
    }
  }

  bool is_active() const {
    return active;
  }
};

#endif

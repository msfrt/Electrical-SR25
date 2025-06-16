#ifndef MISC_FUNCTIONS_HPP
#define MISC_FUNCTIONS_HPP

#include "brakelight_startup.hpp" 
static MorseStartup startup_sequence;

// template <class T1, class T2>
// void engine_timer(EEPROM_Value<T1> &hours, EEPROM_Value<T2> &minutes){
//   static unsigned int last_minute_millis = 0;

//   // if the engine is not on (state 2), keep setting the last minute to the current time. This ensures that the
//   // next minute is only triggered when the engine is actuall on.
//   if (GLO_engine_state != 2){
//     last_minute_millis = millis();
//   }

//   if (millis() > last_minute_millis + 60000){  // 60,000ms = 60s

//     // minutes AND hours have changed
//     if (eeprom.read(minutes) >= 59){
//       hours = eeprom.read(hours) + 1;

//       minutes = 0;
//       eeprom.write(hours);
//       eeprom.write(minutes);

//     // just minutes have changed
//     } else {
//       minutes = eeprom.read(minutes) + 1;
//       eeprom.write(minutes);
//     }

//     // update the last minute timer
//     last_minute_millis = millis();
//   }
// }


// call the odemeter at a decently fast rate for semi-accurate calculations. Beware, if you call this too fast, the
// time difference may be close to 0, and therefore may not. MILEAGE STORED IS FACTORED BY 10
// template <class T1>
// void odometer(StateSignal &speed, EEPROM_Value<T1> &mileage10){
//   static unsigned int last_calc_time = 0;
//   static float calc_period_seconds = 0.0;
//   static float miles10_per_second = 0;
//   static float running_mileage10 = 0; // counts mileage10 since start up. Once it reaches 1, the value in memory is
//                                       // incremented and this is reset to 0


//   // determine the number of seconds for this calculation
//   calc_period_seconds = (millis() - last_calc_time) / 1000.0;
//   last_calc_time = millis();

//   // if the car is moving forward, the speed signal is valid, and the car is determined to be on: increment mileage
//   if (speed.value() > 0 && speed.is_valid() && GLO_engine_state == 2){

//     // turn miles per hour to miles10 per second
//     miles10_per_second = (speed.value() / 3600.0) * 10;

//     // calulate the mileage10 since the last calculation and add it to the running total
//     running_mileage10 += miles10_per_second * calc_period_seconds;

//     // if there's been a half of a mile driven, increment the mileage and write it
//     if (running_mileage10 >= 5.0){
//       mileage10 = mileage10.value() + 1;
//       running_mileage10 -= 5.0; // subtract one mile10
//       eeprom.write(mileage10);
//     }
//   }
// }





// this function takes a reference to the engine state variable and returns a reference to the same variable.
// the engine state will be updated if determined necessary.
// int &determine_engine_state(int &engine_state){
//   static unsigned long cooldown_until_time;
//   static unsigned long current_time;

//   current_time = millis(); // update the time

//   // determine if engine is cranking
//   if (starter_volt_sens.last_calc_avg() >= GLO_cranking_starter_volt_threshold &&
//       M400_rpm.value() <= GLO_cranking_rpm_threshold){
//     engine_state = 1; // cranking

//   // determine if engine is on
//   } else if (M400_rpm.value() >= GLO_engine_on_rpm_threshold){
//     engine_state = 2; // on

//   // determine if cooldown or off
//   } else {
//     // was the engine just running? If it was and we made it to the else statement, trigger cooldown mode.
//     // note: this can only be triggered if the engine was determined previously to be on.
//     if (engine_state == 2){
//       cooldown_until_time = current_time + GLO_engine_cooldown_duration;
//     }

//     // should we still be in the cooldown? Otherwise the engine is off
//     if (current_time <= cooldown_until_time){
//       engine_state = 3;
//     } else {
//       engine_state = 0;
//     }
//   }


//   return engine_state;
// }

// bool determine_logging_state(int &engine_state, const unsigned long &timeout_dur){
//   static unsigned long log_until_time;
//   static bool log_bool = 0;

//   if (engine_state == 1 || engine_state == 2 || engine_state == 3){
//     log_until_time = millis() + timeout_dur;
//   }

//   // set le bool
//   if (millis() < log_until_time){
//     log_bool = 1;
//   } else {
//     log_bool = 0;
//   }

//   return log_bool;
// }

bool has_called_startup = false;

bool brakelight_run() {

  if (VCU_brakeLightCmd.can_value() == 1) {
    analogWrite(GLO_brakelight_teensy_pin, 255);
    return true;
  } else {
    if (!has_called_startup) {
      const int morse_message[] = {1,1, 0,0,0, 0,0,1}; // SOS
      startup_sequence.begin(morse_message, sizeof(morse_message)/sizeof(morse_message[0]));
      has_called_startup = true;
    }

    if (millis() > 5000) {
      analogWrite(GLO_brakelight_teensy_pin, 0);
      Serial.println("brakelight off");
    }

    startup_sequence.update(); // non-blocking update

    return startup_sequence.is_active();  // false = LED off
  }
}



void brakelight_start(){

  analogWrite(GLO_brakelight_teensy_pin, 0);

}


#endif

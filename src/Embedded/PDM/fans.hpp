#ifndef FANS_HPP
#define FANS_HPP

#include <PWMControl.h>
#include <StateCAN.h>

#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

extern int fan_signalL;
extern int fan_signalR;
extern int wp_signal;

// **Left Fan Variables**
int fanl_pin = 8;
int fanl_min_pwm = 0;
int fanl_max_pwm = 255;
int fanl_ss_dur = 5000; // Soft start duration in milliseconds
int fanl_update_freq = 10;
int fanl_pwm_freq_norm = 40;
int fanl_pwm_freq_ss = 420;

// **Right Fan Variables**
int fanr_pin = 7;
int fanr_min_pwm = 0;
int fanr_max_pwm = 255;
int fanr_ss_dur = 5000;
int fanr_update_freq = 10;
int fanr_pwm_freq_norm = 40;
int fanr_pwm_freq_ss = 420;

StateSignal fan_left_row_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal fan_left_col_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal fan_left_override(16, true, 0, 0, 0, 100, 1);

StateSignal fan_right_row_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal fan_right_col_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal fan_right_override(16, true, 0, 0, 0, 100, 1);

// pwm fans
PWMDevice fan_left(fanl_pin, 12, 14, 10, 10000, fan_left_row_signal, fan_left_col_signal, fan_left_override,
                   fanl_min_pwm, fanl_max_pwm, fanl_ss_dur, fanl_update_freq, fanl_pwm_freq_norm, fanl_pwm_freq_ss);

PWMDevice fan_right(fanr_pin, 12, 14, 10, 10000, fan_right_row_signal, fan_right_col_signal, fan_right_override,
                    fanr_min_pwm, fanr_max_pwm, fanr_ss_dur, fanr_update_freq, fanr_pwm_freq_norm, fanr_pwm_freq_ss);

// **Water Pump Variables**
int wp_pin = 6;
int wp_min_pwm = 0;
int wp_max_pwm = 255;
int wp_ss_dur = 5000;
int wp_update_freq = 10;
int wp_pwm_freq_norm = 40;
int wp_pwm_freq_ss = 420;

// **Declare StateSignal for Water Pump**
StateSignal wp_row_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal wp_col_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal wp_override(16, true, 0, 0, 0, 100, 1);

// water pump
PWMDevice water_pump(wp_pin, 12, 14, 10, 10000, wp_row_signal, wp_col_signal, wp_override,
                     wp_min_pwm, wp_max_pwm, wp_ss_dur, wp_update_freq, wp_pwm_freq_norm, wp_pwm_freq_ss);

void updateFanSpeed(int canFanL, int canFanR, int canWp) {
    fan_signalL = constrain(canFanL, 0, 100); // Ensure valid range (0-100%)
    fan_signalR = constrain(canFanR, 0, 100);
    wp_signal = constrain(canWp, 0, 100);

    // Use override to set PWM directly
    fan_left.set_pwm(0, 0, 2, fan_signalL);
    fan_right.set_pwm(0, 0, 2, fan_signalR);
    water_pump.set_pwm(0,0,2, wp_signal);
}

#endif
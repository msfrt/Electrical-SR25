#ifndef LIGHT_BAR_SOC_H
#define LIGHT_BAR_SOC_H

#include <Adafruit_NeoPixel.h>
#include <EasyTimer.h>
#include <FlexCAN_T4.h>
#include <StateCAN.h>

#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"
#include "LightBar.hpp"
#include "arduino.h"

class LightBarSOC : public LightBar {
    private:
    
    int min_;  ///< The minimum bound for the SOC bar to start lighting up
    int max_;  ///< The maximum bound for the SOC bar light up before signalling
             ///< an upshift

    protected:
    public:
    unsigned long start = 0;
    int count = 0;
    //StateSignal & soc_signal_;
    StateSignal & soc_signal_;
    /** Constructor */
    LightBarSOC(Adafruit_NeoPixel &lights, int first_index, int num_leds,
              StateSignal & soc_signal, int min_soc, int max_soc);

    /** Destructor */
    virtual ~LightBarSOC(){};

    /** Copy constructor disabled */
    LightBarSOC(const LightBarSOC &) = delete;
    /** Assignment operator disabled */
    void operator=(const LightBarSOC &) = delete;

    virtual void Initialize() override;
    virtual void Update(unsigned long &elapased) override;

    //Getters
    //float soc() {return soc_signal_;}
};

LightBarSOC::LightBarSOC(Adafruit_NeoPixel &lights, int first_index, int num_leds,
              StateSignal & soc_signal, int min_soc, int max_soc) 
              
        : LightBar(lights, first_index, num_leds),
        min_(min_soc),
        max_(max_soc),
        soc_signal_(soc_signal) {
    
        }

/**
 * Initialize the lights by clearing them.
 */
void LightBarSOC::Initialize() { LightBar::Initialize();}

void LightBarSOC::Update(unsigned long & elapsed) {
    // Reset the LEDs from the previous battery percentage value
    for (int i = GetFirstLEDIndex(); i <= GetLastLEDIndex(); i++) {
        lights_.setPixelColor(i, 0, 0, 0);
    }

    if(elapsed == 2) {
        count += 1;
    }
    
    float value = (PM_commandedTorque.can_value() - 0.0) / (1500 - 0.0);
    int no_of_leds = value * GetLastLEDIndex();
    for (int led = GetFirstLEDIndex(); led <= GetLastLEDIndex(); led++) {
        if(value >= 0.80) {
            //green
            if(led <= no_of_leds) {
                lights_.setPixelColor(led, 0, 50, 0);
            }
        } else if(value < 0.80 && value >= 0.21) {
            //orange
            if(led <= no_of_leds) {
                lights_.setPixelColor(led, 50, 25, 0);
            }
        } else {
            //red
            if(led <= no_of_leds) {
                lights_.setPixelColor(led, 50, 0, 0);
            }
        }
    }
    LightBar::Update(elapsed);
}

#endif
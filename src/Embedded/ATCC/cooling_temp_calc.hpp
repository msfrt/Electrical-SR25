#define cooling_temp_calc

#include <StateCAN.h>
#include <math.h>

// accounts for 50% of rotor being slots
float voltage_to_temp(float voltage) {
    float result = 0.4484 * pow(voltage,4) -
           6.3663 * pow(voltage,3) +
           31.482 * pow(voltage,2) -
           85.979 * voltage + 
           146.03;
    return result;
}
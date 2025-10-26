#define cooling_temp_calc

#include <StateCAN.h>
#include <math.h>

// accounts for 50% of rotor being slots
float voltage_to_temp(float voltage) {
    float result = 1215 * pow(voltage,4) -
           2571.6 * pow(voltage,3) +
           -646.74 * pow(voltage,2) -
           119.11 * voltage + 
           121.11;
    return result;
}
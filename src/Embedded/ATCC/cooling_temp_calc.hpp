#define cooling_temp_calc

#include <StateCAN.h>
#include <math.h>

// accounts for 50% of rotor being slots
float voltage_to_temp(float voltage) {
    float result = 5.1603 * pow(voltage,4) -
           47.621 * pow(voltage,4) +
           149.7 * pow(voltage,4) -
           199.57 * voltage + 
           92.933;
    return result;
}
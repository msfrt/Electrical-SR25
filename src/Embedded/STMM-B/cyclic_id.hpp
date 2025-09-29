#ifndef CYCLIC_ID_HPP
#define CYCLIC_ID_HPP

#include <vector>
#include <algorithm>

#include "bms_controller.hpp"

using std::vector;
using std::pair;
using std::sort;

bool comparator(const pair<int, float> &a, const pair<int, float> &b){
    return a.second > b.second;
}

// clamps nonesense values to a definitive value 
// int clamp(float val){
//     if (val > 55){
//         if (val > 127){
//             return 127;
//         }
//         return val;
//     } else if (val < 5){
//         if (val < -128){
//             return -128;
//         }
//         return val;
//     } else{
//         return val;
//     }
// }

// this fuction returns the unsorted vector of vectors that is useful for incrementing the 
// CURRENT module that is being sent over CAN
// scale up for BMS pls
vector<pair<int, float>> get_mod_volts(const int &seg){
    
    // the idx of each nested vector is the local id/module within the segment 
    // {global ID, module voltage}

    // some wack shit is up if the ID turns out to be negative, good for a default value 
    // until the voltage values get updated again
    // vector<pair<int, float>> mod_temps = 
    //                 {{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0}};
    vector<pair<int, float>> mod_volts = 
                        {{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0}};
    switch (seg){
    
        case 1:
        mod_volts = {{100, module_voltage_0}, {101, module_voltage_1}, {102, module_voltage_2}, 
                    {103, module_voltage_3}, {104, module_voltage_4}, {105, module_voltage_5}, 
                    {106, module_voltage_6}, {107, module_voltage_7}, {108, module_voltage_8}, 
                    {109, module_voltage_9}};
        break;
        
        case 2:
        mod_volts = {{200, module_voltage_0}, {201, module_voltage_1}, {202, module_voltage_2}, 
                    {203, module_voltage_3}, {204, module_voltage_4}, {205, module_voltage_5}, 
                    {206, module_voltage_6}, {207, module_voltage_7}, {208, module_voltage_8}, 
                    {209, module_voltage_9}};
        break;

        case 3:
        mod_volts = {{300, module_voltage_0}, {301, module_voltage_1}, {302, module_voltage_2}, 
                    {303, module_voltage_3}, {304, module_voltage_4}, {305, module_voltage_5}, 
                    {306, module_voltage_6}, {307, module_voltage_7}, {308, module_voltage_8}, 
                    {309, module_voltage_9}};
        break;

        case 4:
        mod_volts = {{400, module_voltage_0}, {401, module_voltage_1}, {402, module_voltage_2}, 
                    {403, module_voltage_3}, {404, module_voltage_4}, {405, module_voltage_5}, 
                    {406, module_voltage_6}, {407, module_voltage_7}, {408, module_voltage_8}, 
                    {409, module_voltage_9}};
        break;

        case 5:
        mod_volts = {{500, module_voltage_0}, {501, module_voltage_1}, {502, module_voltage_2}, 
                    {503, module_voltage_3}, {504, module_voltage_4}, {505, module_voltage_5}, 
                    {506, module_voltage_6}, {507, module_voltage_7}, {508, module_voltage_8}, 
                    {509, module_voltage_9}};
        break;

        case 6:
        mod_volts = {{600, module_voltage_0}, {601, module_voltage_1}, {602, module_voltage_2}, 
                    {603, module_voltage_3}, {604, module_voltage_4}, {605, module_voltage_5}, 
                    {606, module_voltage_6}, {607, module_voltage_7}, {608, module_voltage_8}, 
                    {609, module_voltage_9}};
        break;

        case 7:
        mod_volts = {{700, module_voltage_0}, {701, module_voltage_1}, {702, module_voltage_2}, 
                    {703, module_voltage_3}, {704, module_voltage_4}, {705, module_voltage_5}, 
                    {706, module_voltage_6}, {707, module_voltage_7}, {708, module_voltage_8}, 
                    {709, module_voltage_9}};
        break;

        case 8:
        mod_volts = {{800, module_voltage_0}, {801, module_voltage_1}, {802, module_voltage_2}, 
                    {803, module_voltage_3}, {804, module_voltage_4}, {805, module_voltage_5}, 
                    {806, module_voltage_6}, {807, module_voltage_7}, {808, module_voltage_8}, 
                    {809, module_voltage_9}};
        break;
    }
    
    return mod_volts;

}

// returns the sorted vector of vectors that is useful for grabbing the max, min, and average of the module temps
vector<pair<int, float>> sort_mod_volts(vector<pair<int, float>> &mod_volts){
    // create a copy to sort
    vector<pair<int, float>> sorted_mod_volts = mod_volts;
    // sort it
    // O(10), constant time sorting since constant input size
    sort(sorted_mod_volts.begin(), sorted_mod_volts.end(), comparator);
    return sorted_mod_volts;
}

// // returns the modulo value of 11
// int get_teensy_id(int &counter) {
//     return counter % 11;
// }

// dealing with the unsorted nested vectors

// returns the global id of the module (good for incrementing through the unsorted list)
// int get_global_id(int &counter, vector<pair<int, float>> &mod_temps) {
//     return (mod_temps.at(counter)).first;
// }

// returns the module temp (good for incrementing through the unsorted list)
float get_module_volt(int &counter, vector<pair<int, float>> &mod_volts){
    return (mod_volts.at(counter)).second;
}

// returns the average temperature of all of the modules in the segment  
float get_avg_temp(vector<pair<int, float>> &mod_volts){
    float sum = 0;
    for (const auto &element : mod_volts){
        sum += element.second;
    }
    return sum/mod_volts.size();
}

// dealing with the sorted nested vectors

// returns the min temp in a sorted nested vector
float get_min_volt(vector<pair<int, float>> &sorted_mod_volts){
    // return (sorted_mod_temps.at(11)).second;
    return (sorted_mod_volts.at(9)).second;
}

// returns the max temp in a sorted nested vector
float get_max_volt(vector<pair<int, float>> &sorted_mod_volts){
    return (sorted_mod_volts.at(0)).second;
}

// returns the min temp local id in a sorted nested vector
int get_min_id(vector<pair<int, float>> &sorted_mod_volts){
    // converts the global ID to a local one
    // return (sorted_mod_temps.at(11)).first % 80;
    return (sorted_mod_volts.at(9)).first % 80;
}

// returns the max temp local id in a sorted nested vector
int get_max_id(vector<pair<int, float>> &sorted_mod_volts){
    // converts the global ID to a local one
    return (sorted_mod_volts.at(0)).first % 80;
}

// int main() {
    
//     int segment_number = 0;
//     for(int counter = 0; counter <= 95; counter++) {
//         cout << "Teensy ID: " << get_teensy_id(counter) << ", ";
//         cout << "Global ID: " << get_global_id(counter, segment_number) << ", ";
//         cout << "Counter: " << counter << ", ";
//         cout << "Segment ID: " << segment_number << endl;
//     }
//     return 0;
// }

#endif

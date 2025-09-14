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
int clamp(float val){
    if (val > 55){
        if (val > 127){
            return 127;
        }
        return val;
    } else if (val < 5){
        if (val < -128){
            return -128;
        }
        return val;
    } else{
        return val;
    }
}

float voltage_to_ENEPAQ_cell_temp(float v) {
    // return -740.85 * pow(v,5) + 
    //         7056.8 * pow(v,4) +
    //         -26800 * pow(v,3) +
    //          50732 * pow(v,2) +
    //         -47967 * pow(v,1) +
    //         18213;
    return  155.35203 * pow(v,4) -
           1381.39248 * pow(v,3) +
           4484.86765 * pow(v,2) -
           6407.60322 * pow(v,1) +
           3457.41389;
}

// this fuction returns the unsorted vector of vectors that is useful for incrementing the 
// CURRENT module that is being sent over CAN
vector<pair<int, float>> get_mod_temps(const int &seg){
    
    // the idx of each nested vector is the local id/module within the segment 
    // {global ID, module temp}
    // global IDs are +80 for each segement

    // some wack shit is up if the ID turns out to be negative, good for a default value 
    // until the temp values get updated again
    // vector<pair<int, float>> mod_temps = 
    //                 {{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0}};
    vector<pair<int, float>> mod_temps = 
                        {{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0}};
    switch (seg){
    
        case 1:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_0)}, {1, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_1)}, {2, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_2)}, 
                    {3, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_3)}, {4, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_4)}, {5, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_5)}, 
                    {6, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_6)}, {7, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_7)}, {8, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_8)}, 
                    {9, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_9)}};
        break;
        
        case 2:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_0)}, {1, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_1)}, {2, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_2)}, 
                    {3, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_3)}, {4, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_4)}, {5, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_5)}, 
                    {6, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_6)}, {7, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_7)}, {8, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_8)}, 
                    {9, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_9)}};
        break;

        case 3:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_0)}, {1, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_1)}, {2, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_2)}, 
                    {3, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_3)}, {4, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_4)}, {5, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_5)}, 
                    {6, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_6)}, {7, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_7)}, {8, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_8)}, 
                    {9, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_9)}};
        break;

        case 4:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_0)}, {1, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_1)}, {2, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_2)}, 
                    {3, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_3)}, {4, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_4)}, {5, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_5)}, 
                    {6, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_6)}, {7, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_7)}, {8, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_8)}, 
                    {9, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_9)}};
        break;

        case 5:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_0)}, {1, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_1)}, {2, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_2)}, 
                    {3, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_3)}, {4, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_4)}, {5, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_5)}, 
                    {6, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_6)}, {7, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_7)}, {8, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_8)}, 
                    {9, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_9)}};
        break;

        case 6:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_0)}, {1, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_1)}, {2, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_2)}, 
                    {3, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_3)}, {4, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_4)}, {5, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_5)}, 
                    {6, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_6)}, {7, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_7)}, {8, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_8)}, 
                    {9, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_9)}};
        break;

        case 7:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_0)}, {1, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_1)}, {2, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_2)}, 
                    {3, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_3)}, {4, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_4)}, {5, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_5)}, 
                    {6, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_6)}, {7, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_7)}, {8, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_8)}, 
                    {9, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_9)}};
        break;

        case 8:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_0)}, {1, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_1)}, {2, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_2)}, 
                    {3, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_3)}, {4, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_4)}, {5, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_5)}, 
                    {6, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_6)}, {7, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_7)}, {8, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_8)}, 
                    {9, voltage_to_ENEPAQ_cell_temp(module_temp_voltage_9)}};
        break;
    }
    
    return mod_temps;

}

// returns the sorted vector of vectors that is useful for grabbing the max, min, and average of the module temps
vector<pair<int, float>> sort_mod_temps(vector<pair<int, float>> &mod_temps){
    // create a copy to sort
    vector<pair<int, float>> sorted_mod_temps = mod_temps;
    // sort it
    // O(10), constant time sorting since constant input size
    sort(sorted_mod_temps.begin(), sorted_mod_temps.end(), comparator);
    return sorted_mod_temps;
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
float get_module_temp(int &counter, vector<pair<int, float>> &mod_temps){
    return (mod_temps.at(counter)).second;
}

// returns the average temperature of all of the modules in the segment  
float get_avg_temp(vector<pair<int, float>> &mod_temps){
    float sum = 0;
    for (const auto &element : mod_temps){
        sum += element.second;
    }
    return sum/mod_temps.size();
}

// dealing with the sorted nested vectors

// returns the min temp in a sorted nested vector
float get_min_temp(vector<pair<int, float>> &sorted_mod_temps){
    // return (sorted_mod_temps.at(11)).second;
    return (sorted_mod_temps.at(9)).second;
}

// returns the max temp in a sorted nested vector
float get_max_temp(vector<pair<int, float>> &sorted_mod_temps){
    return (sorted_mod_temps.at(0)).second;
}

// returns the min temp local id in a sorted nested vector
int get_min_id(vector<pair<int, float>> &sorted_mod_temps){
    // converts the global ID to a local one
    // return (sorted_mod_temps.at(11)).first % 80;
    return (sorted_mod_temps.at(9)).first % 80;
}

// returns the max temp local id in a sorted nested vector
int get_max_id(vector<pair<int, float>> &sorted_mod_temps){
    // converts the global ID to a local one
    return (sorted_mod_temps.at(0)).first % 80;
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

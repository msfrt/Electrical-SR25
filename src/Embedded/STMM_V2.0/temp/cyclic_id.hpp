#ifndef CYCLIC_ID_HPP
#define CYCLIC_ID_HPP

#include <ReadADC.h>
#include "sensors.hpp"
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;
using std::sort;

bool comparator(const pair<int, float> &a, const pair<int, float> &b){
    return a.second > b.second;
}

// clamps nonesense values to a definite value 
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

// this fuction returns the unsorted vector of vectors that is useful for incrementing the 
// CURRENT module that is being sent over CAN
vector<pair<int, float>> get_mod_temps(const int &seg){
    
    // the idx of each nested vector is the local id/module within the segment 
    // {global ID, module temp}
    // global IDs are +80 for each segement

    // some wack shit is up if the ID turns out to be negative, good for a default value 
    // until the temp values get updated again
    vector<pair<int, float>> mod_temps = 
                    {{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0}};
    switch (seg){
    
        case 1:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(seg_1_mod_0.avg())}, {1, voltage_to_ENEPAQ_cell_temp(seg_1_mod_1.avg())}, {2, voltage_to_ENEPAQ_cell_temp(seg_1_mod_2.avg())}, 
                    {3, voltage_to_ENEPAQ_cell_temp(seg_1_mod_3.avg())}, {4, voltage_to_ENEPAQ_cell_temp(seg_1_mod_4.avg())}, {5, voltage_to_ENEPAQ_cell_temp(seg_1_mod_5.avg())}, 
                    {6, voltage_to_ENEPAQ_cell_temp(seg_1_mod_6.avg())}, {7, voltage_to_ENEPAQ_cell_temp(seg_1_mod_7.avg())}, {8, voltage_to_ENEPAQ_cell_temp(seg_1_mod_8.avg())}, 
                    {9, voltage_to_ENEPAQ_cell_temp(seg_1_mod_9.avg())}, {10, voltage_to_ENEPAQ_cell_temp(seg_1_mod_10.avg())}, {11, voltage_to_ENEPAQ_cell_temp(seg_1_mod_11.avg())}};
        break;
        
        case 2:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(seg_2_mod_0.avg())}, {1, voltage_to_ENEPAQ_cell_temp(seg_2_mod_1.avg())}, {2, voltage_to_ENEPAQ_cell_temp(seg_2_mod_2.avg())}, 
                    {3, voltage_to_ENEPAQ_cell_temp(seg_2_mod_3.avg())}, {4, voltage_to_ENEPAQ_cell_temp(seg_2_mod_4.avg())}, {5, voltage_to_ENEPAQ_cell_temp(seg_2_mod_5.avg())}, 
                    {6, voltage_to_ENEPAQ_cell_temp(seg_2_mod_6.avg())}, {7, voltage_to_ENEPAQ_cell_temp(seg_2_mod_7.avg())}, {8, voltage_to_ENEPAQ_cell_temp(seg_2_mod_8.avg())}, 
                    {9, voltage_to_ENEPAQ_cell_temp(seg_2_mod_9.avg())}, {10, voltage_to_ENEPAQ_cell_temp(seg_2_mod_10.avg())}, {11, voltage_to_ENEPAQ_cell_temp(seg_2_mod_11.avg())}};
        break;

        case 3:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(seg_3_mod_0.avg())}, {1, voltage_to_ENEPAQ_cell_temp(seg_3_mod_1.avg())}, {2, voltage_to_ENEPAQ_cell_temp(seg_3_mod_2.avg())}, 
                    {3, voltage_to_ENEPAQ_cell_temp(seg_3_mod_3.avg())}, {4, voltage_to_ENEPAQ_cell_temp(seg_3_mod_4.avg())}, {5, voltage_to_ENEPAQ_cell_temp(seg_3_mod_5.avg())}, 
                    {6, voltage_to_ENEPAQ_cell_temp(seg_3_mod_6.avg())}, {7, voltage_to_ENEPAQ_cell_temp(seg_3_mod_7.avg())}, {8, voltage_to_ENEPAQ_cell_temp(seg_3_mod_8.avg())}, 
                    {9, voltage_to_ENEPAQ_cell_temp(seg_3_mod_9.avg())}, {10, voltage_to_ENEPAQ_cell_temp(seg_3_mod_10.avg())}, {11, voltage_to_ENEPAQ_cell_temp(seg_3_mod_11.avg())}};
        break;

        case 4:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(seg_4_mod_0.avg())}, {1, voltage_to_ENEPAQ_cell_temp(seg_4_mod_1.avg())}, {2, voltage_to_ENEPAQ_cell_temp(seg_4_mod_2.avg())}, 
                    {3, voltage_to_ENEPAQ_cell_temp(seg_4_mod_3.avg())}, {4, voltage_to_ENEPAQ_cell_temp(seg_4_mod_4.avg())}, {5, voltage_to_ENEPAQ_cell_temp(seg_4_mod_5.avg())}, 
                    {6, voltage_to_ENEPAQ_cell_temp(seg_4_mod_6.avg())}, {7, voltage_to_ENEPAQ_cell_temp(seg_4_mod_7.avg())}, {8, voltage_to_ENEPAQ_cell_temp(seg_4_mod_8.avg())}, 
                    {9, voltage_to_ENEPAQ_cell_temp(seg_4_mod_9.avg())}, {10, voltage_to_ENEPAQ_cell_temp(seg_4_mod_10.avg())}, {11, voltage_to_ENEPAQ_cell_temp(seg_4_mod_11.avg())}};
        break;

        case 5:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(seg_5_mod_0.avg())}, {1, voltage_to_ENEPAQ_cell_temp(seg_5_mod_1.avg())}, {2, voltage_to_ENEPAQ_cell_temp(seg_5_mod_2.avg())}, 
                    {3, voltage_to_ENEPAQ_cell_temp(seg_5_mod_3.avg())}, {4, voltage_to_ENEPAQ_cell_temp(seg_5_mod_4.avg())}, {5, voltage_to_ENEPAQ_cell_temp(seg_5_mod_5.avg())}, 
                    {6, voltage_to_ENEPAQ_cell_temp(seg_5_mod_6.avg())}, {7, voltage_to_ENEPAQ_cell_temp(seg_5_mod_7.avg())}, {8, voltage_to_ENEPAQ_cell_temp(seg_5_mod_8.avg())}, 
                    {9, voltage_to_ENEPAQ_cell_temp(seg_5_mod_9.avg())}, {10, voltage_to_ENEPAQ_cell_temp(seg_5_mod_10.avg())}, {11, voltage_to_ENEPAQ_cell_temp(seg_5_mod_11.avg())}};
        break;

        case 6:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(seg_6_mod_0.avg())}, {1, voltage_to_ENEPAQ_cell_temp(seg_6_mod_1.avg())}, {2, voltage_to_ENEPAQ_cell_temp(seg_6_mod_2.avg())}, 
                    {3, voltage_to_ENEPAQ_cell_temp(seg_6_mod_3.avg())}, {4, voltage_to_ENEPAQ_cell_temp(seg_6_mod_4.avg())}, {5, voltage_to_ENEPAQ_cell_temp(seg_6_mod_5.avg())}, 
                    {6, voltage_to_ENEPAQ_cell_temp(seg_6_mod_6.avg())}, {7, voltage_to_ENEPAQ_cell_temp(seg_6_mod_7.avg())}, {8, voltage_to_ENEPAQ_cell_temp(seg_6_mod_8.avg())}, 
                    {9, voltage_to_ENEPAQ_cell_temp(seg_6_mod_9.avg())}, {10, voltage_to_ENEPAQ_cell_temp(seg_6_mod_10.avg())}, {11, voltage_to_ENEPAQ_cell_temp(seg_6_mod_11.avg())}};
        break;

        case 7:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(seg_7_mod_0.avg())}, {1, voltage_to_ENEPAQ_cell_temp(seg_7_mod_1.avg())}, {2, voltage_to_ENEPAQ_cell_temp(seg_7_mod_2.avg())}, 
                    {3, voltage_to_ENEPAQ_cell_temp(seg_7_mod_3.avg())}, {4, voltage_to_ENEPAQ_cell_temp(seg_7_mod_4.avg())}, {5, voltage_to_ENEPAQ_cell_temp(seg_7_mod_5.avg())}, 
                    {6, voltage_to_ENEPAQ_cell_temp(seg_7_mod_6.avg())}, {7, voltage_to_ENEPAQ_cell_temp(seg_7_mod_7.avg())}, {8, voltage_to_ENEPAQ_cell_temp(seg_7_mod_8.avg())}, 
                    {9, voltage_to_ENEPAQ_cell_temp(seg_7_mod_9.avg())}, {10, voltage_to_ENEPAQ_cell_temp(seg_7_mod_10.avg())}, {11, voltage_to_ENEPAQ_cell_temp(seg_7_mod_11.avg())}};
        break;

        case 8:
        mod_temps = {{0, voltage_to_ENEPAQ_cell_temp(seg_8_mod_0.avg())}, {1, voltage_to_ENEPAQ_cell_temp(seg_8_mod_1.avg())}, {2, voltage_to_ENEPAQ_cell_temp(seg_8_mod_2.avg())}, 
                    {3, voltage_to_ENEPAQ_cell_temp(seg_8_mod_3.avg())}, {4, voltage_to_ENEPAQ_cell_temp(seg_8_mod_4.avg())}, {5, voltage_to_ENEPAQ_cell_temp(seg_8_mod_5.avg())}, 
                    {6, voltage_to_ENEPAQ_cell_temp(seg_8_mod_6.avg())}, {7, voltage_to_ENEPAQ_cell_temp(seg_8_mod_7.avg())}, {8, voltage_to_ENEPAQ_cell_temp(seg_8_mod_8.avg())}, 
                    {9, voltage_to_ENEPAQ_cell_temp(seg_8_mod_9.avg())}, {10, voltage_to_ENEPAQ_cell_temp(seg_8_mod_10.avg())}, {11, voltage_to_ENEPAQ_cell_temp(seg_8_mod_11.avg())}};
        break;
    }
    
    return mod_temps;

}

// returns the sorted vector of vectors that is useful for grabbing the max, min, and average of the module temps
vector<pair<int, float>> sort_mod_temps(vector<pair<int, float>> &mod_temps){
    // create a copy to sort
    vector<pair<int, float>> sorted_mod_temps = mod_temps;
    // sort it
    // O(12), constant time sorting since constant input size
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
    return (sorted_mod_temps.at(11)).second;
}

// returns the max temp in a sorted nested vector
float get_max_temp(vector<pair<int, float>> &sorted_mod_temps){
    return (sorted_mod_temps.at(0)).second;
}

// returns the min temp local id in a sorted nested vector
int get_min_id(vector<pair<int, float>> &sorted_mod_temps){
    // converts the global ID to a local one
    return (sorted_mod_temps.at(11)).first % 80;
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

#ifndef BMS_CONTROL_HPP
#define BMS_CONTROL_HPP

#include <EasyTimer.h>
#include "bms_hardware.h"
#include "index.h"
#include "LT_SPI.h"
#include "LTC681x.h"
#include "LTC6811.h"

int cell_temp_0;
int cell_temp_1;
int cell_temp_2;
int cell_temp_3;
int cell_temp_4;
int cell_temp_5;
int cell_temp_6;
int cell_temp_7;
int cell_temp_8;
int cell_temp_9;

void read_voltage(cell_asic &bms_ic, const int &state) {
    
    // default balancing switch state before switching again
    LTC6811_clear_discharge(TOTAL_IC, bms_ic);

    // half the aquisition cycle dedicated to "odds" and the other to "evens"
    switch(state){
        case 1: 
            LTC6811_set_discharge(1, TOTAL_IC, bms_ic);
            cell_temp_0 = bms_ic[1].cells.c_codes[1];
            LTC6811_set_discharge(3, TOTAL_IC, bms_ic);
            cell_temp_2 = bms_ic[1].cells.c_codes[3];
            LTC6811_set_discharge(5, TOTAL_IC, bms_ic);
            cell_temp_4 = bms_ic[1].cells.c_codes[5];
            LTC6811_set_discharge(8, TOTAL_IC, bms_ic);
            cell_temp_6 = bms_ic[1].cells.c_codes[8];
            LTC6811_set_discharge(10, TOTAL_IC, bms_ic);
            cell_temp_8 = bms_ic[1].cells.c_codes[10];
        break;
        
        case 2:
            LTC6811_set_discharge(2, TOTAL_IC, bms_ic);
            cell_temp_1 = bms_ic[1].cells.c_codes[2];
            LTC6811_set_discharge(4, TOTAL_IC, bms_ic);
            cell_temp_3 = bms_ic[1].cells.c_codes[4];
            LTC6811_set_discharge(7, TOTAL_IC, bms_ic);
            cell_temp_5 = bms_ic[1].cells.c_codes[7];
            LTC6811_set_discharge(9, TOTAL_IC, bms_ic);
            cell_temp_7 = bms_ic[1].cells.c_codes[9];
            LTC6811_set_discharge(11, TOTAL_IC, bms_ic);
            cell_temp_9 = bms_ic[1].cells.c_codes[11];
        break;
    }

    wakeup_sleep(TOTAL_IC);
    LTC6811_wrcfg(TOTAL_IC, bms_ic);
}

void read_voltage(cell_asic &bms_ic, const int &cell) {
    int cell_temp = 0;
    
    // activate the ICs
    wakeup_sleep(TOTAL_IC);
    // default balancing switch state before measuring
    LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    LTC6811_wrcfg(TOTAL_IC, bms_ic);
    
    enable_bal_switch(bms_ic, 1);
    cell_temp = bms_ic[1].cells.c_codes[cell];

    // switch(cell){
    //     case 0:
    //         LTC6811_set_discharge(1, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;
        
    //     case 1:
    //         LTC6811_set_discharge(2, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;

    //     case 2:
    //         LTC6811_set_discharge(3, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;

    //     case 3:
    //         LTC6811_set_discharge(4, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;
    
    //     case 4:
    //         LTC6811_set_discharge(5, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;

    //     case 5:
    //         LTC6811_set_discharge(7, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;

    //     case 6:
    //         LTC6811_set_discharge(8, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;

    //     case 7:
    //         LTC6811_set_discharge(9, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;

    //     case 8:
    //         LTC6811_set_discharge(10, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;

    //     case 9:
    //         LTC6811_set_discharge(11, TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         cell_temp = bms_ic[1].cells.c_codes[cell];
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         LTC6811_clear_discharge(TOTAL_IC, bms_ic);
    //         LTC6811_wrcfg(TOTAL_IC, bms_ic);
    //         return cell_temp;
    //     break;
    // }


    // // loop through all connected ICs (should only be one)
    // for (int current_ic = 0; current_ic < TOTAL_IC; current_ic++) {
    //     // loop through all connected cells
    //     for (int i = 0; i < bms_ic[0].ic_reg.cell_channels; i++) {
    //         // EnableBalancingSwitches(1);
    //         Serial.println(bms_ic[current_ic].cells.c_codes[i]);
            
    //     }
      
    // }
}

#endif

#ifndef BMS_CONTROL_HPP
#define BMS_CONTROL_HPP

#include <EasyTimer.h>
#include "bms_hardware.h"
#include "index.h"
#include "LT_SPI.h"
#include "LTC681x.h"
#include "LTC6811.h"

// ADC Command Configurations
const uint8_t ADC_OPT = ADC_OPT_DISABLED;          // See LTC6811_daisy.h for Options
const uint8_t ADC_CONVERSION_MODE = MD_7KHZ_3KHZ;  // MD_7KHZ_3KHZ; //MD_26HZ_2KHZ;//MD_7KHZ_3KHZ; // See LTC6811_daisy.h for Options
const uint8_t ADC_DCP = DCP_DISABLED;              // See LTC6811_daisy.h for Options
const uint8_t CELL_CH_TO_CONVERT = CELL_CH_ALL;    // See LTC6811_daisy.h for Options
const uint8_t AUX_CH_TO_CONVERT = AUX_CH_ALL;      // See LTC6811_daisy.h for Options
const uint8_t STAT_CH_TO_CONVERT = STAT_CH_ALL;    // See LTC6811_daisy.h for Options

const uint16_t MEASUREMENT_LOOP_TIME = 5 * 6000;  // milliseconds(mS)
const uint16_t BALANCE_LOOP_TIME = 60000;         // milliseconds(mS)

// Loop Measurement Setup These Variables are ENABLED or DISABLED Remember ALL CAPS
const uint8_t WRITE_CONFIG = DISABLED;  // This is ENABLED or DISABLED
const uint8_t READ_CONFIG = DISABLED;   // This is ENABLED or DISABLED
const uint8_t MEASURE_CELL = ENABLED;   // This is ENABLED or DISABLED
const uint8_t MEASURE_AUX = DISABLED;   // This is ENABLED or DISABLED
const uint8_t MEASURE_STAT = DISABLED;  // This is ENABLED or DISABLED
const uint8_t PRINT_PEC = DISABLED;     // This is ENABLED or DISABLED

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

void measurement_loop(uint8_t datalog_en)
{
  int8_t error = 0;
  if (WRITE_CONFIG == ENABLED)
  {
    wakeup_sleep();
    ltc6811_wrcfg(TOTAL_IC,tx_cfg);
    print_config();
  }

  if (READ_CONFIG == ENABLED)
  {
    wakeup_sleep();
    error = ltc6811_rdcfg(TOTAL_IC,rx_cfg);
    check_error(error);
    print_rxconfig();
  }

  if (MEASURE_CELL == ENABLED)
  {

    ltc6811_adcv(ADC_CONVERSION_MODE,ADC_DCP,CELL_CH_TO_CONVERT);
    ltc6811_pollAdc();
    wakeup_idle();
    error = ltc6811_rdcv(0, TOTAL_IC,cell_codes);
    check_error(error);
    print_cells(datalog_en);

  }

  if (MEASURE_AUX == ENABLED)
  {
    wakeup_idle();
    ltc6811_adax(ADC_CONVERSION_MODE , AUX_CH_ALL);
    ltc6811_pollAdc();
    wakeup_idle();
    error = ltc6811_rdaux(0,TOTAL_IC,aux_codes); // Set to read back all aux registers
    check_error(error);
    print_aux(datalog_en);
  }

  if (MEASURE_STAT == ENABLED)
  {
    wakeup_idle();
    ltc6811_adstat(ADC_CONVERSION_MODE, STAT_CH_ALL);
    ltc6811_pollAdc();
    wakeup_idle();
    error = ltc6811_rdstat(0,TOTAL_IC,stat_codes,flags_uvov,system_muxfail,system_thsd); // Set to read back all aux registers
    check_error(error);
    print_stat();
  }
}

    
    // check_error(error);
    // print_cells(datalog_en);

void read_voltage(cell_asic &bms_ic, const int &state) {
    
    // default balancing switch state before switching again
    LTC6811_clear_discharge(TOTAL_IC, bms_ic);

    // half the aquisition cycle dedicated to "odds" and the other to "evens"
    switch(state){
        case 1: 
            LTC6811_set_discharge(1, TOTAL_IC, bms_ic);
            LTC6811_set_discharge(3, TOTAL_IC, bms_ic);
            LTC6811_set_discharge(5, TOTAL_IC, bms_ic);
            LTC6811_set_discharge(8, TOTAL_IC, bms_ic);
            LTC6811_set_discharge(10, TOTAL_IC, bms_ic);
            
            ltc6811_adcv(ADC_CONVERSION_MODE,ADC_DCP,CELL_CH_TO_CONVERT);
            ltc6811_pollAdc();
            wakeup_idle();

            cell_temp_0 = bms_ic[1].cells.c_codes[1];
            cell_temp_2 = bms_ic[1].cells.c_codes[3];
            cell_temp_4 = bms_ic[1].cells.c_codes[5];
            cell_temp_6 = bms_ic[1].cells.c_codes[8];
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

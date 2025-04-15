#ifndef INDEX_H
#define INDEX_H

#include <Arduino.h>
#include <stdint.h>

// #define GPIO_BALTEMP 1  // balence temp
// #define GPIO_HDD1 2     // Headder 1
// #define GPIO_BACKBAL 3
// #define GPIO_HDD2 4        // Header 2
// #define GPIO_BYPASSTEMP 5  // bypass temp

//#define DEVBAORD 0

// #ifdef DEVBAORD
// #define TOTAL_IC 1  //!< number of ICs in the daisy chain
// // Under Voltage and Over Voltage Thresholds
// #else
#define TOTAL_IC 1  //!< number of ICs in the daisy chain
// Under Voltage and Over Voltage Thresholds
// #endif

extern const uint16_t OV_THRESHOLD;  // Over voltage threshold ADC Code. LSB = 0.0001    //also set in LTC681x.cpp Line: 1443
extern const uint16_t UV_THRESHOLD;  // Under voltage threshold ADC Code. LSB = 0.0001

typedef struct {
  uint16_t voltage;
  uint8_t IC;
  uint8_t cell;
} cell;

typedef struct {
  cell min;
  cell max;
  float bypassTEMP;
  float balanceTEMP;
  int average;
  int sum;
  int cells[12];
  uint16_t discharge;
} CellData;

typedef struct {
  CellData pack[TOTAL_IC];

  uint16_t average;
  int sum;
  cell min;  // reset at each read
  cell max;  // reset at each read

  cell Globalmin;  // reset on end of charging
  cell Globalmax;  // reset on end of charging
} Battery;

// extern Battery battery;

#endif

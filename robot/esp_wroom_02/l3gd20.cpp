#include "Arduino.h"
#include "l3gd20.h"
#include "i2c.h"

// Gyro/temperature sensor L3GD20

// L3GD20 device address (7bit)
const byte L3GD20 = B1101011;

// Register list
const byte WHO_AM_I = 0x0f;
const byte RES_OK = 0xd4;
const byte CTRL_REG1 = 0x20;
const byte OUT_TEMP = 0x26;
const byte OUT_X_L = 0x28;
const byte OUT_X_H = 0x29;
const byte OUT_Y_L = 0x2a;
const byte OUT_Y_H = 0x2b;
const byte OUT_Z_L = 0x2c;
const byte OUT_Z_H = 0x2d;

const byte ENABLE = 0x0f;  // power on
const float SENSIVITY = 0.00875;  // as per the L3GD20 datasheet

// initialize the device
void init_l3gd20() {
  byte who = i2c_read(L3GD20, WHO_AM_I);
  if (who == RES_OK) {
    Serial.println("L3GD20 WHO_AM_I OK");
  } else {
    Serial.println("L3GD20 WHO_AM_I NG");
  }
  i2c_write(L3GD20, CTRL_REG1, ENABLE);
}

// get temperature
int8_t get_temp() {
  byte t = i2c_read(L3GD20, OUT_TEMP);
  return (int8_t)t;
}

// get motion
int16_t get_motion(char axis) {
  byte msb, lsb;
  // read the registers
  switch(axis) {
    case 'x': 
      msb = i2c_read(L3GD20, OUT_X_H);
      lsb = i2c_read(L3GD20, OUT_X_L);
      break;
    case 'y':
      msb = i2c_read(L3GD20, OUT_Y_H);
      lsb = i2c_read(L3GD20, OUT_Y_L);
      break;
    case 'z':
      msb = i2c_read(L3GD20, OUT_Z_H);
      lsb = i2c_read(L3GD20, OUT_Z_L);
      break;
  }

  // cast to signed int (16bit): 2's complement
  int16_t data = (int16_t)(((msb << 8) & 0xFF00) | lsb);
  data *= SENSIVITY;  // -250dps to +250dps
  return data;
}


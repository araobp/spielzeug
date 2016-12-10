#ifndef i2c_h
#define i2c_h
#include "Arduino.h"

byte i2c_read(byte device_address, byte register_address);

void i2c_write(byte device_address, byte register_address, byte data);

#endif

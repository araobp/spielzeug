#include "Arduino.h"
#include "i2c.h"

// I2C read/write func

#include <Wire.h>

byte i2c_read(byte device_address, byte register_address)
{
  byte data;
  Wire.beginTransmission(device_address);
  Wire.write(register_address);
  Wire.endTransmission(false);
  Wire.requestFrom(device_address, 1);
  return Wire.read();
}

void i2c_write(byte device_address, byte register_address, byte data)
{
  Wire.beginTransmission(device_address);
  Wire.write(register_address);
  Wire.write(data);
  Wire.endTransmission(false);
}

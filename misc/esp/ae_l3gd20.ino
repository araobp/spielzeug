#include <Wire.h>

const byte L3GD20_ADDRESS = B1101011; //7bit address

#define WHO_AM_I 0x0f
#define CTRL_REG1 0x20
#define OUT_TEMP 0x26
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2a
#define OUT_Y_H 0x2b
#define OUT_Z_L 0x2c
#define OUT_Z_H 0x2d

#define ENABLE 0x0f
#define SENSIVITY 0.00875  // as per the L3GD20 datasheet


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

int8_t get_temp() {
  return (int8_t)i2c_read(L3GD20_ADDRESS, OUT_TEMP);
}

int16_t get_motion(char axis) {
  byte msb, lsb;
  switch(axis) {
    case 'x': 
      msb = i2c_read(L3GD20_ADDRESS, OUT_X_H);
      lsb = i2c_read(L3GD20_ADDRESS, OUT_X_L);
      break;
    case 'y':
      msb = i2c_read(L3GD20_ADDRESS, OUT_Y_H);
      lsb = i2c_read(L3GD20_ADDRESS, OUT_Y_L);
      break;
    case 'z':
      msb = i2c_read(L3GD20_ADDRESS, OUT_Z_H);
      lsb = i2c_read(L3GD20_ADDRESS, OUT_Z_L);
      break;
  }

  // cast to signed int (16bit): 2's complement
  int16_t data = (int16_t)(((msb << 8) & 0xFF00) | lsb);
  data *= SENSIVITY;  // -250dps to +250dps
  return data;
}

void setup() 
{
  Wire.begin();  // IO4 SDA, IO5 SCL
  Serial.begin(9600);
  delay(10);
  byte who = i2c_read(L3GD20_ADDRESS, WHO_AM_I);
  Serial.println(who);
  i2c_write(L3GD20_ADDRESS, CTRL_REG1, ENABLE);
}

void loop() 
{
  int8_t temp = get_temp();
  int16_t x = get_motion('x');
  int16_t y = get_motion('y');
  int16_t z = get_motion('z');
  Serial.println(temp);
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  Serial.println("---");
  delay(5000);
}

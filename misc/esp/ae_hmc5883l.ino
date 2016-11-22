#include <Wire.h>
#include <math.h>
#define HMC5883L_ADDRESS 0x1E //7bit address

unsigned char i2c_read(unsigned char register_address)
{
  unsigned char data;
  Wire.beginTransmission(HMC5883L_ADDRESS);
  Wire.write(register_address);
  Wire.endTransmission(false);
  Wire.requestFrom(HMC5883L_ADDRESS, 1);
  data = (unsigned char)Wire.read();
  return data;
}

void i2c_write(unsigned char register_address, unsigned char data)
{
  Wire.beginTransmission(HMC5883L_ADDRESS);
  Wire.write(register_address);
  Wire.write(data);
  Wire.endTransmission(false);
}

double get_radian(void)
{
  unsigned char x_msb;
  unsigned char x_lsb;
  unsigned char y_msb;
  unsigned char y_lsb;
  unsigned char z_msb;
  unsigned char z_lsb;
  int16_t x;
  int16_t y;
  int16_t z;

  delay(250);
  
  x_msb = i2c_read(0x03);
  x_lsb = i2c_read(0x04);
  z_msb = i2c_read(0x05);
  z_lsb = i2c_read(0x06);
  y_msb = i2c_read(0x07);
  y_lsb = i2c_read(0x08);

  // cast to signed int (16bit): 2's complement
  x = (int16_t)(((x_msb << 8) & 0xFF00) | x_lsb);
  y = (int16_t)(((y_msb << 8) & 0xFF00) | y_lsb);
  z = (int16_t)(((z_msb << 8) & 0xFF00) | z_lsb);
  Serial.println(x);
  Serial.println(y);
  
  // return radian
  return atan2((double)y, (double)x);
}

void setup() 
{
  Wire.begin();  // IO4 SDA, IO5 SCL
  Serial.begin(9600);
  delay(10);
  i2c_write(0x02, 0x00);
}

void loop() 
{
  Serial.println(get_radian());
  Serial.println("---");
  delay(5000);
}

#include "i2c.h"

// I2C devices
#include "l3gd20.h"  // Gyro/temperature sensor L3GD20
#include "hmc5883l.h"  // Geomagnetic sensor HMC5883L

void setup() 
{
  Wire.begin();  // ESP8266: IO4 SDA, IO5 SCL
  Serial.begin(9600);
  delay(50);
  init_hmc5883l;  // initialize HMC5883L
  delay(50);
  init_l3gd20();  // initialize L3GD20
  delay(50);
}

void loop() 
{
  int8_t t = get_temp();
  double m = get_radian();
  int16_t x = get_motion('x');
  int16_t y = get_motion('y');
  int16_t z = get_motion('z');
  Serial.println(t);
  Serial.println(m);
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  Serial.println("---");
  delay(5000);
}

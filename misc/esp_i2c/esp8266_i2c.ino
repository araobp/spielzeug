#include "i2c.h"

// I2C device: HMC5883L
#include "hmc5883l.h"  // Geomagnetic sensor HMC5883L
#define X_MAX 263
#define X_MIN -326
#define Y_MAX 55
#define Y_MIN -537

// I2C device: L3GD20
#include "l3gd20.h"  // Gyro/temperature sensor L3GD20

void setup() 
{
  set_constants(X_MAX, X_MIN, Y_MAX, Y_MIN);
  Wire.begin();  // ESP8266: IO4 SDA, IO5 SCL
  Serial.begin(9600);
  delay(1000);
  init_hmc5883l();  // initialize HMC5883L
  init_l3gd20();  // initialize L3GD20
}

void loop() 
{
  int8_t t = get_temp();
  double r = get_radian();
  int16_t x = get_motion('x');
  int16_t y = get_motion('y');
  int16_t z = get_motion('z');
  Serial.println(r);
  Serial.println("-");
  Serial.println(t);
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  Serial.println("---");
  delay(5000);
}

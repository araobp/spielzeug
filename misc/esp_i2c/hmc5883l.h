#include <math.h>

// HMC5883L
// Reference: http://www.jameco.com/Jameco/Products/ProdDS/2150248.pdf

// HMC5883L device address (7bit)
const byte HMC5883L = 0x1E;

// Register list
#define X_MSB_REG 0x03
#define X_LSB_REG 0x04
#define Z_MSB_REG 0x05
#define Z_LSB_REG 0x06
#define Y_MSB_REG 0x07
#define Y_LSB_REG 0x08

// Mode
#define MODE_REGISTER 0x02
#define CONTINUOUS_MEASUREMENT 0x00

// constants for calibration
float Xsf=1.0;
float Ysf=1.0;
float Xoff=0.0;
float Yoff=0.0;

// set X-axis/Y-axix scale factor
void set_constants(int16_t x_max, int16_t x_min, int16_t y_max, int16_t y_min) {
  int16_t x_sf = (y_max - y_min) / (x_max - x_min);
  if (x_sf > 1.0) {
    Xsf = x_sf;
  }
  int16_t y_sf = (x_max - x_min) / (y_max - y_min);
  if (y_sf > 1.0) {
    Ysf = x_sf;
  }
  Xoff=((x_max - x_min) / 2 - x_max) * Xsf;
  Yoff=((y_max - y_min) / 2 - y_max) * Ysf;
}

// initialize the device
void init_hmc5883l() {
  i2c_write(HMC5883L, MODE_REGISTER, CONTINUOUS_MEASUREMENT);
}

// get direction in radian
double get_radian(void)
{
  // read the registers
  byte x_msb = i2c_read(HMC5883L, X_MSB_REG);
  byte x_lsb = i2c_read(HMC5883L, X_LSB_REG);
  byte z_msb = i2c_read(HMC5883L, Z_MSB_REG);
  byte z_lsb = i2c_read(HMC5883L, Z_LSB_REG);
  byte y_msb = i2c_read(HMC5883L, Y_MSB_REG);
  byte y_lsb = i2c_read(HMC5883L, Y_LSB_REG);

  // cast to signed int (16bit): 2's complement
  int16_t x = (int16_t)(((x_msb << 8) & 0xFF00) | x_lsb);
  int16_t y = (int16_t)(((y_msb << 8) & 0xFF00) | y_lsb);
  int16_t z = (int16_t)(((z_msb << 8) & 0xFF00) | z_lsb);

  // calibration (assuming that the sensor is level with the ground),
  // i.e., XH is x and YH is y.
  x = Xsf * x + Xoff;
  y = Ysf * y + Yoff;
  Serial.println(x);
  Serial.println(y);
  
  // return radian
  return atan2((double)y, (double)x);
}

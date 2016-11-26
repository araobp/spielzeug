// Gyro/temperature sensor L3GD20

// L3GD20 device address (7bit)
const byte L3GD20 = B1101011;

// Register list
#define WHO_AM_I 0x0f
#define OK 0xd4
#define CTRL_REG1 0x20
#define OUT_TEMP 0x26
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2a
#define OUT_Y_H 0x2b
#define OUT_Z_L 0x2c
#define OUT_Z_H 0x2d

#define ENABLE 0x0f  // power on
#define SENSIVITY 0.00875  // as per the L3GD20 datasheet

// initialize the device
void init_l3gd20() {
  byte who = i2c_read(L3GD20, WHO_AM_I);
  if (who == OK) {
    Serial.println("L3GD20 WHO_AM_I OK");
  } else {
    Serial.println("L3GD20 WHO_AM_I NG");
  }
  i2c_write(L3GD20, CTRL_REG1, ENABLE);
}

// get temperature
int8_t get_temp() {
  return (int8_t)i2c_read(L3GD20, OUT_TEMP);
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

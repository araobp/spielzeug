#ifndef hmc5883l_h
#define hmc5883l_h
#include "Arduino.h"

void set_constants(int16_t x_max, int16_t x_min, int16_t y_max, int16_t y_min);

void init_hmc5883l();

double get_radian();

int16_t get_degree();

#endif

#ifndef l3gd20_h
#define l3gd20_h
#include "Arduino.h"

void init_l3gd20();

int8_t get_temp();

int16_t get_motion(char axis);

#endif

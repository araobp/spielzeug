#ifndef config_h
#define config_h
#include "Arduino.h"

struct Config {
  char wifi_ssid[32];
  char password[32];
  char mqtt_server[32];
  int mqtt_port;
};

void put_config(Config conf);

Config get_config();

#endif

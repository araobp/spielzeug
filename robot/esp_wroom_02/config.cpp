// Config management

#include <EEPROM.h>
#include "config.h"

// put config onto EEPROM
void put_config(char* wifi_ssid, char* password, char* mqtt_server, int mqtt_port) {
  EEPROM.begin(256);
  Config conf;
  strcpy(conf.wifi_ssid, wifi_ssid);
  strcpy(conf.password, password);
  strcpy(conf.mqtt_server, mqtt_server);
  conf.mqtt_port = mqtt_port;
  EEPROM.put(0, conf);
  EEPROM.commit();
}

// get config from EEPORM
Config get_config() {
  Config conf;
  EEPROM.get(0, conf);
  return conf;
}


// Config management

#include <EEPROM.h>
#include "config.h"

// put config onto EEPROM
void put_config(Config conf) {
  EEPROM.begin(256);
  EEPROM.put(0, conf);
  EEPROM.commit();
  EEPROM.end();
}

// get config from EEPORM
Config get_config() {
  EEPROM.begin(256);
  Config conf;
  EEPROM.get(0, conf);
  EEPROM.end();
  return conf;
}


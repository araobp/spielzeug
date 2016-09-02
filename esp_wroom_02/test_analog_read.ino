extern "C" {
#include "user_interface.h"
}

#define PIN_LED 13

// Circuit
//
// 3.3v
// |
// R1 10k ohm
// |
// +----> TOUT
// |
// R2 510 ohm
// |
// GND
//
// 3.3(V) * 510 / (10000 + 510) = 0.16(V)
//
void setup(){
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //Serial.println(A0);
  int vout_level = analogRead(A0);  // input MUST be <= 1.0v
  Serial.println(vout_level); // should be around 0.16
  // it showed "155" on the serial monitor  -- correct!
  
  digitalWrite(PIN_LED, HIGH);
  delay(200);
  digitalWrite(PIN_LED, LOW);  

  delay(4800);
}

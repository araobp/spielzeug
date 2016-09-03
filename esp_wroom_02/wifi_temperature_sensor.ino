extern "C" {
#include "user_interface.h"
}
#include<ESP8266WiFi.h>
#include <PubSubClient.h>

#define PIN_LED 13

// WiFi setup
const char* ssid = "********";
const char* password = "*************";

// MQTT server
const char* mqtt_server = "192.168.57.130";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

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
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
    if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //Serial.println(A0);
  int vout_level = analogRead(A0);  // input MUST be <= 1.0v
  Serial.println(vout_level); // should be around 0.16
  // it showed "155" on the serial monitor  -- correct!

  // publish the voltage level to MQTT server
  char buf[4];
  String(vout_level).toCharArray(buf, 4);
  client.publish("temp", buf);  // publish to topic "temp"

  // blink LED
  digitalWrite(PIN_LED, HIGH);
  delay(200);
  digitalWrite(PIN_LED, LOW);
  delay(4800);
}

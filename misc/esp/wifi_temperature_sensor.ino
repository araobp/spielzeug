// WiFi temperature sensor
// 2019/09/04

extern "C" {
#include "user_interface.h"
}
#include<ESP8266WiFi.h>
#include <PubSubClient.h>

#define PIN_THERMISTOR 12
#define PIN_LED 13

// WiFi setup
const char* ssid = "******";
const char* password = "******";

// MQTT server
const char* mqtt_server = "192.168.***.***";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

// Circuit
//
//  Vdd
//   |
// +-+-+ MCP9700-E/TO
// |   +--Vout --> TOUT
// +-+-+
//   |
//  GND
//
void setup(){
  pinMode(PIN_THERMISTOR,OUTPUT);
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

byte mac[6];
char mac_addr[18];

void setup_wifi() {
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println(WiFi.localIP());
  WiFi.macAddress(mac);
  sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); 
  Serial.println(mac_addr);
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

  // Microchip MCP9700-E/TO
  digitalWrite(PIN_THERMISTOR, HIGH);
  delay(200);
  float vout = analogRead(A0) * 1000.0 / 1023.0;  // input MUST be <= 1.0v
  digitalWrite(PIN_THERMISTOR, LOW);
  int temp = (int)( (vout - 500.0) / 10.0 + 0.5);
  Serial.println(temp);
  // it showed "155" on the serial monitor  -- correct!

  // publish the voltage level to MQTT server
  //0         1         2         3         4
  //012345678901234567890123456789012345678901234
  //{"device_id":"AA:BB:CC:DD:EE:FF","temp":1234}
  char msg[44];
  sprintf(msg, "{\"device_id\":\"%s\",\"temp\":%d}", mac_addr, temp);
  client.publish("temp", msg);  // publish to topic "temp"

  // blink LED
  digitalWrite(PIN_LED, HIGH);
  delay(200);
  digitalWrite(PIN_LED, LOW);
  delay(4800);
}

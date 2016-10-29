extern "C" {
#include "user_interface.h"
}
#include<ESP8266WiFi.h>
#include <PubSubClient.h>

#define PIN_LED 13

#define TOPIC_EVENT "event"

// WiFi setup
const char* ssid = "****";
const char* password = "****";

// MQTT server
const char* mqtt_server = "192.168.***.***";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup(){
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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
      client.subscribe(mac_addr);
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int len) {
  for (int i=0; i<len; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //Serial.println(A0);

  if (Serial.available() > 0) {
    char event[32];
    int len = Serial.readBytesUntil('\n', event, 32);

    if (len > 0) {
      
      event[len-1] = NULL;
      
      //0         1         2         3         4
      //012345678901234567890123456789012345678901234
      //{"device_id":"AA:BB:CC:DD:EE:FF","temp":1234}
      char msg[44];
      sprintf(msg, "{\"device_id\":\"%s\",\"event\":%s}", mac_addr, event);
      client.publish(TOPIC_EVENT, msg); 

      // blink LED
      digitalWrite(PIN_LED, HIGH);
      delay(200);
      digitalWrite(PIN_LED, LOW);
    }
  }
}

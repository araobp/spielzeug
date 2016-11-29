extern "C" {
#include "user_interface.h"
}
#include<ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "lan.h"
#include "scheduler.h"
#include "protocol.h"

// I2C devices
#include "i2c.h"
// I2C device: HMC5883L
#include "hmc5883l.h"  // Geomagnetic sensor HMC5883L
#define X_MAX 263
#define X_MIN -326
#define Y_MAX 55
#define Y_MIN -537
// I2C device: L3GD20
#include "l3gd20.h"  // Gyro/temperature sensor L3GD20

// Pin assginment
// Note: IO4 and IO5 are used implicitly by Wire library
#define PIN_STARTED 12
#define PIN_LED 13


// MQTT topic
#define TOPIC_EVENT "event"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

int sign8(int8_t v) {
  int s;
  if (v > 0) {
    s = PLUS;
  } else {
    s = MINUS;
  }
  return s;
}

int sign16(int16_t v) {
  int s;
  if (v > 0) {
    s = PLUS;
  } else {
    s = MINUS;
  }
  return s;
}

// get data from I2C devices (category 1)
void get_data_i2c_dev1() {
  int8_t t = get_temp();
  double r = get_radian();
  int16_t d = get_degree();
  Serial.println(t);
  Serial.println(r);
  Serial.println(d);
  Serial.println("---");
  char event_i2c_dev1[13];
  sprintf(event_i2c_dev1, "%d%d%d%03d,%d%d%d%03d\0,", EVENT_I2C_DEV1, TEMPERATURE, sign8(t), abs(t), EVENT_I2C_DEV1, GYROSCOPE, sign16(d), abs(d)); 
  publish(event_i2c_dev1);
}

// get data from I2C devices (category2)
void get_data_i2c_dev2() {
  int16_t x = get_motion('x');
  int16_t y = get_motion('y');
  int16_t z = get_motion('z');
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  Serial.println("---");
  char event_i2c_dev2[28];
  sprintf(event_i2c_dev2, "%d%d%d%d%05d,%d%d%d%d%05d,%d%d%d%d%05d\0,", EVENT_I2C_DEV2, GYROSCOPE, X, sign16(x), abs(x), EVENT_I2C_DEV2, GYROSCOPE, Y, sign16(y), abs(y), EVENT_I2C_DEV2, GYROSCOPE, Z, sign16(z), abs(z)); 
  publish(event_i2c_dev2);
}

void setup(){

  // setup pins and serial interface
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_STARTED, OUTPUT);
  Serial.begin(9600);

  // setup WiFi and MQTT
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
 
  // setup I2C devices
  set_constants(X_MAX, X_MIN, Y_MAX, Y_MIN);
  Wire.begin();  // ESP8266: IO4 SDA, IO5 SCL
  init_hmc5883l();  // initialize HMC5883L
  init_l3gd20();  // initialize L3GD20

  // periodic tasks
  set_tasks(NULL, get_data_i2c_dev2, get_data_i2c_dev1);
    
  // Start Arduino Uno and TA7291P
  digitalWrite(PIN_STARTED, HIGH);
  delay(200);
  digitalWrite(PIN_STARTED, LOW);

}

byte mac[6];
char mac_addr[13];

void setup_wifi() {
  delay(100);
  WiFi.begin(WIFI_SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println(WiFi.localIP());
  WiFi.macAddress(mac);
  sprintf(mac_addr, "%02X%02X%02X%02X%02X%02X",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); 
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

// publish a message to MQTT server
void publish(char* event) {
  char msg[44];
  sprintf(msg, "%s,%s", mac_addr, event);
  client.publish(TOPIC_EVENT, msg); 
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  scheduler_loop();

  // receive data from Arduino Uno and send a message to MQTT server
  if (Serial.available() > 0) {
    char event[32];
    int len = Serial.readBytesUntil('\n', event, 32);
    
    if (len > 0) {
      event[len-1] = NULL;
      publish(event);
      // blink LED
      digitalWrite(PIN_LED, HIGH);
      delay(200);
      digitalWrite(PIN_LED, LOW);
    }
  }
}

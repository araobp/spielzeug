package main

import (
	MQTT "github.com/eclipse/paho.mqtt.golang"
)

const MQTT_SERVER = "tcp://localhost:1883"
const CLIENT_ID = "manager"
const MESSAGE = "Hello World!"

func main() {
	opts := MQTT.NewClientOptions().AddBroker(MQTT_SERVER).SetClientID(CLIENT_ID)
	client := MQTT.NewClient(opts)
	token := client.Connect()
	if token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
	token = client.Publish("tsd", 0, true, MESSAGE)
	if token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
}

package main

import (
	"flag"
	"fmt"
	MQTT "github.com/eclipse/paho.mqtt.golang"
)

func main() {
	server := flag.String("server", "tcp://localhost:1883", "MQTT server")
	id := flag.String("id", "manager", "MQTT client id")
	topic := flag.String("topic", "test", "MQTT topic")

	flag.Parse()

	opts := MQTT.NewClientOptions().AddBroker(*server).SetClientID(*id)
	client := MQTT.NewClient(opts)
	token := client.Connect()
	if token.Wait() && token.Error() != nil {
		panic(token.Error())
	}

	handler := func(client MQTT.Client, msg MQTT.Message) {
		fmt.Println(string(msg.Payload()))
	}

	token = client.Subscribe(*topic, 0, handler)
	if token.Wait() && token.Error() != nil {
		panic(token.Error())
	}

	for {
	}

}

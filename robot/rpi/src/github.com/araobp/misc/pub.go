package main

import (
	"flag"
	"fmt"
	MQTT "github.com/eclipse/paho.mqtt.golang"
	"os"
)

func main() {
	server := flag.String("server", "tcp://localhost:1883", "MQTT server")
	id := flag.String("id", "manager", "MQTT client id")
	topic := flag.String("topic", "test", "MQTT topic")

	flag.Parse()

	message := os.Args[1]

	fmt.Println(message)

	opts := MQTT.NewClientOptions().AddBroker(*server).SetClientID(*id)
	client := MQTT.NewClient(opts)
	token := client.Connect()
	if token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
	token = client.Publish(*topic, 0, true, message)
	if token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
}

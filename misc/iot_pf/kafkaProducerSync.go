package main

import (
	kafka "github.com/Shopify/sarama"
	"log"
)

const TOPIC = "lan"
const MESSAGE = "Hello World!"

func main() {

	producer, err := kafka.NewSyncProducer([]string{"localhost:9092"}, nil)
	if err != nil {
		log.Fatalln(err)
	}
	defer func() {
		if err := producer.Close(); err != nil {
			log.Fatalln(err)
		}
	}()

	msg := &kafka.ProducerMessage{Topic: TOPIC, Value: kafka.StringEncoder(MESSAGE)}
	partition, offset, err := producer.SendMessage(msg)
	if err != nil {
		log.Printf("FAILED to send message: %s\n", err)
	} else {
		log.Printf("> message sent to partition %d at offset %d\n", partition, offset)
	}
}

package client

import (
	kafka "github.com/Shopify/sarama"
	"github.com/araobp/spielzeug/util"
	"log"
)

var producer kafka.SyncProducer

func Init(conf util.Config) {
	var err error
	producer, err = kafka.NewSyncProducer([]string{conf.KafkaServer}, nil)
	if err != nil {
		log.Fatalln(err)
	}
}

func Close() {
	if err := producer.Close(); err != nil {
		log.Fatalln(err)
	}
}

func ProduceString(topic string, message string) {

	msg := &kafka.ProducerMessage{Topic: topic, Value: kafka.StringEncoder(message)}
	partition, offset, err := producer.SendMessage(msg)
	if err != nil {
		log.Printf("FAILED to send message: %s\n", err)
	} else {
		log.Printf("> message sent to partition %d at offset %d\n", partition, offset)
	}
}

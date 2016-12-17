package protocol

import (
	_ "bufio"
	MQTT "github.com/eclipse/paho.mqtt.golang"
	"log"
	"strings"
)

var client MQTT.Client
var topicRobot string

func eventMainCat1(event string) {
	switch event[1:2] {
	case TEMPERATURE:
		log.Println("TEMPERATURE")
	case GEOMAGNETIC:
		log.Println("GEOMAGNETIC")
	default:
	}
}

func eventMainCat2(event string) {
	switch event[1:2] {
	case GYROSCOPE:
		log.Println("GYROSCOPE")
	default:
	}
}

func handler(client MQTT.Client, msg MQTT.Message) {
	msgs := string(msg.Payload())
	//log.Println(msgs)
	msgsSplit := strings.Split(msgs, ",")
	_topicRobot := msgsSplit[0]
	//log.Println(topicRobot)
	if _topicRobot != topicRobot {
		log.Printf("topic(robot) changed: %s => %s\n", topicRobot, _topicRobot)
		topicRobot = _topicRobot
	}
	events := msgsSplit[1:]
	for _, event := range events {
		log.Println(event)
		switch event[0:1] {
		case READ:
		case WRITE:
		case EVENT_PERIPHERAL:
		case EVENT_MAIN_CAT1:
			log.Println("EVENT_MAIN_CAT1")
			eventMainCat1(event)
		case EVENT_MAIN_CAT2:
			log.Println("EVENT_MAIN_CAT2")
			eventMainCat2(event)
		default:
		}
	}
}

func Loop() {
	select {}
}

func init() {
	opts := MQTT.NewClientOptions().AddBroker(SERVER).SetClientID(CLIENT_ID)
	client = MQTT.NewClient(opts)
	token := client.Connect()
	if token.Wait() && token.Error() != nil {
		panic(token.Error())
	}

	token = client.Subscribe(TOPIC_EVENT, 0, handler)
	if token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
}

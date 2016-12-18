package protocol

import (
	_ "bufio"
	MQTT "github.com/eclipse/paho.mqtt.golang"
	"log"
	"strconv"
	"strings"
)

var client MQTT.Client
var topicRobot string

func toSign(s string) int {
	sign := 1
	switch s {
	case "0":
	case "1":
		sign = -1
	default:
		log.Fatalln("Illegal sign")
	}
	return sign
}

func toInt(num string) int {
	sign := toSign(num[0:1])
	value := 0
	for _, s := range num[1:] {
		v, _ := strconv.Atoi(string(s))
		value = value*10 + v
	}
	return sign * value
}

func toUint(num string) int {
	value := 0
	for _, s := range num {
		v, _ := strconv.Atoi(string(s))
		value = value*10 + v
	}
	return value
}

var Axis map[string]string = map[string]string{
	X_AXIS: "x",
	Y_AXIS: "y",
	Z_AXIS: "z",
}

func eventMainCat1(event string) {
	switch event[1:2] {
	case TEMPERATURE:
		temp := toInt(event[2:])
		log.Printf("Temperature: %d (degrees Celsius)\n", temp)
	case GEOMAGNETIC:
		direction := toInt(event[2:])
		log.Printf("Orientation: %d (degrees)\n", direction)
	default:
	}
}

func eventMainCat2(event string) {
	switch event[1:2] {
	case GYROSCOPE:
		log.Printf("Angular velocity %s axis: %d (degree per second)\n", Axis[event[2:3]], toInt(event[3:]))
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
		log.Printf("Event received: %s\n", event)
		switch event[0:1] {
		case READ:
		case WRITE:
		case EVENT_PERIPHERAL:
		case EVENT_MAIN_CAT1:
			//log.Println("EVENT_MAIN_CAT1")
			eventMainCat1(event)
		case EVENT_MAIN_CAT2:
			//log.Println("EVENT_MAIN_CAT2")
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

package protocol

import (
	"encoding/json"
	"io/ioutil"
	"log"
)

type Config struct {
	MqttServer     string `json:"mqtt_server"`
	MqttClientId   string `json:"mqtt_client_id"`
	MqttTopicEvent string `json:"mqtt_topic_event"`
}

func GetConfig(confPath string) Config {
	bf, err := ioutil.ReadFile(confPath)
	if err != nil {
		panic(err)
	}
	conf := Config{}
	err = json.Unmarshal(bf, &conf)
	if err != nil {
		panic(err)
	}
	log.Printf("%v\n", conf)
	return conf
}

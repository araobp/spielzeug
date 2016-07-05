package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"reflect"
	"time"

	"github.com/samuel/go-zookeeper/zk"
)

const ZK_SERVER = "127.0.0.1"
const THING_ID = "toy1"

type Config struct {
	A int    `json:"a"`
	B string `json:"b"`
}

func main() {

	// reads conf.json
	bf, err := ioutil.ReadFile("./conf.json")
	if err != nil {
		panic(err)
	}

	// unmarshals the byte array into Config
	conf := Config{}
	err = json.Unmarshal(bf, &conf)
	if err != nil {
		panic(err)
	}
	log.Printf("%v\n", conf)

	// panic recovery
	defer func() {
		if err := recover(); err != nil {
			log.Print("Unable to fetch config from ZooKeeper", err)
		}
		log.Printf("%v\n", conf)
	}()

	// a path to the config data on ZooKeeper
	path := fmt.Sprintf("/things/%s", THING_ID)

	// connects to ZooKeeper
	conn, _, err := zk.Connect([]string{ZK_SERVER}, time.Second)
	if err != nil {
		panic(err)
	}

	// gets the config data
	bz, stat, _ := conn.Get(path)
	ver := stat.Version
	log.Printf("%v %d\n", bz, ver)

	// unmarshals the config data into Config
	conf_ := Config{}
	err = json.Unmarshal(bz, &conf_)
	if err != nil {
		panic(err)
	}
	//log.Printf("%v\n", conf_)

	// compares confg.json with the config on ZooKeeper
	if !reflect.DeepEqual(conf, conf_) {
		log.Print("updating config.json...")
		conf = conf_
		// writes the config to conf.json
		_ = ioutil.WriteFile("./conf.json", bz, 0644)
	}
}

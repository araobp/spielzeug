package main

import (
	"github.com/araobp/spielzeug/client"
	"github.com/araobp/spielzeug/protocol"
	"github.com/araobp/spielzeug/util"
	"time"
)

func main() {
	conf := util.GetConfig("./conf.json")
	protocol.Init(conf)
	client.Init(conf)
	defer client.Close()
	time.Sleep(3 * time.Second)
	client.ProduceString(conf.KafkaTopic, "Hello World!")
	protocol.Loop()
}

package main

import (
	"github.com/araobp/spielzeug/protocol"
)

func main() {
	protocol.Init("./conf.json")
	protocol.Loop()
}

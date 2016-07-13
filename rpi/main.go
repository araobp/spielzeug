package main

import (
	"github.com/araobp/spielzeug/rpi/parts"

	"time"
)

func main() {
	done := make(chan bool, 1)
	go func(done chan bool) {
		parts.Blink(parts.GREEN)
		time.Sleep(time.Second)
		parts.Blink(parts.RED)
		time.Sleep(time.Second)
		parts.Blink(parts.GREEN)
		done <- true
	}(done)
	<-done
}

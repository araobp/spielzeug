package main

import (
	"github.com/araobp/spielzeug/rpi/parts"

	"time"
)

func main() {

	// Blinking LED on Raspberry Pi
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

	// Blinking LED on Arduino Uno
	parts.LedOn()
	time.Sleep(time.Second)
	parts.LedOff()

	// Rorate the arm of SG90 servo motor
	parts.Rotate(-90)
	time.Sleep(time.Second)
	parts.Rotate(0)
	time.Sleep(time.Second)
	parts.Rotate(+90)
}

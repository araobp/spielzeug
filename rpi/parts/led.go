package parts

import (
	"fmt"
	"log"
	"time"
)

var gpioPinGreen []byte = []byte("5")
var gpioPinRed []byte = []byte("6")

const (
	GREEN = "gpio5"
	RED   = "gpio6"
)

const timeout = 50 // 50msec

var off []byte = []byte("0") // LED OFF
var on []byte = []byte("1")  // LED ON

func init() {
	Write("/sys/class/gpio/unexport", gpioPinGreen)
	Write("/sys/class/gpio/unexport", gpioPinRed)
	Write("/sys/class/gpio/export", gpioPinGreen)
	Write(fmt.Sprintf("/sys/class/gpio/%s/direction", GREEN), []byte("out"))
	Write("/sys/class/gpio/export", gpioPinRed)
	Write(fmt.Sprintf("/sys/class/gpio/%s/direction", RED), []byte("out"))
	log.Print("Done!")
}

func Blink(color string) {
	if color == GREEN || color == RED {
		Write(fmt.Sprintf("/sys/class/gpio/%s/value", color), on)
		time.Sleep(timeout * time.Millisecond)
		Write(fmt.Sprintf("/sys/class/gpio/%s/value", color), off)
	}
}

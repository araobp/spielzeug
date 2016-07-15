package parts

import (
	"fmt"
	"github.com/araobp/spielzeug/rpi/util"
	"log"
	"time"
)

const (
	GPIO_PIN_GREEN = "5" // GPIO pin for green LED
	GPIO_PIN_RED   = "6" // GPIO pin for red LED
)

const (
	GREEN = "gpio" + GPIO_PIN_GREEN
	RED   = "gpio" + GPIO_PIN_RED
)

const TIMEOUT = 50 // 50msec

const (
	OFF = "0" // LED OFF
	ON  = "1" // LED ON
)

func init() {
	util.Write("/sys/class/gpio/unexport", GPIO_PIN_GREEN)
	util.Write("/sys/class/gpio/unexport", GPIO_PIN_RED)
	util.Write("/sys/class/gpio/export", GPIO_PIN_GREEN)
	util.Write(fmt.Sprintf("/sys/class/gpio/%s/direction", GREEN), "out")
	util.Write("/sys/class/gpio/export", GPIO_PIN_RED)
	util.Write(fmt.Sprintf("/sys/class/gpio/%s/direction", RED), "out")
	log.Print("Done!")
}

// blinks a LED
func Blink(color string) {
	if color == GREEN || color == RED {
		util.Write(fmt.Sprintf("/sys/class/gpio/%s/value", color), ON)
		time.Sleep(TIMEOUT * time.Millisecond)
		util.Write(fmt.Sprintf("/sys/class/gpio/%s/value", color), OFF)
	}
}

package parts

import (
	"fmt"
	"log"
	"os"
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

func write(path string, data []byte) {
	f, err := os.OpenFile(path, os.O_WRONLY, 0770)
	defer f.Sync()
	defer f.Close()
	if err != nil {
		panic(err)
	}
	_, err = f.Write(data)
	if err != nil {
		panic(err)
	}
}

func init() {
	write("/sys/class/gpio/unexport", gpioPinGreen)
	write("/sys/class/gpio/unexport", gpioPinRed)
	write("/sys/class/gpio/export", gpioPinGreen)
	write(fmt.Sprintf("/sys/class/gpio/%s/direction", GREEN), []byte("out"))
	write("/sys/class/gpio/export", gpioPinRed)
	write(fmt.Sprintf("/sys/class/gpio/%s/direction", RED), []byte("out"))
	log.Print("Done!")
}

func Blink(color string) {
	if color == GREEN || color == RED {
		write(fmt.Sprintf("/sys/class/gpio/%s/value", color), on)
		time.Sleep(timeout * time.Millisecond)
		write(fmt.Sprintf("/sys/class/gpio/%s/value", color), off)
	}
}

package parts

import (
	"bufio"
	"github.com/tarm/serial"
	"log"
)

var port *serial.Port

func init() {
	// opens a serial interface to Arduino Uno
	c := &serial.Config{Name: "/dev/ttyACM0", Baud: 9600}
	var err error
	port, err = serial.OpenPort(c)
	if err != nil {
		log.Print(err)
	}
}

const (
	LED_HIGH = iota
	LED_LOW
)

func control(command int) {
	if port == nil {
		log.Print("Arduino inaccessible")
		return
	}
	switch command {
	case LED_HIGH:
		port.Write([]byte("h"))
		log.Printf("Command to Arduino: h")
	case LED_LOW:
		port.Write([]byte("l"))
		log.Printf("Command to Arduino: l")
	}
	reader := bufio.NewReader(port)
	ack, err := reader.ReadBytes('\x0a')
	if err != nil {
		log.Fatal(err)
	}
	log.Printf("ACK from Arduino: %s", ack)
}

func LedOn() {
	control(LED_HIGH)
}

func LedOff() {
	control(LED_LOW)
}

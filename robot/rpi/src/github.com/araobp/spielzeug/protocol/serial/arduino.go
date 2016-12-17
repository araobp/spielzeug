package protocol

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

func control(command string) {
	if port == nil {
		log.Print("Arduino inaccessible")
		return
	}
	port.Write([]byte(command))
	log.Printf("Command to Arduino: %s", command)
	reader := bufio.NewReader(port)
	ack, err := reader.ReadBytes('\x0a')
	if err != nil {
		log.Fatal(err)
	}
	log.Printf("ACK from Arduino: %s", ack)
}

func LedOn() {
	command := WRITE + LED + UNIT_0 + PLUS + LED_HIGH
	control(command)
}

func LedOff() {
	command := WRITE + LED + UNIT_0 + PLUS + LED_LOW
	control(command)
}

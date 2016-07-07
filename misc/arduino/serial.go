package main

/*

   [Raspberry Pi 3] /dev/ttyACM0 <----- USB -----> [Arduino Uno]

*/

import (
	"bufio"
	"github.com/tarm/serial"
	"log"
	"time"
)

func main() {

	c := &serial.Config{Name: "/dev/ttyACM0", Baud: 9600}
	s, err := serial.OpenPort(c)
	if err != nil {
		log.Fatal(err)
	}

	go func() {
		for {
			reader := bufio.NewReader(s)
			ack, err := reader.ReadBytes('\x0a') // \n
			if err != nil {
				panic(err)
			}
			log.Printf("%s", ack)
		}
	}()

	for {
		_, _ = s.Write([]byte("h")) // "high": LED on
		time.Sleep(time.Second)

		_, _ = s.Write([]byte("l")) // low: LED off
		time.Sleep(time.Second)
	}
}

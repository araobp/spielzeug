/*

Enable GPIO 21 for PWM before executing this program:
$ ./pi-blaster -g 21 -D

*/

package main

import (
	"github.com/hybridgroup/gobot"
	"github.com/hybridgroup/gobot/platforms/gpio"
	"github.com/hybridgroup/gobot/platforms/raspi"
	"log"
	"os"
	"strconv"
)

func main() {

	a, _ := strconv.Atoi(os.Args[1])
	angle := uint8(a)

	if angle < 0 || angle > 180 {
		os.Exit(1)
	}

	gbot := gobot.NewGobot()
	r := raspi.NewRaspiAdaptor("raspi")
	servo := gpio.NewServoDriver(r, "servo", "40")
	work := func() {
		log.Printf("Moving servo to %d", angle)
		servo.Move(angle)
	}
	robot := gobot.NewRobot(
		"servoBot",
		[]gobot.Connection{r},
		[]gobot.Device{servo},
		work,
	)

	gbot.AddRobot(robot)
	gbot.Start()
}

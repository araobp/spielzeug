package main

import (
	"github.com/hybridgroup/gobot"
	"github.com/hybridgroup/gobot/platforms/gpio"
	"github.com/hybridgroup/gobot/platforms/raspi"
	"log"
	"time"
)

func main() {
	gbot := gobot.NewGobot()
	r := raspi.NewRaspiAdaptor("raspi")
	servo := gpio.NewServoDriver(r, "servo", "40")
	work := func() {
		gobot.Every(5*time.Second, func() {
			i := uint8(gobot.Rand(180))
			log.Printf("Moving servo to %d", i)
			servo.Move(i)
		})
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

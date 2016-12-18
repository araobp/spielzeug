package main

import (
	"time"

	"github.com/hybridgroup/gobot"
	"github.com/hybridgroup/gobot/platforms/gpio"
	"github.com/hybridgroup/gobot/platforms/raspi"
)

func main() {

	gbot := gobot.NewGobot()

	r := raspi.NewRaspiAdaptor("raspi")
	ledGreen := gpio.NewLedDriver(r, "led", "29")
	ledRed := gpio.NewLedDriver(r, "led", "31")

	work := func() {
		ledGreen.Toggle()
		gobot.Every(1*time.Second, func() {
			ledGreen.Toggle()
			ledRed.Toggle()
		})
	}

	robot := gobot.NewRobot("blinkBot",
		[]gobot.Connection{r},
		[]gobot.Device{ledGreen, ledRed},
		work,
	)
	gbot.AddRobot(robot)
	gbot.Start()
}

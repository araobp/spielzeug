/*
 * Circuit
 *
 *  GND    5V  GPIO21(PWM)
 *   |     |     |
 *   |     |     |
 *  ++-----+-----++
 *  |  SG90       |
 *  +-------------+
 *         |
 *    -----+ arm
 *
 * You have to run the following command before using this script:
 *
 * $ sudo ./pi-blaster -g 21
 */
package parts

import (
	"fmt"
	"log"
	"os"
)

const GPIO = "21" // GPIO 21

/*
  frequency: 100Hz

  PWM
  degree      duty cycle
  ----------------------
     -90      0.05%
       0      0.15%
     +90      0.25%
*/

func Rotate(angle int) {
	if angle < -90 || angle > 90 {
		panic("angle out of range")
	}
	duty := 15 + angle*10/90
	param := fmt.Sprintf("%v=0.%02d\n", GPIO, duty)
	log.Printf("pi-blaster: %s", param)
	f, _ := os.OpenFile("/dev/pi-blaster", os.O_WRONLY|os.O_APPEND, 0644)
	defer f.Close()
	_, err := f.WriteString(param)
	if err != nil {
		panic(err)
	}
}

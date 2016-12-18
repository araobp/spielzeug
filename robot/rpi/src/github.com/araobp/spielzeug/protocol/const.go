package protocol

const SERVER = "tcp://localhost:1883"
const CLIENT_ID = "manager"
const TOPIC_EVENT = "event"

// Operations
// event[0:1]
const (
	READ             = "0"
	WRITE            = "1"
	EVENT_PERIPHERAL = "2"
	EVENT_MAIN_CAT1  = "3"
	EVENT_MAIN_CAT2  = "4"
)

// Devices
// event[1:2]
const (
	LED              = "0"
	MOTOR            = "1"
	SERVO_MOTOR      = "2"
	PROXIMITY_SENSOR = "3"
	PHOTO_MICRO      = "4"
	TEMPERATURE      = "5"
	GEOMAGNETIC      = "6"
	GYROSCOPE        = "7"
)

// Device units
const (
	RIGHT  = "0"
	LEFT   = "1"
	UNIT_0 = "0"
	UNIT_1 = "1"
)

// Sign
const (
	FORWARD  = "0"
	BACKWARD = "1"
	PLUS     = "0"
	MINUS    = "1"
)

// Axis
const (
	X_AXIS = "0"
	Y_AXIS = "1"
	Z_AXIS = "2"
)

// LED control
const (
	LED_LOW  = "000"
	LED_HIGH = "001"
)

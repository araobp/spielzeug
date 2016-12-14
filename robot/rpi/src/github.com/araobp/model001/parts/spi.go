package parts

import (
	"golang.org/x/exp/io/spi"
	"math"
)

const A = 7.0 // note: this is a tentative value

// AD converter (MCP3008) ch1
var txBufCh0 []byte = []byte{0x01, 0x80, 0x00}

// AD converer (MCP3008) ch2
var txBufCh1 []byte = []byte{0x01, 0x90, 0x00}

// opens SPI to MCP3008
func getSpi() (dev *spi.Device) {
	dev, err := spi.Open(&spi.Devfs{
		Dev:      "/dev/spidev0.0",
		Mode:     spi.Mode0,
		MaxSpeed: 500000,
	})
	if err != nil {
		panic(err)
	}
	return dev
}

// obtains temperature data
func GetTemp() (temp float64) {
	dev := getSpi()
	defer dev.Close()

	rxBuf := []byte{0x00, 0x00, 0x00}

	// Ch0: Thermo
	if err := dev.Tx(txBufCh0, rxBuf); err != nil {
		panic(err)
	}
	result := ((rxBuf[1] & 0x03) << 8) + rxBuf[2]
	volt := float64(result) * 3.3 / 1023
	temp = (volt*1000 - 500) / 10
	return temp
}

// obtains luminous intensity data
func GetLumi() (lumi float64) {
	dev := getSpi()
	defer dev.Close()

	// Ch1: CdS
	rxBuf := []byte{0x00, 0x00, 0x00}
	if err := dev.Tx(txBufCh1, rxBuf); err != nil {
		panic(err)
	}
	result := ((rxBuf[1] & 0x03) << 8) + rxBuf[2]
	volt := float64(result) * 3.3 / 1023
	r := (3.3/volt - 1) * 10000
	var l float64
	if math.IsInf(r, 1) {
		l = 0
	} else {
		l = A - math.Log10(r)
	}
	return l
}

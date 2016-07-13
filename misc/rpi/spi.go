package main

import (
	"fmt"
	"golang.org/x/exp/io/spi"
	"math"
)

const A = 7.0

func main() {
	dev, err := spi.Open(&spi.Devfs{
		Dev:      "/dev/spidev0.0",
		Mode:     spi.Mode0,
		MaxSpeed: 500000,
	})
	if err != nil {
		panic(err)
	}
	defer dev.Close()

	txBufCh0 := []byte{0x01, 0x80, 0x00}
	txBufCh1 := []byte{0x01, 0x90, 0x00}
	rxBuf := []byte{0x00, 0x00, 0x00}

	// Ch0: Thermo
	if err := dev.Tx(txBufCh0, rxBuf); err != nil {
		panic(err)
	}
	fmt.Printf("%v\n", rxBuf)
	result := ((rxBuf[1] & 0x03) << 8) + rxBuf[2]
	fmt.Printf("%v\n", result)
	volt := float64(result) * 3.3 / 1023
	temp := (volt*1000 - 500) / 10
	fmt.Printf("%.1f\n", temp)

	// Ch1: CdS
	rxBuf = []byte{0x00, 0x00, 0x00}
	if err := dev.Tx(txBufCh1, rxBuf); err != nil {
		panic(err)
	}
	fmt.Printf("%v\n", rxBuf)
	result = ((rxBuf[1] & 0x03) << 8) + rxBuf[2]
	fmt.Printf("%v\n", result)
	volt = float64(result) * 3.3 / 1023
	r := (3.3/volt - 1) * 10000
	fmt.Printf("%.1f\n", r)
	var l float64
	if math.IsInf(r, 1) {
		l = 0
	} else {
		l = A - math.Log10(r)
	}
	fmt.Printf("%.1f\n", l)
}

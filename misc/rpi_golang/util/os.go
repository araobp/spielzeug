package util

import (
	"os"
)

func Write(path string, data string) (err error) {
	f, err := os.OpenFile(path, os.O_WRONLY, 0770)
	defer f.Sync()
	defer f.Close()
	if err != nil {
		panic(err)
	}
	_, err = f.WriteString(data)
	return err
}

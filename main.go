package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	fp, err := os.Open("test_input.txt")

	if err != nil {
		panic(err)
	}

	c := make([]byte, 1)

	for err == nil {
		_, err = fp.Read(c)
		fmt.Printf(strings.ToUpper(string(c)))
	}
}

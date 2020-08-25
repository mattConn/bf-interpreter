package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	args := os.Args[1:]
	if len(args) == 0 {
		fmt.Println("No BF file specified.")
		return
	}

	fp, err := os.Open(args[0])
	defer fp.Close()

	if err != nil {
		panic(err)
	}

	const MEM_SIZE = 30000
	var mem [MEM_SIZE]byte

	fmt.Println(mem)

	c := make([]byte, 1)

	for err == nil {
		_, err = fp.Read(c)
		fmt.Printf(strings.ToUpper(string(c)))
	}
}

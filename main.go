package main

import (
	"fmt"
	"os"
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
	var ptr uint16 // mem ptr

	buf := make([]byte, 1) // file data buffer

	bracketCount := 0 // count brackets to find open/closing brackets

	for err == nil {
		_, err = fp.Read(buf)

		switch buf[0] {
		case '>': // inc mem ptr
			ptr = (ptr + 1) % MEM_SIZE

		case '<': // dec mem ptr
			if ptr == 0 {
				ptr = MEM_SIZE - 1
			} else {
				ptr--
			}

		case '+': // inc cell
			mem[ptr]++

		case '-': // dec cell
			mem[ptr]--

		case '.': // output
			fmt.Printf("%c", mem[ptr])

		case '[':
			if mem[ptr] != 0 {
				break
			}

			bracketCount = 1

			for bracketCount != 0 {
				_, err = fp.Read(buf)

				if err != nil {
					fmt.Println("Missing ']'.")
					return
				}

				if buf[0] == '[' {
					bracketCount++
				} else if buf[0] == ']' {
					bracketCount--
				}

			}

		case ']':
			if mem[ptr] == 0 {
				break
			}

			bracketCount = 1

			for bracketCount != 0 {
				fp.Seek(-2, 1)

				if err != nil {
					fmt.Println("Missing '['.")
					return
				}

				_, err = fp.Read(buf)
				if buf[0] == '[' {
					bracketCount--
				}
				if buf[0] == ']' {
					bracketCount++
				}
			}

			// NEED: input

		} // end switch
	} // end loop

}

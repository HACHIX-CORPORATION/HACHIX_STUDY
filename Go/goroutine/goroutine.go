package main

import (
	"fmt"
	"time"
)

// goroutine = a thread
// channels = goroutine間を接続するパイプ(トンネル)のイメージ

func f(value string) {
	for i := 0; i < 3; i ++ {
		fmt.Println(value)
		time.Sleep(3 * time.Second)
	}
}

func main() {
	go f("by go routine")
	f("normal")
	fmt.Println("done")
}


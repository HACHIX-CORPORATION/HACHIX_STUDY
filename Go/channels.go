package main

import (
	"fmt"
)

// chan: one type of variable
// バッファとして使える。
// バッファが詰まるとチャネルへの送信をブロックする
// バッファが空のときは、チャネルの受信をブロックする

func main() {
    ch := make(chan int, 2)
    ch <- 1
    ch <- 2 

    fmt.Println(<-ch)
    fmt.Println(<-ch)

}
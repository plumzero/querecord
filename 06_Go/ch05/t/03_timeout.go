
package main

import (
    "fmt"
    "time"
)

func main() {

    timeout := make(chan bool, 1)
    go func() {
        time.Sleep(time.Second)
        timeout <- true
    }()

    ch := make(chan int, 1)

    select {
        case <- ch:
            // wait for nothing
        case <- timeout:
            fmt.Println("Time out")
    }
}
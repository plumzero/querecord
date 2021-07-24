
package main

import "fmt"

func IntegerGenerator() chan int {
    var ch chan int = make(chan int)

    go func() {
        for i := 0; ; i++ {
            ch <- i		// 阻塞，只有当通道索要数据时才会发送数据
        }
    }()

    return ch
}

func main() {
    generator := IntegerGenerator()

    for i := 0; i < 100; i++ {
        fmt.Println(<-generator)
    }
}

package main

import (
    "time"
    "fmt"
)

func main() {
    done := make(chan struct{})

    go func() {
        // 主动关闭通道的协程
        defer close(done)
        for i := 0; i < 5; i++ {
            fmt.Println("已经执行了", i, "次")
            time.Sleep(time.Second)
        }
    }()

    for {
        select {
        case <- done:   // 读等待
            fmt.Println("主动关闭通道的协程调用了 close 退出了!")
            return
        }
    }
}
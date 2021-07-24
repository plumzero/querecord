
package main

import "fmt"

func main() {
    ch, quit := make(chan int), make(chan int)

    go func() {
        ch <- 8		// 添加数据
        quit <- 1 	// 发送完成信号
    } ()

    for isQuit := false; ! isQuit; {
        select {
        case v := <-ch:
            fmt.Printf("received %d from ch\n", v)
        case <-quit:
            isQuit = true		// 通道 quit 有输出，关闭 for 循环
        }
    }
}

package main

import (
	"context"
	"log"
	"os"
	"time"
)

var logs *log.Logger

func doClean(ctx context.Context) {
	for {
		time.Sleep(1 * time.Second)
		select {
		case <- ctx.Done():
			log.Println("doClean: 收到 Cancel，做好收尾工作后马上退出")
			return
		default:
			log.Println("doClean: 每隔 1 秒观察信号，继续观察...")
		}
	}
}

func doNothing(ctx context.Context) {
	for {
		time.Sleep(3 * time.Second)
		select {
		case <- ctx.Done():
			logs.Println("doNothing: 收到 Cancel，但不退出...")
			// return
		default:
			logs.Println("doNothing: 每隔 3 秒观察信号，一直运行")
		}
	}
}

func main() {
	logs = log.New(os.Stdout, "", log.Ltime)
	// 创建上下文
	ctx, cancel := context.WithCancel(context.Background())
	// 传递上下文
	go doClean(ctx)
	go doNothing(ctx)

	// 主协程阻塞 20 秒，观察
	time.Sleep(20 * time.Second)
	log.Println("cancel")

	cancel()

	// 发出 cancel 命令后，主协程阻塞 10 秒，再看协程的运行情况
	time.Sleep(10 * time.Second)
}
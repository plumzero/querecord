
package main

import (
    "flag"
    "log"
    "net/url"
    "os"
    "os/signal"
    "time"

    "github.com/gorilla/websocket"
)

var addr = flag.String("addr", ":8080", "http service address")

func main() {
    flag.Parse()
    log.SetFlags(0)

    interrupt := make(chan os.Signal, 1)
    signal.Notify(interrupt, os.Interrupt)

    u := url.URL{Scheme: "ws", Host: *addr, Path: "/echo"}
    log.Printf("connecting to %s", u.String())

    c, _, err := websocket.DefaultDialer.Dial(u.String(), nil)  // 客户端尝试发起建立 websocket 连接
    if err != nil {
        log.Fatal("dial:", err)
    }
    defer c.Close()

    done := make(chan struct{})

    // 读协程
    go func() {
        defer close(done)
        for {
            _, message, err := c.ReadMessage()  // 读取来自服务端的数据
            if err != nil {
                log.Println("read:", err)
                return
            }
            log.Printf("recv: %s", message)
        }
    }()

    ticker := time.NewTicker(time.Second)
    defer ticker.Stop()

    for {
        select {
        case <- done:   // 读协程退出时(如读失败或服务端关闭时)会走这里
            return
        case t := <- ticker.C:  // 定时器会定时写入特定时间格式数据
            err := c.WriteMessage(websocket.TextMessage, []byte(t.String()))
            if err != nil {
                log.Println("write:", err)
                return
            }
        case <- interrupt:  // 遭遇中断信号，向服务端发送连接关闭请求，
            log.Println("interrupt")
            err := c.WriteMessage(websocket.CloseMessage, websocket.FormatCloseMessage(websocket.CloseNormalClosure, ""))
            if err != nil {
                log.Println("write close:", err)
                return
            }
            select {
            case <- done:  // 客户端发送连接关闭请求，服务端关闭后，客户端读协程退出，会走这时
            case <- time.After(time.Second):   // 服务端一直不关闭，设置定时后客户端退出
            }
            return
        }
    }
}
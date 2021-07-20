
package main

import (
    "bytes"
    "log"
    "net/http"
    "time"

    "github.com/gorilla/websocket"
)

// 这里的客户端实际上是真正客户端的一个代理，客户端与真正客户端之间建立 websocket 连接

const (
    writeWait = 10 * time.Second
    pongWait = 60 * time.Second
    pingPeriod = (pongWait * 9) / 10
    maxMessageSize = 32
)

var (
    newline = []byte{'\n'}
    space = []byte{' '}
)

// ReadBufferSize 和 WriteBufferSize 指定了 I/O 缓存尺寸。如果缓存尺寸为 0，则指定一个缺省尺寸。
// I/O 缓存尺寸的大小并不会限制可以收发的数据的长度。
var upgrader = websocket.Upgrader{
    ReadBufferSize:  1024,
    WriteBufferSize: 1024,
}

// websocket.Conn 类型代表了一个 WebSocket 连接。服务端在一个 HTTP 请求处理器函数中调用 Upgrader.Upgrade 方法可以获取它。
// 之后使用这个 Conn 进行数据的收发
type Client struct {
    hub 	*Hub
    conn	*websocket.Conn
    send	chan []byte
}

// readPump 将收到的来自 websocket 的数据泵到 hub
// 每个连接一个 readPump 协程
func (c *Client) readPump() {
    defer func() {
        c.hub.unregister <- c
        c.conn.Close()
    }()
    // SetReadLimit 用于设置收到来自对端的最大消息尺寸(字节计)
    // 如果收到的消息大于这个尺寸，则向对端发送一个关闭消息，并返回 ErrReadLimit
    c.conn.SetReadLimit(maxMessageSize)
    // SetReadDeadline 设置收取数据的截止时间线，相当于一个超时。不过与超时不同的是，如果到了那个时间线还未收到数据，
    // 那么连接状态将会销毁，之后所有的读都将会返回错误。
    // 如果设置为 0，则表示没有超时限制。
    c.conn.SetReadDeadline(time.Now().Add(pongWait))
    // 为来自对端的 pong 消息设置处理句柄
    c.conn.SetPongHandler(func(string) error { c.conn.SetReadDeadline(time.Now().Add(pongWait)); return nil})

    for {
        _, message, err := c.conn.ReadMessage()
        if err != nil {
            // 查看是否为非预期关闭
            if websocket.IsUnexpectedCloseError(err, websocket.CloseGoingAway, websocket.CloseAbnormalClosure) {
                log.Printf("error: %v", err)
            }
            break
        }
        message = bytes.TrimSpace(bytes.Replace(message, newline, space, -1))
        c.hub.broadcast <- message      // 因为是聊天室，所以要进行'广播'
    }
}

// writePump 将 hub 的数据发往 websocket 连接
// 每个连接一个 writePump 协程
func (c *Client) writePump() {
    ticker := time.NewTicker(pingPeriod)
    defer func() {
        ticker.Stop()
        c.conn.Close()
    }()

    for {
        select {
        case message, ok := <- c.send:  // 1. 接收客户端缓冲里的消息
            c.conn.SetWriteDeadline(time.Now().Add(writeWait))
            if ! ok {
                c.conn.WriteMessage(websocket.CloseMessage, []byte{})
                return
            }

            // 返回一个 writer 用于下次消息的发送
            // 一条连接上最多只有一个打开的 writer。NextWriter 将会关闭之前的 writer(如果打开的话)
            // NextWriter 支持所有的消息类型(TextMessage, BinaryMessage, CloseMessage, PingMessage, PongMessage)
            // IMHO 1: 不同的 writer 写不同类型的消息，通过 NextWriter 可以很容易获得写不同类型消息的 writer
            // IMHO 2: 获取下一个 writer 不是说关闭这条连接，以及创建一条新连接。它只是消息类型的转换
            w, err := c.conn.NextWriter(websocket.TextMessage)
            if err != nil {
                return
            }
            w.Write(message)    // 2. 将客户端缓冲里的消息发往 websocket 连接对端

            n := len(c.send)
            for i := 0; i < n; i++ {
                w.Write(newline)
                w.Write(<-c.send)
            }

            if err := w.Close(); err != nil {
                return
            }
        case <- ticker.C:
            c.conn.SetWriteDeadline(time.Now().Add(writeWait))
            if err := c.conn.WriteMessage(websocket.PingMessage, nil); err != nil {
                return
            }
        }
    }
}

func serveWs(hub *Hub, w http.ResponseWriter, r *http.Request) {
    conn, err := upgrader.Upgrade(w, r, nil)
    if err != nil {
        log.Println(err)
        return
    }
    client := &Client{hub: hub, conn: conn, send: make(chan []byte, 256)}
    client.hub.register <- client

    go client.writePump()
    go client.readPump()
}

package main

type Hub struct {
    // 记录已经连接的客户端
    clients map[*Client]bool
    //
    broadcast chan []byte
    // 用于接收来自客户端的连接请求
    register chan *Client
    // 用于接收来自客户端的断开连接请求
    unregister chan *Client
}

func newHub() *Hub {
    return &Hub{
        broadcast:  make(chan []byte),
        register:   make(chan *Client),
        unregister: make(chan *Client),
        clients:    make(map[*Client]bool),
    }
}
func (h *Hub) run() {
    for {
        select {
        case client := <- h.register:
            h.clients[client] = true
        case client := <- h.unregister:
            if _, ok := h.clients[client]; ok {
                delete(h.clients, client)
                close(client.send)
            }
        case message := <-h.broadcast:
            for client := range h.clients {
                select {
                case client.send <- message:
                default:
                    close(client.send)
                    delete(h.clients, client)
                }
            }
        }
    }
}

package main

import (
	"fmt"
	"net"
)

// 定义心跳
type Heartbeat struct {
	endTime  int64	// 过期时间
}

var ConnSlice map[net.Conn]*Heartbeat

func main() {
	ConnSlice = map[net.Conn]*Heartbeat{}
	l, err := net.Listen("tcp", ":8888")
	if err != nil {
		fmt.Println("服务端启动失败")
		return
	}
	defer l.Close()

	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Println("Accept err:", err)
			return
		}
		fmt.Printf("Received message %s -> %s\n", conn.RemoteAddr(), conn.LocalAddr())

		ConnSlice[conn] = &Heartbeat{
			endTime: time.Now().Add(time.Second * 5).Unix(),		// 心跳初始化
		}
		
		go handleConn(conn)
	}
}

func handleConn(c net.Conn) {
	buffer := make([]byte, 1024)

	for {
		n, err := c.Read(buffer)
		if ConnSlice[c].endTime > time.Now().Unix() {
			ConnSlice[c].entTime = time.Now().Add(time.Second * 5).Unix()		// 更新心跳到下一个检测点
		} else {
			fmt.Println("长时间未发消息，断开连接")
			return
		}
		if err != nil {
			return
		}
		// 如果是心跳检测，则跳过执行
		if string(buffer[0:n]) == "1" {
			c.Write([]byte("1"))
			continue
		}
		for conn, heart := range ConnSplice {
			if conn == c {
				continue
			}
			// 心跳检测，在需要发送数据时才检查规定时间内有没有数据到达
			if heart.endTime < time.Now().Unix() {
				delete(ConnSlice, conn)
				conn.Close()
				fmt.Println("删除连接", conn.RemoteAddr())
				fmt.Println("现在存有连接", ConnSlice)
				continue
			}
			conn.Write(buffer[0:n])
		}
	}
}
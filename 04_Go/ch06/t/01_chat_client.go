
package main

import (
	"fmt"
	"log"
	"net"
	"bufio"
	"os"
	"time"
)

func main() {
	tcpAddr, err := net.ResolveTCPAddr("tcp4", ":8888")
	if err != nil {
		log.Fatal("net.ResolveTCPAddr err:", err)
		return
	}

	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		log.Fatal("net.DialTCP err:", err)
		return
	}

	Sender(conn)
}

func Sender(conn *net.TCPConn) {
	defer conn.Close()

	sc := bufio.NewReader(os.Stdin)
	
	// 心跳例程，定期发送心跳包给服务器端
	go func() {
		t := time.NewTicker(time.Second)
		defer t.Stop()
		for {
			<- t.C
			_, err := conn.Write([]byte("1"))
			if err != nil {
				fmt.Println("Conn.Write err:", err)
				return
			}
		}
	}()

	name := ""
	fmt.Println("请输入聊天昵称")
	fmt.Fscan(sc, &name)
	msg := ""
	buffer := make([]byte, 1024)
	_t := time.NewTimer(time.Second * 5)	// 创建定时器，每次服务端发来消息就刷新时间
	defer _t.Stop()

	go func() {
		<- _t.C
		fmt.Println("服务器出现故障，断开连接")
		return
	}()

	// 接收服务器消息
	for {
		go func() {
			for {
				n, err := conn.Read(buffer)
				if err != nil {
					return
				}
				_t.Reset(time.Second * 5)
				if string(buffer[0:1]) != "1" {
					fmt.Println(string(buffer[0:n]))
				}
			}
		}()
		fmt.Fscan(sc, &msg)
		i := time.Now().Format("2006-01-02 15:04:05")
		conn.Write([]byte(fmt.Sprintf("%s\n\t%s: %s", i, name, msg)))
	}
}

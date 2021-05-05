package main

import (
    "fmt"
    "net"
    "os"
	
    "github.com/golang/protobuf/proto"
	
	"ipc.com/msg"
)

func main() {
    // listen
    listener, err := net.Listen("tcp", "localhost:6600")
    if err != nil {
        panic(err)
    }

    for {
        conn, err := listener.Accept()
        if err != nil {
            panic(err)
        }
        fmt.Println("new connect", conn.RemoteAddr())
        go readMessage(conn)
    }
}

// receive
func readMessage(conn net.Conn) {
    defer conn.Close()
    buf := make([]byte, 4096, 4096)
    for {
        // read
        cnt, err := conn.Read(buf)
        if err != nil {
            panic(err)
        }

        stReceive := &msg.UserInfo{}
        pData := buf[:cnt]

        // protobuf
        err = proto.Unmarshal(pData, stReceive)
        if err != nil {
            panic(err)
        }

        fmt.Println("receive", conn.RemoteAddr(), stReceive)
        if stReceive.Message == "stop" {
            os.Exit(1)
        }
    }
}

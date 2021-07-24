
Go 语言标准库对传统的 Socket 编程过程进行了抽象和封装，无论需要使用什么协议建立什么形式的连接，都只需要调用 `net.Dial()` 即可。


### Dial() 函数

```go
    func Dial(net, addr string) (Conn, error)
```
其中 net 参数是网络协议的名字，addr 参数是 IP 地址或域名，而端口号以 ":" 的形式跟随在地址或域名的后面，端口号可选。如果连接成功，返回连接对象，否则返回 error 。

TCP协议链接:
```go
    conn, err := net.Dial("tcp", "192.168.0.10:2100")
```

UDP协议链接:
```go
    conn, err := net.Dial("udp", "192.168.0.12:975")
```

ICMP链接(使用协议名称):
```go
   conn, err := net.Dial("ip4:icmp", "www.baidu.com") 
```

ICMP链接(使用协议编号):
```go
    conn, err := net.Dial("ip4:1", "10.0.0.3")
```
目前，Dial() 函数支持如下几种网络协议:"tcp", "tcp4"(仅限IPv4), "tcp5"(仅限IPv6), "udp", "udp4"(仅限IPv4), "udp6"(仅限IPv6), "ip", "ip4"(仅限IPv4)和"ip6"(仅限IPv6)。

在成功建立连接后，我们就可以进行数据的发送和接收。发送数据时，使用 conn 的 Write() 成员方法，接收数据时使用 Read() 方法。

[Dial使用示例](t/01_Dial.go)

实际上，Dial() 函数是对 DialTCP(), DialUDP(), DialIP() 和 DialUnix() 的封装。我们也可以直接调用这些函数，其功能是一致的:
```go
    func DialTCP(net string, laddr, raddr * TCPAddr) (c * TCPConn, err error)
    func DialUDP(net string, laddr, raddr * UDPAddr) (c * UDPConn, err error)
    func DialIP(netProto string, laddr, raddr * IPAddr) (* IPConn, error)
    func DialUnix(net string, laddr, raddr * UnixAddr) (c * UnixConn, err error)
```

[DialTcp使用示例](t/01_DialTcp.go)

[编写Tcp server](t/01_tcp_server.go)  [编写与之通信的Tcp client](t/01_tcp_client.go)

进行 UDP Socket 编程，需要了解以下函数或方法的使用:
```go
    func ResolveUDPAddr(network, address string) (*UDPAddr, error)          // 创建监听地址
    func ListenUDP(network string, laddr UDPAddr) (UDPConn, error)          // 创建监听连接
    func (c *UDPConn) ReadFromUDP(b []byte) (int, *UDPAddr, error)          // 接收 UDP 数据
    func (c *UDPConn) WriteToUDP(b []byte, addr *UDPAddr) (int, error)      // 写出数据到 UDP
```

[编写Udp server](t/01_udp_server.go)  [编写与之通信的Udp client](t/01_udp_client.go)

[并发Udp server示例](t/01_concurrent_udp_server.go)  [与之通信的并发Udp client](t/01_concurrent_udp_client.go)

[tcp简易聊天服务端](t/01_chat_server.go)  [与之对应的tcp简易聊天客户端](t/01_chat_client.go)
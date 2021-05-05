
Go 语言标准库对传统的 Socket 编程过程进行了抽象和封装，无论需要使用什么协议建立什么形式的连接，都只需要调用 net.Dial() 即可。


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

[发送ICMP测试，执行效果不佳](t/01_icmptest.go)

[发送HTTP请求测试](t/02_simplehttp.go)

实际上，Dial() 函数是对 DialTCP(), DialUDP(), DialIP() 和 DialUnix() 的封装。我们也可以直接调用这些函数，其功能是一致的:
```go
    func DialTCP(net string, laddr, raddr * TCPAddr) (c * TCPConn, err error)
    func DialUDP(net string, laddr, raddr * UDPAddr) (c * UDPConn, err error)
    func DialIP(netProto string, laddr, raddr * IPAddr) (* IPConn, error)
    func DialUnix(net string, laddr, raddr * UnixAddr) (c * UnixConn, err error)
```

[发送HTTP请求测试二](t/03_simplehttp2.go)

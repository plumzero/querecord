
参考:
[Manpage of PCAP-FILTER](http://www.tcpdump.org/manpages/pcap-filter.7.html)

用途:
	tcpdump
	Wireshark

pcap-filter - 包过滤语法

描述：
	1.过滤表达式包括一个或多个基元。基元通常由位于一个或多个修饰语之前的一个 id(名称或数字)组成。有三种不同的修饰语：
	  type
		id 引用代表的事物。可能的 type 有 host, net, port, portrange 。例如 "host foo", "net 128.3", "port 20", "portrange 6000-6008"。缺省为 host。
	  dir
		指定到 id 或（和）来自 id 的一个特定转化方向。可能的方向有 src, dst, src or dst, src and dst, ra, ta, addr1, addr2, addr3, addr4 。例如 "src foo", "dst net 128.3", "src or dst port ftp-data"。缺省为 src or host 。
		ra, ta, addr1, addr2, addr3, addr4 只对 IEEE 802.11 无线局域网链接层有效。
	  proto
		特定协议下地严格匹配。可能的协议类型有 ether, fddi, tr, wlan, ip, ip6, arp, rarp, decnet, tcp, udp 。例如 "ether src foo", "arp net 128.3", "tcp port 21", "udp portrange 7000-7009", "wlan addr2 0:2:3:4:5:6" 。缺省
		根据协议类型而定，"src foo" 也即 "(ip or arp or rarp) src foo", "net bar" 也即 "(ip or arp or rarp) net bar", "port 53" 也即 "(tcp or udp) port 53" 。
	2.还有一些不遵从以上模式的特殊基元关键字： gateway, broadcast, less, greater 以及计算表达式。
	3.可以通过 and, or, not 来组合复杂的过滤表达式。例如 "host foo and not port ftp and not port ftp-data"。为了简约，可以忽略相同的修饰语，例如，以下两种表达是相同的。
		"tcp dst port ftp or ftp-data or domain"
		"tcp dst port ftp or tcp dst port ftp-data or tcp dst port domain"
	4.允许的基元表达式
		dst host [host]
			如果数据包的IPv4/v6 目标字段域是主机，则匹配成功。 [host] 可以是地址名名称。
		src host [host]
			略
		host [host]
			略
		以上的表达式可以用于关键字 ip, arp, rarp, ip6 中，例如：
			ip host [host]
		ether dst [ehost]
			如果数据包的以太网目标地址是 [ehost]，则匹配成功。[ehost] 可以是一个来自于 /etc/ethers 的名称或是一个数字格式的MAC地址"xx:xx:xx:xx:xx:xx"， "xx.xx.xx.xx.xx.xx", "xx-xx-xx-xx-xx-xx", "xxxx.xxxx.xxxx", "xxxxxxxxxxxx"。
		ether src [ehost]
			略
		ether host [ehost]
			略
		gateway [host]
			如果数据包是使用的主机地址作为网关，则匹配成功。以太网的源地址或目的地址是 [host], 但是 IP 源地址和 IP 目的地址不是 [host].[host] 必须是一个名称，必须既可以被机器的主机名到IP地址映射解析机制(如 DNS, NIS)找到，也可以被机
			器的主机名到以太网地址解析机制(如/etc/ethers)找到。
			一个等价的表达式是
				ether host [ehost] and not host [host]
			不适用于 IPv6。
		dst net [net]
			如果数据包的 IPv4/v6 地址有一个 [net] 的网络号，则匹配成功。[net] 可能是一个来自网络数据库(如/etc/networks)的名称，或者是一个网络号。IPv4可以写成点分四元组(如 192.168.1.0), 点分三元组(如192.168.1), 点分二元组(172.16), 或者单数(如10);
			相对应的掩码是 255.255.255.255（匹配一个主机），255.255.255.0，255.255.0.0，255.0.0.0。
			IPv6必须写全，其掩码为  ff:ff:ff:ff:ff:ff:ff:ff, 因此，IPv6 网络总是匹配主机地址。如果是匹配网络，则需要一个掩码长度。
		src net [net]
			略
		net [net]
			略
		net [net] mask [netmask]
			如果 IPv4 地址匹配由掩码 netmask 指定的网络 net，则匹配成功。可以使用 src 或 dst 进行限定。不对 IPv6 网络有效。
		net [netlen]
			如果 IPv4/v6 地址匹配以 netlen 长度比特位指定的 net 网络，则匹配成功。可以使用 src 或 dst 进行限定。
		dst port [port]
			适用于 ip/tcp, ip/udp, ip6/tcp, ip6/udp，如果数据包目标服务端口为 port，则匹配成功。port 可以是数字或名称(来自于/etc/services)。
		src port [port]
			略
		port [port]
			略
		dst portrange [port1-port2]
			适用于 ip/tcp, ip/udp, ip6/tcp, ip6/udp, 如果数据包的目标服务端口在 port1 和 port2 之间，则匹配成功。
		src portrange [port1-port2]
			略
		portrange [port1-port2]
			略
		less [length]
			如果数据包长度小于等于 length，则匹配成功。
		greater [length]
			如果数据包的长度大于等于 length，则匹配成功。
		ip proto [protocol]
			如果数据包类型是 IPv4 包的协议类型，则匹配成功。protocal 可以是数字或名称，如 icmp, icmp6, igmp, igrp, pim, ah, esp, vrrp, udp, tcp。由于 tcp, udp, icmp 也是关键字，需要用 \ 进行转义。
		ip6 proto [protocol]
			略
		proto [protocol]
			略
		tcp,udp,icmp
			proto p 的缩略
		ether broadcast
			如果是一个以太网广播包，则匹配成功。
		ip broadcast
			如果是一个 IPv4 广播包，则匹配成功。它检查全0和全1广播约定，并在正在进行捕获的接口上查找子网掩码。
			如果正在进行捕获的接口的子网掩码不可用，或者因为正在进行捕获的接口没有网络掩码，或者因为捕获是在Linux的"any"接口上完成的，这可以捕获多个接口，此检查将无法正常工作。
		ether multicast
			如果是以太网多播数据包，则匹配成功。
		ip multicast
			略
		ip6 multicast
			略
		ether proto [protocol]
			如果是以太网类型的数据包，则匹配成功。protocol 可以是数字或名称，如 ip, ip6, arp, rarp, atalk, aarp, decnet, sca, lat, mopdl, moprc, iso, stp, ipx, netbeui。这些标识符也是关键字，需要 \ 转义。
			示例： "fddi proto arp", "tr proto arp", "wlan proto arp"
		...

示例：
	host sundown
		过滤所有到达或离开 sundown 的数据包
	host helios and \(hot or ace \)
		过滤 helios 与 [hot 或 ace] 通信的数据包
	ip host ace and not helios
		过滤所有与 ace 通信的包，但不包括 helios
	gateway snup and (port ftp or ftp-data)
		过滤所有从网关 snup 经过的 ftp 服务端口流量
	ip and not net localnet
		过滤既不是到达也不是离开 localnet 的流量
	tcp[tcpflags] & (tcp-syn|tcp-fin) != 0 and not src and dst net localnet
		过滤每个TCP会话开始会话包和结束会话包（SYN和FIN包），但不包括本地通话。
	tcp port 80 and (((ip[2:2] - ((ip[0]&0xf)<<2)) - ((tcp[12]&0xf0)>>2)) != 0)
		过滤所有来自或去往服务端口 80 的 HTTP 协议数据包，只打印包含用户数据的包。
	gateway snup and ip[2:2] > 576
		过滤通过网关 snup 且长度大于 576 字节的IP数据包。
	ether[0] & 1 = 0 and ip[16] >= 224
		过滤IP广播或多播数据包，但不包括通过以太网发送的数据包。
	icmp[icmptype] != icmp-echo and icmp[icmptype] != icmp-echoreply                			
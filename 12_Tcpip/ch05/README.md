
在访问 Web 站点和发送、接收电子邮件时．我们通常会直接输入 Web 网站的地址或电子邮件地址等那些由应用层提供的地址，而不会使用由十进制数字组成的某个地址。因此，为了能让主机根据实际的 IP 包进行通信，就有必要实现一种功能 —— 将应用中使用的地址映射为 IP 地址。

此外，在数据链路层也不使用 IP 地址，比如在以太网传输中只会使用 MAC 地址传输数据包。而实际上将众多 IP 数据包在网络上进行传送的就是数据链路本身，因此，必须了解发送端 MAC 地址。如果不知道 MAC 地址，那么通信也就无从谈起。

由此可知，在实际通信中，仅凭 IP 远远不够，还需要众多支持 IP 的相关技术才能够实现最终通信。
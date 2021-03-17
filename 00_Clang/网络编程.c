三次握手
发送方 ---  SYN  ---> 接收方
接收方 ---SYN/ACK---> 发送方
发送方 ---  ACK  ---> 接收方
TCP在传输过程中使用序列号和确认号来跟踪数据的接收情况。
TCP重传
TCP提供校验和计算来实现数据在传输过程中的完整性。
TCP负责将接收到的数据包按正确顺序重新排列。

UDP不提供数据包分组、组装，不能对数据包进行排序。

常见TCP端口
21	FTP文件传输服务
23	TELNET终端仿真服务
25	SMTP简单邮件传输服务
53	DNS域名解析服务
80	HTTP超文本传输服务

sockaddr 和 sockaddr_in
数据结构sockaddr用作bind、connect、recvfrom、sendto等函数的参数，用于指明地址信息。
一般编程中并不直接对sockaddr进行操作，而是对sockaddr_in进行操作。
sockaddr_in和sockaddr是并列的数据结构，指向sockaddr_in结构体的指针也可以指向sockaddr的结构体，并代替它。
sockaddr_in结构体中的端口号和IP地址必须使用网络字节序，需要将套接字地址结构赋给函数时候，可以使用强制类型转换将sockaddr_in转换为sockaddr。	
	
服务器主要分为循环服务器和并发服务器。
循环服务器：一次只能处理一个客户端的请求，可用于UDP协议，但很少用于TCP协议。
并发服务器：每个客户端的请求并不由服务器直接处理，而是由服务器创建一个子进程来处理。创建子进程是一种非常消耗资源的操作。

为了解决创建子进程带来的系统资源消耗，提出了多路复用I/O模型。

【TCP套接字】
通信工作的大致流程如下：
	1.服务器先用socket()函数建立一个套接字，用这个套接字完成通信的监听及数据的收发。
	2.服务器用bind()函数绑定一个端口号和IP地址，使套接字与指定的端口号和IP地址相关联。
	3.服务器调用listen()函数，使服务器的这个端口和IP处于监听状态，等待网络中某一客户端的连接请求。
	4.客户端用socket()函数建立一个套接字，设定远程IP和端口。
	5.客户端调用connect()函数连接远程计算机指定的端口。
	6.服务器调用accept()函数接收远程计算机的连接请求，建立起与客户端之间的通信连接。
	7.建立连接以后，客户端用write()函数（或send()函数）向Socket中写入数据。也可以用read()函数（或recv()函数）读取服务器送来的数据。
	8.完成通信以后，使用close()函数关闭Socket连接。
	
TCP用三次握手和滑动窗口机制保证传输的可靠性并进行流量控制。
	
int listen(int sockfd, int backlog);
如果Socket为AF_INET，则参数backlog的最大值可设为128，即最多可以同时接收128个客户端的请求。

服务器处于监听状态时，如果某时刻获得客户端的连接请求，则当时并未立即处理这个请求，而是将这个请求放在等待队列中，当系统空闲时再处理客户端
的连接请求。接收请求的函数是accept()。
	
由于在程序中将IP地址类型设置为"INADDR_ANY"，所以本地计算机既作为服务器，又作为客户端。
	
connect()函数会将本地的Socket连接到serv_addr指定的服务器IP与端口号上。

在网络编程中，当套接字建立连接以后，向这个套接字中写入数据即表示向远程主机发送数据，从套接字中读取数据则相当于接收远程主机发送过来的数据。

在C\S模式中，一个连接由服务器IP、客户端IP、端口号唯一确定，可以调用getsockname()函数获取与某个套接字关联的本地地址，调用getpeername()函数获取与某个套接字
关联的目的地址。
两个网络程序之间的一个网络连接包括5种信息：通信协议、本地协议地址、本地主机端口、远端主机地址和远端协议端口。

使用bind函数时，可以用下面的赋值实现自动获得本机IP地址和随机获取一个没有被占用的端口号：
	my_addr.sin_port = 0;						//系统随机选择一个未被使用的端口号
	my_addr.sin_addr.s_addr = INADDR_ANY;		//填入本机IP地址
	
仅知道域名是不能直接访问一个主机的，需要转换成相应的IP地址。用域名返回IP地址的函数是gethostbyname()。

int shutdown(int sockfd, int how);

当某个套接字绑定一个端口之后，在默认情况下，该端口无法被其他套接字绑定，执行bind()函数返回的错误代码总是报告试图连接的端口已经被别的进程所绑定，这与默认的
套接字选项有关。为了使多个套接字可以同时绑定同一个端口，可以使用setsockopt()函数来配置套接字选项，与之对应，还可以使用getsockopt()函数来获取套接字选项。
通常使用如下语句来允许一个套接字复用端口：
	/* 设定参数数值，1表示开启，0表示关闭 */
	int opt = 1;
	len = sizeof(opt);
	/* 开启套接字端口复用 */
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, &len);
还可以使用setsockopt()函数来设置众多的套接字选项：
	/* 设定参数数值，1表示允许，0表示不允许 */
	int yes = 1;
	len = sizeof(yes);
	/* 允许套接字接收广播数据 */
	setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
	
getpeername()函数可以取得一个已经连接上的套接字的远程信息（如IP地址和端口），让我们知道某个套接字目前连接的是哪个服务器。
当拥有了远程连接用户的IP地址以后，就可以使用inet_ntoa()或gethostbyaddr()来输出信息或是做进一步的处理。

gethostname()函数可以取得本地主机的信息，返回正在执行它的计算机的名字，这个名字可以被gethostbyname()函数使用，由此可以得到本地主机的IP地址。
	
I/O模式
当CPU在执行代码（当前活动线程）的过程中遇到一个I/O请求（如调用read()/write()或recv()/send()）时，系统将产生一个中断，当前活动线程阻塞在此，让CPU去完成这个
I/O请求，等到完成后，系统再次产生一个中断使原先的程序继续运行。这就是所谓的同步I/O。如果要反复读/写大文件，同步I/O的效率是很低的。 

当CPU执行代码遇到一个I/O请求时，使用一个线程去处理I/O请求，并且当前调用线程并不挂起。如果后续代码和这个I/O有关（如需要等待I/O操作的结果），它就要等到这个
I/O操作完成。但如果后续代码和这个I/O操作无关，就可以以更快的速度执行下去，而无须等待I/O请求的完成，这就是异步I/O。

为了提高系统性能及程序的并发性，经常要用到异步I/O模式。在Linux网络编程中，select函数、poll函数和epoll函数常被用来实现异步I/O模式。

connect、accept、recv或recvfrom都是阻塞函数，select是一个非阻塞函数。
所谓非阻塞函数，就是进程或线程执行此函数时，不必非要等待事件的发生，一旦执行肯定返回，以返回值的不同来反映函数的执行情况，如果事件发生则与阻塞方式相同，若
事件没有发生则返回一个回码来告知事件未发生，让进程或线程继续执行，所以效率很高。

int select(int maxfdp, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval * timeout);
timeout是select的超时时间，它可以使select处于如下3种状态：
	1）形参以NULL传入，就是将select置于阻塞状态，一定要等到监视文件描述符集合中某个文件描述符发生变化为止；
	2）设为零秒零毫秒，就变成了一个纯粹的非阻塞函数，执行后立刻返回。文件无变化返回零，有变化则返回一个正值；
	3）timeout值大于零，这就是等待的超时时间，即select在timeout内阻塞，超时间内有事件到来立即返回，否则超时一过一定返回，返回值同上。
	
网络字节序使用的是大端模式。
在TCP/IP网络中，用到的IP是以"."隔开的的十进制的数（如192.168.1.1），而在套接字的数据结构中用的则是32位的网络字节序的二进制数值。
	
#include <netdb.h>
struct hostent *gethostbyname(const char *hostname);
struct hostent *gethostbyaddr(const char *addr, size_t len, int family);
gethostbyname()函数实现域名或主机名到IP地址的转换，参数hostname指向存放域名或主机名的字符串。
gethostbyaddr()函数实现IP地址到域名或主机名的转换。通常，参数addr指向含有IP地址的字符串，参数len是此字符串的大小，参数family为协议族。

struct hostent
{
	char *h_name;		/*主机的正式名称*/
	char **h_aliases;	/*主机的别名*/
	int h_addrtype;		/*主机的地址类型，IPv4为AF_INET*/
	int h_length;		/*地址长度，对于IPv4是4字节，即32位*/
	char **h_addr_list;	/*主机的IP地址列表 整数表示*/
};
#define h_addr h_addr_list[0]	/*主机的第一个IP地址*/
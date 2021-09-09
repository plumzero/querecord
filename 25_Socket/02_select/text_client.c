#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <netinet/tcp.h>

#define BUF_SIZE 500

#define USAGE   \
    "\n  ./* <host> <port or service> <input filename>\n" \
    "\n"
/**
 * 修改： 
 *	1. 增加了 connect 调用对捕获的中断信号的处理
 *	2. 大小端模式判断简化
 *  3. 增加了休眠机制。原因：服务端进程从socket读数据的速度跟不上客户端进程向socket写数据的速度，最终导致客户端 write 调用阻塞，造成"粘包"现象。(但不确定是否真的是粘包)
 *		参考：https://www.cnblogs.com/junneyang/p/6126635.html
 *			  浅谈TCP/IP网络编程中socket的行为
 *  4. 客户端套接字为阻塞套接字，阻塞写是只有在缓冲区足以放下整个buffer时才返回（与阻塞读并不相同）。而非阻塞写则是返回能够放下的字节数，之后调用则返回 -1(errno = EAGAIN 或 EWOULDBLOCK)
 * 适用情况 && 功能：
 *	1. 只在 linux 下运行
 *	2. 从文本文件中行读取内容，并以一行一行地发送给服务器
 * 注意：
 *	1. 理论上，是不需要发送行文本字符串长度的，但考虑到服务端接收的准确性，还是加了。另外，这也有利于后续的二进制文件扩展
 *	2. cleanup 节中 ret 打印出的判断未必准确
 */
 
void go_sleep(long ms)
{
	struct timeval timeout;
	timeout.tv_sec = ms / 1000L;
	ms = ms % 1000L;
	timeout.tv_usec = (int)ms * 1000;
	select(0, NULL,  NULL, NULL, &timeout);
}

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
	int fd, i, flag, ret = 0;
	uint16_t slen;
    ssize_t nw;
    unsigned char sbuf[BUF_SIZE] = { 0 };
	FILE *f;
	// 大小端模式判断
	unsigned LE = 1;
	unsigned isLittleEndian = *((char*)&LE);
	// 参数校验
    if (argc < 4) 
	{
        printf(USAGE);
        exit(-1);
    }
	// 设定规则
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;				// IPv4 或 IPv6
    hints.ai_socktype = SOCK_STREAM;			// 流数据报
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_TCP;			// TCP协议
	// 获取指定地址上的 addrinfo 结构体
	if ((ret = getaddrinfo(argv[1], argv[2], &hints, &result)) != 0)
	{
		fprintf(stderr, "%d ecode(%08X): %s\n", __LINE__, ret, gai_strerror(ret));
		goto cleanup;
	}
	// 尝试 result 中的每个地址，直到可以 connect
	ret = -1;
    for (rp = result; rp != NULL; rp = rp->ai_next) 
	{
        if ((fd = (int)socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1)
			continue;
		// 设置 close-on-exec 标志位
		if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1) {
			close(fd);
			continue;
		}
		// 对捕获的中断信号的处理
		while (connect(fd, rp->ai_addr, rp->ai_addrlen) == -1 && errno != EISCONN)
		{
			if (errno != EINTR)
			{
				fprintf(stderr, "%d ecode(%08X): %s\n", __LINE__, errno, strerror(errno));
				close(fd);
				continue;
			}
		}
		// 禁用 Nagle 算法
		flag = 1;
		if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void*)&flag, sizeof(flag)) != 0)
		{
			fprintf(stderr, "%d ecode(%08X): %s\n", __LINE__, errno, strerror(errno));
			close(fd);
			continue;
		}
		ret = 0;
        break;
    }
	if (ret)
	{
		fprintf(stderr, "%d ecode(%08X): %s\n", __LINE__, errno, strerror(errno));
		goto cleanup;
	}
	// 打开文本读取内容
	if ((f = fopen(argv[3], "r")) == NULL)
	{
		perror("fopen");
		goto cleanup;
	}
	// 行读取直到 eof
	while((fscanf(f, "%[^\n]", sbuf + 2)) != EOF)
	{
		fgetc(f);
		slen = (uint16_t)strlen(sbuf + 2);
		if (isLittleEndian)
		{
			for (i = 0; i < 2; i++)
				sbuf[i] = (unsigned char)(((uint16_t)slen >> ((2 - i - 1) << 3)) & 0xFF);
		}
		else
		{
			for (i = 0; i < 2; i++)
				sbuf[i] = (unsigned char)(((uint16_t)slen >> (i << 3)) & 0xFF);
		}
		if ((nw = write(fd, sbuf, slen + 2)) != slen + 2)
		{
			fprintf(stderr, "%d ecode(%08X): %s\n", __LINE__, errno, strerror(errno));
			goto cleanup;
		}
		printf("SEND (%2d bytes): %s\n", slen, sbuf + 2);
		memset(sbuf, 0, BUF_SIZE);
		// 必须加上休眠，否则"粘包"
		go_sleep(10);
	}
	// 读取完毕，再发送一个 eof (0x04) 告知服务端发送完毕
	memset(sbuf, 0, BUF_SIZE);
	slen = 1;
	if (isLittleEndian)
	{
		for (i = 0; i < 2; i++)
			sbuf[i] = (unsigned char)(((uint16_t)slen >> ((2 - i - 1) << 3)) & 0xFF);
	}
	else
	{
		for (i = 0; i < 2; i++)
			sbuf[i] = (unsigned char)(((uint16_t)slen >> (i << 3)) & 0xFF);
	}
	sbuf[2] = 0x04;
	if ((nw = write(fd, sbuf, 3)) != 3)
	{
		fprintf(stderr, "%d ecode(%08X): %s\n", __LINE__, errno, strerror(errno));
		goto cleanup;
	}
	else
	{
		printf("Transmission over.\n");
	}
	
cleanup:
	printf("ret (%08x)\n", ret);
	// 释放
	if (result)
		freeaddrinfo(result);
	close(fd);
	fclose(f);
	return ret;
}
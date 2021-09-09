
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "abc.h"

struct TestHeader
{
	uint16_t 	ver;
	uint16_t	psize;				/** payload size */
	uint8_t 	crc32[4];
	uint32_t	pholder;			/** placeholder */
	
	TestHeader() :ver(0), psize(0), pholder(0) {}
} __attribute__ ((packed));

#define HBUFSIZE		sizeof(TestHeader)
#define DBUFSIZE		1024

#define TOTAL           100000

static const unsigned char crc32[4] = { 0x1f, 0x3d, 0x7e, 0xac };

int main(int argc, char *argv[])
{
	int ret = -1;
	int sfd, cfd;
	struct sockaddr_in ssai;
	struct sockaddr_in csai;
	socklen_t len;
	int on = 1;
	char hbuf[HBUFSIZE];
	char dbuf[DBUFSIZE];
	ssize_t nbytes;
	
	if (argc != 3) {
		printf("Usage: %s <ip> <port>\n", argv[0]);
		return -1;
	}
		
	sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sfd == -1) {
		printf("socket failed\n");
		return -1;
	}
	
	on = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on)) != 0) {
		printf("setsockopt(SO_REUSEADDR) failed\n");
		close(sfd);
		return -1;
	}
	
	memset(&ssai, 0, sizeof(ssai));
	
	ssai.sin_addr.s_addr = inet_addr(argv[1]);
	ssai.sin_port = htons(atoi(argv[2]));
	ssai.sin_family = AF_INET;

	if (bind(sfd, (struct sockaddr*)&ssai, sizeof(struct sockaddr_in)) != 0 ) {
		printf("bind failed\n");
		close(sfd);
		return -1;
	}
	
	if (listen(sfd, 5) == -1) {
		printf("listen failed\n");
		close(sfd);
		return -1;
	}
	if (fcntl(sfd, F_SETFL, fcntl(sfd, F_GETFL) | O_NONBLOCK) == -1) {
		printf("fcntl(F_SETFL, O_NONBLOCK)\n");
		close(sfd);
		return -1;
	}

	while (1) {
		len = sizeof(struct sockaddr_in);
		cfd = accept(sfd, (struct sockaddr *)&csai, &len);
		if (cfd == -1) {
			if (errno == EINTR || errno == ECONNABORTED || errno == EAGAIN)
				continue;
			else {
				printf("accept failed: %s\n", strerror(errno));
				close(sfd);
				return -1;
			}
		} else {
			printf("accept a connection success\n");
			break;
		}
	}
	
	int count = 0;
	time_t btime = time(NULL);
	
	
	for ( ; ; )
	{	
		/// 窥-读
		nbytes = recv(cfd, hbuf, sizeof(hbuf), MSG_PEEK);
		if (nbytes == 0)
			continue;
		if (nbytes != HBUFSIZE) {
			printf("recv(MSG_PEEK) failed, %d bytes\n", nbytes);
			continue;
		}
		/// parse header
		TestHeader th;
		memcpy(&th, hbuf, HBUFSIZE);
		
		// DBUG("version=%d, psize=%d, crc32=[%02X %02X %02X %02X], pholder=%d", 
				// th.ver, ntohs(th.psize), th.crc32[0], th.crc32[1], th.crc32[2], th.crc32[3], th.pholder);
		
		int psize = ntohs(th.psize);
		nbytes = recv(cfd, dbuf, HBUFSIZE + psize, 0);
		if (nbytes != HBUFSIZE + psize) {
			printf("recv failed\n");
			continue;
		}
		++count;
		// DBUG("(%d)recv %d payload bytes: %s", count, psize, dbuf + HBUFSIZE);
		if (count == TOTAL) {
			time_t etime = time(NULL);
			DBUG("cost time %d seconds\n", etime - btime);
		}
	}
	
	if (sfd > 0) close(sfd); 
	if (cfd > 0) close(cfd);
	
	return 0;
}

/**
	代替 for ( ; ; ) { ... } 中内容进行 读-读 测试
		/// 读-读
		nbytes = recv(cfd, hbuf, sizeof(hbuf), 0);
		if (nbytes == 0)
			continue;
		if (nbytes != HBUFSIZE) {
			printf("recv failed, %d bytes\n", nbytes);
			continue;
		}
		/// parse header
		TestHeader th;
		memcpy(&th, hbuf, HBUFSIZE);
		
		// DBUG("version=%d, psize=%d, crc32=[%02X %02X %02X %02X], pholder=%d", 
				// th.ver, ntohs(th.psize), th.crc32[0], th.crc32[1], th.crc32[2], th.crc32[3], th.pholder);
		
		int psize = ntohs(th.psize);
		nbytes = recv(cfd, dbuf, psize, 0);
		if (nbytes != psize) {
			printf("recv failed\n");
			continue;
		}
		++count;
		DBUG("(%d)recv %d payload bytes: %s", count, psize, dbuf);
		if (count == TOTAL) {
			time_t etime = time(NULL);
			DBUG("cost time %d seconds\n", etime - btime);
		}
 */


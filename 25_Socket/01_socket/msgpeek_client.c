
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>	//for sockaddr_in
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
	int cfd;
	struct sockaddr_in ssai, csai;
	socklen_t len;
	char ip[32] = { 0 };
	char hbuf[HBUFSIZE];
	char dbuf[DBUFSIZE];
	ssize_t nbytes, ncheck;
	
	if (argc != 3) {
		printf("Usage: %s <ip> <port>\n", argv[0]);
		return -1;
	}
	
	strcpy(ip, argv[1]);
	
	cfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (cfd == -1) {
		printf("socket failed\n");
		return -1;
	}

	memset(&ssai, 0, sizeof(ssai));
	ssai.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, ip, &ssai.sin_addr);
	ssai.sin_family = AF_INET;
	
	if (connect(cfd, (const struct sockaddr*)&ssai, sizeof(struct sockaddr_in)) == -1) {
		printf("connect failed\n");
		close(cfd);
		return -1;
	}
	
	len = sizeof(struct sockaddr_in);
	ret = getsockname(cfd, (struct sockaddr *)&csai, &len);
	if (ret != 0) {
		printf("getsockname failed\n");
		close(cfd);
		return -1;
	}
	printf("clinet(%s:%d)\n", inet_ntoa(csai.sin_addr), ntohs(csai.sin_port));
	
	int circle = TOTAL;
	int count = 0;
	time_t btime = time(NULL);
	
	for ( ; circle--; )
	{
		memset(dbuf, 0, sizeof(dbuf));
		
		char tbuf[1024];
		int n = snprintf(tbuf, 1024, "========== hello world from client %d ==========", circle);
		if (n < 0 || n >= 1024) {
			printf("snprintf failed\n");
			continue;
		}
		/** fill header */
		TestHeader th;
		th.ver = 1022;
		th.psize = htons(n);
		memcpy(th.crc32, crc32, 4);
		th.pholder = 0;
		memcpy(dbuf, &th, sizeof(th));
		memcpy(dbuf + sizeof(th), tbuf, n);
		
		// DBUG("version=%d, psize=%d, crc32=[%02X %02X %02X %02X], pholder=%d", th.ver, ntohs(th.psize), 
				// (int)th.crc32[0], (int)th.crc32[1], (int)th.crc32[2], (int)th.crc32[3], th.pholder);
		
		nbytes = send(cfd, dbuf, n + sizeof(th), 0);
		if (nbytes != n + sizeof(th)) {
			printf("send error\n");
			continue;
		}
		++count;
		// DBUG("(%d)send %d bytes: %s", count, n + sizeof(th), tbuf);
		if (count == TOTAL) {
			time_t etime = time(NULL);
			DBUG("cost time %d seconds\n", etime - btime);
		}
	}
	
cleanup:
	if (cfd > 0) close(cfd);
	
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define PERRO_FLUSH_FD  stderr
#define CERRO_FLUSH_FD  stderr
#define ERRO_FLUSH_FD   stderr
#define PINFO_FLUSH_FD  stdout
#define CINFO_FLUSH_FD  stdout
#define INFO_FLUSH_FD   stdout

#define ECHO_LOG(type, format, ...)           \
    do {                                      \
        fprintf(type, format, __VA_ARGS__);   \
    } while (0)

#define ECHO(type, format, ...)                                       \
    do {                                                              \
        ECHO_LOG(type ## _FLUSH_FD, "%s %3d " format "\n",            \
                        "[" #type "]", __LINE__, ##__VA_ARGS__);      \
    } while (0)

#define BUFSIZE 1024
#define CHILD_PROCESS_NUM 3

int fd[2];
int child_ps_id[CHILD_PROCESS_NUM];

/**
 * select 注意:
 * 1. 一个描述符可以加入到多个描述符集中进行监控，但一次只能触发一种动作，使
 *    用 select 对一个描述符的多个动作(读、写、异常)进行监控，易造成混乱，此
 *    时更建议使用 poll 或 epoll ；
 * 2. 每次 select 调用有动作事件触发(返回值大于 0)时，该动作事件对应描述符会
 *    根据动作类型加入到相应的描述符集中，也就是说会原描述符集会被覆盖，务必
 *    对原描述符集进行备份；
 * 3. 对多个描述符进行监控时，可以循环检查所有描述符，依次判断(通过 FD_ISSET)
 *    每个描述符是否在描述符集中，根据动作类型作出相应处理；
 * 4. select 超时参数设置不为空时，如果超时后返回为 0， 此时 errno 为 0 ，表示
 *    没有错误。此时所有受监控描述符均处于无动作状态；
 * 5. select 应用于管道时，最好超时参数设置为空，即阻塞等待；
 * 6. select 对多个描述符的监控并不太友好；
 * 7. select 功能不强，但比 poll epoll 要更复杂一些；
 *
 * 测试程序说明:
 * 1. 父进程与多个子进程间的管道通信，使用 select 进行轮询；
 * 2. 父进程进行写操作，子进程进行读操作；
 *
 * 注意:
 * 1. 子进程退出时，因为父进程处于无限轮询状态，故其无法调用 waitpid 对退出的子
 *    进程进行处理(如关闭管道读端的一个引用计数)；
 * 2. 子进程的退出务必使用 exit ，使用 return 会退栈到父进程代码，造成混乱；
 * 3. 关闭子进程描述符时，父进程中并未触发异常描述符集，可不必监控；
 * 4. 
 *
 * 未解决问题
 * 1. 子进程退出，父进程不退出时，子进程会变成僵尸进程存在，在父进程中调用 kill 
 *    或 waitpid 也没办法解决，只有在父进程也退出时，僵尸进程才会销毁；
 */

void signal_handler(int signum)
{
	ECHO(INFO, "process(pid=%d) received signal %d", getpid(), signum);
	signal(SIGINT, SIG_DFL);
}

int main_process()
{
	ECHO(PINFO, "P(%d): start ...", getpid());
	int ret, i, j, max_fd, rt;
	fd_set rfds, rfds_bak;
	char rbuf[BUFSIZE], wbuf[BUFSIZE];
	ssize_t rn;
	struct stat sb;
	
	close(fd[1]);
	FD_ZERO(&rfds);
	FD_SET(fd[0], &rfds);
	rfds_bak = rfds;
	
	max_fd = fd[0] + 1;
	
	for ( ; ; ) {
		rfds = rfds_bak;
		ret = select(max_fd, &rfds, NULL, NULL, NULL);
		if (ret == -1) {
			ECHO(PERRO, "P(%d): select failed: %s", getpid(), strerror(errno));
			sleep(5);
		} else if (ret == 0) {
			ECHO(PINFO, "P(%d): select would block", getpid());
			sleep(5);
		} else {
			for (i = 0; i < max_fd; i++) {
				if (FD_ISSET(fd[i], &rfds)) {
					memset(rbuf, 0, BUFSIZE);
					rn = read(fd[i], rbuf, BUFSIZE);
					if (rn < -1) {
						ECHO(PERRO, "P(%d): read fd(%d) failed: %s", getpid(), fd[i], strerror(errno));
					} else if (rn == 0) {
						ECHO(PINFO, "P(%d): fd(%d) peer pipe may be closed", getpid(), fd[i]);
						FD_CLR(fd[i], &rfds_bak);
						close(fd[i]);
					} else {
						ECHO(PINFO, "P(%d): recv(%d bytes): %s", getpid(), rn, rbuf);
					}
				}
			}
		}
	}
	
	return 0;
}

int child_process()
{
	ECHO(CINFO, "C(%d): start ...", getpid());
	
	char buf[BUFSIZE] = { 0 };
	int ret, i, count = 0;
	ssize_t wn = 0;
	time_t t;
	
	close(fd[0]);
	
	for ( ; ; ) {
		memset(buf, 0, BUFSIZE);
		time(&t);
		ret = snprintf(buf, BUFSIZE, "process %d send this at time %s", getpid(), ctime(&t));
		if (ret < -1 || ret >= BUFSIZE) {
			continue;
		}
		
		wn = write(fd[1], buf, ret);
		if (wn < -1) {			/** 套接字出错，再循环已无意义，返回 */
			ECHO(CERRO, "C(%d): write fd(%d) failed: %s", getpid(), fd[1], strerror(errno));
			return -1;
		} else if (wn == 0) {	/** 无字可写 */
			ECHO(CINFO, "C(%d): fd(%d) write over.", getpid(), fd[1]);
		} else {				/** 成功写入 */
			ECHO(CINFO, "C(%d): send(%d bytes): %s", getpid(), wn, buf);
		}
		/** 假如退出 */
		if (count == 5) {
			break;
		}
		
		count++;
		sleep(1);
	}
	/** 假如退出 */
	close(fd[1]);
	/**  */
	sleep(1);
	
	exit(0);
}

int main()
{	
	ECHO(INFO, "begin test");
	
	signal(SIGINT, signal_handler);
	
	int ret, on;
	size_t i, total;
	pid_t p;
	
	if (pipe(fd) < 0) {
		ECHO(PERRO, "pipe failed: %s", strerror(errno));
		return -1;
	}
		
	total = sizeof(fd) / sizeof(fd[0]);
	
	on = 1;
	for (i = 0; i < total; i++) {
		if (ioctl(fd[i], FIONBIO, &on) == -1) {
			ECHO(CERRO, "ioctl(FIONBIO, on) failed: %s", strerror(errno));
			return -1;
		}
		if (fcntl(fd[i], F_SETFD, FD_CLOEXEC) == -1) {
			ECHO(CERRO, "fcntl(F_SETFD, FD_CLOEXEC) failed: %s", strerror(errno));
			return -1;
		}
	}
	/** 开多个进程 */
	for (i = 0; i < CHILD_PROCESS_NUM; i++) {
		p = fork();
		if (p > 0) {
			child_ps_id[i] = p;
		} else if (p == 0) {
			child_process();
		} else if (p < 0) {
			ECHO(PERRO, "fork failed: %s", strerror(errno));
			return -1;
		}
	}
	
	/** 为防在循环困死，主进程的处理程序放在最后开启 */
	main_process();
	
	return 0;
}
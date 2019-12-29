
#include <stdio.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include <signal.h>
/**
  ANSI C 信号处理句柄
    typedef void (*sighandler_t)(int);
    sighandler_t signal(int signum, sighandler_t handler);
  描述:
    该句柄行为会因 UNIX 版本不同而异，Linux 也是。可以通过 sigaction 进行替代来避免这种差异。
    如果信号 signum 传入进程，会触发下列情形的一种:
       1. 如果配置设置为 SIG_IGN，则该信号被忽略；
       2. 如果配置设置为 SIG_DFL，执行该信号对应的缺省动作；
       3. 如果配置设置有信号处理句柄，则调用参数为 signum 的信号处理句柄
    SIGKILL 和 SIGSTOP 信号不能被抓取、阻塞或忽略。
  返回值:
    失败时返回 SIG_ERR
 */

void signal_handler(int signum)
{
	switch (signum) {
		case SIGINT:
		case SIGTERM:
		{
			printf("\nSignal %d received, preparing to exit...\n", signum);
			// 具体处理 ...
			signal(signum, SIG_DFL);
			kill(getpid(), signum);
			break;
		}
		case SIGTSTP:
		{
			printf("\nSignal %d received, preparing to hangle the process...\n", signum);
			signal(signum, SIG_DFL);
			break;
		}
		default:
		{
			printf("Could not process this signal\n");
			break;
		}
	}
}
 
int main() {
	// 注册信号处理句柄
	if (SIG_ERR == signal(SIGINT, signal_handler)) {
		return -1;
	}
	if (SIG_ERR == signal(SIGTERM, signal_handler)) {
		return -1;
	}
	if (SIG_ERR == signal(SIGTSTP, signal_handler)) {
		return -1;
	}
	
	int i;
	for (i = 0; i < 1000; i++) {
		printf("%d \n", i);
		sleep(1);
	}
	
	return 0;
}

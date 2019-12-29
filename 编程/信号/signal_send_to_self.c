
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

static void signal_handler(int sig_num)
{
	printf("received signal %d\n", sig_num);
	signal(sig_num, signal_handler);
}

void sleep_for_ms(int timeout_ms)
{
	struct timeval tv;
	
	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;
	select(0, NULL, NULL, NULL, &tv);
}

int main()
{
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGKILL, signal_handler);		// SIGKILL 信号无法被捕获
	
	printf("getpid = %d, getppid = %d\n", (int)getpid(), (int)getppid());
	
	int count = 0;
	struct timeval tv;
	int timeout_ms = 1000;

	while (1) {
		if (count == 5) {
			printf("will send SIGTERM(%d) signal to current process in %d seconds\n", SIGTERM, 2);
			sleep_for_ms(2000);
			if (kill(getpid(), SIGTERM) != 0) {
				printf("send SIGTERM failed(reason: %s)\n", strerror(errno));
			} else {
				printf("send SIGTERM signal success\n");
			}
		}
		
		if (count == 10) {
			printf("will send SIGINT(%d) signal to current process in %d seconds\n", SIGINT, 2);
			sleep_for_ms(2000);
			if (kill(getpid(), SIGINT) != 0) {
				printf("send SIGINT failed(reason: %s)\n", strerror(errno));
			} else {
				printf("send SIGINT signal success\n");
			}
		}

		if (count == 15) {
			printf("will send SIGKILL(%d) signal to current process in %d seconds\n", SIGKILL, 2);
			sleep_for_ms(2000);
			if (kill(getpid(), SIGKILL) != 0) {
				printf("send SIGKILL failed(reason: %s)\n", strerror(errno));
			}
		}
		count++;
		
		printf(".\n");
		sleep_for_ms(1000);
	}
		
	return 0;
}
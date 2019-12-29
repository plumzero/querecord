
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

/**
 * 场景: 在 A 线程中阻塞某信号，但 B 线程不阻塞该信号；
 * 1. 主线程阻塞所有信号 ，从线程不对 SIGINT 信号阻塞；
 * 2. 主线程打开从线程后，将信号集设置为系统默认集；
 */

void *slave_thread(void *arg)
{
	printf("从线程: 开始运行...\n");
	
	int ret, i;
	sigset_t set;
	
	sigfillset(&set);
	sigdelset(&set, SIGINT);
	ret = pthread_sigmask(SIG_BLOCK, &set, NULL);
	if (ret == 0) {
		printf("从线程: 不阻塞 SIGINT 信号!\n");
	}
		
	for (i = 0; i < 10; i++) {
		printf("从线程: 将调用打印 10 次(这是第 %d 次)\n", i + 1);
		sleep(1);
	}
}

int main()
{
	signal(SIGINT, SIG_IGN);
	
    sigset_t new_set, old_set;
	pthread_t pid;
	int ret, i;
		
    sigfillset(&new_set);
	sigdelset(&new_set, SIGINT);
	/** 注意，这里方式参数必须设置为 SIG_SETMASK */
    ret = pthread_sigmask(SIG_BLOCK, &new_set, &old_set); /* block signals */
	if (ret == 0) {
		printf("主线程: 阻塞所有信号!\n");
	}

    ret = pthread_create(&pid, NULL, slave_thread, NULL);
	if (ret == 0) {
		printf("主线程: 创建从线程成功!\n");
	}
	
    ret = pthread_sigmask(SIG_SETMASK, &old_set, NULL); /* unblock signals */
	if (ret == 0) {
		printf("主线程: 设置回系统默认信号集.\n");
	}

	for (i = 0; i < 10; i++) {
		printf("主线程: 将调用打印 10 次(这是第 %d 次)\n", i + 1);
		sleep(1);
	}

	return 0;
}
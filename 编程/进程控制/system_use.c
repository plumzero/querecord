#include <stdlib.h>
#include <stdio.h>

/**
 * system 会开一个子进程进行 shell 调用，shell 调用执行完毕后会返回原进程。
 * exec 也会开一个子进程进行调用，但并不会返回原进程。
 */

int main()
{
	int status;
	
	if ((status = system(NULL)) < 0) {
		printf("system error!\n");
		exit(0);
	}
	printf("exit status=%d\n", status);
	
	if ((status = system("date")) < 0) {
		printf("system error!\n");
		exit(0);
	}
	printf("exit status=%d\n", status);
	
	if ((status = system("invalidcommand")) < 0) {
		printf("system error!\n");
		exit(0);
	}
	printf("exit status=%d\n", status);
	
	if ((status = system("who;exit 44")) < 0) {
		printf("system error!\n");
		exit(0);
	}
	printf("exit status=%d\n", status);
	
	return 0;
}

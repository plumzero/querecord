#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/**
 * waitpid 的用法
 */

int main(void)
{
	pid_t pChild, pWait;
	time_t timer;
	struct tm *tblock;
	if ((pChild = fork()) == -1)
	{
		printf("failed to create a new process\n");
		exit(1);
	} else if (pChild == 0) {
		printf("child process: PID=%d\n", getpid());
		sleep(10);
		exit(0);
	} else {
		printf("pareant process: PID=%d\n", getpid());
		do{
			int status;
			pWait = waitpid(pChild, &status, WNOHANG);		// 获取返回的子进程的 id
			if (pWait == 0) {
				sleep(1);
				timer = time(NULL);
				tblock = localtime(&timer);
				printf("No child process exited! Local time :%s", asctime(tblock));
			}
		} while(pWait == 0);
		if (pWait == pChild) {
			printf("Successfully get child %d\n", pWait);
		} else {
			printf("some error occured\n");
		}
	}

	return 0;
}

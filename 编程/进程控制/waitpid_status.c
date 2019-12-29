#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		exit(1);
	}
	if (pid == 0) {
		int i;
		for (i = 3; i > 0; i--) {
			printf("this is the child\n");
			sleep(1);
		}
		exit(3);
	} else {
		int stat_val;
		waitpid(pid, &stat_val, 0);
		if (WIFEXITED(stat_val))				// 子进程正常终止， WIFEXITED 取出的字段值非零
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));				// 打印退出状态
		else if (WIFSIGNALED(stat_val))  		// 子进程异常终止， WIFSIGNALED 取出的字段值非零
			printf("Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));		// 打印信号编号
	}
	
	return 0;
}
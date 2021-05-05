#include <unistd.h>
#include <stdio.h>

/**
 * exec 族函数的用法
 */

int main(void)
{
	char *envp[] = {"PATH=/home", "USER=lb", "STATUS=testing", NULL};
	char *argv_execv[] = {"echo", "excuted by execv", NULL};
	char *argv_execvp[] = {"echo", "excuted by execvp", NULL};
	char *argv_execve[] = {"env", NULL};
	int ret = 0;
	
	if (fork() == 0) {
		if ((ret = execl("/bin/echo", "echo", "executed by execl", NULL)) == -1)
			perror("Error on execl");
	}
	if (fork() == 0) {
		if ((ret = execlp("echo", "echo", "executed by execlp", NULL)) == -1)
			perror("Error on execlp");
	}
	if (fork() == 0) {
		if ((ret = execle("/usr/bin/env", "env", NULL, envp)) == -1)
			perror("Error on execlp");
	}
	if (fork() == 0) {
		if ((ret = execv("/bin/echo", argv_execv)) == -1)
			perror("Error on execv");
	}
	if (fork() == 0) {
		if ((ret = execvp("echo", argv_execvp)) == -1)
			perror("Error on execvp");
	}
	if (fork() == 0){
		if ((ret = execve("/usr/bin/env", argv_execve, envp)) == -1)
			perror("Error on execvp");
	}
	return 0;
}

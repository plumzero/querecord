#include <stdlib.h>
#include <stdio.h>

/**
 * system �Ὺһ���ӽ��̽��� shell ���ã�shell ����ִ����Ϻ�᷵��ԭ���̡�
 * exec Ҳ�Ὺһ���ӽ��̽��е��ã��������᷵��ԭ���̡�
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

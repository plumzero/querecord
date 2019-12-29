

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>

/**
 * getcwd    获取当前路径
 * access    访问某个文件
 * mkdir     创建某个目录
 * rmdir     删除某个空目录
 */

int main(int argc, char *argv[])
{
	char *path;
	char cwd[PATH_MAX] = { 0 };
	char dir[PATH_MAX] = { 0 };
	int ret;
	
	if (argc < 2) {
		fprintf(stderr, "USAGE: ./%s <directory name>\n", argv[0]);
		return -1;
	}
	
	path = getcwd(cwd, PATH_MAX);
	if (!path) {
		fprintf(stderr, "Cannot get current working directory\n");
		return -1;
	}
	ret = snprintf(dir, sizeof(dir), "%s/%s", path, argv[1]);
	if (ret < 0 || ret == sizeof(dir)) {
		fprintf(stderr, "Could not format directory path: %s\n", dir);
		return -1;
	}
	
	if (0 == access(dir, F_OK)) {
		if (0 != rmdir(dir)) {
			fprintf(stderr, "Could not rmdir old directory: %s\n", dir);
			return -1;
		}
	}
	
	ret = mkdir(dir, 0700);
	if (ret < 0 && errno != EEXIST) {
		fprintf(stderr, "Could not make directory: %s\n", dir);
		return -1;
	}
	
	return 0;
}
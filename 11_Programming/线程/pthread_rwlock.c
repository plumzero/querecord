
/**
 * int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, 
 *                         const pthread_rwlockattr_t *restrict attr); 
 *  1. 作用: 初始化读写锁 rwlock ，attr 是 NULL 时使用缺省属性，此时状态为未
 *     锁定态；
 *  2. 初始化后，读写锁可以一直被使用；
 *  3. 对已初始化的读写锁再进行初始化，其后果是未定义的；
 *  4. 直接使用未初始化的读写锁，其后果是未定义的；
 *
 * int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
 *  1. 作用: 释放读写锁 rwlock；
 *  2. 调用此函数后，rwlock 会被设置为无效值，由此（对其他拥有该锁的线程）造
 *     成的后果是未定义的；
 *  3. 试图销毁一个未初始化的读写锁的结果也是未定义的；
 *
 * 读写锁好像不适合多线程时日志的写入，因为日志很少有读出的，使用普通锁即可。
 * 读写锁适合于对数据结构读的次数远大于写的情况。 
 *
 * pthread_rwlock_init 和 pthread_rwlock_destroy 函数调用失败的可能原因及处理
 * 方法，可以参考:
 *  https://linux.die.net/man/3/pthread_rwlock_init  Errors
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_NUM  4

volatile int shared = 0;
pthread_rwlock_t rwlock;

void *transaction_write(void *arg)
{
	while (1) {
		if (shared < 20) {
			pthread_rwlock_wrlock(&rwlock);
			shared++;
			printf("w thread %d write shared variable: %d\n", *(int*)arg, shared);
			pthread_rwlock_unlock(&rwlock);
			sleep(1);
		}
	}
	
	return NULL;
}

void *transaction_read(void *arg)
{
	while (1) {
		pthread_rwlock_rdlock(&rwlock);
		printf("r thread %d read shared variable: %d\n", *(int*)arg, shared);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
	
	return NULL;
}

int main(int argc, char *argv[])
{
	int ret = -1;
	pthread_t pid_w[THREAD_NUM] = { 0 };
	pthread_t pid_r[THREAD_NUM] = { 0 };
	int index_w[THREAD_NUM] = { 0 };
	int index_r[THREAD_NUM] = { 0 };
	int i;
	
	ret = pthread_rwlock_init(&rwlock, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_rwlock_init failed: %s\n", strerror(ret));
	}
	
	for (i = 0; i < THREAD_NUM; i++) {
		index_w[i] = i;
		ret = pthread_create(&pid_w[i], NULL, transaction_write, &index_w[i]);
		if (ret != 0) {
			fprintf(stderr, "pthread_create failed: index=%d\n", i);
			continue;
		}
	}
	
	for (i = 0; i < THREAD_NUM; i++) {
		index_r[i] = i;
		ret = pthread_create(&pid_r[i], NULL, transaction_read, &index_r[i]);
		if (ret != 0) {
			fprintf(stderr, "pthread_create failed: index=%d\n", i);
			continue;
		}
	}
	
	while (1) {
		if (shared == 20) {
			printf("main thread: shared = %d\n", shared);
			for (i = 0; i < THREAD_NUM; i++) {
				pthread_cancel(pid_w[i]);
			}
			for (i = 0; i < THREAD_NUM; i++) {
				pthread_cancel(pid_r[i]);
			}
			break;
		}
	}

cleanup:
	pthread_rwlock_destroy(&rwlock);
	
	return ret;
}
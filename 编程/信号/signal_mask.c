#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define handle_error_en(en, msg) \
	   do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static void* sig_thread(void *arg)
{
   sigset_t *set = arg;
   int s, sig;

   for (;;) {
	   s = sigwait(set, &sig);
	   if (s != 0)
		   handle_error_en(s, "sigwait");
	   printf("Signal handling thread got signal %d\n", sig);
   }
}

/**
 * 设置信号掩码，阻塞 SIGQUIT 和 SIGUSR1 信号，即程序收到这两个信号时不作任何处理。
 * 由主线程创建的子进程会继承这份掩码。
 *
 * 即本程序中的主线程、子线程均会阻塞这两个信号。
 */

int main(int argc, char *argv[])
{
   pthread_t thread;
   sigset_t set;
   int s;

   sigemptyset(&set);
   sigaddset(&set, SIGQUIT);
   sigaddset(&set, SIGUSR1);
   s = pthread_sigmask(SIG_BLOCK, &set, NULL);
   if (s != 0)
	   handle_error_en(s, "pthread_sigmask");

   s = pthread_create(&thread, NULL, &sig_thread, (void *) &set);
   if (s != 0)
	   handle_error_en(s, "pthread_create");

   pause();		// 暂停主线程，防止子线程因主线程退出而销毁
}
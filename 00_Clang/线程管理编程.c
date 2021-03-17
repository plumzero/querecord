【多线程实现】
基本概念：线程、互斥锁、条件
线程操作：线程的创建、退出、等待
互斥锁操作：创建、销毁、加锁、解锁
条件操作：创建、销毁、触发、广播、等待

创建线程
	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg);
说明：
	使用此函数创建的线程并不具备与主线程相同的执行序列，而是使其运行参数start_routine(arg)所指向的函数
参数：
	thread			指向线程描述符的指针
	attr			用来设置线程的属性，通常被设为空指针，这样将生成默认属性的线程
	start_routine	线程运行函数的起始地址。函数返回值由 pthread_join 获取
	arg				传递给运行函数的参数
返回值 
	0 	- 成功
	非0 - 失败 	EAGAIN - 超出了系统限制，如创建的线程太多
				EPERM - 调用者没有适当的权限设置所需的参数或安排调度策略
				EINVAL - 表示第二个参数代表的属性值非法

终止线程
	void pthread_exit(void *retval);
参数：
	如果pthread_join中第二个参数thread_return不是NULL，参数retval就将被传递给thread_return。用于接收新线程处理结果。
线程终止的途径：
	主线程通过return函数或exit函数返回
	线程从执行函数返回
	调用pthread_exit函数退出
	被同一进程的其他线程调用pthread_cancel函数终止
	注：1.主线程通过return函数返回或调用exit函数退出时，则整个进程及所有线程都将终止，所以要确保主线程不会从main过早的
		返回。这可以在主线程中调用pthread_join等待子线程结束。
		2.在其他线程调用exit函数也会终止整个进程。
		3.如果主线程仅仅调用了pthread_exit函数，则仅仅是主线程消亡，进程不会结束，进程中的其他线程也不会结束，直到所有
		的线程都结束时进程才结束。				

等待线程
	int pthread_join(pthread_t thread, void **thread_return);
说明：
	将调用pthread_join的线程挂起，直到参数thread所代表的线程终止
参数：
	thread			指定了将要等待的线程，它就是pthread_create返回的线程标识符
	thread_return	此指针指向另外一个指针，之后再指向线程的返回值
返回值
	函数返回时，等待线程的资源被收回 
	0	- 成功
	非0 - 失败	ESRCH - 没有找到与给定的线程ID相对应的线程。
				EDEADLK - 将出现死锁，如一个线程等待其本身，或者线程A和线程B互相等待。
				EINVAL - 与给定的线程ID相对应的线程是分离线程。
注：1.主线程比新线程提前退出，会导致新线程无法抢占CPU而被忽略。
	2.等待的线程必须是当前进程中的非分离线程。如果没有必要等待特定线程终止之后才进行其他处理，则应当将该线程分离。
	3.第二个参数thread_return不为NULL是，会指向已终止线程（所等待线程）的退出状态。
	4.一个线程不能被多个线程等待，否则第一个接收到信号的线程成功返回，其余调用pthread_join的线程则返回错误码ESRCH。
	5.子线程最终一定要使用pthread_join或者设置为分离状态来结束线程，否则线程的资源不会被完全释放（使用取消线程功能
	也不能完全释放）。
	
一个线程可以在创建后使用pthread_self函数调用来获取自己的线程ID
	pthread_t pthread_self(void);
	
【线程属性】
只需要创建并填充一个phtread_attr_t类型的线程属性对象ATTR，并将其作为第二个参数传递给phtread_create就可以指定新创建的线程
的属性。
仅当创建新线程的时候线程属性对象才被参考，同一个线程对象可用于创建多个线程。在pthread_create之后修改一个线程对象并不会修
改之前创建的线程的属性。
线程属性结构如下：
	typedef struct
	{
		int 				detachstate;			//线程的分离状态
		int 				schedpolicy;			//线程调度策略
		struct sched_param	schedparam;				//线程的调度参数
		int					inheritsched;			//线程的继承性
		int					scope;					//线程的作用域
		size_t				guardsize;				//线程栈末尾的警戒缓冲区大小
		int					stackaddr_set;			//
		void *				stackaddr;				//线程栈的位置
		size_t				stacksize;				//线程栈的大小
	}pthread_attr_t;

属性初始化
	int pthread_attr_init(pthread_attr_t * attr);
参数：
	attr			线程属性变量，对线程初始化
返回值：
	0	- 成功
	-1	- 失败

去除初始化
	int pthread_attr_destroy(pthread_attr_t * attr);
参数：
	attr			线程属性变量，对线程属性去除初始化
返回值：
	0	- 成功
	-1	- 失败

获取线程的分离状态属性。
	int phtread_attr_getdetachstate(const phthead_attr_t * attr, int * detachstate);
参数：
	attr			线程属性变量
	detachstate		线程的分离状态属性
返回值：
	0	- 成功
	-1	- 失败
	
修改线程的分离状态属性
	int pthread_attr_setdetachstate(pthread_attr_t * attr, int detachstate);
参数：
	attr			线程属性变量
	detachstate		线程的分离状态属性
返回值：
	0	- 成功
	-1	- 失败
注：1.在任何一个时间点上，线程都是可结合（Joinable）或者分离的（Detached）。一个可结合的线程能够被其他线程收回资源和杀死，
	在被其他线程回收之前，它的存储器资源（如栈）是不释放的；相反，一个分离的线程是不能被其他线程回收或杀死的，它的存储资
	源在它终止时由系统自动释放。
	2.如果我们在创建线程时不需要了解线程的终止状态，则可以设置phtread_attr_t结构体中的detachstate线程属性，让线程以分离状
	态启动。
	3.detachstate取值：PTHREAD_CREATE_DETACHED（以分离状态启动线程）和PTHREAD_CREATE_JOINABLE（正常启动线程）。
	4.如果以分离状态启动线程，为了避免分离线程在pthread_create函数返回之前终止，造成调用pthread_create的线程得到错误的线
	程号（因为它终止以后就可能将线程号和系统资源移交给其他的线程使用），可以在分离线程里调用pthread_cond_timewait函数，让
	分离线程等待一会儿，留出足够时间让pthread_create返回。
	
设置线程的继承性
	int pthread_attr_setinheritsched(pthread_attr_t * attr, int inheritsched);
参数：
	attr			线程属性变量
	inheritsched	线程的继承性
返回值：
	0	- 成功
	-1	- 失败

获取线程的继承性
	int pthread_attr_getinheritsched(const pthread_attr_t * attr, int * inheritsched);
参数：
	attr			线程属性变量
	inheritsched	线程的继承性
返回值：
	0	- 成功
	-1	- 失败
注：1.继承性决定调度的参数是从创建的线程中继承还是使用在schedpolicy和schedparam属性中显式设置的调度信息。
	2.inheritsched取值：PTHREAD_INHERIT_SCHED（新线程将继承创建线程的调度策略和参数）和PTHREAD_EXPLICIT_SCHED（使用在
	schedpolicy和schedparam属性中显式设置的调度策略和参数）。
	3.如果需要显式设置一个线程的调度策略或参数，就必须在设置之前将inheritsched属性值设置为PTHREAD_EXPLICIT_SCHED。

获取线程的调度策略
	int pthread_attr_getschedpolicy(const pthread_attr_t * attr, int * policy);
参数：
	attr			线程属性变量
	policy			调度策略
返回值：
	0	- 成功
	-1	- 失败
设置线程的继承性
	int pthread_attr_setschedpolicy(pthread_attr_t * attr, int policy);
参数：
	attr			线程属性变量
	policy			调度策略
返回值：
	0	- 成功
	-1	- 失败
注：1.policy取值：SCHED_FIFO（先进先出）、SCHED_RR（轮转法）、SCHED_OTHER（其他）。
	2.SCHED_FIFO策略允许一个线程运行直到有更高优先级的线程准备好，或者直到它自愿阻塞自己为止。
	3.SCHED_RR与SCHED_FIFO基本相同。不同之处在于：如果有一个SCHED_RR策略的线程执行了超过一个固定的时期没有阻塞，而另外
	的SCHED_RR或SCHED_FIFO策略的相同优先级的线程准备好时，运行的线程将被抢占以便准备好的线程可以执行。
	4.当有SCHED_FIFO或SCHED_RR策略的线程在一个条件变量上等待或等待加锁同一个互斥量时，它们将以优先级顺序被唤醒。
	
获取线程的调度参数
	int pthread_attr_getschedparam(const pthread_attr_t * attr, struct sched_param * param);
参数：
	attr			线程属性变量
	sched_param		调度参数
返回值：
	0	- 成功
	-1	- 失败

设置线程的调度参数
	int pthread_attr_setschedparam(pthread_attr_t * attr, const struct_param * param);
参数：
	attr			线程属性变量
	sched_param		调度参数
返回值：
	0	- 成功
	-1	- 失败
注：1.结构体sched_param定义 struct sched_param { int sched_priority; }; 成员sched_priority大小对应优先权值大小。
	2.系统支持的最大和最小优先权值可以分别用sched_get_priority_max函数和shce_get_priority_min函数得到。
	3.如果不是编写实时程序，不建议修改线程的优先级。
	
获取系统支持的最大优先权值
	int sched_get_priority_max(int policy);
参数：
	policy			系统支持的线程优先权的最大值
返回值：
	0	- 成功
	-1	- 失败

获取系统支持的最小优先权值
	int sched_set_priority_max(int policy);
参数：
	policy			系统支持的线程优先权的最小值
返回值：
	0	- 成功
	-1	- 失败
	
【互斥锁】
互斥锁初始化
	int pthread_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr * mutexattr);
参数：
	mutex			互斥锁
	mutexattr		PTHREAD_MUTEX_INITIALIZER					创建快速互斥锁
					PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP		创建递归互斥锁
					PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP		创建检错互斥锁
返回值：
	0	- 成功
	-1	- 失败
注：快速型：默认类型。如果线程给一个互斥量重复上锁，那么线程将会无限阻塞，导致死锁。
	递归型：同一线程循环给互斥量上锁，不会死锁，但需要同样次数的解锁。
	错误检测型：如果互斥量已经上锁，则后续上锁则会失败而不会阻塞，pthread_mutex_lock操作将会返回EDEADLK。

互斥操作函数
	int pthread_mutex_lock(pthread_mutex_t * mutex);			//上锁
	int pthread_mutex_trylock(pthread_mutex_t * mutex);			//互斥被锁住时不会阻塞，而是立刻返回EBUSY
	int pthread_mutex_unlock(pthread_mutex_t * mutex);			//解锁
	int pthread_mutex_destroy(pthread_mutex_t * mutex);			//消除互斥锁
参数：
	mutex			互斥锁
返回值：
	0	- 成功
	-1	- 失败

互斥量的属性
	int pthread_mutexattr_settype(pthread_mutexattr_t * attr, int kind);
参数：
	mutex			互斥锁
	kind			设置的属性类型 取值 PTHREAD_MUTEX_FAST_NP、PTHREAD_MUTEX_RECURSIVE_NP、PTHREAD_MUTEX_ERRORCHECK_NP 
返回值：
	0	- 成功
	-1	- 失败
注：1.互斥量的属性类型为pthread_mutexattr_t，声明后调用pthread_mutexattr_init来创建该互斥量，然后调用
	pthread_mutexattr_settype来设置属性。
	2.使用属性的简单过程
		pthread_mutex_t mutex;
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
		pthread_mutex_init(&mutex, &attr);
		pthread_mutex_destroy(&attr);

【创建条件变量】
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;			//静态创建
	int pthread_cond_init(pthread_cond_t * cond, pthread_condattr_t * cond_attr);		//动态创建
参数：
	cond			条件变量
	cond_attr		条件变量属性 linux下取值 NULL
【等待条件变量】
	int pthread_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);				//正常等待
	int pthread_cond_timedwait(pthread_cond_t, pthread_mutex_t * mutex, const struct timespec * abstime);//超时等待
参数：
	cond			条件变量
	mutex			互斥锁
	abstime			超时时间	在给定时刻前条件没有满足，则返回ETIMEOUT，结束等待。
注：1.必须与互斥锁配合以防止多个线程同时请求pthread_cond_wait或pthread_cond_timedwait而致竞争。
	2.互斥锁必须为普通锁（PTHREAD_MUTEX_TIMED_NP）或者适应锁（PTHREAD_MUTEX_ADAPTIVE_NP）。
	3.线程A在调用等待函数之前必须确保本线程处于加锁状态（即调用了pthread_mutex_lock），当条件不满足时，线程A解开相应
	互斥锁并等待条件发生变化。一旦线程B改变了条件变量（即调用了pthread_cond_signal或pthread_cond_broadcast），它将通
	知相应的条件变量唤醒正被此条件变量阻塞的线程A。（在线程B执行完剩余程序）之后线程A将重新锁定互斥锁并测试条件是否
	满足。
【激发条件变量】
	int pthread_cond_signal(pthread_cond_t * cond);			//按顺序激活等待线程队列中的一个
	int pthread_cond_broadcast(pthread_cond_t * cond);		//激活所有等待线程
参数：
	cond		条件变量
【销毁条件变量】
	int pthread_cond_destroy(pthread_cond_t * cond);
参数：
	cond		条件变量
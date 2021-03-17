
组织原则
1. 类型定义、宏定义尽量与函数声明相分离；
   内部函数声明头文件与外部函数声明头文件相分离；
   内部类型定义头文件与外部类型定义头文件相分离；
2. 不同语义层次的类型定义不要放在一个头文件中；
   不同层次的函数声明不要放在一个头文件中；
3. 头文件内不允许定义变量和函数，只能有宏、类型(typedef/struct/union/enum 等)及变量和函数
   的声明。
4. 特殊情况下，头文件可 extern 基本类型(build-in type)的全局变量，源文件通过包含该头文件访
   问该全局变量。
5. 头文件内不建议 extern 自定义类型(如结构体)的全局变量，否则将迫使本不需要访问该变量的源
   文件包含自定义类型所在头文件。
   如果要在头文件内 extern 自定义类型，作为全局变量，可以采用的做法是将类型定义与 extern 
   置于同一个头文件中，而真正的实现在其它源文件中。这样别的源文件也可以通过引用该文件使用
   该全局变量。如下
   // global.h
	typedef struct {
		int mInt;
	} GLOBAL_OPTIONS;

	extern GLOBAL_OPTIONS global_options;
	// before_test.h
	void before_test_print_st();
	// before_test.c
	#include "global.h"
	#include <stdio.h>
	
	extern GLOBAL_OPTIONS global_options;
	
	void before_test_print_st()
	{
		printf("before_test_print_st : %d\n", global_options.mInt);
	}
	// test.h
	void test_print_st();
	// test.c
	#include "global.h"
	#include <stdio.h>

	GLOBAL_OPTIONS global_options = { .mInt = 99 };		// 全局变量在这里定义

	void test_print_st()
	{
        printf("test_print_st : %d\n", global_options.mInt);
	}
   // main.c
	#include <stdio.h>
	#include "before_test.h"
	#include "test.h"

	int main()
	{
        before_test_print_st();
        test_print_st();
        before_test_print_st();

        return 0;
	}
   输出结果为:
		before_test_print_st : 99
		test_print_st : 99
		before_test_print_st : 99
   注意: 强烈不建议将类型定义与全局变量定义放在同一个头文件中。
6. C++ 中要引用 C 函数时，函数所在头文件内应包含 extern "C" 。
   // .h 文件头部
	#ifdef __cplusplus
	extern "C" {
	#endif
   // .h 文件尾部
	#ifdef __cplusplus
	}
	#endif
   被 extern "C" 修饰的变量和函数将按照 C 语言方式编译和链接，否则编译器将无法找到 C 函
   数定义，从而寻到链接失败。
   
   
包含原则
略

全局变量的使用原则
1. 若全局变量仅在单个源文件中访问，则可将该变量改为该文件内的静态全局变量；
2. 若全局变量仅由单个函数访问，则可将该变量改为该函数内的静态局部变量；
3. 尽量不要使用 extern 声明全部变量，最好提供函数访问这些变量。直接暴露全局变量是不安全
   的，外部用户未必完全理解这些变量的含义；
4. 设计和调用访问动态全局变量、静态全局变量、静态全局变量的函数时，需要考虑重入问题。
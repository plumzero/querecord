
const 和 volatile
1. const 常量总是占用存储。这样，C编译器不能把 const 看成是一个编译期间的常量。在 C 中，
   如下代码是不正确的。
	const int size = 100;
	char buffer[size];
2. const 常量是全局符，在 C 中默认是外部连接的。在一个文件中定义的 const 常量，在其他文
   件中也可引用，而不必使用 extern 关键字。
3. volatile 告知编译器不能对其所修饰的变量进行优化，每次用到该变量时，需要从寄存器中重
   读数据uuuuuu7777777777777778（因为有可能被其他进程所改变）。
   volatile 常用于多任务系统或嵌入式系统中。

centos 6.4 源码安装 gdb-8.1.tar.gz
make install后会出现了错误，根据错误提示应该安装 texinfo 包
	yum install texinfo

GDB程序调试的对象是可执行文件，而不是程序的源代码文件。
调试信息包含程序里每个变量的类型和在可执行文件内的地址映射及源代码的行号。

gdb功能：
	设置断点（可以是条件表达式）
	单步执行
	查看变量
	动态改变执行环境
	分析崩溃程序产生的core文件

常用命令
	名称		含义描述
	file		装入想要调试的可执行文件
	run			执行当前被调试的程序	简写 r
	kill		终止正在调试的程序
	step		执行一行源代码并且进入函数内部
	next		执行一行源代码但不进入函数内部	简写 n
	break		在代码里设置断点，这将使程序执行到此处时被挂起
	print		打印表达式或变量的值，或打印内存中某个变量开始的一段连续区域的值，还可用于对变量赋值
	display		设置自动显示的表达式或变量，当程序停住或在单步跟踪时，这些变量会自动显示其当前值
	list		列出产生执行文件的源代码的一部分
	quit		退出gdb
	watch		使用户能监视一个变量的值而不管其何时被改变
	backtrace	回溯跟踪	简写 bt
	frame n		定位到发生错误的代码段，n为backtrace命令的输出结果中的行号
	examine		查看内存地址中的值
	jump		使程序跳转执行
	signal		产生信号量
	return		强制函数返回
	call		强制调用函数
	make		使用户不退出gdb就可以重新产生可执行文件
	shell		使用户不离开gdb就能执行Linux的shell命令
	help		请求帮助
	
程序由于段错误（Segmentation fault）而异常终止，说明内存操作出了问题。

break命令的含义
命令					含义描述
break <function>		在进入指定函数时停住
break <linenum>			在指定行号停住
break +offset			在当前行号前面的offset行停住。offset为自然数
break -offset			在当前行号后面的offset行停住。
break filename:linenum	在源文件filename的linenum行停住
break filename:function	在源文件filename的function函数的入口处停住
break *address			在程序运行的内存地址处停住
break					该命令没有参数时，表示在下一条指令处停住
break...if<condition>	condition表示条件，在条件成立时停住。
info break				查看断点信息

print命令格式：
	print <expr>
	print /<f> <expr>	//	<f>是输出格式

gdb数据显示格式
符号		含义
x			十六进制
d			十进制
u			十六进制无符号整型
o			八进制
t			二进制
a			十六进制
c			字符
f			浮点

自动显示命令display格式：
	display <expr>
	display /<fmr> <expr>	//	<fmr>是显示格式
	display /<fmr> <addr>	//	<addr>是内存地址
	
examine命令
	x/<n/f/u> <addr>
命令说明：
	n、f、u是可选参数，可独立或联合使用
	n表示内存长度，即从当前地址向后显示几个地址的内容
	f显示格式。如果地址所指是字符串，格式可以是s；如果是指令地址，格式可以是i
	u表示从当前向后请求的字节数，如果不指定，默认4bytes。u参可以用下面的字符代替：
		b	单字节
		h	双字节
		w	4字节
		g	8字节
	<addr>内存地址
	
gdb环境变量
定义自己的环境变量，用来保存一些调试程序中的运行数据。
	set $foo=*object_ptr
环境变量没有类型，可以给环境变量定义任意的类型，包括结构体和数组。
	show convenience

查看寄存器
info registers		查看寄存器情况（浮点寄存器除外）
info all-registers	查看所有寄存器情况（包括浮点寄存器）
print $寄存器名		访问某个寄存器

显示源代码list
命令					含义描述
list <linenum>			第linenum周围的源程序
list <function>			此函数的源程序
list					当前行后面的源程序
list -					当前行前面的源程序
set listsize <count>	设置一次显示源代码的行数
show listsize			查看当前listsize的设置
list <first>, <last>	从first行到last行之前的源代码
list, <last>			从当前行到last行之间的源代码
list + 					向后显示

源代码的内存
使用info line命令查看源代码在内存中的地址。info line后面可以跟“行号”、“函数名”、“文件名:函数名”的参数形式，该命令会显示出所指定源码在运行时的内存地址。

查看源程序当前执行的机器码disassemble
使用方法参见info line

改变程序的执行
	修改变量值
		print x=a
	跳转执行
		jump <linespce>			//可以是文件行号（file:line格式），也可以是+num偏移量格式
		jump <address>
		注意：最好在同一个函数中跳转
	产生信号量
		signal <signal>
	强制函数返回
		return					//取消当前函数执行并立即返回
		return <expression>		//立即返回且此表达式作返回值
	强制调用函数
		call <expr>				//并显示函数返回值，若为void就不显示
		
试图把char型按照字符串格式输出，这里的字符会解释成整数，再解释成地址，会报段错误。int型类同。
printf("%s", c);

如何避免多线程创建不成功导致的段报错
描述：用pthread_create创建了各个线程，然后用pthread_join来等待线程的结束。在创建线程都成功的时候，pthread_join能够顺利等待各个线程结束，但是一旦创建线程失败，
那用pthread_join来等待那个本不存在的线程时自然会存在访问不能访问的内存的情况，从而导致段错误的发生。
原因和解决办法：
在创建线程之前，先初始化线程（数组），在等待线程的结束的时候，判断线程是否为初始的值。如果是的话，说明线程并没有创建成功。

在linux中，最好不要这样定义一个字符串
char * str = "abcdefg";
因为在做内存拷贝时容易报段错误。
应该这样
char str[] = "abcdefg";


//学习之二
gdb命令补充
指令		解释
file		载入程序，如file hello。当然，程序的路径名要正确
info		查看程序的信息。多用来查看断点信息。
		info source	查看当前文件的名字，路径，所使用的程序语言等信息
		info stack	查看调用栈
		info local	查看局部变量信息
		info br		查看断点信息
watch		监视某个表达式或变量，当它被读或被写时让程序断下
set		修改变量值 格式：set varible=first

在gdb中运行程序主要涉及4个方面
1）运行程序前的设置
	程序运行参数
		set args 可指定运行时参数
		show args 命令可以查看设置好的运行参数
	运行环境
		path <dir> 可设置程序的运行路径
		show paths 查看程序的运行路径
		set environment varname[=value]设置环境变量
	工作目录
		cd <dir>相当于shell的cd命令
		pwd显示当前的所在目录
	程序的输入/输出
		info terminal 显示程序用到的终端的模式
2）改变程序的执行
	跳转执行（最好在同一个函数中跳转）
		jump <linespec>	<linespec>可以是文件行号，可以是+num这种偏移量格式。
		jump <address>	<address>代码行的内存地址。
	强制函数返回
		return <expression>	取消当前函数执行，并立即返回。<expression>为返回值。
	强制调用函数
		call <expr>
3）查看栈信息
	当程序被停止时，需要做的第一件事就是查看程序是在哪里停止的。当程序调用了一个函数时，
	函数的地址、函数参数、函数内的局部变量都会被压入栈中。
	backtrace	查看函数调用栈信息的命令
	frame		查看当前栈层的信息
	info frame	显示出这些信息：栈的层编号，当前的函数名，函数参数值，函数所在文件
			及行号，函数执行到的语句
	info args	显示当前函数的参数名及值
	info locals	显示出当前函数中所有局部变量及值
	info catch	显示出当前函数中的异常处理信息
4）源程序的查看
	略

暂停和恢复程序运行
在gdb中，有几种暂停方式：断点、观察点、捕捉点。
如果要恢复程序运行，可以使用continue命令。
1）设置断点
	break <function>		进入指定函数时停止
	break <linenum>			在指定行号停止
	break filename: linenum		在源文件filename的linenum行处停止
	break filename: function	在源文件filename的function函数的入口处停止
	break *address			在程序运行的内存地址停止
	info break[n]			查看断点
2）设置观察点
	watch <expr>	为表达式（变量）设置一个观察点。一旦表达式值有变化时，马上停止程序
	rwatch <expr>	当表达式（变量）expr被读时，停止程序
	awatch <expr>	当表达式（变量）的值被读或被写时，停止程序
3）设置捕捉点
	catch <event>	只设置一次捕捉点，当程序停止后，该点被自动删除
4）维护停止点
	clear			清除所有的已定义的停止点
	clear <function>	清除所有设置在指定函数上的停止点
	clear <linenum>		清除所有设置在指定行上的停止点
	delete [breakpoints]	删除指定的断点。如果不指定断点号，则表示删除所有的断点。
5）恢复程序运行和单步调试
	continue [ignore-count]	恢复程序运行，直到程序结束或下一个断点到来。ignore-count表示忽略其后断点次数
	step <count>		如果有函数调用，且此函数被编译有debug信息，会进入此函数
	next <count>		如果有函数调用，不会进入该函数。加count表示执行后面的count条指定后停止

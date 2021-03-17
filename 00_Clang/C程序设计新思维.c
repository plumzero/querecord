
C 语言变迁
  K&R -> ANSI C89 -> ISO C99 -> C11
  
其中 ANSI C89 通常称为 ANSI C 。
微软 Visual Studio 的 C++ 编译器目前只提供了与 C89 相容的模式。

支持 for 循环内变量定义是 C99 出现的标准，不过 VS 也支持，太乱了。
  
POSIX 标准
  UNIX
    POSIX
	  BSD (Berkeley Software Distribution, 伯克利软件发行版，如 Mac)
	    BSD 许可证(如 clang)
	  GNU (GNU's Not UNIX，如 Linux)
	    GNU 公共许可证(如 gcc)
		次级 GPL 许可证(如 Glib)
 
//////////////////////////////////////// 准备方便的编译环境 ////////////////////////////////////////
	
C 开发环境包
  GCC
  GDB 调试器
  Valgrind 用于测试 C 内在使用错误
  Gprof 用于运行效率评测
  Make 使得你不用直接调用编译器
  Pkg-config 用于查找库
  Doxygen 用于生成程序文档
  
操作系统分类
  POSIX 兼容系统家族
  Windows 操作系统家族
  
查看一个程序或者动态链接库依赖于哪些库，用下面的命令：
  Cygwin: cygcheck libxx.dll
  Linux: ldd libxx.so
  Mac: otool -L libxx.dylib
  
Windows 下使用 POSIX 环境，需要使用 Cygwin 。
如果不需要调用 POSIX 函数，则可以使用 MinGW(Minimalist GUN for Winodws)。

通过 Autotools 建立软件包的三个标志性命令是： ./configure, make, make install 。

gcc 编译依赖
如果你有一个叫作 specific.o 的文件依赖于 Libbroad 库，而 Libbroad 库依赖于 Libgeneral，那么你应该输入：
  gcc specific.o -lbroad -lgeneral

pkg-config 不是一个标准，一些软件会在安装成功时生成一个 pkg-config 目录，该目录下的文件有该软件的相关配置和位置信息。
你可以将此目录添加到 $PKG_CONFIG_PATH 搜索路径上，之后可以通过 pkg-config 命令搜索到相关库的信息。
  pkg-config --libs lua5.3
  pkg-config --cflags lua5.3
也可以与 gcc 结合使用
  gcc `pkg-config --libs --cflags lua5.3` -o test test.c
你也可以编写自己的 pkg-config 文件实现相同操作目的。

运行时连接库
一般将动态连接路径设置在 /etc/ld.so.conf.d/ 目录下适当文件中。当然也可以在编译器中指定参数实现操作，如下（未作测试）：
  LDADD=-Llibpath -Wl, -Rlibpath

//////////////////////////////////////// 调试、测试和文档 //////////////////////////////////////// 

C++ 编译器会对代码命名进行重整，而 C 则不会，gdb 对调试 C 更加有用。

堆栈帧
示例伪码
  // addresses.c
  agent_address(int) {}
  get_agents() {
	 ...
	 agent_address(int);
	 ...
  }
  main() {
	 ...
	 get_agents();
	 ...
  }
通过 backtrace 命令可以查看该程序堆栈帧如下：
  #0 0x00413bbe in agent_address (agent_number=312) at addresses.c:100
  #1 0x004148b6 in get_agents() at addresses.c:163
  #2 0x00404f9b in main(argc=1,argv=0x7fffffffe278) at addresses.c:227
堆栈顶端是 0 帧，帧号后的十六进制是一个地址，被调函数返回的时候，程序执行将返回这个地址。地址后面是函数名、入参，以及当前执行到的源代码行号。
很多程序分析技巧就是跳入堆栈中，从一个个的函数的堆栈中追踪因果关系。

gdb 常用交互命令
  b		break
  c		continue
  r		run
  l		list
  p		print

run args		带参运行
p verbose++		提升信息输出级别
p i=100			为变量赋值

gdb print 打印数组 array[20]
  p *array			// 打印首个数据
  p *array@10		// 打印前 10 个数据
  
gdb 关于断点的操作
  b 25 				// 在 25 行处设置断点
  info break		// 查看断点信息
  dis 1				// 使断点 1 无效
  ena 1				// 使断点 1 有效
  del 1				// 删除断点 1
  
gdb 变量查看
  info local		// 查看本地变量表
  info args			// 查看输入参数
  disp avg			// 程序执行过程中，对 avg 进行实时观察
  info disp			// 查看正在实时观察的成员			乱猜的，不知道有没有这个命令
  undisp 1			// 取消对编号为 1 的成员的观察
  
gdb 对堆栈的操作
  bt				// 堆栈回溯，即列举中堆栈帧
  f 1				// 切换到第 1 帧堆栈
  up/down			// 在堆栈中上下移动
  
gdb 单步执行操作
  s
  n
  u
  c
  ret				// 从当前函数立即抬，并给出返回值
  j 105				// 跳到第 105 行
  
gdb 对多线程的操作
  info threads		// 获得多线程列表
  thread 2			// 切换到线程 2
  
gdb 为参数指定别名，方便处理
  set $vd = my_model->dataset->vector->data
  p *$vd@10
  set $ptr=&x[3]
  p *$ptr=8
  p *($ptr++)
  
通过 gprof 对程序运行效率进行评测
  gcc 编译时 CFLAGS 添加 -pg 项
  gprof your_program > file
  
利用 valgrind 检查错误
  valgrind --db-attach=yes your_program			// 在第一个出错的地址运行调试器
  valgrind --leak-check=full your_program		// 检测内存泄露
  
单元测试：为比较小的组件写单元测试
集成测试：为了确认不同的组件之间可以协同工作而进行集成测试
测试框架：为每个测试配置环境、运行测试，以及报告是否得到期望结果的系统

CFLAGS=-DTest_operations 	// POSIX 标准的编译器选项，相当于在每个 .c 文件中加入 #define Test_operations。单独编译文件进行调试时很有用。

测试覆盖：你所写的测试是否执行到你所写的所有代码行
通过 gcov 来计算每行代码被程序执行的次数
  gcc -O0 -fprofile-arcs-ftest-coverge ...
  编译过程中，每个源代码文件会产生一个或两个数据文件 *.gcda 和 *.gcno
  运行 `gcov *.gcda` 。 *.gcda 将向 stdout 输出程序中可执行代码的被执行次数的百分比（声明、#include 不计在内），并产生 *.c.cov 文件
  *.c.cov 的第一栏将展示在你的测试中每个可执行行的被执行频率，并且将没有被执行的行用一堆 ##### 来标识。
测试脚本示例
  vim makefile
  make ./coverage_test
  for i in *gcda; do gcov $i; done;
  grep -C3 '#####' *.c.gcov
  
对于一个错误，一般可以以下 3 种方式去处理，其深层应用场景如下（仅针对 C）：
  return -x;		// 返回错误代码，由调用者处理，程序可继续运行
  exit(-x);			// 中断程序，使用调试器时会清除错误痕迹
  abort();			// 中断程序，使用调试器时可以继续进行调试

//////////////////////////////////////// 打包项目 ////////////////////////////////////////

Autotools 是一个为给定系统自动产生完美 makefile 的系统。

在命令行中，反引号大体上相当于 $()。例如，echo `date` 和 echo $(data) 基本相同。然而，make 对 $() 有自己特别的用途，所以在写 makefile 时需要用反引号。

统计 .c 文件中特定行的总数
grep "[;{}()]$" *.c | wc -l

脚本示例: 在所有的 .c 文件中寻找以非数字开头的非空行，并确认该行是否含有 $i 字。如果有，写入 lines_with_${i} 中
for i in `seq 0 9`;
do
	grep -E '(^|[^0-9.])'$i *.c > lines_with_${i};
done

脚本示例：执行某个程序多次，并将各自的执行结果写入对应的文件
for i in `seq 1 1000`;
do
	./run_program > ${i}.out;		// 写入同一个文件 ./run_program >> run_outputs
done

echo 命令本身也有一个返回值，因此在运行 echo $? 之后， $? 的值又被设定为 echo 命令的返回值了。如果你想为了某种目的而多次使用 $?, 
需要把它赋值给另一个变量，比如 returnval=$? 。

if 程序运行正常; then
	#
fi

像下面这样写是不对的，因为第一个命令执行失败后并不会影响第二个命令的执行
	cd junkdir
	rm -rf *
应该像下面这样
	cd junkdir && rm -rf *
不过最好还是
	rm -f junkdir*

//////////////////////////////////////// 版本控制 ////////////////////////////////////////

Git 基于一小组对象，关键对象是提交对象。它们就是一组 diff ，给定上一个提交对象和一些以此为基线的变化，一个新的提交对象就可以打包所有的信息。
它利用了来自 index 的支持，记录自从上一次提交开始所注册下来的变化列表，主要的用途是为了产生下一个提交对象。

提交对象连接起来以形成一个树。每个提交对象有（至少）一个父提交对象。

得到一个版本库
	git init
	git clone https://github.com/b-k/21st-Century-Examples.git

释放一个版本库
	rm -rf .git

产生一个提交对象。因为提交对象记录着从最开始点或者前一个提交到目前的差异，所以必须先产生一些差异，然后才能建立 commit。
index 是一个变化列表，记录着想在下一个提交中提交的变化。它的存在是因为我们实际上并不希望项目目录中的每个差异都被记录下来。
index 的关键操作就是向它的变化列表里添加元素。用：
	git add gnomes.c gnomes.h
来把这些文件加入 index 中。其他需要被加入 index 的文件追踪列表典型的变化还有：
	git add newfile
	git rm oldfile
	git mv file file
你对文件做出的改变虽然被 Git 追踪到，但并不能自动添加到 index 中，而是通过 git add changedfile 加入每个文件。



在你提交之后，你非常有可能拍着额头想起你忘记了什么，你可以运行 git commit -amend a 来重新做最后的提交，而不用执行另一次提交。

切换到历史版本
	git checkout fe9c4
返回到现在的状态，即最近的提交
	git checkout master

索引就是 git commit 产生的 SHA1 hash

工作目录与当前 index 的不同
	git diff
工作目录与历史 index 的不同
	git diff fe9c4
历史索引与历史 index 的不同
	git diff 234e2a 8b90ac
	
有一些名字可以避免去使用那些 hash 值。 HEAD 代表目前最后一个提交，也就是一个分支的头部；如果它不是，git 会给出一个错误报告，指出这是一个"分离的头"。
加上 ~1 代表这个提交的父提交， -2 代表祖父提交，以此类推。
	git diff HEAD~4					# 工作目录与四次之前的提交作比较
	git checkout master~1			# 切换到 master 的上次提交版本
	git checkout master~			# 同上
	git diff b0897~ b0897			# b0897 的变化

stash
提交对象是参考点，而大部分的 Git 活动是基于这些参考点发生的。
你可以跳到任何提交，但是如果你当前的工作目录的内容没有对应的提交来恢复的话，跳过去也可以，但是你却跳不回来了。
如果想回到某个提交，你应该把自从最后一个提交以后所做的工作保存在某处，然后回到你最后的提交，执行某个操作，当你结束跳转或者打补丁后，再从保存的地方
恢复你以前的工作。
stash 就可以做到，其典型用法如下：
	git stash
	git checkout fe9c4
	git checkout master
	git stash pop
	
树和它们的分支
除了最初的那个，所有的提交对象都有一个父对象，并且对象本身记录了自己和其父对象之间的 diff。整个序列中最终的节点，也就是树枝的末梢，用一个分支名字作
为标签。
习惯上一般是保持主分支随时具有完整的功能。根据需要创建新的分支，当这个分支充分实现了功能的时候，再融合进主分支中。
创建分支的两种方法：
	git branch newleaf
	git checkout newleaf
	git checkout -b newleaf
查看当前所处分支：
	git branch
如果你导出一个老的版本，做一些修改，然后把你最新的修改用一个新的提交对象来交付，那么现在你有一个与主分支(master)差异甚大的新分支。当完成这样的分叉之
后运行 git branch ，你会发现自己现在处于(no branch)。没有标签的分支容易产生问题，所以只要你处于(no branch)，那么运行 git branch -m new_branch_name 来
命名你刚分出的分支。

融合
为了融合所有的发生在 newleaf 与 master 之间的变化，切换到 master 分支然后用 git merge:
	git checkout master
	git merge newleaf
假设当工作于新的特性的时候，你从没有对 master 作任何修改，那么当你把来自于别的分支的 diff 序列应用于 master 就相当于把该分支中的每个提交对象变化的录像
做了快速向前的播放，称为"快进"。
但是如果对 master 做了改变，则 git 就无法自动处理了。git 的解决方案是把你的文本文件修改成同时包含两个版本的样子，就像：
	<<<<<<< HEAD
	// changed in master
	=======
	// changed in 3c3c3c
	>>>>>>> 3c3c3c
这时融合就停下来了，等待你对文件的编辑。
融合的一般过程如下：
	1. 运行 git merge other_branch
	2. 很有可能，被告知存在你必须解决的冲突
	3. 用 git status 来检查未融合的文件列表
	4. 选择一个文件来手工检查。用一个文本编辑打开它，如果有内容冲突，找到需要手工融合的标记。如果有一个文件名或者文件位置出现冲突，把这个文件转移到合适的
	   位置
	5. 运行 git add your_now_fixed_file
	6. 重复 3~5 步，直到所有的文件和未融合的文件都被提交。
	7. 运行 git commit 来确认融合并结束
删除旁支：
	git delete other_branch

迁移
假设从主支分出了测试分支，不久对主支进行了修改并提交，假设新提交对象编号为 abcd123，现在要把所有发生在主支上的发动用在测试分支上，应：
	git branch testing
	git rebase abcd123
现在所有到 abcd123 的变化在两个分支都出现了，这就好像两个分支实际上是从这个提交迁移分化出来的一样，而不是刚开始那个提交。
从主支到旁支迁移 diff，从旁支到主支融合 diff 。

远程版本库
你的版本库有一个远程的列表，指向与这个库有关的存放在别处的版本库。
如果你通过 git clone 得到你的版本库，那么你用来克隆的那个版本库就被命名为 origin。
用 git pull origin master 来拉取远程变化，并把它们一次性融合进入你当前的版本库。
相反的动作是 push ，根据你当前的提交来更新远端版本库 git push origin bbranch。

非常有可能，当你推送你的变化时，应用来自你的分支的改变到远程分支将不是个快进（如果是，那就是你的同事还没做什么工作）。解决一个非快进式的融合一般来说需要
人的干预。因此 git 将允许只有快进式的推送。那么怎么确保你的推送是一个快进呢？
	1. 运行 git pull origin 以得到自从你上次导出所作的变化
	2. 以前面讲述的方式手工融合
	3. 运行 git commit -a -m "dealt with merges"
	4. 运行 git push origin bbranch
	
如果想跨越分支，即进行不同分支之间的提交，使用冒号分割的 source:destination 分支名字对。
	git pull origin new_changes:master			// 远端 new_changes merge 到本地 master
	git push origin my_fixes:version2			// 本地分支 my_fixes merge 到远端一个新的分支 version2
	git push origin :prune_me					// 删除远端分支 prune_me
	git pull origin new_changes:				// Pull to no branch; create a commit named FETCH_HEAD

//////////////////////////////////////// “不常用”语法 ////////////////////////////////////////

断言类型的宏，它在断言失败时将会返回：
#define Testclaim(assertion, returnval) if (!(assertion))		\
		{ fprintf(stderr, #assertion " failed to be true.		\
		Returning " #returnval "\n"); return returnval; }
int do_thing() {
	int x, y;
	...
	Testclaim(x == y, -1);
	...
	return 0;
}

//////////////////////////////////////// 更好的结构 ////////////////////////////////////////

可变参数宏
一个用于处理错误的宏
	char error_mode;
	FILE *error_log;
	#define Stopif(assertion, error_action, ...) {					\
		if (assertion) {											\
			fprintf(error_log ? error_log : stderr, __VA_ARGS__);	\
			fprintf(error_log ? error_log : stderr, "\n");			\
			if (error_mode == 's') 	abort();						\
			else					{ error_action; }				\
		} }
	// sample usage
	Stopif(x < 0 || x > 1, return -1, "x has value %g, "
						"but it should be between zero and one.", x)

安全终止的列表
	double sum_array(double in[]) {
		double out = 0;
		for (int i = 0; !isnan(int[i]); i++) out += in[i];
		return out;
	}
	#define sum(...) sum_array((double[]){__VA_ARGS__, NAN})
	
	#define Foreach_string(iterator, ...)	\
		for (char **iterator = (char*[]){ __VA_ARGS__, NULL }; *iterator; iterator++)
	Foreach_string(i, "yarn", "thread", "rope");
		printf("%s\n", *i);
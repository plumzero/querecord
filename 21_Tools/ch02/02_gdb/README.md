
### gdb功能

- 设置断点(可以是条件表达式)
- 单步执行
- 查看变量
- 动态改变执行环境
- 分析崩溃程序产生的core文件

### 常用交互命令一览

| 名称       |  含义描述                            |
|:-----------|:-------------------------------------|
|   file     |   装入想要调试的可执行文件           |
|   run      |   执行当前被调试的程序  简写 r       |
|   kill     |   终止正在调试的程序                 |
|   step     |   执行一行源代码并且进入函数内部     |
|   next     |   执行一行源代码但不进入函数内部 简写 n  |
|   break    |   在代码里设置断点，这将使程序执行到此处时被挂起 |
|   print    |   打印表达式或变量的值，或打印内存中某个变量开始的一段连续区域的值，还可用于对变量赋值 |
|   display  |   设置自动显示的表达式或变量，当程序停住或在单步跟踪时，这些变量会自动显示其当前值 |
|   list     |   列出产生执行文件的源代码的一部分 |
|   quit     |   退出gdb |
|   watch    |   使用户能监视一个变量的值而不管其何时被改变 |
|   backtrace|   回溯跟踪    简写 bt |
|   frame n  |   定位到发生错误的代码段，n为backtrace命令的输出结果中的行号 |
|   examine  |   查看内存地址中的值 |
|   jump     |   使程序跳转执行 |
|   signal   |   产生信号量 |
|   return   |   强制函数返回 |
|   call     |   强制调用函数 |
|   make     |   使用户不退出gdb就可以重新产生可执行文件 |
|   shell    |   使用户不离开gdb就能执行Linux的shell命令 |
|   help     |   请求帮助 |

其中 gdb 常用交互命令如下:

| 简称 | 全称 |
|:-----|:-----|
| b    | break |
| c    | continue |
| r    | run   |
| l    | list  |
| p    | print |

[部分交互命令说明](部分交互命令说明.md)


### 快速使用

- 关于断点操作
  ```sh
    b 25                // 在 25 行处设置断点
    info break          // 查看断点信息
    dis 1               // 使断点 1 无效
    ena 1               // 使断点 1 有效
    del 1               // 删除断点 1
  ```

- 变量查看
  ```sh
    info local          // 查看本地变量表
    info args           // 查看输入参数
    disp avg            // 程序执行过程中，对 avg 进行实时观察
    undisp 1            // 取消对编号为 1 的成员的观察
  ```

- 对堆栈的操作
  ```sh
    bt                  // 堆栈回溯，即列举中堆栈帧
    f 1                 // 切换到第 1 帧堆栈
    up/down             // 在堆栈中上下移动
  ```

- 单步执行操作
  ```sh
    s
    n
    u
    c
    ret                 // 从当前函数立即抬，并给出返回值
    j 105               // 跳到第 105 行
  ```

- 对多线程的操作
  ```sh
    info threads        // 获得多线程列表
    thread 2            // 切换到线程 2
  ```
  
- 为参数指定别名
  ```sh
    set $vd = my_model->dataset->vector->data
    p *$vd@10
    set $ptr=&x[3]
    p *$ptr=8
    p *($ptr++)
  ```

### 利用 bt 对堆栈的追踪示例

很多程序分析技巧就是跳入堆栈中，从一个个的函数的堆栈中追踪因果关系。

示例伪码
```c
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
```
通过 backtrace 命令可以查看该程序堆栈帧如下:
```sh
    #0 0x00413bbe in agent_address (agent_number=312) at addresses.c:100
    #1 0x004148b6 in get_agents() at addresses.c:163
    #2 0x00404f9b in main(argc=1,argv=0x7fffffffe278) at addresses.c:227
```
堆栈顶端是 0 帧，帧号后的十六进制是一个地址，被调函数返回的时候，程序执行将返回这个地址。

地址后面是函数名、入参，以及当前执行到的源代码行号。

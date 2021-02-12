
bat 脚本要使用 ANSI 编码


## 注释

有两种方式，:: 和 REM

一个脚本应该包含的要素信息可以通过注释写出，如下:
```
    ::  脚本必要的注释信息
    ::  脚本的创建时间与最后修改时间
    ::  脚本的创建者
    ::  脚本的用途
    ::  脚本创建者的联系方式
    ::  脚本输出是否保存及其保存位置
```


## 脚本入参

脚本名本身由 `%0` 表示， `%1` 表示传递给脚本的第一个参数，`%2` 表示传递给脚本的第二个参数。依次类推，直到 `%9` 。

如果超过 9 个参数，多余的参数会保存在一个特殊的变量 `%*` 中，通过 `shift` 可以查看多余的实参。如果不带参数运行 `shift` ，则脚本会左移一个。

从第三个参数起开始移位，%0,%1,%2 不受影响
```
    shift /3
```


## 错误码

环境变量 `errorlevel` 可以追踪最近使用命令的退出代码。如果命令正常执行，则为0，如果错误执行，会返回一个非0值。

| 错误码 |   描述   |
|:------:|:--------:|
|  1     | 通常错误 |
|  2     | 执行错误 |
| -2     | 算数错误 |

```
    if "%ERRORLEVEL%"=="2" echo "An error occurred!"
```


## 转义(或换码)

对于一些保留字符(`@ < > & / ^`)要使用 ^ 进行换码，如 2^3 需要换码为 2^^3


## 设置环境变量

查看所有环境变量
```
    set
```

查看指定环境变量
```
    set | findstr TEMP
    set TEMP
```

设定环境变量
```
    set myVar=HelloWorld
```

取消环境变量
```
    set myVar=
```

给变量追加内容
```
    set myVar=%myVar% Created by C
    set path=%path%;D:\editplus
```

永久设置环境变量
```
    setx DESKTOP C:\Users\lb\Desktop
```

注意，通过 `set` 设置环境变量时，= 等号两边不能有空格。

示例脚本: [set.bat](learn/set.bat)


## 计算

算术操作是使用 `set` 命令(带参数/A)进行的。

bat 支持的运算及运算符优先级: <strong>模数运算 > 乘除运算 > 加减运算</strong>
    
示例脚本: [compute.bat](learn/compute.bat)


## 命令结链

| 符号 |     语法     | 描述 |
|:----:|:------------:|:-----|
| &    | cmd1 & cmd2  | 执行命令1，之后执行命令2 |
| &&   | cmd1 && cmd2 | 如果命令1成功完成，则执行命令2 |
| ||   | cmd1 || cmd2 | 只有命令1没有成功完成时才执行命令2 |

使用示例

进入指定目录，之后获取一份以日期排序的目录列表
```
    cd c:\working\docs & dir /0:d
```

只要current.log文件存在，就移动它
```
    dir c:\working\docs\current.log && move current.log d:\history\logs
```     
结链的做法可以使得脚本不会输出错误信息。


## 命令分组

只有最后一条命令 netstat -a 的信息会输入到log中
```
    hostname & ipconfig & netstat -a > current_config.log
``` 

3条命令都会输入到log中
```
    (hostname & ipconfig & netstat -a) > current_config.log
```

只有前两条都成功执行，后一条命令才得以执行
```
    (hostname & ipconfig) && (netstat -a > current_config.log)
```


## 重定向

将标准错误定向到标准输出，将标准输出定向到 diskerrors.txt文件，即标准错误，标准输出都定向到 diskerrors.txt 文件
```
    chkdsk /r > diskerrors.txt 2>&1
```


## 控制语句 - 判断

bat 支持三种 if 语句，分别是: <strong>if 语句</strong>、<strong>if not 语句</strong>、<strong>if ... else 语句</strong>，用法如下:

<pre>
    <strong> if condition (statement1) [else (statement2)] </strong>
    <strong> if condition (statement) </strong>
    <strong> if not condition (statement1) [else (statement2)] </strong>
    <strong> if not condition (statement1) </strong>
    <strong> if not errorlevel 0 (echo An error has occurred!) & (goto :EXIT) </strong>
</pre>

示例
```
    if stringA == stringB statement
    if "%varA%%" == "%varB%" statement
```
字符串比较区分大小写，除非指定 /i 参数
```
    if /I "%1" == "a" (echo A) else (echo is not A)
```

利用 if 命令也可以检查变量是否存在

<pre>
    <strong> if defined </strong>
    <strong> if not defined </strong>
</pre>

示例
```
    if not "%varA%" == "string" statement
```

更高级的相同性测试

| 运算符  |  描述  |
|:-------:|:-------|
| equ     | 检查两个值是否相等 |
| neq     | 检查两个值是否不相等 |
| lss     | 检查两个值之间的小于关系 |
| leq     | 检查两个值之间的小于等于关系 |
| gtr     | 检查两个值之间的大于关系 |
| geq     | 检查两个值之间的大于等于关系 |

示例
```
    if "%varA%" equ "%varB%" (echo The values match!)
```

示例脚本: [if.bat](learn/if.bat)


## 控制语句 - 迭代

最基本的 for 语句形式
```
    for iterator do (statement)
```

`iterator` 通常包含一个初始化变量和一组需要反复执行的元素，比如需要遍历的一组文件或某范围内的一组值。

使用初始化变量时，应该注意如下几点:
- iterator 变量只存在于 for 循环的上下文中
- iterator 变量名必须在 a~z 或者 A~Z 的范围内，比如 %%A, %%B, %%C
- iterator 变量名是大小写敏感的，也就是说，%%A 与 %%a 是不同的

其他 for 语句形式

| 迭代用途 | 语法格式 |
|:--------:|:---------|
| 文件集合 | for %%variable in (fileSet) do statement |
| 目录集合 | for /D %%variable in (directorySet) do statement |
| 子目录中的文件 | for /R [path] %%variable in (fileSet) do statement |
| 遍历一系列的值 | for /L %%variable in (stepRange) do statement |
| 分析文本文件、字符串以及命令输出 | for /F ["options"] %%variable in (source) do statement |

#### for 用法

##### 遍历一系列的值
```
    for /L %%variable in (start, step, end) do (statement)
```

##### 在成组的文件中迭代执行
```
    for %%variable in (fileSet) do (statement)
```
fileSet 可以是:
- 通过文件名指定的单独的文件，比如 MyFile.txt
- 通过文件名通配符指定的一组文件，比如 *.txt
- 通过多个文件名（使用空格分隔）指定的多个或多组文件，比如 *.txt *.rtf *.doc

##### 在目录中迭代执行
```
    for /D %%variable in (directorySet) do (statement)
```
会对 directorySet 的下的子目录进行处理，但不对这些子目录的目录进行处理。如果需要对子目录的目录进行处理，可以使用 `for /r` 循环。

##### 分析文件的内容与输出
```
    for /F ["options"] %%variable in (file-set) do (statement)
```
file-set 为一个或多个文件名，对每个文件打开、读取并进行处理，根据情况将每行解析成零个或更多的符号。可以对找到的符号字符串调用 for 循环。

在处理完一个文件之后，会继续调用下一个文件处理。

optons 的关键字及含义:

| 关键字  | 描述  |
|:--------|:------|
| eol=c   | 设置行尾注释字符，行尾注释字符后的所有数据都被命令shell看成注释。只能设置一个行尾注释字符 |
| skip=n  | 设置文件起始处跳过的行数 |
| delims=xxx | 设置各字段之间的分隔符，缺省为制表符或空格 |
| tokens=x,y,m-n | 为每一源行设置令牌字段，如果以a或A作为起始的迭代变量，则至多可以指定26个令牌。缺省时，只对第一个令牌进行检查 |
| usebackq | 激活选项。对文件名使用双引号，对命令使用反引号，对字符串使用单引号 |

> 使用分析一:
```
    FOR /F "eol=; tokens=2,3* delims=, " %i in (myfile.txt) do @echo %i %j %k
```
该命令会分析 myfile.txt 中的每一行，忽略以分号";"打头的那些行，用逗号或空格分隔符号，将分隔后每行中的第二个和第三个符号传递给 for 函数体。

请注意，此 for 函数体的语句引用 `%i` 来获得第二个符号，引用 `%j` 来获得第三个符号，引用 `%k` 来获得第三个符号后的所有剩余符号。

对于带有空格的文件名，需要用双引号将文件名括起来。为了用这种方式来使用双引号，还需要使用 `usebackq` 选项，否则，双引号会被理解成是用作定义某个要分析的字符串的。

`%i` 在 for 语句中显式声明，`%j` 和 `%k` 是通过 `tokens=` 选项隐式声明的。可以通过 `tokens=` 一行指定最多 26 个符号，**只要不试图声明一个高于字母 "z" 或"Z" 的变量**。

请记住，FOR 变量是单一字母、分大小写和全局的变量。而且，不能同时使用超过 52 个。

> 使用分析二:
```
    for /F ["options"] %%variable in ("string") do (statement)
```
还可以在相邻字符串上使用 `FOR /F` 分析逻辑，方法是，**用单引号将括号之间的 file-set 括起来。这样，该字符串会被当作一个文件中的一个单一输入行进行解析**。

> 使用分析三:
```
    for /F ["options"] %%variable in ('command') do (statement)
```
可以用 `FOR /F` 命令来分析命令的输出。方法是，**将括号之间的 set 变成一个反括字符串。该字符串会被当作命令行，传递到一个子 CMD.EXE，其输出会被捕获到内存中，并被当作文件分析**。

示例
```
    FOR /F "usebackq delims==" %i IN (`set`) DO @echo %i
```

示例脚本: 

[for.bat](learn/for.bat)

[search.bat](usage/search.bat)


## 控制语句 - 跳转

goto 语句

bat 脚本严格意义上来说没有循环，但可以利用 goto 语句来实现循环控制。

示例脚本: [memusage.bat](usage/memusage.bat)


## 子程序和过程

过程: 在脚本中调用其他脚本，而又不会退出原脚本。通过 `call` 调用其他脚本。
```
    set Arg1=mailer1
    set Arg2=dc2
    set Arg3=web3
    call system-checks Arg1 Arg2 Arg3       ::为调用的脚本传入参数
```

示例脚本: [subroutine.bat](learn/subroutine.bat)

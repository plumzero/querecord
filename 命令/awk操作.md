
## 参考
- [AWK程序设计语言](https://awk.readthedocs.io/en/latest/index.html)

## awk 简要说明
- 功能及定义
    + 逐行对文本和数据进行处理，每行称为一个**记录**。作用对象是流，可以是文件流，标准输入流
      或其他命令输出流。
    + 记录中由指定分隔符切分开的每个小块，称为一个**字段**。
    + 为了更易理解，这里**扫描行**可以理解为与记录同义。
- 基本结构
  ```shell
  awk [cmd] 'BEGIN{...} pattern1{action1} pattern2{action2}...{actionx} END{...}' <文本>
  ```
- 命令选项
    + -F fs fs指定输入分隔符(默认空白字符)，如-F:, fs也可以是正则表达式或字符串
      ```shell
        awk -F: '{ print $NF; }' /etc/passwd
      ```
    + -v var=value 将外部变量 value 作为 awk 内部变量 var 传入 awk
      ```shell
        VAR=10000
        echo | awk -v VARIABLE=$VAR '{ print VARIABLE }'
      ```
      暂时没有找到将 awk 内部变量传出的方法，而将外部变量传入的情形平时又很少见，这个特性稍显
      鸡胁。
- 语句块
    + 共包括 3 个语句块，每个块内可以执行多条语句，语句之间使用 ; 分隔，语句按照先后顺序执行；
        + BEGIN 语句块常用于对流进行扫描之前的规则设定或变量定义；
        + 模式动作块用于对扫描到的每一行，根据模式 pattern 执行相应的动作；
        + END 语句块用于对执行的结果进行总结统计处理；
    + 模式动作块中 pattern 可以省略，也可以有多个模式动作语句。当有多个模式动作语句时相当于执行
      `if(pattern1){ action; } else if(pattern2){ action2; } ... else{ actionx; }`
    + pattern 可以有两种写法 `{if(pattern){action}}` 或 `/pattern/{action}`。当要设置一些变量(
      如进行标识或统计)以进行后续处理时，常使用前者；当只进行简单行扫描处理(如单纯打印)时，常使
      用后者。
    + awk 块以 ' ' 包裹，这会导致在其中无法使用命令行扩展，只能使用预定义内部变量。当然也可以使
     用 " " 包裹，这样就可以使用命令行扩展，但 awk 的初衷是处理格式文本的，且预定义内部变量基本
     可满足需要，所以并不建议那样做。
    + 3 个语句块，可任意舍取，pattern 也可以进行省略。BEGIN 块和 END 块最多只有一个，其余的作为
      模式动作块看待。如:
      ```shell
       awk '{U}'                            将{U}视作模式动作块
       awk 'U {V} W'                        将U {V} W视作模式动作块
       awk '{U} {V} {W}'                    将{U} {V} {W}视作模式动作块
       awk 'BEGIN{U} {V} {W}'               将{V} {W}视作模式动作块
       awk '{U} {V} END{W}'                 将{U} {V}视作模式动作块
       awk 'BEGIN{U} {V} {W} {X} END{Y}'    将{V} {W} {X}视作模式动作块
      ```
- 内置变量
  ```shell
    $0    当前扫描行的整行内容；
    $n    当前记录的第n个字段，比如n为1表示第一个字段，n为2表示第二个字段；
    FS    字段分隔符（默认是任何空格）；
    RS    记录分隔符（默认是一个换行符）；
    NF    表示字段数，在执行过程中对应于当前的字段数；
    NR    表示记录数，在执行过程中对应于当前的行号；
  ```
- 记录与字段
  一行就是一个记录，一个记录可以有多个字段。
  ```shell
    root:x:0:0:root:/root:/bin/bash
    daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
    bin:x:2:2:bin:/bin:/usr/sbin/nologin
  ```
  对于以上几行，如果 FS=":" RS="\n", 则 NF=7, RS=2

## 打印
- awk 支持两种方式的打印，分别是 print 和 printf。前者是简单的字符串输出打印，后者是类似于
  C 语言 printf 函数的支持格式化处理的输出打印。
- print 打印时如果字符串之间以空格隔开时，打印展示为无缝粘接:
  ```shell
    # awk -F: '{ print $2 $3 "hello" }' /etc/passwd
    x0hello
    x1hello
    ...
  ```
  如果字符串之间以逗号 , 隔开时，打印展示为空格隔开:
  ```shell
    # awk -F: '{ print $2, $3, "hello" }' /etc/passwd
    x 0 hello
    x 1 hello
    ...
  ```
- printf 格式化打印示例
  ```shell
    # awk -F: '{ printf("%4d, %s\n", $3, $5); }' /etc/passwd
     0, root
     1, bin
     2, daemon
     3, adm
     4, lp
     5, sync
     6, shutdown
     7, halt
     8, mail
    11, operator
    12, games
    14, FTP User
    99, Nobody
   192, systemd Network Management
   ...
  ```
- NF 和 NF 意思不同，前者表示最后一个字段，后者表示当前行被分隔符切开后的字段数
  ```shell
    print NF;    打印当前扫描行的字段数
    print $(NF); 命令扩展，打印第 NF 个字段的内容， $(NF-1) 表示倒数第二个字段的内容
  ```

## 语法与运算
- 支持语法
  ```shell
    if else
    for
    do while
    while
    break
    continue
    in
    数组
  ```
  基本上使用 if else 就可满足一般处理需要。 
- 算术运算符
  ```shell
    + -         加，减
    * / %       乘，除与求余
    + - !       一元加，减和逻辑非
    ^           求幂
    ++ --       增加或减少，作为前缀或后缀
  ```
  注意: 所有用作算术运算符进行操作，操作数自动转为数值，所有非数值都变为0
- 赋值运算符
  ```shell
    =           赋值
    +=          加
    -=          减
    *=          乘
    /=          除
    %=          余
    ^=          幂
  ```
- 逻辑运算符
  ```shell
    ||          或
    &&          与
  ```
- 关系运算
  ```shell
    <
    <=
    >
    >=
    !=
    ==
  ```
  注意: > < 可以作为字符串比较，也可以用作数值比较，关键看操作数如果是字符串就会转换为字符
  串比较。两个都为数字才转为数值比较。字符串比较：按照ASCII码顺序比较。
- **其它运算符**
  ```shell
    $           字段引用
    空格        字符串连接符
    ?:          三目运算
    in          数组中是否存在某键值
  ```
  
## 正则(重要)
- 正则运算符
  ```shell
    + ~           匹配
    + !~          不匹配
  ```
- 支持扩展形式的正则表达式，可以无拘束使用
  ```shell
    ^           以某字符串开始的行
    $           以某字符串结束的行
    \<          以某字符串开始的单词
    \>          以某字符串结束的单词
    .           任意单个字符
    *           >=0, 贪婪匹配
    +           >=1
    ?
    []
    [^]
    ()          子表达式组合，如 /(rool)+/, 表示一个或多个 rool 的组合
    |
    \           转义字符
    x{m}        匹配重复 m 次的 x 
    x{m,}       匹配重复 m 次以上(包括 m 次)的 x，如 /\(root\)\{2,\}/
    x{m, n}     匹配重复至少 m 次，至多 n 次的 x，使用这个时 awk 需要指定 -posix 或 --re-interval 参数
  ```

## 其他常用特性
- next 的使用
    + 循环逐行匹配，如果遇到 next，就会跳出当前记录，执行下一条记录；
    + 可用于条件判断，也常用于行的合并；
- 循环控制语句**支持基于范围的 for 循环打印**
    + 包括条件判断语句，while 循环语句，for 循环语句，do...while 循环语句几种主要语句，其用法
      和C语言相似
    + 不过for还有另外一种格式用法:
      ```shell
        for(变量 in 数组)
          {变量在数组中为真}
      ```
      这种方式的打印输出结果是无序的。
- 数组的使用
    + awk 数组不必提前声明，也不必声明大小;
    + 数组元素用 0 或空字符串来初始化，这根据上下文而定；
    + 特别注意，**awk 数组索引默认以 1 开始**，这与C语言数组不同；
    + 可以使用数字或字符串作数组索引；
    + 遍历数组
      ```shell
        awk 'BEGIN{num[0]="apper"; num[1]="pear"; for(i=0;i<2;i++){print num[i];}}'
        awk 'BEGIN{color["red"]=1; color["green"]=2; color["blue"]=3; for(item in color) {print item, color[item];}}'
      ```
    + 分隔字符串成数组
      ```shell
        awk 'BEGIN{str="red green blue white black"; clen=split(str, color, " "); for(k=1; k<=clen; k++){print k, color[k];}}'
      ```
      将str以空格作定界符分隔，存入color数组中，有序打印
    + 数组是否存在某键值
      ```shell
        awk 'BEGIN{color["red"]=1; color["green"]=2; color["blue"]=3; if ("grey" in color){print "exist";}else{print "not exist";}}'
      ```
    + 删除数组某键值
      ```shell
        awk 'BEGIN{color["red"]=1; color["green"]=2; color["blue"]=3; if ("green" in color){delete color["green"];}; for(item in color){print item, color[item];}}'
      ```

## awk 常用命令示例
- `ifconfig enp0s3 | awk 'BEGIN{FS="[[:space:]]+";} NR==2{ print $3; }'`
    获取 ip 地址
- `awk 'BEGIN{ FS="[:/]+"; } { print $1 " " $(NF); }' /etc/passwd`
    以 : 和 / 作为分隔符查找
- `awk '{ if (NR >= 5 && NR <= 10 ){ print $1; } }' /etc/passwd`
    查看文件第 5 行到第 10 行的内容
- `awk '/^root/{print "I am root"}/^daemon/{print "I am daemon"}{print "I am other"}' /etc/passwd`
    简单匹配
- `netstat -an | awk '/^tcp/{ ++s[$NF]; } END{ for (a in s) print a, s[a]; }'`
    查看服务器所有的连接状态并汇总
- `awk 'BEGIN{ FS=":"; } { print ($0 ~ /^s/) ? $1 : "It is not match!"; }' /etc/passwd`
    找到以 s 开头的用户，打印完整用户名，否则打印 It is no match!
- `awk 'NR%2==1{ next; } { print $0; }' /etc/passwd`
    打印偶数行
- `awk '/^web/{ T=$0; next; } { print T":\t"$0; }' web.txt`
    + 若记录以 web 开头，T 保存此记录，跳出当前记录执行下一行；
    + 若下一行不以 web 开头，则执行 { print T":\t"$0; }，T是之前保存的变量
- `ps -ef | grep "stunnel" | awk '$0 !~ /grep/ && $8 ~ /stunnel\>/{ print $0; }'`
    查看进程是否存在
- `ps -ef | grep stunnel | awk '$0 !~ /grep/{ print $2; }' | xargs kill -9`
    杀掉指定进程
- `ps -ef | grep xxx | awk '{ print $1; }' | xargs -I {} kill -9 {}`
    杀掉一串进程
- `free | awk '/Mem/{printf("RAM Usage: %.2f %%\n"), $3 / $2 * 100}'`
    内存占用检查
- `nm test.so | cut -d" " -f3 | awk '$0 ~ /\<V2x/ && $0 !~ /url\>/{ print $0; }'`
    匹配以空格分隔的第 3 个字段，且该字段以 V2x 开头，但不以 url 结尾
- `awk '/^sslVersion/ || /^output/ || /^pid/ || /^cert/ || /^key/ { print "    "$0; }' test.conf`
    一次性匹配文件中的多个行
- `awk '$0 ~ /DUMP/{ print $0; }' test.log | cut -d: -f 3 | sed 's/|//g'| sed 'N;N;N;N;s/\n//g'`
    行处理文件
- `ls -al | grep '^-'  | awk '{ print $(NF); }' | sort -r | head -n $(($(ls -al | grep '^-' | wc -l) - 180))`
    打印当前目录下按规定排序后的常规总文件数量的除后面 180 个文件的前面的文件
- `ls -al './v2x/log' | grep '^-'  | awk '{ print $(NF) }' | sort -r | tail -n +161 | xargs -I {} rm -rf {}`
    只保留当前目录下按规定排序后的前 160 个常规文件
- `openssl x509 -text -noout -in rsa.crt | awk 'BEGIN{ pubkey=""; flag=0; } { if($0 ~ /\<Modulus:/){ flag=1; }else if($0 ~ /\<Exponent:/){ flag=0;}else if(flag==1){ pubkey=pubkey""$0; } } END{ print pubkey; }'| sed 's/\s*//g'`
    打印证书的公钥部分，并合并成一行字符串
- `find . | xargs -I {} ls -al {} | grep "^-" | awk '{ print $NF; }' | xargs -I {} file -i {} | grep "charset"`
    查看当前路径下所有普通文件的编码格式
- `find . | xargs -I {} ls -al {} | grep "^-" | awk '{ print $NF; }' | xargs -I {} dos2unix {}`
    将该目录下所有常规文件转为 unix 格式
- `sed 's/^\s*//' bookmarks.json | awk '/^\"title\"|^\"uri\"/{ print $0; }'`
    去掉空格，输出以 "title" 或 "url" 开头的行
- `awk '/Signed data/{ print $0; }' test.txt | cut -d: -f2 | sed 's/\s*//g' | awk '{ print length($0)"\n"$0; }'`
    找出包含 Signed data 的行，以 : 分隔成两部分，提取第二部分，去掉所有空格，打印之后的长度与内容
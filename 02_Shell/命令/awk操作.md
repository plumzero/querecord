
## 参考
- [Linux命令大全 awk命令](https://man.linuxde.net/awk)
- [AWK程序设计语言](https://awk.readthedocs.io/en/latest/index.html)
- [awk从放弃到入门](http://www.zsythink.net/archives/tag/awk/)

## 简要说明
- 功能及定义
    + 逐行对文本和数据进行处理，每行称为一个**记录**。作用对象是流，可以是文件流，标准输入流
      或其他命令输出流。
    + 记录中由指定输入分隔符切分开的每个小块，称为一个**字段**。
- 一行就是一个记录，一个记录可以有多个字段。
  ```shell
    root:x:0:0:root:/root:/bin/bash
    daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
    bin:x:2:2:bin:/bin:/usr/sbin/nologin
  ```
  对于以上几行，如果分隔符是 RS="\n" FS=":", 则记录数 RS=2, 每个记录的字段数 NF=7
- 说明
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
- 分隔符
    + awk 的分隔符分为两种，输入分隔符(FS)和输出分隔符(OFS)，前者用于对每一条记录进行分割，后者
      用于在进行屏幕输出时的分隔，二者均以空格作为默认分隔符。
    + 输入分隔符可以通过命令选项的 -F 指定:
      ```shell
        awk -F: '{ print $NF; }' /etc/passwd
      ```
      还可以通过设置内置变量的方式指定:
      ```shell
        awk -v FS=':' '{ print $NF; }' /etc/passwd
      ```
      有时可能需要指定多个分隔符，可以这样:
      ```shell
        awk 'BEGIN{ FS="[:/]+"; } { print $1 " " $(NF); }' /etc/passwd
      ```
    + 输出分隔符可以通过设置内置变量的方式指定:
      ```shell
        awk -v FS=':' -v OFS=' 的默认登录shell是 ' '{ print $1, $NF; }' /etc/passwd
      ```
    + 通常很少用到输出分隔符。如无特别说明，后续的分隔符均指输入分隔符。
   
## 变量   
- 内置变量
  ```shell
    $0    当前扫描行的整行内容；
    $n    当前记录的第n个字段，比如n为1表示第一个字段，n为2表示第二个字段；
    FS    输入字段分隔符(默认是空白字符)；
    OFS   输出字段分隔符(默认是空白字符)
    RS    输入记录分隔符(默认是换行符)；
    ORS   输出记录分隔符(默认是换行符)，输出时用指定符号代替换行号；
    NF    表示字段数，在执行过程中对应于当前的字段数；
    NR    表示记录数，在执行过程中对应于当前的行号；
  ```
  $NF 和 NF 意思不同，前者表示最后一个字段，后者表示当前行被分隔符切开后的字段数
  ```shell
    print NF;    打印当前扫描行的字段数
    print $(NF); 命令扩展，打印第 NF 个字段的内容， $(NF-1) 表示倒数第二个字段的内容
  ```
- 自定义变量
    + 自定义变量的方式有两种，一种是通过 -v 进行定义，还有一种是在程序中直接定义；
    + 通过 -v 定义:
      ```shell
        awk -v myVar="Hello World" 'BEGIN{ print myVar; }'
      ```
      这种定义方式也可以引入外部变量:
      ```shell
        awk -v myBash=$BASH 'BEGIN{ print myBash; }'
      ```
    + 在程序中直接定义:
      ```shell
        awk 'BEGIN{ myVar="Hello World"; print myVar; }'
      ```
      
## 打印
- awk 支持两种方式的打印，分别是 print 和 printf。前者是简单的字符串输出打印，后者是类似于
  C 语言 printf() 函数的支持格式化处理的输出打印。
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
    $           对分隔后字段的引用。注意: awk 中对内置变量和自定义变量都是直接使用变量名，不加 $
    空格        字符串连接符
    ?:          三目运算
    in          数组中是否存在某键值
  ```
  
## 模式匹配与正则表达式
- 设定某个条件，只有当扫描记录满足该条件时才进行处理，这个过程就是模式匹配。
  ```shell
    awk -F: 'NF==7 { print $0; }' /etc/passwd       # 只打印字段数为 7 的记录
    awk -F: '$1=="root" { print $0; }' /etc/passwd  # 只打印用户名为 root 的记录
  ```
  上面的模式匹配也称为**关系运算符模式匹配**。
- 将正则表达式作为条件进行扫描处理，这种匹配方式也称为**正则模式匹配**。
    + awk 支持扩展正则表达式，可以无拘束使用
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
      与格式化打印结合使用示例:
      ```shell
        awk -F: 'BEGIN{ printf("%-10s%-10s\n", "用户名", "用户ID"); } /^root/{ printf("%-10s%-10s\n", $1, $3); }' /etc/passwd
      ```
      注意字符转义，找出使用 /bin/bash 作为登录 shell 的用户:
      ```shell
        awk '/\/bin\/bash$/{ print $0; }' /etc/passwd
      ```
- 关系运算符模式可以通过运算符 ~ 或 !~ 与正则模式配合使用
  ```shell
    + ~           匹配
    + !~          不匹配
  ```
  其含义可以理解为 == 或 !=, 示例如下:
  ```shell
    awk -F: '$NF ~ /^\/bin\/bash$/{ print $0; }' /etc/passwd    # 打印最后一个字段内容为 "/bin/bash" 的行
  ```
- 行范围模式
    + 略

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
    + awk 数组不必提前声明，也不必声明大小，直接为数组元素赋值即可;
    + 数组元素用 0 或空字符串来初始化，这根据上下文而定；
    + 特别注意，**awk 数组索引默认以 1 开始**，这与C语言数组不同；
    + **awk 的数组是关联数组**，可以使用数字或字符串作数组索引；
    + awk 数组的一个常见用法是统计某字符串的出现次数；
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
    + 通过 in 来判断数组是否存在某键值
      ```shell
        awk 'BEGIN{color["red"]=1; color["green"]=2; color["blue"]=3; if ("grey" in color){print "exist";}else{print "not exist";}}'
      ```
    + 通过 delete 删除数组某键值
      ```shell
        awk 'BEGIN{color["red"]=1; color["green"]=2; color["blue"]=3; if ("green" in color){delete color["green"];}; for(item in color){print item, color[item];}}'
      ```
      也可以使用 delete 删除整个数组。

## 常用内置函数
- 算数函数
    + rand srand int
      ```shell
        awk 'BEGIN{ srand(); print rand(); }'
        awk 'BEGIN{ srand(); print int(100 * rand()); }'
      ```
- 字符串函数
    + 使用 gsub 函数替换某些文本
      ```shell
        awk -F: '{ gsub("o", "O", $1); print $0; }' /etc/passwd # 第一个字段中的所有小写 o 替换为大写 O
        awk -F: '{ gsub("[a-d]", "6"); print $0; }' /etc/passwd # 将 a b c d 替换为 6
      ```
      gsub 省略第三个参数时，默认是 $0 。
      gsub 执行记录内或指定字段内的全局替换。
    + 使用 sub 函数替换文本
      ```shell
        awk -F: '{ sub("o", "O", $1); print $0; }' /etc/passwd  # 只替换第一个字段中第一次出现的 o
      ```
      与 gsub 不同，sub 函数只会替换指定范围内第一次匹配到的符合条件的字符，这也是它与 gsub 的唯一
      不同之处。
    + length 函数获取字符串的长度
      ```shell
        awk -F: '{ print length($1); }' /etc/passwd # 打印第一个字段字符串的长度
        awk -F: '{ print length(); }' /etc/passwd   # 打印当前记录字符串的长度
      ```
      length 函数可以省略传入的参数，此时默认参数为 $0 。
    + 使用 index 函数获取指定字符串第一次出现在整个字符串中的位置
      ```shell
        awk '{ print index($0, "x"); }' /etc/passwd
      ```
      字符串不存在时返回 0。
    + 通过 split 函数将字符串按指定分隔符分割，并存入数组
      ```shell
        awk -v ts="大娃:二娃:三娃" 'BEGIN{ split(ts, huluwa, ":"); for(i in huluwa){ print huluwa[i]; }}'
      ```
      函数返回生成数组的长度。
      
    
## 常用命令示例
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
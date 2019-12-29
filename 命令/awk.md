
可以参考：
    AWK程序设计语言
    https://awk.readthedocs.io/en/latest/index.html

功能：
  逐行对文本和数据进行处理，每行称为一个记录。作用对象是流，可以是文件流，标准输入流或其他命令输出流。
基本结构：
  awk [cmd] 'BEGIN{...} pattern1{action1} pattern2{action2}...{actionx} END{...}' <文本>
命令选项：
  -F fs	fs指定输入分隔符（默认空白字符），如-F:, fs也可以是正则表达式或字符串
    awk -F: '{ print $NF; }' /etc/passwd
  -v var=value 将外部变量 value 作为 awk 内部变量 var 传入 awk
    VAR=10000
    echo | awk -v VARIABLE=$VAR '{ print VARIABLE }'
语句块：
  1. 共包括 3 个语句块，每个块内可以执行多条语句，语句之间使用 ; 分隔，语句按照先后顺序执行；
     BEGIN 语句块常用于对文件进行扫描之前的规则设定或变量定义；
     模式动作块用于对扫描到的每一行，根据 pattern 执行相应的动作；
     END 语句块用于对执行的结果进行总结统计处理；
  2. 模式动作块中 pattern 可以省略，也可以有多个模式动作语句。当有多个模式动作语句时相当于执行
     if(pattern1){ action; } else if(pattern2){ action2; } ... else{ actionx; }
  3. pattern 可以有两种写法 {if(pattern){action}} 或 /pattern/{action}。当要设置一些变量（进行
     标志或统计）以进行后续处理时，常使用前者；当只进行简单行扫描处理时，常使用后者。
  4. awk 块以 ' ' 包裹，这会导致在其中无法使用命令行扩展，只能使用预定义内部变量。当然也可以使
     用 " " 包裹，这样就可以使用命令行扩展，但 awk 的初衷是处理格式文本的，且预定义内部变量基本
     可满足需要，所以并不建议那样做。
  5. 3 个语句块，可任意舍取，pattern 也可以进行省略。BEGIN 块和 END 块最多只有一个，其余的作为
     模式动作块看待。如：
       awk '{U}'							将{U}视作模式动作块
       awk 'U {V} W'						将U {V} W视作模式动作块
       awk '{U} {V} {W}'					将{U} {V} {W}视作模式动作块
       awk 'BEGIN{U} {V} {W}'				将{V} {W}视作模式动作块
       awk '{U} {V} END{W}'				    将{U} {V}视作模式动作块
       awk 'BEGIN{U} {V} {W} {X} END{Y}'	将{V} {W} {X}视作模式动作块
内置变量：
  $0    这个变量包含执行过程中当前行的文本内容；
  $n    当前记录的第n个字段，比如n为1表示第一个字段，n为2表示第二个字段；
  FS    字段分隔符（默认是任何空格）；
  RS    记录分隔符（默认是一个换行符）；
  NF    表示字段数，在执行过程中对应于当前的字段数；
  NR    表示记录数，在执行过程中对应于当前的行号；
记录与字段: 
  一行就是一个记录，一个记录可以有多个字段。
    root:x:0:0:root:/root:/bin/bash
    daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
    bin:x:2:2:bin:/bin:/usr/sbin/nologin
  对于以上几行，如果 FS=":" RS="\n", 则 NF=7, RS=2
支持语法：
    if else
    for
    do while
    while
    break
    continue
    in
    数组
  基本上使用 if else 就可满足一般处理需要。 
对于 NF 的打印：
  print NF;    打印当前扫描行的字段数
  print $(NF); 命令扩展，打印第 NF 个字段的内容， $(NF-1) 表示倒数第二个字段的内容
正则运算符：
    ~           匹配
    !~          不匹配
正则表达式：
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
算术运算符：
    + -         加，减
    * / %       乘，除与求余
    + - !       一元加，减和逻辑非
    ^           求幂
    ++ --       增加或减少，作为前缀或后缀
  注意：所有用作算术运算符进行操作，操作数自动转为数值，所有非数值都变为0
赋值运算符：
    =           赋值
    +=          加
    -=          减
    *=          乘
    /=          除
    %=          余
    ^=          幂
逻辑运算符：
    ||          或
    &&          与
关系运算：
    <
    <=
    >
    >=
    !=
    ==
  注意：> < 可以作为字符串比较，也可以用作数值比较，关键看操作数如果是字符串就会转换为字符串比较。两个都
  为数字才转为数值比较。字符串比较：按照ASCII码顺序比较。
其它运算符：
    $           字段引用
    空格        字符串连接符
    ?:          三目运算
    in          数组中是否存在某键值
next的使用：
  1. 循环逐行匹配，如果遇到next，就会跳出当前记录，执行下一条记录；
  2. 可用于条件判断，也常用于行的合并；
流程控制语句：
  1.包括条件判断语句，while循环语句，for循环语句，do...while循环语句几种主要语句，其用法和C语言相似
  2.不过for还有另外一种格式用法（无序输出）：
    for(变量 in 数组)
      {变量在数组中为真}
  3.其他语句还包括 break，continue，next，exit等
数组应用及数组相关函数：
  1. awk数组不必提前声明，也不必声明大小;
  2. 数组元素用0或空字符串来初始化，这根据上下文而定；
  3. 特别注意，awk数组索引默认以1开始，这与C语言数组不同；
  4. 可以使用数字或字符串作数组索引；
  5. 遍历数组
     awk 'BEGIN{num[0]="apper"; num[1]="pear"; for(i=0;i<2;i++){print num[i];}}'
     awk 'BEGIN{color["red"]=1; color["green"]=2; color["blue"]=3; for(item in color) {print item, color[item];}}'
  6. 分隔字符串成数组
     awk 'BEGIN{str="red green blue white black"; clen=split(str, color, " "); for(k=1; k<=clen; k++){print k, color[k];}}'
     将str以空格作定界符分隔，存入color数组中，有序打印
  7. 数组是否存在某键值
     awk 'BEGIN{color["red"]=1; color["green"]=2; color["blue"]=3; if ("grey" in color){print "exist";}else{print "not exist";}}'
  8. 删除数组某键值
     awk 'BEGIN{color["red"]=1; color["green"]=2; color["blue"]=3; if ("green" in color){delete color["green"];}; for(item in color){print item, color[item];}}'

	
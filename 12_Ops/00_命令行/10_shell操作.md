

### set

- `set +e`  指令传回值虽不等于0，不退出shell，继续向下执行
- `set -e`  若指令传回值不等于0，则立即退出shell
- `set +u`  当执行时使用到未定义过的变量，不显示错误信息，继续向下执行
- `set -u`  当执行时使用到未定义过的变量，则显示错误信息
- `set -o pipefail`     在管道连接的命令序列中，只要有任何一个命令返回非0值，则整个管道返回非0值，即使最后一个命令返回0
- `set -euo pipefail`   执行大型脚本必须带上这个

----
### dirname

去除一个文件名的非目录部分

- `cd /home/lb/public; dirname $PWD`    打印显示 /home/lb

----
### alias

- `alias la='ls -al'`       设置别名，注意=两边不能有空格
- `alias`                   查询所有别名
- `unalias la`              取消别名

----
### seq

序列化输出数字

- `seq 1 12`                输出 1 到 12
- `seq 1 2 12`              步进输出
- `seq -w 1 12`             定宽输出，不足补0
- `seq -f"%03g" 1 12`       格式(format)输出，不足补 0

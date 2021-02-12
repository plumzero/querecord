#!/usr/bin/bash

## bash 脚本风格写法示例

## 数值的操作
(( counter++ ))
counter=$(( counter + 2 ))

## 变量的声明
MY_VERSION=

## 进入父目录中
FDIR="$( cd "$( dirname "$pwd" )/.." && pwd )"		## 也可以写成 	FDIR="$(dirname $PWD)"
cd "$FDIR/"

## 在执行该命令之前判断该命令是否存在
if which ls &>/dev/null; then
	ls -al
fi

## 删除无用目录
[ -d $USELESSDIR ] && rm -rf $SUSELESSDIR

## 字符串是否相等
[[ ${str1} == ${str2} ]] && echo "equal"

## 在ubuntu上安装软件，如果系统不是ubuntu发行本，则执行脚本 install_mysf_on_centos.sh
if grep -qi "ubuntu" /etc/issue ; then
	apt-get install -y mysf
	if (( $? != 0 )); then
		apt-get update
		apt-get install -y mysf
	fi
else
	sh -x "$DIR/hack/install_mysf_on_centos.sh"
fi

## 静默下载，存储到本地，文件名为 /tmp/local-xxx
wget --quiet -O /tmp/local-xxx "https://xxx"
## 静默下载，文件和子目录存储到以 /usr/local/src/xxx 为前缀的目录下
wget --quiet "https://xxx" -P /usr/local/src/xxx

## set 的技巧使用: 如果执行命令不等于 0，不立即退出程序，而是获取错误日志并打印，之后再回置
set +e
my-exe
if (( $? != 0 )); then
	echo "error occured:"
	cat "$TMP/my.log"
fi
set -e

## 获取传入参数
for p in $@
do
	echo $1
	shift 1		## 此步骤可省略
done

## 字符串str中是否含有 "hello world"
if ! echo "$mystr" | grep -q "hello world" ; then
	echo "no, I have not."
fi

## 遍历数组
array=("one" "two" "three" "four")
idx=0
while [ ! -z "${array[idx]}" ]
do
	echo ${array[idx++]}
done

## 备份操作
## 将当前目录下的所有 xxx 文件备份为 xxx.bak
rename 's/$/\.bak/' *
## 将当前目录下的所有 xxx 文件备份为 xxx.bak
ls | xargs -i mv {} {}.bak	//备份目录下文件

## 大括号 {} 扩展
touch {1,2,4}.txt    ## 创建 1.txt 2.txt 4.txt 文件
touch {a..z}.txt     ## 创建 a.txt, b.txt, ..., z.txt 文件

## 快速生成数组
array=($(seq 1 5))  ## 或者写成 array=(`seq 1 5`)

for i in ${array[*]}
do
	echo $i
done

## 清除字符串前后空白字符
echo $(echo "  hello world   ")

## 正则表达式分组捕获
rename -n 's/(.*)/HEAD$1/' *

## 输入重定向操作
cat >file_name				## cat从标准输入获得数据，然后输出给file_name文件，按Ctrl+D键停止录入
cat >file_name <testfile	## cat从testfile获得输入数据，然后输出给文件file_name
	
## 输出重定向操作
cmd > file_name 2>&1		## 把cmd命令的标准输出和标准错误输出均重定向到file_name文件中

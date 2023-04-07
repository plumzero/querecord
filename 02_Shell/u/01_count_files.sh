
#!/usr/bin/env bash

#统计给定目录下的文件个数

#全局大变量
times=0		#用来记录当前第几次递归调用
files=0		#用来记录文件的个数

function readdir()
{
	#保存目标目录
	local location=$(pwd)
	((times++))
	echo "第 $times 次调用readdir!"
	pushd $location"/"$1
	
	#循环查找，递归调用
	for j in *
	do
		if [[ -f $j ]] ; then
			echo $j				#如果是文件，打印文件名
			((files++))			#如果是文件，变量files自加1
		elif [[ -d $j ]] ; then
			readdir $j			#进入新目录
		fi
	done
	
	popd
}

echo "请输入要统计文件个数的目录的绝对路径"
#保存用户输入的目录

read dirPath

if [[ -d $dirPath ]] ; then
	cd $dirPath
	for i in *
	do
		if [[ -f $i ]] ; then
			echo $i
			((files++))
		elif [[ -d $i ]] ; then
			readdir $i
		fi
	done
	echo "$dirPath 目录下共有 $files 个文件！"		#最后显示文件的个数
elif [[ -f $dirPath ]] ; then
	echo "$dirPath 是文件名！！请输入要统计文件个数的目录的绝对路径"
else
	echo "输入有误！！请输入要统计文件个数的目录的绝对路径"
fi

exit

#!/usr/bin/env bash

a=192
b=168
c=43
dset=(`seq 183 187`)


#ping 3 次，测试网络

isalive()
{ 
	ping -c 3 $1 >/dev/null
	if [ $? -eq 0 ] ; then			# 成功返回 0
		return 0
	else
		return 1
	fi
}

for d in ${dset[*]}
do
	isalive $a.$b.$c.$d
	if [[ $? -eq 0 ]]; then
		echo "=====" $a.$b.$c.$d "====="
	else
		echo "xxxxx" $a.$b.$c.$d "xxxxx"
	fi
done

exit 0


#!/bin/bash

# strace -tt ./程序
# 计算每个系统调用的占用时间耗费
# 统计大于 1000 的调用

printf '%-10s  %-20s  %-10s\n' "索引号" "系统调用名称" "占用时间(微秒)"
awk \
	'BEGIN{ FS="[.( ]+"; idx=0; last=0; now=0; flag=1; } 
	$2 ~ /^[0-9]/{
		now=$2; func_name_array[idx]=$3;
		if (flag==1) { time_consume_array[idx]=0; flag=0; } else { time_consume_array[idx]=now-last; }
		printf("%-10d%-20s%-10d\n", idx+1, func_name_array[idx], time_consume_array[idx]); 
		last=now;
		idx++; 
	} 
	END{
		printf("============= statics =============\n");
		for (i in time_consume_array)
		{
			if (time_consume_array[i] >= 1000)
				print i+1, func_name_array[i], time_consume_array[i];
		}
		printf("============= statics =============\n");
	}' $1


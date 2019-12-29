#!/bin/bash

year=2019
monthset=($(seq -f"%02g" 1 12))

# 生成大量日志测试文件，文件中填充 uuid ，格式如下(年月日.v2x.log):
# 20190901.v2x.log

echo "use bash shell please!!!"

for month in ${monthset[*]}
do
	echo "~~~ $month ~~~"
	case $month in
	"01"|"03"|"05"|"07"|"08"|"10"|"12")
		dayset=($(seq -f"%02g" 1 31))
		for day in ${dayset[*]}
		do
			touch $year$month$day.v2x.log
			cat /proc/sys/kernel/random/uuid >> $year$month$day.v2x.log
		done
	;;
	"04"|"06"|"09"|"11")
		dayset=($(seq -f"%02g" 1 30))
		for day in ${dayset[*]}
		do
			touch $year$month$day.v2x.log
			cat /proc/sys/kernel/random/uuid >> $year$month$day.v2x.log
		done
	;;
	"02")
		dayset=($(seq -f"%02g" 1 28))
		for day in ${dayset[*]}
		do
			touch $year$month$day.v2x.log
			cat /proc/sys/kernel/random/uuid >> $year$month$day.v2x.log
		done
	;;
	*)
		"illegal month"
	;;
	
	esac
done

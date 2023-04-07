
#!/bin/bash

pid=`ps -ef | awk '$0 ~ /diasmpugnss/ && $0 !~ /grep/ { print $2; }'`

echo pid = $pid

time_consumed=0
now_time=

last_memuse=0
memuse=0

while [ 1 ];
do
	memuse=$(grep 'VmRSS' /proc/$pid/status | awk '{ print $2; }')
	if [ $memuse -ne $last_memuse ]; then
		echo 
		echo "============================================================================="
		now_time=`date +"%Y/%m/%d %H:%M:%S"`
		echo  "now time: $now_time | time consumed: $time_consumed | VmRss: $memuse | diff: `expr $memuse - $last_memuse`"
		echo "============================================================================="
		time_consumed=0
	fi
	last_memuse=$memuse
	sleep 1
	time_consumed=`expr $time_consumed + 1`
	if [ $(($time_consumed % 2)) -eq 0 ]; then
		echo -n .
	fi
done

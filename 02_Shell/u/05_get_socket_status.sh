
#!/usr/bin/env bash

# 查看套接字（状态、数量变化、变化时间）
# 只统计 LISTEN ESTABLISHED TIME_WAIT 三种状态

# MAX TIME_WAIT  754

now_listen_count=0
now_established_count=0
now_time_wait_count=0

last_listen_count=0
last_established_count=0
last_time_wait_count=0

flag=0      # 1-上次是 .  2-上次是数据

consume_time=0

while [ 1 ];
do
    result_array=($(netstat -ant | awk 'BEGIN{ S["LISTEN"]=0; S["ESTABLISHED"]=0; S["TIME_WAIT"]=0; } \
    /^tcp\>/ { ++S[$NF]; }
    END{ printf("%d  %d  %d\n", S["LISTEN"], S["ESTABLISHED"], S["TIME_WAIT"]); }'))
            
    now_listen_count=${result_array[0]}
    now_established_count=${result_array[1]}
    now_time_wait_count=${result_array[2]}
    
    if [ $now_listen_count -ne $last_listen_count ] || 
       [ $now_established_count -ne $last_established_count ] || 
       [ $now_time_wait_count -ne $last_time_wait_count ]; then
        if [ $flag -eq 1 ]; then
            echo -n "   time consumed:" $consume_time "seconds"
            echo
        fi
        echo `date +"%H:%M:%S"` "LISTEN:" $now_listen_count   "ESTABLISHED:" $now_established_count   "TIME_WAIT:" $now_time_wait_count
        flag=2
    else
        if [ $flag -eq 2 ]; then
            consume_time=0;
        fi
        echo -n .
        flag=1
    fi
    
    last_listen_count=$now_listen_count
    last_established_count=$now_established_count
    last_time_wait_count=$now_time_wait_count
    
    let consume_time+=1
    sleep 1
done

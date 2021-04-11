
#!/usr/bin/env bash

files=()
sizes=()

function findbigger()
{
    for file in $(ls)
    do
        if [ -f $file ]; then
            size=$(ls -alb $file | awk '{ print $5 }')
            index=0
            echo ${#sizes[*]}
            for ele in ${sizes[*]}
            do
                echo size=$size ele=$ele
                if [ size -gt $ele ]; then
                    echo file=$file size=$size
                    sizes[$index]=$size
                    files[$index]=$file
                    break
                fi
            done
        else
            findbigger $file
        fi
    done
}


### 参数为前几个文件
main()
{
    ## 初始化
    for i in $(seq 1 $1)
    do
        files[${#files[*]}]=""
        files[${#files[*]}]=0
    done

    findbigger

    echo ${files[*]}
    echo ${sizes[*]}
}

main 3

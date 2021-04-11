
#!/usr/bin/env bash

### 向函数中传入数组
function printarray()
{
    array=$1
    ### 遍历数组
    for ele in ${array[*]}
    do
        echo -n $ele " "
    done
    echo   
}

function main()
{
    ### 定义数组
    array=("one" "two" "three")


    ### 打印数组长度: 方法一
    echo ${#array[*]}


    ### 打印数组长度: 方法二
    echo ${#array}


    ### 打印整个数组
    echo ${array[*]}


    ### 查看数组中某个值
    echo "array[2]="${array[2]}


    ### 向数组中添加元素
    array[${#array[*]}]="four"
    array+=("five" "six")


    ### 替换数组中某个值
    array[2]="3"


    ### 删除数组某个值
    unset array[3]

    printarray ${array[*]}
}

main

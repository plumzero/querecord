
#!/usr/bin/env bash

function callback1()
{
    echo "hello" $1 "in callback 1"
}

function callback2()
{
    echo "hello" $1 "in callback 2"
}

### $1 是函数, $2 是函数参数
function call()
{
    $1 $2
}

### 实现回调
function main()
{
    call callback1 "XYZ"

    call callback2 "123"
}

main

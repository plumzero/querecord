
#!/usr/bin/env bash

function d2u()
{
    for file in $1/*
    do
        if [ -f $file ]; then
            
            x=$(echo $(file $file) | grep 'text' | grep 'CRLF')
            if [ ! -z "$x" ]; then
                dos2unix $file
            fi
        else
            d2u $file
        fi
    done
}


### 参数为文件
main()
{
    if [ ! -d $1 -a ! -f $1 ]; then
        echo "not found" $1
        exit 1
    fi

    d2u $1
}

main "$@"
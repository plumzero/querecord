
#!/bin/bash

function getdir(){
        echo $1
        for file in $1/*
        do
        if [ -f $file ]; then
            # echo $file
            dos2unix $file
            arr=(${arr[*]} $file)
        else
            getdir $file
        fi
        done
}
getdir .
echo  ${arr[@]}
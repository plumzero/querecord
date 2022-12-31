#!/bin/bash

set -euo >/dev/null

if [ $# != 2 ]; then
    echo "Usage:"
    echo " $0 <pack dir> <des dir>"
    exit
fi

pack_path=`realpath $1`
echo "" $pack_path

exclude_files=("version")

readdir()
{
	local_dir=$(pwd)
	pushd $local_dir"/"$1
	
	for val in `ls | grep ^`
	do
		if [ -f $val ]; then
            if [ "${val##*.}" == "log" ]; then
                exclude_files[${#exclude_files[*]}]=$val
            fi
		elif [ -d $val ]; then
			readdir $val
		fi
	done
	
	popd
}

if [ -d $pack_path ]; then
	cd $pack_path
	for val in `ls | grep ^`
	do
		if [ -f $val ]; then
            if [ "${val##*.}" == "log" ]; then
                exclude_files[${#exclude_files[*]}]=$val
            fi
		elif [ -d $val ]; then
			readdir $val
		fi
	done
elif [ -f $pack_path ] ; then
	echo "$pack_path is not a directory, please input an absolute directory"
else
	echo "unexpected error"
fi

str=""
for ele in ${exclude_files[*]}
do
    echo "exclude file: " $ele
    str=" --exclude $ele "$str
done

sleep 3

cd $pack_path
tar -zcvf $2/target.tar.gz $str ./
cd -

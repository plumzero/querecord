#!/usr/bin/bash

baseurl1=https://xxx1.com/pt1/ir1/tns1
baseurl2=https://xxx2.com/pt2/ir2/tns2

baseurl=${baseurl1}

suffix=${baseurl##*/}

# url1 [1, 2]
# url2 [1, 5]
begin_iter=1
end_iter=2
count=200

function get_picture()
{
	# 下载
	local cnt=0;
	for y in $(seq -f "%02g" 1 $2)
	do
		thirdurl=${secondurl}/${y}.jpg
		if [ $(curl -o /dev/null -s -w %{http_code} ${thirdurl}) -eq 200 ]; then
			curl -o ${y}.jpg ${thirdurl} 2>/dev/null
			echo ${thirdurl} ...
			cnt=0
		else
			echo ${thirdurl} not found
			if [ ${cnt} -gt 3 ]; then
				break;
			fi
			let cnt++
		fi
	done
	# 打包
	if [ -e $3.tar.gz ]; then
		rm -rf $3.tar.gz
	fi
	tar -zcf $3.tar.gz *.jpg
	# 删除
	rm -rf *.jpg
}

for x in $(seq -f "%03g" ${begin_iter} ${end_iter})
do
	secondurl=${baseurl}/A-${x}	
	tarname=${suffix}-A-${x}
	echo ==================== ${tarname} ====================
	
	get_picture ${secondurl} ${count} ${tarname}
	
done

echo "完成"



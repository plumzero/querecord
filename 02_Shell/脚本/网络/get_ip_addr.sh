#!/bin/bash


# 暂只适用于 Redhat 系列
# ip与网络适配器

## 获取所有网络接口的IP地址，如果没有参数，则默认获取网络接口lo的IP地址
get_ipaddr()
{
	local ipall=$(/sbin/ifconfig | awk '/inet/{ if($2 !~ /127.0.0.1/) { print $2; } }')
	
	ipall=$(echo $ipall)		##去掉空白字符
	
	if [[ ! -z $ipall ]] ; then
		echo $ipall
	else
		return 1
	fi
}

## 获取所有的局域网地址
get_localip_all()
{
	local ip ipall
	
	for ip in $(get_ipaddr)
	do
		##循环调用函数get_ipaddr，获取所有网络接口的信息
		case $ip in 172.[16-31]* | 192.168.* | 10.*)
			ipall="$ipall $ip"
		esac		
	done
	
	ipall=$(echo $ipall)		##去掉空白字符
	
	if [[ ! -z $ipall ]] ; then
		echo $ipall
	else
		return 1
	fi
}

##获取默认网关
get_gateway_ip()
{
	local default_gw=$(
		/bin/netstat -nr | awk '/^0.0.0.0/{print $2;}'
	)
	default_gw=$(echo $default_gw)
	echo $default_gw
}

##只在Redhat系统上进行测试
if [[ ! -e /etc/redhat-release ]] ; then
	echo "Only test in Redhat, comment it if wanna continue"
	exit
fi

echo "获取所有的局域网地址："
get_localip_all

echo "获取默认网关"
get_gateway_ip
#!/bin/bash

# 说明
## 1. index 好像是 awk 的关键字

awk 'BEGIN {
		FS="[() ]+";
		count_910_total=0;
		count_success=0;
		count_914=0;
		count_1031=0;
		first_occured_914=0;
		first_occured_1031=0;
		max_key="";
		max_value=0;
		line=0;
		below_ten=0;
		below_twenty=0;
		below_thirty=0;
		below_forty=0;
		below_fifty=0;
		below_sixty=0;
		below_seventy=0;
		below_eighty=0;
		beyond_eighty=0;
		flag=1;
	}
	/910/{
		count_910_total++;
		++map_bytes_count[$9];
	}
	/914/{
		++map_errtime_count[$2];
		count_914++;
		if (first_occured_914 == 0) {
			map_first_occured["914"]=$2;
			first_occured_914 = 1;
		}
	}
	/1031/{
		count_1031++;
		++map_errtime_count[$2];
		if (first_occured_1031 == 0) {
			map_first_occured["1031"]=$2;
			first_occured_1031 = 1;
		}
	}
	/1034/{
		++map_1034_time[$2];
		count_success++;
		++map_sucbytes_count[$6];
	}
	/ERRO/ {
		++map_erro[$4];
	}
	END {
		printf("单位时间: 秒计\n");
		printf("当前时间: ");
		system("date +\"%H:%M:%S\"");
		printf("========================= v2x 日志数据统计略览 =========================\n");
		printf("T = S + F1 + F2(= %d):\n", count_success + count_914 + count_1031);
		printf("  总(T):%d   成功(S):%d   无法解析消息(F1):%d   非法荷载消息(F2):%d\n", 
				count_910_total, count_success, count_914, count_1031);
		printf("  失败率: %.2f %%\n", (count_914 + count_1031) / count_910_total * 100);
		printf("========================= v2x 日志数据统计略览 =========================\n\n");
		
		total_check=0;
		for (key in map_1034_time)
		{
			if (map_1034_time[key] > max_value) 
			{
				max_key = key;
				max_value = map_1034_time[key];
			}
			if (map_1034_time[key] < 10) {
				below_ten++;
				total_check += map_1034_time[key];
			} else if (map_1034_time[key] < 20) {
				below_twenty++;
				total_check += map_1034_time[key];
			} else if (map_1034_time[key] < 30) {
				below_thirty++;
				total_check += map_1034_time[key];
			} else if (map_1034_time[key] < 40) {
				below_forty++;
				total_check += map_1034_time[key];
			} else if (map_1034_time[key] < 50) {
				below_fifty++;
				total_check += map_1034_time[key];
			} else if (map_1034_time[key] < 60) {
				below_sixty++;
				total_check += map_1034_time[key];
			} else if (map_1034_time[key] < 70) {
				below_seventy++;
				total_check += map_1034_time[key];
			} else if (map_1034_time[key] < 80) {
				below_eighty++;
				total_check += map_1034_time[key];
			} else {
				beyond_eighty++;
				total_check += map_1034_time[key];
			}
			
			line++;
		}
		printf("========================= 成功验签事务日志统计 =========================\n");
		printf("成功验签数量: %d\n", total_check);
		printf("单位时间内验签数量落入的区间，及触发该区间次数:\n");
		printf("  [ 0 ~ 10): %-6d\t", below_ten);
		printf("  [10 ~ 20): %-6d\t", below_twenty);
		printf("  [20 ~ 30): %-6d\n", below_thirty);
		printf("  [30 ~ 40): %-6d\t", below_forty);
		printf("  [40 ~ 50): %-6d\t", below_fifty);
		printf("  [50 ~ 60): %-6d\n", below_sixty);
		printf("  [60 ~ 70): %-6d\t", below_seventy);
		printf("  [70 ~ 80): %-6d\t", below_eighty);
		printf("  [80 ~  *): %-6d\n", beyond_eighty);
		printf("单位时间内最大触发某区间次数及对应触发时刻: %d | %s\n", map_1034_time[max_key], max_key);
		printf("\n");
		
		max_key=0;
		ikey=0;
		printf("进行验签事务的签名数据长度，及对应出现次数:\n");
		printf("  数据长度  出现次数\t  数据长度  出现次数\t  数据长度  出现次数\n");
		for (key in map_sucbytes_count)
		{
			keys_1034[key]=1;
			printf("  %-10d  %-8d", key, map_sucbytes_count[key]);
			if (flag % 3 != 0)
				printf("\t");
			else
				printf("\n");
			flag++;
			ikey=key+0;
			if (ikey > max_key) {
				max_key=ikey;
			}
		}
		printf("\n");
		printf("进行验签事务的最长签名数据长度，及出现次数: %d | %d\n", max_key, map_sucbytes_count[max_key]);
		printf("========================= 成功验签事务日志统计 =========================\n\n");
		
		total_check=0;
		max_key="";
		max_value=0;
		line=0;
		below_ten=0;
		below_twenty=0;
		below_thirty=0;
		below_forty=0;
		below_fifty=0;
		below_sixty=0;
		below_seventy=0;
		below_eighty=0;
		beyond_eighty=0;
		for (key in map_errtime_count)
		{
			if (map_errtime_count[key] > max_value) 
			{
				max_key = key;
				max_value = map_errtime_count[key];
			}
			if (map_errtime_count[key] < 10) {
				below_ten++;
				total_check += map_errtime_count[key];
			} else if (map_errtime_count[key] < 20) {
				below_twenty++;
				total_check += map_errtime_count[key];
			} else if (map_errtime_count[key] < 30) {
				below_thirty++;
				total_check += map_errtime_count[key];
			} else if (map_errtime_count[key] < 40) {
				below_forty++;
				total_check += map_errtime_count[key];
			} else if (map_errtime_count[key] < 50) {
				below_fifty++;
				total_check += map_errtime_count[key];
			} else if (map_errtime_count[key] < 60) {
				below_sixty++;
				total_check += map_errtime_count[key];
			} else if (map_errtime_count[key] < 70) {
				below_seventy++;
				total_check += map_errtime_count[key];
			} else if (map_errtime_count[key] < 80) {
				below_eighty++;
				total_check += map_errtime_count[key];
			} else {
				beyond_eighty++;
				total_check += map_errtime_count[key];
			}
			
			line++;
		}
		printf("xxxxxxxxxxxxxxxxxxxxxxxxx 失败验签事务日志统计 xxxxxxxxxxxxxxxxxxxxxxxxx\n");
		printf("失败验签数量: %d (F1 + F2 = %d)\n", total_check, count_914 + count_1031);
		printf("单位时间内验签数量落入的区间，及触发该区间次数:\n");
		printf("  [ 0 ~ 10): %-6d\t", below_ten);
		printf("  [10 ~ 20): %-6d\t", below_twenty);
		printf("  [20 ~ 30): %-6d\n", below_thirty);
		printf("  [30 ~ 40): %-6d\t", below_forty);
		printf("  [40 ~ 50): %-6d\t", below_fifty);
		printf("  [50 ~ 60): %-6d\n", below_sixty);
		printf("  [60 ~ 70): %-6d\t", below_seventy);
		printf("  [70 ~ 80): %-6d\t", below_eighty);
		printf("  [80 ~  *): %-6d\n", beyond_eighty);
		printf("单位时间内最大触发某区间次数及对应触发时刻: %d | %s\n", map_errtime_count[max_key], max_key);
		printf("\n");
		max_key=0;
		ikey=0
		flag=1;
		printf("进行验签事务的签名数据长度，及对应出现次数:\n");
		printf("  数据长度  出现次数\t  数据长度  出现次数\t  数据长度  出现次数\n");
		for (key in map_bytes_count)
		{
			if (!(key in keys_1034))
				printf("  %-10d  %-8d", key, map_bytes_count[key]);
			else
				continue;
			if (flag % 3 != 0)
				printf("\t");
			else
				printf("\n");
			flag++;
			ikey=key+0;
			if (ikey > max_key) {
				max_key=ikey;
			}
		}
		printf("\n");
		printf("进行验签事务的最长签名数据长度，及出现次数: %d | %d\n", max_key, map_bytes_count[max_key]);
		printf("\n");
		printf("无法解析消息(F1)最早出现时刻: %s\n", map_first_occured["914"]);
		printf("非法荷载消息(F2)最早出现时刻: %s\n", map_first_occured["1031"]);
		printf("\n");
		printf("日志中出现 ERRO 的行位置(键)，及出现次数(值):\n");
		printf("  行位置      出现次数\n");
		for (key in map_erro)
		{
			if (key != 1265)
				printf("  %-10d     %-8d\n", key, map_erro[key]);
		}
		printf("xxxxxxxxxxxxxxxxxxxxxxxxx 失败验签事务日志统计 xxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
	}' $1

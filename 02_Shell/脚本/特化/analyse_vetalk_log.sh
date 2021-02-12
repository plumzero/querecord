#!/bin/bash

awk 'BEGIN {
		total_use_secure_mode=0;
		total_err=0;
		total_verify_err=0;
		first_verify_err_occured_time="";
		total_verify_suc=0;
		max_key=0;
		max_value=0;
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
	/USE SECURE MODE/{
		total_use_secure_mode++;
	}
	/\[RX signed data:HEX DUMP\]buffer/{
		map_bytes_count[$9]++;
	}
	/ERR/{
		total_err++;
	}
	/V2xVerifyData/{
		total_verify_err++;
		map_errtime_count[substr($1, 1, 8)]++;
		map_errcode_count[$7]++;
		if (first_verify_err_occured_time == "") {
			first_verify_err_occured_time = substr($1, 1, 8);
		}
	}
	/Verify success/{
		total_verify_suc++;
		map_suctime_count[substr($1, 1, 8)]++;
	}
	END {
		printf("单位时间: 秒计\n");
		printf("==================== vetalk 日志数据统计略览 ====================\n");
		printf("T = S + F(= %d):\n", total_verify_suc + total_verify_err);
		printf("  总(T):%d  成功(S):%d  失败(F):%d\n", 
						total_use_secure_mode, total_verify_suc, total_verify_err);
		printf("接收的字节数量(键)，及对应的接收次数(值):\n");
		printf("  数据长度  出现次数\t  数据长度  出现次数\t  数据长度  出现次数\n");
		for (key in map_bytes_count)
		{
			printf("  %-10d  %-8d", key, map_bytes_count[key]);
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
		if (--flag % 3 != 0) printf("\n");
		printf("处理事务的最长数据长度，及出现次数: %d | %d\n", max_key, map_bytes_count[max_key]);
		printf("==================== vetalk 日志数据统计略览 ====================\n\n");
	
		total_check=0;
		for (key in map_suctime_count)
		{
			if (map_suctime_count[key] > max_value) 
			{
				max_key = key;
				max_value = map_suctime_count[key];
			}
			if (map_suctime_count[key] < 10) {
				below_ten++;
				total_check += map_suctime_count[key]
			} else if (map_suctime_count[key] < 20) {
				below_twenty++;
				total_check += map_suctime_count[key]
			} else if (map_suctime_count[key] < 30) {
				below_thirty++;
				total_check += map_suctime_count[key]
			} else if (map_suctime_count[key] < 40) {
				below_forty++;
				total_check += map_suctime_count[key]
			} else if (map_suctime_count[key] < 50) {
				below_fifty++;
				total_check += map_suctime_count[key]
			} else if (map_suctime_count[key] < 60) {
				below_sixty++;
				total_check += map_suctime_count[key]
			} else if (map_suctime_count[key] < 70) {
				below_seventy++;
				total_check += map_suctime_count[key]
			} else if (map_suctime_count[key] < 80) {
				below_eighty++;
				total_check += map_suctime_count[key]
			} else {
				beyond_eighty++;
				total_check += map_suctime_count[key]
			}			
		}
		printf("===================== 成功处理事务日志统计 ======================\n");
		printf("成功处理数量: %d\n", total_check);
		printf("单位时间内处理数量落入的区间，及触发该区间次数:\n");
		printf("  [ 0 ~ 10): %-6d\t", below_ten);
		printf("  [10 ~ 20): %-6d\t", below_twenty);
		printf("  [20 ~ 30): %-6d\n", below_thirty);
		printf("  [30 ~ 40): %-6d\t", below_forty);
		printf("  [40 ~ 50): %-6d\t", below_fifty);
		printf("  [50 ~ 60): %-6d\n", below_sixty);
		printf("  [60 ~ 70): %-6d\t", below_seventy);
		printf("  [70 ~ 80): %-6d\t", below_eighty);
		printf("  [80 ~  *): %-6d\n", beyond_eighty);
		printf("单位时间内最大触发某区间次数及对应触发时刻: %d | %s\n", map_suctime_count[max_key], max_key);
		printf("===================== 成功处理事务日志统计 ======================\n\n");
		
		max_key=0;
		max_value=0;
		below_ten=0;
		below_twenty=0;
		below_thirty=0;
		below_forty=0;
		below_fifty=0;
		below_sixty=0;
		below_seventy=0;
		below_eighty=0;
		beyond_eighty=0;
		total_check=0;
		flag=0;
		for (key in map_errtime_count)
		{
			if (map_errtime_count[key] > max_value) 
			{
				max_key = key;
				max_value = map_errtime_count[key];
			}
			if (map_errtime_count[key] < 10) {
				below_ten++;
				total_check += map_errtime_count[key]
			} else if (map_errtime_count[key] < 20) {
				below_twenty++;
				total_check += map_errtime_count[key]
			} else if (map_errtime_count[key] < 30) {
				below_thirty++;
				total_check += map_errtime_count[key]
			} else if (map_errtime_count[key] < 40) {
				below_forty++;
				total_check += map_errtime_count[key]
			} else if (map_errtime_count[key] < 50) {
				below_fifty++;
				total_check += map_errtime_count[key]
			} else if (map_errtime_count[key] < 60) {
				below_sixty++;
				total_check += map_errtime_count[key]
			} else if (map_errtime_count[key] < 70) {
				below_seventy++;
				total_check += map_errtime_count[key]
			} else if (map_errtime_count[key] < 80) {
				below_eighty++;
				total_check += map_errtime_count[key]
			} else {
				beyond_eighty++;
				total_check += map_errtime_count[key]
			}			
		}
		printf("xxxxxxxxxxxxxxxxxxxxx 失败处理事务日志统计 xxxxxxxxxxxxxxxxxxxxxx\n");
		printf("失败处理数量: %d\n", total_check);
		printf("单位时间内处理数量落入的区间，及触发该区间次数:\n");
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
		printf("\n首次出现错误时刻: %s\n", first_verify_err_occured_time);
		printf("\n返回的错误码与对应数量:\n");
		printf("  错误码  出现次数\n");
		for (key in map_errcode_count)
		{
			keys_1034[key]=1;
			printf("  %-10d  %-8d", key, map_errcode_count[key]);
			if (flag % 3 != 0)
				printf("\t");
			else
				printf("\n");
			flag++;
		}
		printf("\n");
		printf("xxxxxxxxxxxxxxxxxxxxx 失败处理事务日志统计 xxxxxxxxxxxxxxxxxxxxxx\n\n");
	}' $1

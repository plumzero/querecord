#!/bin/bash

awk 'BEGIN {
		FS = "[: ]+";
		first = 1;
		cur_hour = 0;
		cur_minute = 0;
		cur_second = 0;
		last_hour = 0;
		last_minute = 0;
		last_second = 0;
		span_hour = 0;
		span_minute = 0;
		span_second = 0;
		borrow_minute = 0;
		borrow_hour = 0;
		span_time = 0;
	}
	{
		cur_hour = 0;
		cur_minute = 0;
		cur_second = 0;
		span_hour = 0;
		span_minute = 0;
		span_second = 0;
		borrow_minute = 0;
		borrow_hour = 0;
		span_time = 0;		
		if (first) {
			last_hour = $2+0;
			last_minute = $3+0;
			last_second = $4+0;
			first = 0;
			# printf("%02d:%02d:%02d\n", $2, $3, $4);
		} else {
			cur_hour = $2+0;
			cur_minute = $3+0;
			cur_second = $4+0;
			if (cur_second >= last_second) {
				span_second = cur_second - last_second;
			} else {
				span_second = cur_second + 60 - last_second;
				borrow_minute = 1;
			}

			if (borrow_minute) {
				if (cur_minute == 0) {   # 整时
					cur_minute = 59;
					if (cur_hour == 0) {
						cur_hour = 23;
					} else {
						cur_hour -= 1;
					}
				} else {
					cur_minute -= 1;
				}
			}
			if (cur_minute >= last_minute) {
				span_minute = cur_minute - last_minute;
			} else {
				span_minute = cur_minute + 1 - last_minute;
				borrow_hour = 1;
			}
		
			if (borrow_hour) {
				if (cur_hour == 0) {
					cur_hour = 23;
				} else {
					cur_hour -= 1;
				}
			}
			if (cur_hour >= last_hour) {
				span_hour = cur_hour - last_hour;
			} else {
				printf("xxxxxxxxxx error occured xxxxxxxxxx");
			}
			# printf("%02d:%02d:%02d  ", $2, $3, $4);
			# printf("borrow_minute:%02d | span_second:%02d | ", borrow_minute, span_second);
			# printf("borrow_hour:%02d | span_minute:%02d | ", borrow_hour, span_minute);
			# printf("span_hour:%02d  ", span_hour);
			span_time = span_second + span_minute * 60 + span_hour * 3600;
			# printf("span time(seconds): %d\n", span_time);
			
			if (span_time > 70) {
				map_timespan[$2":"$3":"$4] = span_time;
			}
			
			last_hour = $2;
			last_minute = $3;
			last_second = $4;
			first = 0;
		}
	}
	END {
		for (key in map_timespan) {
			printf("timestamp: %s --- span time: %d\n", key, map_timespan[key]);
		}
	}' $1

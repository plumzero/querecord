#!/usr/bin/env awk

# *******************************************
# Script Status: 完结 
# Creation Data:
# Last Modified:
# Author:
# E-mail:
# *******************************************
# Description: 读取 INFO 日志，统计订单状态，数量与占比
# *******************************************
# Usage:
#   bash get_order_status.sh
#   bash get_order_status.sh 20210104
# *******************************************

whichday=

if [ ! -z "$1" ]; then
    whichday=$1
else
    whichday=`date +%Y%m%d`
fi

logdirectory=/path/to/logdirectory

files=$(ls -alh $logdirectory | grep "^-" | grep "INFO.${whichday}" | awk '{ print $NF; }')

if [ ! -n "$files" ]; then
    echo "files is null"
    exit -1
fi

echo files: $files

awk 'BEGIN {
        FS="[|]+";
        status_string_None              = "None";
        status_string_Pending           = "Pending";
        status_string_Accepted          = "Accepted";
        status_string_Removing          = "Removing";
        status_string_PartialMatch      = "PartialMatch";
        status_string_TotalMatch        = "TotalMatch";
        status_string_PartialRemoved    = "PartialRemoved";
        status_string_TotalRemoved      = "TotalRemoved";
        status_string_Failed            = "Failed";
    }
    
    /STATUS None/{
        map_status[$2] = status_string_None;
    }
    /STATUS Pending/{
        map_status[$2] = status_string_Pending;
    }
    /STATUS Accepted/{
        map_status[$2] = status_string_Accepted;
    }
    /STATUS Removing/{
        map_status[$2] = status_string_Removing;
    }
    /STATUS PartialMatch/{
        map_status[$2] = status_string_PartialMatch;
    }
    /STATUS TotalMatch/{
        map_status[$2] = status_string_TotalMatch;
    }
    /STATUS PartialRemoved/{
        map_status[$2] = status_string_PartialRemoved;
    }
    /STATUS TotalRemoved/{
        map_status[$2] = status_string_TotalRemoved;
    }
    /STATUS Failed/{
        map_status[$2] = status_string_Failed;
    }
    
    END {
        printf("当前时间: ");
        system("date +\"%H:%M:%S\"");
        
        printf("========================= 订单状态一揽 =========================\n");
        total_counter = 0;
        for (key in map_status) {
            map_counter[map_status[key]]++;
            total_counter++;
            
            if (map_status[key] == status_string_TotalMatch) {
                map_TotalMatch[total_counter] = key;
            } else if (map_status[key] == status_string_PartialRemoved) {
                map_PartialRemoved[total_counter] = key;
            } else if (map_status[key] == status_string_TotalRemoved) {
                map_TotalRemoved[total_counter] = key;
            } else if (map_status[key] == status_string_Failed) {
                map_Failed[total_counter] = key;
            }
        }
        
        printf("total_counter=%d\n", total_counter);
                
        printf("状态  数量  占比(%)\n");
        for (key in map_counter) {
            printf("%-15s   %-5d   %5.2f%%\n", key, map_counter[key], map_counter[key] * 100 / total_counter);
        }
        
        line_break = 26;
        
        for (key in map_counter) {
            printf("具体订单号: %s\n", key);
            flag = 0;
            if (key == status_string_TotalMatch) {
            
            } else if (key == status_string_PartialRemoved) {
                for (k in map_PartialRemoved) {
                    printf("%d ", map_PartialRemoved[k]);
                    if (++flag % line_break == 0) {
                        printf("\n");
                    }
                }
            } else if (key == status_string_TotalRemoved) {
                map_TotalRemoved[total_counter] = key;
                for (k in map_TotalRemoved) {
                    printf("%d ", map_TotalRemoved[k]);
                    if (++flag % line_break == 0) {
                        printf("\n");
                    }
                }
            } else if (key == status_string_Failed) {
                for (k in map_Failed) {
                    printf("%d ", map_Failed[k]);
                    if (++flag % line_break == 0) {
                        printf("\n");
                    }
                }
            }
            printf("\n");
        }

    }' $files

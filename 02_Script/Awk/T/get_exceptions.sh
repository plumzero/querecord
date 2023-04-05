#!/usr/bin/env awk

# *******************************************
# Script Status: 完结
# Creation Data:
# Last Modified:
# Author:
# E-mail:
# *******************************************
# Description: 读取 WARNING 日志，统计异常情况
# *******************************************
# Usage:
#   bash get_exceptions.sh
#   bash get_exceptions.sh 20210104
# *******************************************

file=$1

whichday=

if [ ! -z "$1" ]; then
    whichday=$1
else
    whichday=`date +%Y%m%d`
fi

logdirectory=/path/to/logdirectory

files=$(ls -alh $logdirectory | grep "^-" | grep "WARNING.${whichday}" | awk '{ print $NF; }')

if [ ! -n "$files" ]; then
    echo "files is null"
    exit -1
fi

echo files: $files

awk 'BEGIN {
        descript_RC_ReqId_Non_Exist                     = "订单 ID 不存在";
        descript_RC_Order_Check_Status                  = "状态检测不过 ";
        descript_RC_Order_Check_Selfdeal                = "自成交检测不过";
        descript_RC_Order_Send2TSide                    = "发送给交易端失败";
        descript_RC_Order_Match_Dealvol_Zero            = "成交股数小于等于 0";
        descript_RC_Order_Match_Repeated_Matchid        = "重复处理订单的成交号";
        descript_RC_Order_Match_Dealvol_Excess          = "成交量超过订单规定量";
        descript_RC_Order_Match_Dealprice_Out_Of_Range  = "交易价溢出区间";
        descript_RC_Cancel_Timeout                      = "订单超时撤单";
        descript_RC_Cancel_Reqid_Dealed_Over            = "订单之前已经交易结束";
        descript_RC_Account_Create_With_Error_Balance   = "尝试以不合理 balance 创建帐户";
        descript_RC_Account_Already_Exist               = "帐户已存在";
        descript_RC_Account_Update_Non_Exist            = "要更新的帐户不存在";
        descript_RC_Stock_Create_With_Error_Quantity    = "股票创建量不合理";
        descript_RC_Stock_Already_Exist                 = "帐户下已存在该股票";
        descript_RC_Stock_Update_With_Error_Quantity    = "尝试以不合理的量更新股票";
        descript_RC_Stock_Update_Non_Exist              = "帐户下不存在要更新的股票";
    }
    
    /order not found/{
        ++map_counter[descript_RC_ReqId_Non_Exist];
        map_code[descript_RC_ReqId_Non_Exist] = "RC_ReqId_Non_Exist";
    }
    /SC Reject/{
        ++map_counter[descript_RC_Order_Check_Status];
        map_code[descript_RC_Order_Check_Status] = "RC_Order_Check_Status";
    }
    /SDC Reject/{
        ++map_counter[descript_RC_Order_Check_Selfdeal];
        map_code[descript_RC_Order_Check_Selfdeal] = "RC_Order_Check_Selfdeal";
    }
    /negative dealvolume/{
        ++map_counter[descript_RC_Order_Match_Dealvol_Zero];
        map_code[descript_RC_Order_Match_Dealvol_Zero] = "RC_Order_Match_Dealvol_Zero";
    }
    /duplicate match/{
        ++map_counter[descript_RC_Order_Match_Repeated_Matchid];
        map_code[descript_RC_Order_Match_Repeated_Matchid] = "RC_Order_Match_Repeated_Matchid";
    }
    /excessived match/{
        ++map_counter[descript_RC_Order_Match_Dealvol_Excess];
        map_code[descript_RC_Order_Match_Dealvol_Excess] = "RC_Order_Match_Dealvol_Excess";
    }
    /match price out of range/{
        ++map_counter[descript_RC_Order_Match_Dealprice_Out_Of_Range];
        map_code[descript_RC_Order_Match_Dealprice_Out_Of_Range] = "RC_Order_Match_Dealprice_Out_Of_Range";
    }
    /Cancel Timeout/{
        ++map_counter[descript_RC_Cancel_Timeout];
        map_code[descript_RC_Cancel_Timeout] = "RC_Cancel_Timeout";
    }
    /dealed over/{
        ++map_counter[descript_RC_Cancel_Reqid_Dealed_Over];
        map_code[descript_RC_Cancel_Reqid_Dealed_Over] = "RC_Cancel_Reqid_Dealed_Over";
    }
    /no cash in account/{
        ++map_counter[descript_RC_Account_Create_With_Error_Balance];
        map_code[descript_RC_Account_Create_With_Error_Balance] = "RC_Account_Create_With_Error_Balance";
    }
    /already exsited account id/{
        ++map_counter[descript_RC_Account_Already_Exist];
        map_code[descript_RC_Account_Already_Exist] = "RC_Account_Already_Exist";
    }
    /update an unexsited account id/{
        ++map_counter[descript_RC_Account_Update_Non_Exist];
        map_code[descript_RC_Account_Update_Non_Exist] = "RC_Account_Update_Non_Exist";
    }
    /Try to create a stock with error quatity/{
        ++map_counter[descript_RC_Stock_Create_With_Error_Quantity];
        map_code[descript_RC_Stock_Create_With_Error_Quantity] = "RC_Stock_Create_With_Error_Quantity";
    }
    /Try to create an exsited stock/{
        ++map_counter[descript_RC_Stock_Already_Exist];
        map_code[descript_RC_Stock_Already_Exist] = "RC_Stock_Already_Exist";
    }
    /Try to update a stock with error quatity/{
        ++map_counter[descript_RC_Stock_Update_With_Error_Quantity];
        map_code[descript_RC_Stock_Update_With_Error_Quantity] = "RC_Stock_Update_With_Error_Quantity";
    }
    /Try to update an unexsited stock/{
        ++map_counter[descript_RC_Stock_Update_Non_Exist];
        map_code[descript_RC_Stock_Update_Non_Exist] = "RC_Stock_Update_Non_Exist";
    }
    
    END {
        printf("当前时间: ");
        system("date +\"%H:%M:%S\"");
        
        printf("========================= 异常统计一览 =========================\n");
        counter_total = 0;
        for (key in map_counter) {
            counter_total += map_counter[key]; 
        }
        printf("异常总数: %d\n", counter_total);
        printf("%-40s%-10s%-10s%-20s\n", "异常码", "数量", "占比(%)", "描述");
        for (key in map_counter) {
            printf("%-40s%-10d%-10.0f%-20s\n", map_code[key], map_counter[key], map_counter[key] * 100 / counter_total, key);
        }
    }' $files

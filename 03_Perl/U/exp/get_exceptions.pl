
#!/usr/bin/env perl -w

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
#   perl get_exceptions.pl
#   perl get_exceptions.pl 20210104
# *******************************************

$whichday = "";

$args = @ARGV;

if ($args != 0) {
    $whichday = $ARGV[0];
} else {
    $whichday = sprintf("%d", `date +%Y%m%d`);
}

$logdirectory = "/path/to/logdirectory";

my @all_log_files = <$logdirectory/*>;

my @specified_log_files;

my $array_index = 0;

foreach (@all_log_files) {
    if (/WARNING\.$whichday/) {
        $specified_log_files[$array_index++] = $_;
    }
}

@specified_log_files = sort(@specified_log_files);

my $descript_RC_ReqId_Non_Exist                     = "订单 ID 不存在";
my $descript_RC_Order_Check_Status                  = "状态检测不过 ";
my $descript_RC_Order_Check_Selfdeal                = "自成交检测不过";
my $descript_RC_Order_Send2TSide                    = "发送给交易端失败";
my $descript_RC_Order_Match_Dealvol_Zero            = "成交股数小于等于 0";
my $descript_RC_Order_Match_Repeated_Matchid        = "重复处理订单的成交号";
my $descript_RC_Order_Match_Dealvol_Excess          = "成交量超过订单规定量";
my $descript_RC_Order_Match_Dealprice_Out_Of_Range  = "交易价溢出区间";
my $descript_RC_Cancel_Timeout                      = "订单超时撤单";
my $descript_RC_Cancel_Reqid_Dealed_Over            = "订单之前已经交易结束";
my $descript_RC_Account_Create_With_Error_Balance   = "尝试以不合理 balance 创建帐户";
my $descript_RC_Account_Already_Exist               = "帐户已存在";
my $descript_RC_Account_Update_Non_Exist            = "要更新的帐户不存在";
my $descript_RC_Stock_Create_With_Error_Quantity    = "股票创建量不合理";
my $descript_RC_Stock_Already_Exist                 = "帐户下已存在该股票";
my $descript_RC_Stock_Update_With_Error_Quantity    = "尝试以不合理的量更新股票";
my $descript_RC_Stock_Update_Non_Exist              = "帐户下不存在要更新的股票";

my %hash_code_desc;
my %hash_code_counter;

foreach (@specified_log_files)
{
    open(DATA, "<$_") or die "open $_ failed: $!\n";
    
    while (<DATA>)
    {
        if (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*order not found/) {
            $hash_code_desc{$descript_RC_ReqId_Non_Exist} = "RC_ReqId_Non_Exist";
            ++$hash_code_counter{$descript_RC_ReqId_Non_Exist} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*SC Reject/) {
            $hash_code_desc{$descript_RC_Order_Check_Status} = "RC_Order_Check_Status";
            ++$hash_code_counter{$descript_RC_Order_Check_Status} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*SDC Reject/) {
            $hash_code_desc{$descript_RC_Order_Check_Selfdeal} = "RC_Order_Check_Selfdeal";
            ++$hash_code_counter{$descript_RC_Order_Check_Selfdeal} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*negative dealvolume/) {
            $hash_code_desc{$descript_RC_Order_Match_Dealvol_Zero} = "RC_Order_Match_Dealvol_Zero";
            ++$hash_code_counter{$descript_RC_Order_Match_Dealvol_Zero} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*duplicate match/) {
            $hash_code_desc{$descript_RC_Order_Match_Repeated_Matchid} = "RC_Order_Match_Repeated_Matchid";
            ++$hash_code_counter{$descript_RC_Order_Match_Repeated_Matchid} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*excessived match/) {
            $hash_code_desc{$descript_RC_Order_Match_Dealvol_Excess} = "RC_Order_Match_Dealvol_Excess";
            ++$hash_code_counter{$descript_RC_Order_Match_Dealvol_Excess} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*match price out of range/) {
            $hash_code_desc{$descript_RC_Order_Match_Dealprice_Out_Of_Range} = "RC_Order_Match_Dealprice_Out_Of_Range";
            ++$hash_code_counter{$descript_RC_Order_Match_Dealprice_Out_Of_Range} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*Cancel Timeout/) {
            $hash_code_desc{$descript_RC_Cancel_Timeout} = "RC_Cancel_Timeout";
            ++$hash_code_counter{$descript_RC_Cancel_Timeout} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*dealed over/) {
            $hash_code_desc{$descript_RC_Cancel_Reqid_Dealed_Over} = "RC_Cancel_Reqid_Dealed_Over";
            ++$hash_code_counter{$descript_RC_Cancel_Reqid_Dealed_Over} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*no cash in account/) {
            $hash_code_desc{$descript_RC_Account_Create_With_Error_Balance} = "RC_Account_Create_With_Error_Balance";
            ++$hash_code_counter{$descript_RC_Account_Create_With_Error_Balance} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*already exsited account id/) {
            $hash_code_desc{$descript_RC_Account_Already_Exist} = "RC_Account_Already_Exist";
            ++$hash_code_counter{$descript_RC_Account_Already_Exist} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*update an unexsited account id/) {
            $hash_code_desc{$descript_RC_Account_Update_Non_Exist} = "RC_Account_Update_Non_Exist";
            ++$hash_code_counter{$descript_RC_Account_Update_Non_Exist} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*Try to create a stock with error quatity/) {
            $hash_code_desc{$descript_RC_Stock_Create_With_Error_Quantity} = "RC_Stock_Create_With_Error_Quantity";
            ++$hash_code_counter{$descript_RC_Stock_Create_With_Error_Quantity} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*Try to create an exsited stock/) {
            $hash_code_desc{$descript_RC_Stock_Already_Exist} = "RC_Stock_Already_Exist";
            ++$hash_code_counter{$descript_RC_Stock_Already_Exist} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*Try to update a stock with error quatity/) {
            $hash_code_desc{$descript_RC_Stock_Update_With_Error_Quantity} = "RC_Stock_Update_With_Error_Quantity";
            ++$hash_code_counter{$descript_RC_Stock_Update_With_Error_Quantity} ;
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*Try to update an unexsited stock/) {
            $hash_code_desc{$descript_RC_Stock_Update_Non_Exist} = "RC_Stock_Update_Non_Exist";
            ++$hash_code_counter{$descript_RC_Stock_Update_Non_Exist} ;
        }
    }
    
    close(DATA);
}

printf("当前时间: %s\n", `date +%H:%M:%S`);
printf("========================= 异常统计一览 =========================\n");

my $total_counter = 0;

foreach $key (keys %hash_code_counter) {
    $total_counter += $hash_code_counter{$key};
}

printf("异常总数: %d\n", $total_counter);
printf("%-40s%-10s%-10s%-20s\n", "异常码", "数量", "占比(%)", "描述");

foreach $key (keys %hash_code_counter) {
    printf("%-40s%-10d%-10.0f%-20s\n", $hash_code_desc{$key}, $hash_code_counter{$key}, $hash_code_counter{$key} * 100 / $total_counter, $key);
}

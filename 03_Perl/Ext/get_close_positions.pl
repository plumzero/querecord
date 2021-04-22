
#!/usr/bin/env perl -w

# *******************************************
# Script Status: 完结 
# Creation Data:
# Last Modified:
# Author:
# E-mail:
# *******************************************
# Description: 读取 INFO 日志，统计相关信息
# *******************************************
# Usage:
#   perl get_close_positions.pl
#   perl get_close_positions.pl 20210104
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
    if (/INFO\.$whichday/) {
        $specified_log_files[$array_index++] = $_;
    }
}

@specified_log_files = sort(@specified_log_files);

my $tail_close_position_mark = 150000000;

my $string_buy_limit_move    = "涨跌停买平仓";
my $string_sell_limit_move   = "涨跌停卖平仓";
my $string_buy_tail          = "尾买平仓";
my $string_sell_tail         = "尾卖平仓";
my $string_buy_half_life     = "半衰期策略买平仓";
my $string_sell_half_life    = "半衰期策略卖平仓";

my %hash_buy_sell;

foreach (@specified_log_files)
{
    open(DATA, "<$_") or die "open $_ failed: $!\n";
 
    while (<DATA>)
    {
        if (/StrategyUtils.hpp:107.*ntime:(?<nt>[\d]{9})/) {
            if ($+{nt} == $tail_close_position_mark) {
                $hash_buy_sell{$string_sell_tail}++;
            } else {
                $hash_buy_sell{$string_sell_limit_move}++;
            }
        } elsif (/StrategyUtils.hpp:114.*ntime:(?<nt>[\d]{9})/) {
            if ($+{nt} == $tail_close_position_mark) {
                $hash_buy_sell{$string_buy_tail}++;
            } else {
                $hash_buy_sell{$string_buy_limit_move}++;
            }
        } elsif (/new order for threshold decline.*targetVol:(?<tv>-?[\d]+),/) {
            if ($+{tv} > 0) {
                $hash_buy_sell{$string_buy_half_life}++;
            } elsif ($+{tv} < 0) {
                $hash_buy_sell{$string_sell_half_life}++;
            } else {
                # should not happen
            }
        }
    }
    
    close(DATA);
}

printf("当前时间: %s\n", `date +%H:%M:%S`);
printf("========================= 平仓信息一览 =========================\n");

my $total_buy_sell_counter = 0;

foreach $key (keys %hash_buy_sell) {
    $total_buy_sell_counter += $hash_buy_sell{$key};
}

printf("平仓总数: %d\n\n", $total_buy_sell_counter);

printf("%-30s%-10s%10s\n", "平仓类型", "数量", "占比(%)");
foreach $key (keys %hash_buy_sell) {
    printf("%-30s%-10d%10.3f%%\n", $key, $hash_buy_sell{$key}, $hash_buy_sell{$key} * 100 / $total_buy_sell_counter);
}

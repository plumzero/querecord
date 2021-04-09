
#!/usr/bin/env perl -w

# *******************************************
# Script Status: 完结 
# Creation Data:
# Last Modified:
# Author:
# E-mail:
# *******************************************
# Description: 统计订单的处理时间: 从创建订单开始，到订单进入某个结束状态为止的时间
# *******************************************
# Usage:
#   perl get_order_period.pl
#   perl get_order_period.pl 20210104
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


%hash_timepoint_None;
%hash_timepoint_Pending;
%hash_timepoint_Accepted;
%hash_timepoint_Removing;
%hash_timepoint_PartialMatch;
%hash_timepoint_TotalMatch;
%hash_timepoint_PartialRemoved;
%hash_timepoint_TotalRemoved;
%hash_timepoint_Failed;

%hash_end_state;

my $string_end_status_TotalMatch        = "TotalMatch";
my $string_end_status_PartialRemoved    = "PartialRemoved";
my $string_end_status_TotalRemoved      = "TotalRemoved";
my $string_end_status_Failed            = "Failed";

# 下面的统计变量用作校验
my $counter_status_None = 0;
my $counter_status_Pending = 0;
my $counter_status_Removing = 0;
my $counter_status_PartialMatch = 0;

my $counter_status_TotalMatch = 0;
my $counter_status_PartialRemoved = 0;
my $counter_status_TotalRemoved = 0;
my $counter_status_Failed = 0;

foreach (@specified_log_files)
{
    open(DATA, "<$_") or die "open $_ failed: $!\n";
    
    while (<DATA>)
    {
        if (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS None.*\|(?<reqid>\d+)\|/) {
            $hash_timepoint_None{$+{reqid}} = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            ++$counter_status_None;
            # printf("hour=%d, minute=%d, second=%d, micros=%d, reqid=%d, timepoint=%d\n", $+{hour}, $+{minute}, $+{second}, $+{micros}, $+{reqid}, $hash_timepoint_None{$+{reqid}});
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS Pending.*\|(?<reqid>\d+)\|/) {
            $hash_timepoint_Pending{$+{reqid}} = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            # printf("hour=%d, minute=%d, second=%d, micros=%d, reqid=%d, timepoint=%d\n", $+{hour}, $+{minute}, $+{second}, $+{micros}, $+{reqid}, $hash_timepoint_Pending{$+{reqid}});
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS Accepted.*\|(?<reqid>\d+)\|/) {
            $hash_timepoint_Accepted{$+{reqid}} = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            # printf("hour=%d, minute=%d, second=%d, micros=%d, reqid=%d, timepoint=%d\n", $+{hour}, $+{minute}, $+{second}, $+{micros}, $+{reqid}, $hash_timepoint_Accepted{$+{reqid}});
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS Removing.*\|(?<reqid>\d+)\|/) {
            $hash_timepoint_Removing{$+{reqid}} = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            # printf("hour=%d, minute=%d, second=%d, micros=%d, reqid=%d, timepoint=%d\n", $+{hour}, $+{minute}, $+{second}, $+{micros}, $+{reqid}, $hash_timepoint_Removing{$+{reqid}});
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS PartialMatch.*\|(?<reqid>\d+)\|/) {
            $hash_timepoint_PartialMatch{$+{reqid}} = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            # printf("hour=%d, minute=%d, second=%d, micros=%d, reqid=%d, timepoint=%d\n", $+{hour}, $+{minute}, $+{second}, $+{micros}, $+{reqid}, $hash_timepoint_PartialMatch{$+{reqid}});
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS TotalMatch.*\|(?<reqid>\d+)\|/) {
            $hash_timepoint_TotalMatch{$+{reqid}} = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            $hash_end_state{$+{reqid}} = $string_end_status_TotalMatch;
            ++$counter_status_TotalMatch;
            # printf("TotalMatch hour=%d, minute=%d, second=%d, micros=%d, reqid=%d, timepoint=%d\n", $+{hour}, $+{minute}, $+{second}, $+{micros}, $+{reqid}, $hash_timepoint_TotalMatch{$+{reqid}});
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS PartialRemoved.*\|(?<reqid>\d+)\|/) {
            $hash_timepoint_PartialRemoved{$+{reqid}} = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            $hash_end_state{$+{reqid}} = $string_end_status_PartialRemoved;
            ++$counter_status_PartialRemoved;
            # printf("PartialRemoved hour=%d, minute=%d, second=%d, micros=%d, reqid=%d, timepoint=%d\n", $+{hour}, $+{minute}, $+{second}, $+{micros}, $+{reqid}, $hash_timepoint_PartialRemoved{$+{reqid}});
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS TotalRemoved.*\|(?<reqid>\d+)\|/) {
            $hash_timepoint_TotalRemoved{$+{reqid}} = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            $hash_end_state{$+{reqid}} = $string_end_status_TotalRemoved;
            ++$counter_status_TotalRemoved;
            # printf("TotalRemoved hour=%d, minute=%d, second=%d, micros=%d, reqid=%d, timepoint=%d\n", $+{hour}, $+{minute}, $+{second}, $+{micros}, $+{reqid}, $hash_timepoint_TotalRemoved{$+{reqid}});
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS Failed.*\|(?<reqid>\d+)\|/) {
            $hash_timepoint_Failed{$+{reqid}} = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            $hash_end_state{$+{reqid}} = $string_end_status_Failed;
            ++$counter_status_Failed;
            # printf("Failed hour=%d, minute=%d, second=%d, micros=%d, reqid=%d, timepoint=%d\n", $+{hour}, $+{minute}, $+{second}, $+{micros}, $+{reqid}, $hash_timepoint_Failed{$+{reqid}});
        }
    }
    
    close(DATA);
}

printf("当前时间: %s\n", `date +%H:%M:%S`);
printf("数据历史: %s\n", $whichday);

printf("========================= 订单状态信息结果一览(关键词:数量) =========================\n");
printf("STATUS B: None(%d)\n", $counter_status_None);
printf("STATUS M: Pending(%d) Removing(%d) PartialMatch(%d)\n", $counter_status_Pending, $counter_status_Removing, $counter_status_PartialMatch);
printf("STATUS E: TotalMatch(%d) PartialRemoved(%d) TotalRemoved(%d) Failed(%d)\n",
                            $counter_status_TotalMatch, $counter_status_PartialRemoved, $counter_status_TotalRemoved, $counter_status_Failed);
printf("STATUS: B - E = %d\n", $counter_status_None - $counter_status_TotalMatch - $counter_status_TotalRemoved - $counter_status_Failed);

printf("========================= 订单处理时间结果一览(关键词:微秒) =========================\n");

my %hash_costtime;

my $costtime_max_TotalMatch = 0;
my $costtime_min_TotalMatch = 1000000000;
my $costtime_max_PartialRemoved = 0;
my $costtime_min_PartialRemoved = 1000000000;
my $costtime_max_TotalRemoved = 0;
my $costtime_min_TotalRemoved = 1000000000;
my $costtime_max_Failed = 0;
my $costtime_min_Failed = 1000000000;

my %hash_range_TotalMatch;
my %hash_range_PartialRemoved;
my %hash_range_TotalRemoved;
my %hash_range_Failed;

foreach $reqid (keys %hash_end_state)
{
    if ($hash_end_state{$reqid} eq $string_end_status_TotalMatch) {
        $hash_costtime{$reqid} = $hash_timepoint_TotalMatch{$reqid} - $hash_timepoint_None{$reqid};
        if ($hash_costtime{$reqid} < 500000) {
            ++$hash_range_TotalMatch{"A"};
        } elsif ($hash_costtime{$reqid} < 1000000) {
            ++$hash_range_TotalMatch{"B"};
        } elsif ($hash_costtime{$reqid} < 2000000) {
            ++$hash_range_TotalMatch{"C"};
        } elsif ($hash_costtime{$reqid} < 4000000) {
            ++$hash_range_TotalMatch{"D"};
        } elsif ($hash_costtime{$reqid} < 8000000) {
            ++$hash_range_TotalMatch{"E"};
        } else {
            ++$hash_range_TotalMatch{"F"};
        }
        if ($hash_costtime{$reqid} > $costtime_max_TotalMatch) {
            $costtime_max_TotalMatch = $hash_costtime{$reqid};
        }
        if ($hash_costtime{$reqid} < $costtime_min_TotalMatch) {
            $costtime_min_TotalMatch = $hash_costtime{$reqid};
        }
    } elsif ($hash_end_state{$reqid} eq $string_end_status_PartialRemoved) {
        $hash_costtime{$reqid} = $hash_timepoint_PartialRemoved{$reqid} - $hash_timepoint_None{$reqid};
        if ($hash_costtime{$reqid} < 500000) {
            ++$hash_range_PartialRemoved{"A"};
        } elsif ($hash_costtime{$reqid} < 1000000) {
            ++$hash_range_PartialRemoved{"B"};
        } elsif ($hash_costtime{$reqid} < 2000000) {
            ++$hash_range_PartialRemoved{"C"};
        } elsif ($hash_costtime{$reqid} < 4000000) {
            ++$hash_range_PartialRemoved{"D"};
        } elsif ($hash_costtime{$reqid} < 8000000) {
            ++$hash_range_PartialRemoved{"E"};
        } else {
            ++$hash_range_PartialRemoved{"F"};
        }
        if ($hash_costtime{$reqid} > $costtime_max_PartialRemoved) {
            $costtime_max_PartialRemoved = $hash_costtime{$reqid};
        }
        if ($hash_costtime{$reqid} < $costtime_min_PartialRemoved) {
            $costtime_min_PartialRemoved = $hash_costtime{$reqid};
        }
    } elsif ($hash_end_state{$reqid} eq $string_end_status_TotalRemoved) {
        $hash_costtime{$reqid} = $hash_timepoint_TotalRemoved{$reqid} - $hash_timepoint_None{$reqid};
        if ($hash_costtime{$reqid} < 500000) {
            ++$hash_range_TotalRemoved{"A"};
        } elsif ($hash_costtime{$reqid} < 1000000) {
            ++$hash_range_TotalRemoved{"B"};
        } elsif ($hash_costtime{$reqid} < 2000000) {
            ++$hash_range_TotalRemoved{"C"};
        } elsif ($hash_costtime{$reqid} < 4000000) {
            ++$hash_range_TotalRemoved{"D"};
        } elsif ($hash_costtime{$reqid} < 8000000) {
            ++$hash_range_TotalRemoved{"E"};
        } else {
            ++$hash_range_TotalRemoved{"F"};
        }
        if ($hash_costtime{$reqid} > $costtime_max_TotalRemoved) {
            $costtime_max_TotalRemoved = $hash_costtime{$reqid};
        }
        if ($hash_costtime{$reqid} < $costtime_min_TotalRemoved) {
            $costtime_min_TotalRemoved = $hash_costtime{$reqid};
        }
    } elsif ($hash_end_state{$reqid} eq $string_end_status_Failed) {
        $hash_costtime{$reqid} = $hash_timepoint_Failed{$reqid} - $hash_timepoint_None{$reqid};
        if ($hash_costtime{$reqid} < 500000) {
            ++$hash_range_Failed{"A"};
        } elsif ($hash_costtime{$reqid} < 1000000) {
            ++$hash_range_Failed{"B"};
        } elsif ($hash_costtime{$reqid} < 2000000) {
            ++$hash_range_Failed{"C"};
        } elsif ($hash_costtime{$reqid} < 4000000) {
            ++$hash_range_Failed{"D"};
        } elsif ($hash_costtime{$reqid} < 8000000) {
            ++$hash_range_Failed{"E"};
        } else {
            ++$hash_range_Failed{"F"};
        }
        if ($hash_costtime{$reqid} > $costtime_max_Failed) {
            $costtime_max_Failed = $hash_costtime{$reqid};
        }
        if ($hash_costtime{$reqid} < $costtime_min_Failed) {
            $costtime_min_Failed = $hash_costtime{$reqid};
        }
    }
}

printf("STATUS          min        max\n");
printf("TotalMatch      %-10d %-10d\n", $costtime_min_TotalMatch, $costtime_max_TotalMatch);
printf("PartialRemoved  %-10d %-10d\n", $costtime_min_PartialRemoved, $costtime_max_PartialRemoved);
printf("TotalRemoved    %-10d %-10d\n", $costtime_min_TotalRemoved, $costtime_max_TotalRemoved);
printf("Failed          %-10d %-10d\n", $costtime_min_Failed == 1000000000 ? 0 : $costtime_min_Failed, $costtime_max_Failed);

printf("========================= 订单处理时间分布区间一览(关键词:时间区间量) =========================\n");

printf("TotalMatch(毫秒):\n");
foreach $key (sort keys %hash_range_TotalMatch) {
    if ($key eq "A") {
        printf("\t[,  0.5): %-5d\n", $hash_range_TotalMatch{$key});
    } elsif ($key eq "B") {
        printf("\t[0.5, 1): %-5d\n", $hash_range_TotalMatch{$key});
    } elsif ($key eq "C") {
        printf("\t[1,   2): %-5d\n", $hash_range_TotalMatch{$key});
    } elsif ($key eq "D") {
        printf("\t[2,   4): %-5d\n", $hash_range_TotalMatch{$key});
    } elsif ($key eq "E") {
        printf("\t[4,   8): %-5d\n", $hash_range_TotalMatch{$key});
    } elsif ($key eq "F") {
        printf("\t[8,    ): %-5d\n", $hash_range_TotalMatch{$key});
    }
}

printf("PartialRemoved(毫秒):\n");
foreach $key (sort keys %hash_range_PartialRemoved) {
    if ($key eq "A") {
        printf("\t[,  0.5): %-5d\n", $hash_range_PartialRemoved{$key});
    } elsif ($key eq "B") {
        printf("\t[0.5, 1): %-5d\n", $hash_range_PartialRemoved{$key});
    } elsif ($key eq "C") {
        printf("\t[1,   2): %-5d\n", $hash_range_PartialRemoved{$key});
    } elsif ($key eq "D") {
        printf("\t[2,   4): %-5d\n", $hash_range_PartialRemoved{$key});
    } elsif ($key eq "E") {
        printf("\t[4,   8): %-5d\n", $hash_range_PartialRemoved{$key});
    } elsif ($key eq "F") {
        printf("\t[8,    ): %-5d\n", $hash_range_PartialRemoved{$key});
    }
}

printf("TotalRemoved(毫秒):\n");
foreach $key (sort keys %hash_range_TotalRemoved) {
    if ($key eq "A") {
        printf("\t[,  0.5): %-5d\n", $hash_range_TotalRemoved{$key});
    } elsif ($key eq "B") {
        printf("\t[0.5, 1): %-5d\n", $hash_range_TotalRemoved{$key});
    } elsif ($key eq "C") {
        printf("\t[1,   2): %-5d\n", $hash_range_TotalRemoved{$key});
    } elsif ($key eq "D") {
        printf("\t[2,   4): %-5d\n", $hash_range_TotalRemoved{$key});
    } elsif ($key eq "E") {
        printf("\t[4,   8): %-5d\n", $hash_range_TotalRemoved{$key});
    } elsif ($key eq "F") {
        printf("\t[8,    ): %-5d\n", $hash_range_TotalRemoved{$key});
    }
}

printf("Failed(毫秒):\n");
foreach $key (sort keys %hash_range_Failed) {
    if ($key eq "A") {
        printf("\t[,  0.5): %-5d\n", $hash_range_Failed{$key});
    } elsif ($key eq "B") {
        printf("\t[0.5, 1): %-5d\n", $hash_range_Failed{$key});
    } elsif ($key eq "C") {
        printf("\t[1,   2): %-5d\n", $hash_range_Failed{$key});
    } elsif ($key eq "D") {
        printf("\t[2,   4): %-5d\n", $hash_range_Failed{$key});
    } elsif ($key eq "E") {
        printf("\t[4,   8): %-5d\n", $hash_range_Failed{$key});
    } elsif ($key eq "F") {
        printf("\t[8,    ): %-5d\n", $hash_range_Failed{$key});
    }
}

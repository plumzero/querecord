
#!/usr/bin/env perl -w

# *******************************************
# Script Status: 完结 
# Creation Data:
# Last Modified:
# Author:
# E-mail:
# *******************************************
# Description: 更快地读取 INFO 日志，统计订单状态，数量与占比
#              处理速度比 awk shell 快 5 倍
#              两种脚本运行结果一致
# *******************************************
# Usage:
#   perl get_order_status.pl
#   perl get_order_status.pl 20210104
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

my $status_string_None              = "None";
my $status_string_Pending           = "Pending";
my $status_string_Accepted          = "Accepted";
my $status_string_Removing          = "Removing";
my $status_string_PartialMatch      = "PartialMatch";
my $status_string_TotalMatch        = "TotalMatch";
my $status_string_PartialRemoved    = "PartialRemoved";
my $status_string_TotalRemoved      = "TotalRemoved";
my $status_string_Failed            = "Failed";

my %hash_status;
my %hash_status_moment;

foreach (@specified_log_files)
{
    open(DATA, "<$_") or die "open $_ failed: $!\n";
    
    while (<DATA>)
    {
        if (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*STATUS None.*\|(?<reqid>\d+)\|/) {
            $hash_status{$+{reqid}} = $status_string_None;
            $hash_status_moment{$+{reqid}} = $+{moment};
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*STATUS Pending.*\|(?<reqid>\d+)\|/) {
            $hash_status{$+{reqid}} = $status_string_Pending;
            $hash_status_moment{$+{reqid}} = $+{moment};
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*STATUS Accepted.*\|(?<reqid>\d+)\|/) {
            $hash_status{$+{reqid}} = $status_string_Accepted;
            $hash_status_moment{$+{reqid}} = $+{moment};
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*STATUS Removing.*\|(?<reqid>\d+)\|/) {
            $hash_status{$+{reqid}} = $status_string_Removing;
            $hash_status_moment{$+{reqid}} = $+{moment};
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*STATUS PartialMatch.*\|(?<reqid>\d+)\|/) {
            $hash_status{$+{reqid}} = $status_string_PartialMatch;
            $hash_status_moment{$+{reqid}} = $+{moment};
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*STATUS TotalMatch.*\|(?<reqid>\d+)\|/) {
            $hash_status{$+{reqid}} = $status_string_TotalMatch;
            $hash_status_moment{$+{reqid}} = $+{moment};
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*STATUS PartialRemoved.*\|(?<reqid>\d+)\|/) {
            $hash_status{$+{reqid}} = $status_string_PartialRemoved;
            $hash_status_moment{$+{reqid}} = $+{moment};
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*STATUS TotalRemoved.*\|(?<reqid>\d+)\|/) {
            $hash_status{$+{reqid}} = $status_string_TotalRemoved;
            $hash_status_moment{$+{reqid}} = $+{moment};
        } elsif (/(?<moment>[\d]{2}:[\d]{2}:[\d]{2}\.[\d]{6}).*STATUS Failed.*\|(?<reqid>\d+)\|/) {
            $hash_status{$+{reqid}} = $status_string_Failed;
            $hash_status_moment{$+{reqid}} = $+{moment};
        }
    }
    
    close(DATA);
}

printf("当前时间: %s\n", `date +%H:%M:%S`);

printf("========================= 订单状态一揽 =========================\n");

my $total_counter = 0;

my %hash_status_counter;

my %hash_status_TotalMatch;
my %hash_status_PartialRemoved;
my %hash_status_TotalRemoved;
my %hash_status_Failed;

foreach $key (keys %hash_status) {
    $hash_status_counter{$hash_status{$key}}++;
    $total_counter++;
    
    if ($hash_status{$key} eq $status_string_TotalMatch) {
        $hash_status_TotalMatch{$total_counter} = $key; 
    } elsif ($hash_status{$key} eq $status_string_PartialRemoved) {
        $hash_status_PartialRemoved{$total_counter} = $key;
    } elsif ($hash_status{$key} eq $status_string_TotalRemoved) {
        $hash_status_TotalRemoved{$total_counter} = $key;
    } elsif ($hash_status{$key} eq $status_string_Failed) {
        $hash_status_Failed{$total_counter} = $key;
    }
}

printf("total_counter=%d\n", $total_counter);

printf("状态  数量  占比(%)\n");
foreach $key (keys %hash_status_counter) {
    printf("%-15s   %-5d   %5.2f%%\n", $key, $hash_status_counter{$key}, $hash_status_counter{$key} * 100 / $total_counter);
}

my $line_break = 26;

my $flag = 0;

foreach $key (keys %hash_status_counter) {
    printf("具体订单号: %s\n", $key);
    
    $flag = 0;
    
    if ($key eq $status_string_TotalMatch) {
        # foreach $k (keys %hash_status_TotalMatch) {
            # printf("%d ", $hash_status_TotalMatch{$k});
            # if (++$flag % $line_break == 0) {
                # printf("\n");
            # }
        # }
    } elsif ($key eq $status_string_PartialRemoved) {
        foreach $k (keys %hash_status_PartialRemoved) {
            printf("%d ", $hash_status_PartialRemoved{$k});
            if (++$flag % $line_break == 0) {
                printf("\n");
            }
        }
    } elsif ($key eq $status_string_TotalRemoved) {
        foreach $k (keys %hash_status_TotalRemoved) {
            printf("%d ", $hash_status_TotalRemoved{$k});
            if (++$flag % $line_break == 0) {
                printf("\n");
            }
        }
    } elsif ($key eq $status_string_Failed) {
        foreach $k (keys %hash_status_Failed) {
            printf("%d ", $hash_status_Failed{$k});
            if (++$flag % $line_break == 0) {
                printf("\n");
            }
        }
    }
    printf("\n");
}

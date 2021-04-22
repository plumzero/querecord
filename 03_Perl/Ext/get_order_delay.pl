
#!/usr/bin/env perl -w

# *******************************************
# Script Status: 完结 
# Creation Data:
# Last Modified:
# Author:
# E-mail:
# *******************************************
# Description: 获取每个对象状态与状态之间的延迟(间隔)
# *******************************************
# Usage:
#   perl get_order_delay.pl
#   perl get_order_delay.pl 20210104
# *******************************************

BEGIN{push(@INC,"/path/to/perl/5.22.1")};

use POSIX qw(strftime);
use JSON;
use OrderDelay;

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

my $string_end_status_TotalMatch        = "TotalMatch";
my $string_end_status_PartialRemoved    = "PartialRemoved";
my $string_end_status_TotalRemoved      = "TotalRemoved";
my $string_end_status_Failed            = "Failed";

%hash_order_delay;

foreach (@specified_log_files)
{
    open(DATA, "<$_") or die "open $_ failed: $!\n";
    
    while (<DATA>)
    {
        if (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS None.*\|(?<reqid>\d+)\|/) {         
            my $id = $+{reqid};
            my $timepoint = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            
            $hash_order_delay{$id} = new OrderDelay();
            $hash_order_delay{$id}->setReqid($id);
            $hash_order_delay{$id}->setNone($timepoint);
            
            $hash_timepoint_None{$id} = $timepoint;
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS Pending.*\|(?<reqid>\d+)\|/) {
            my $id = $+{reqid};
            my $timepoint = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            
            $hash_order_delay{$id}->setNonePending($timepoint - $hash_timepoint_None{$id});
            
            $hash_timepoint_Pending{$id} = $timepoint;
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS Accepted.*\|(?<reqid>\d+)\|/) {
            my $id = $+{reqid};
            my $timepoint = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            
            $hash_order_delay{$id}->setPendingAccepted($timepoint - $hash_timepoint_Pending{$id});
            
            $hash_timepoint_Accepted{$id} = $timepoint;
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS Removing.*\|(?<reqid>\d+)\|/) {
            ## do nothing
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS PartialMatch.*\|(?<reqid>\d+)\|/) {
            ## do nothing
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS TotalMatch.*\|(?<reqid>\d+)\|/) {
            my $id = $+{reqid};
            my $timepoint = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            
            $hash_order_delay{$id}->setAcceptedTotalMatch($timepoint - $hash_timepoint_Accepted{$id});
            $hash_order_delay{$id}->setEndState($string_end_status_TotalMatch);
            
            $hash_timepoint_TotalMatch{$id} = $timepoint;
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS PartialRemoved.*\|(?<reqid>\d+)\|/) {
            my $id = $+{reqid};
            my $timepoint = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            
            $hash_order_delay{$id}->setAcceptedPartialRemoved($timepoint - $hash_timepoint_Accepted{$id});
            $hash_order_delay{$id}->setEndState($string_end_status_PartialRemoved);
            
            $hash_timepoint_PartialRemoved{$id} = $timepoint;
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS TotalRemoved.*\|(?<reqid>\d+)\|/) {
            my $id = $+{reqid};
            my $timepoint = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            
            $hash_order_delay{$id}->setPendingTotalRemoved($timepoint - $hash_timepoint_Pending{$id});
            $hash_order_delay{$id}->setEndState($string_end_status_TotalRemoved);
            
            $hash_timepoint_TotalRemoved{$id} = $timepoint;
        } elsif (/(?<hour>[\d]{2}):(?<minute>[\d]{2}):(?<second>[\d]{2})\.(?<micros>[\d]{6}).*STATUS Failed.*\|(?<reqid>\d+)\|/) {
            my $id = $+{reqid};
            my $timepoint = ($+{hour} * 3600 + $+{minute} * 60 + $+{second}) * 1000000 + $+{micros};
            
            $hash_order_delay{$id}->setPendingFailed($timepoint - $hash_timepoint_Pending{$id});
            $hash_order_delay{$id}->setEndState($string_end_status_Failed);
            
            $hash_timepoint_Failed{$id} = $timepoint;
        }
    }
    
    close(DATA);
}

printf("当前时间: %s\n", strftime("%Y-%m-%d %H:%M:%S", localtime));
printf("数据历史: %s\n", $whichday);

my $xsjson = JSON->new->utf8()->convert_blessed(1)->encode(\%hash_order_delay);

my $filename = "order_delay_" . strftime("%Y_%m_%d", localtime) . ".txt";
open(OUT, ">$filename") or die "open $filename for writing failed: $!\n";
print(OUT $xsjson) or die "output to $filename failed: $!\n";
close(OUT);

printf("========================= 处理完成 =========================\n");


#!/usr/bin/env perl -w

my @months = qw(一月 二月 三月 四月 五月 六月 七月 八月 九月 十月 十一月 十二月);
my @days = qw(星期天 星期一 星期二 星期三 星期四 星期五 星期六);

my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = localtime();
print("$mday $months[$mon] $days[$wday]\n");
print("$hour:$min:$sec\n");

print("-----------------------------------------------------\n");

my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = localtime();
printf("格式化时间: HH:MM:SS\n");
printf("%02d:%02d:%02d\n", $hour, $min, $sec);

print("-----------------------------------------------------\n");

my $epoch = time();
print("从1970年1月1日00:00:00起累计的秒数: $epoch\n");

print("-----------------------------------------------------\n");

my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = localtime();
print("当前时间和日期: ");
printf("%d-%d-%d %d:%d:%d\n", $year+1900, $mon+1, $mday, $hour, $min, $sec);

print("-----------------------------------------------------\n");

use POSIX qw(strftime);

my $datastring = strftime("%Y-%m-%d %H:%M:%s", localtime);
print("时间日期 - $datestring\n");

# GMT 格式化时间日期
my $datestring = strftime("%Y-%m-%d %H:%M:%S", gmtime);
print("时间日期 - $datestring\n");

print("-----------------------------------------------------\n");




#!/usr/bin/env perl -w

BEGIN{push(@INC, "/path/to/this")};

use StatUtil;
use Util;

# perl stat.periods.pl /path/to/121

$args_cnt = @ARGV;
if ($args_cnt != 1) {
  print "param error: ./exe <file-path>";
  return ;
}

my $dir_path = $ARGV[0];
my $stat_file = "./stat.txt";

my @periods = Util::get_periods "185519_5", "190519_5";

my $is_header = 1;
my $dir_path = "/path/to/121/";
my $stat_file = "./stat.txt";
foreach (@periods) {
  StatUtil::stat_period $dir_path . $_, $stat_file, $is_header;
  $is_header = 0;
}


#!/usr/bin/env perl -w

BEGIN{push(@INC, "/path/to/this")};

use StatUtil;
use Util;

$args_cnt = @ARGV;
if ($args_cnt != 1) {
  print "param error: ./exe <file-path>\n";
  return ;
}

my $dir_path = $ARGV[0];
my $stat_file = "./stat.txt";

# for example
# dir_path: /path/to/121/185519
# stat_file: ./stat.txt
StatUtil::stat_period $dir_path, $stat_file, 1;
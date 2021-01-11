
#!/usr/bin/env perl -w

use strict;

my $now = `date`;
print "The time now is $now";

chomp(my $no_newline_now = `date`);
print "The time now is $no_newline_now\n";

my $now_qx = qx(date);
print "The time now is $now_qx";

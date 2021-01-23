
#!/usr/bin/env perl -w

use File::Basename;

my $name = "/usr/local/bin/perl";

my $basename = basename $name;
my $dirname = dirname $name;

print "basename of $name is $basename\n";
print "dirname of $name is $dirname\n";
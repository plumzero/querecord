
#!/usr/bin/env perl -w

use strict;

$_ = "yabba dabba doo";
if (/abba/) {
    print "It matched.\n";
}

my $pattern = "abba";
$_ = "yabba dabba doo";
if (/$pattern/) {
    print "It matched.\n";
}

$pattern = "20210104";
$_ = "today is 20210104";
if (/$pattern/) {
    print "It matched.\n";
}

$pattern = 20210104;
$_ = "today is 20210104";
if (/$pattern/) {
    print "It matched.\n";
}

# my $whichday = `date +%y%m%d`;
# print "$whichday\n";
# $_ = "today is 20210103";
# if (/$whichday/) {
    # print "it matched.\n";
# }

my $whichday = sprintf("%d", `date +%Y%m%d`);
$_ = "today is 20210103";
if (/$whichday/) {
    print "It matched.\n";
}


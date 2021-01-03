
#!/usr/bin/env perl

use strict;
use warnings;

my @files = `ls -l`;

foreach $a (@files) {
    print $a;
}

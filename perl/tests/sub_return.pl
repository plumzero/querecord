
#!/usr/bin/env perl -w

use strict;

sub return_array
{
    return (1..9);
}

my @array = &return_array();

foreach (@array) {
    print $_ . " ";
}
print "\n";


sub return_hash
{
    return ("key1" => 100, "key2" => 200);
}

my %hash = &return_hash();

foreach my $key (keys %hash) {
    print "$key : $hash{$key}\n";
}
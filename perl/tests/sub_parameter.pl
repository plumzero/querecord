
#!/usr/bin/env perl -w

use strict;

sub print_array
{
    foreach (@_) {
        print $_ . " ";
    }
    print "\n";
}

my @array = (1, 3, 5, 7, 9);

print_array(@array);


sub print_hash
{
    # my (%hash) = @_;
    
    foreach (@_) {
        print $_ . " ";
    }
    print "\n";
    
    # foreach my $key (keys %hash) {
        # my $value = $hash{$key};
        # print "$key : $value\n";
    # }
}

    
my %hash = ('name' => "runoob", 'age' => 3);

print_hash(%hash);


sub print_hash_2
{
    my (%hash) = @_;
    
    foreach my $key (keys %hash) {
        my $value = $hash{$key};
        print "$key : $value\n";
    }
}

%hash = ('name' => "runoob", 'age' => 3);

print_hash_2(%hash);

sub max {
    my($max_so_far) = shift @_;
    foreach (@_) {
        if ($_ > $max_so_far) {
            $max_so_far = $_;
        }
    }
    $max_so_far;
}

my $maxinum = &max(3, 5, 10, 4, 6);
print "maxinum=" . $maxinum . "\n";

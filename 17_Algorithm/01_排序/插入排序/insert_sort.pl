#!/usr/bin/env perl -w

sub insert_sort {
    $len = @_;
    for (my $i = 1; $i < $len; $i++) {
        my $j = $i - 1;
        my $ele = $_[$i];
        while ($j >= 0 && $_[$j] > $ele) {
            $_[$j+1] = $_[$j];
            $j--;
        }
        $_[$j+1] = $ele;
    }

    foreach (@_) {
        print $_ . " ";
    }
    print "\n";
}

sub insert_sort_desc {
    $len = @_;
    for (my $i = 1; $i < $len; $i++) {
        my $j = $i - 1;
        my $ele = $_[$i];
        while ($j >= 0 && $_[$j] < $ele) {
            $_[$j+1] = $_[$j];
            $j--;
        }
        $_[$j+1] = $ele;
    }

    foreach (@_) {
        print $_ . " ";
    }
    print "\n";
}

{
    my @arr = (3, 1, 4, 1, 5, 9, 2, 6 );
    insert_sort(@arr);
}

{
    my @arr = (3, 1, 4, 1, 5, 9, 2, 6 );
    insert_sort_desc(@arr);
}
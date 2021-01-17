
#!/usr/bin/env perl -w

{
    $_ = "Hello there, neighbor!";
    my ($first, $second, $third) = /(\S+) (\S+), (\S+)/;
    print "$second is my $third\n"
}

{
    my $text = "Fred dropped a 5 ton granite block on Mr. Slate";
    my @words = ($text =~ /[a-z]+/ig);
    print "Result: @words\n";
}

{
    my $data = "Barney Rubble Fred Flintstone Wilma Flintstone";
    my %last_name = ($data =~ /(\w+)\s+(\w+)/g);
    foreach my $key (keys %last_name) {
        print "$key => $last_name{$key}\n";
    }
}
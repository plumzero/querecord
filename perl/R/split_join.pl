
#!/usr/bin/env perl -w

{
    my @fields = split(/:/, "abc:def:g:h");
    foreach (@fields) {
        print $_ . " ";
    }
    print "\n";
}

{
    my @fields = split(/:/, "abc:def::g:h");
    foreach (@fields) {
        print $_ . " ";
    }
    print "\n";
}

{
    my $some_input = "This is a \t    test.\n";
    my @args = split(/\s+/, $some_input);
    foreach (@args) {
        print $_ . " ";
    }
    print "\n";
}

{
    my @fields = split(/:/, ":::a:b:c:::");
    foreach (@fields) {
        print $_ . " ";
    }
    print "\n";
}

{
    my $x = join(":", (4, 6, 8, 10, 12));
    print $x . "\n";
}

{
    my $x = "4:6:8:10:12";
    my @values = split(/:/, $x);
    my $z = join("-", @values);
    print $z . "\n";
}
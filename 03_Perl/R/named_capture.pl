
#!/usr/bin/env perl -w

my $names = 'Fred or Barney';
if ($names =~ m/(?<name1>\w+) (?:and|or) (?<name2>\w+)/) {
    print "I saw $+{name1} and $+{name2}\n";
}

my $names = 'Fred Flintstone and Wilma Flintstone';
if ($names =~ m/(?<last_name>\w+) and \w+ \g{last_name}/) {
    print "I saw $+{last_name}\n";
}
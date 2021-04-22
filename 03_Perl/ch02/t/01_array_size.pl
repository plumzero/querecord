
#!/usr/bin/env perl -w

my $rocks;

$rocks[0]  = 'bedrock';
$rocks[1]  = 'slate';
$rocks[2]  = 'lava';
$rocks[99] = 'schist';

$end = $#rocks;

$number_of_rocks = $end + 1;

print $end . "\n";

print $number_of_rocks . "\n";

$size = @rocks;

print $size . "\n";
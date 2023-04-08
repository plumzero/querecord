
#!/usr/bin/env perl -w

{
  my @array = (5, 6);

  push(@array, 0);
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n";

  push(@array, 1..10);
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n";

  @others = qw(9 0 2 1 0);
  push(@array, @others);
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n"; 
}

{
  my @array = (5, 6, 7, 8);
  
  my $fred = pop(@array);
  
  print "fred=" . $fred . "\n";
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @array . "\n";
}
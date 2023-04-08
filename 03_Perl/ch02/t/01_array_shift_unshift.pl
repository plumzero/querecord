
#!/usr/bin/env perl -w

{
  my @array = qw/ dino fred barney /;
  
  $m = shift(@array);
  print "m=" . $m . "\n";
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @array . "\n";
  
  unshift(@array, "wilma");
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @array . "\n";
}


#!/usr/bin/env perl -w

{
  my @array = qw( pebbles dino fred barney betty );
  my @removed = splice(@array, 2);
  
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @array . "\n";
  
  foreach $ele (@removed) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @removed . "\n";
}

{
  my @array = qw( pebbles dino fred barney betty );
  my @removed = splice(@array, 1, 2);
  
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @array . "\n";
  
  foreach $ele (@removed) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @removed . "\n";
}

{
  my @array = qw( pebbles dino fred barney betty );
  my @removed = splice(@array, 1, 2, qw/wilma/);
  
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @array . "\n";
  
  foreach $ele (@removed) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @removed . "\n";
}

{
  my @array = qw( pebbles dino fred barney betty );
  my @removed = splice(@array, 1, 0, qw/wilma/);
  
  foreach $ele (@array) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @array . "\n";
  
  foreach $ele (@removed) {
    print $ele . " ";
  }
  print "\n";
  print "size=" . @removed . "\n";
}
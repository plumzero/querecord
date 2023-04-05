
#!/usr/bin/env perl -w

package Util;

sub file_size
{
  my $filename = $_[0];
  my $size = -1;
  if (-e $filename) {
    my @args = stat($filename);
    $size = $args[7];
    if ($size > 1024) {
      return sprintf "%.2fK", $size / 1024;
    } elsif ($size > 1024 * 1024) {
      return sprintf "%.2fM", $size / 1024 / 1024;
    }
  }
  return $size;
}

sub frame_count
{
  my $filename = $_[0];
  my $count = -1;
  if (-e $filename) {
    if (`tail -n 1 $filename` =~ /,([\d]+),/) {
      $count = $1;
    }
  }
  return $count;
}

sub join_sperators
{
  my $count = $_[0] =~ tr/|/|/;
  my @arr = ();
  foreach (1..$count) {
    push(@arr, "|");
  }
  return join(":-", @arr);
}

sub join_fields
{
  my $content = join("|", @_);
  return "|" . $content . "|";
}

sub next_period
{
  my $period = $_[0];
  my $hour = substr($period, 0, 2);
  my $min = substr($period, 2, 2);
  my $sec = substr($period, 4, 2);

  my $carry = 0;
  if (($min + 5) % 60 < $min) {
    $carry = 1;
  }
  $min = ($min + 5) % 60;
  
  if ($carry == 1) {
    $hour += 1;
  }
  $hour = $hour % 24;
  
  return sprintf "%02d%02d%02d", $hour, $min, $sec;
}

sub get_periods
{
  my $start_period = substr($_[0], 0, 6);
  my $end_period = substr($_[1], 0, 6);
  my $suffix = substr($_[0], 6);

  my $cur_period = $start_period;
  my $nxt_period;
  my @periods = ();
  do {
    push(@periods, $cur_period . $suffix);
    $nxt_period = next_period($cur_period);
    $cur_period = $nxt_period;
  } while ($nxt_period != $end_period);

  push(@periods, $nxt_period . $suffix);

  return @periods;
}

1

#!/usr/bin/env perl -w

package Stat;

sub new
{
  my $class = shift;
  my $self = {
    period_name => shift,

    bag_duration => shift,
    bag_start => shift,
    bag_end => shift,
    bag_size => shift,
    bag_messages => shift,
    bag_topics => shift,

    cam_front1m_size => shift,
    cam_front1m_frames => shift,

    cam_left1m_size => shift,
    cam_left1m_frames => shift,

    cam_rear1m_size => shift,
    cam_rear1m_frames => shift,

    cam_right1m_size => shift,
    cam_right1m_frames => shift,
  };

  bless $self, $class;
  
  return $self;
}

sub set_period_name
{
  my ($self, $val) = @_;
  $self->{period_name} = $val if defined($val);
}

sub get_period_name
{
  my ($self) = @_;
  return $self->{period_name};
}

sub set_bag_duration
{
  my ($self, $val) = @_;
  $self->{bag_duration} = $val if defined($val);
}

sub get_bag_duration
{
  my ($self) = @_;
  return $self->{bag_duration};
}

sub set_bag_start
{
  my ($self, $val) = @_;
  $self->{bag_start} = $val if defined($val);
}

sub get_bag_start
{
  my ($self) = @_;
  return $self->{bag_start};
}

sub set_bag_end
{
  my ($self, $val) = @_;
  $self->{bag_end} = $val if defined($val);
}

sub get_bag_end
{
  my ($self) = @_;
  return $self->{bag_end};
}

sub set_bag_size
{
  my ($self, $val) = @_;
  $self->{bag_size} = $val if defined($val);
}

sub get_bag_size
{
  my ($self) = @_;
  return $self->{bag_size};
}

sub set_bag_messages
{
  my ($self, $val) = @_;
  $self->{bag_messages} = $val if defined($val);
}

sub get_bag_messages
{
  my ($self) = @_;
  return $self->{bag_messages};
}

sub set_bag_topics
{
  my ($self, $val) = @_;
  $self->{bag_topics} = $val if defined($val);
}

sub get_bag_topics
{
  my ($self) = @_;
  return $self->{bag_topics};
}

sub set_cam_front1m_size
{
  my ($self, $val) = @_;
  $self->{cam_front1m_size} = $val if defined($val);
}

sub get_cam_front1m_size
{
  my ($self) = @_;
  return $self->{cam_front1m_size};
}

sub set_cam_front1m_frames
{
  my ($self, $val) = @_;
  $self->{cam_front1m_frames} = $val if defined($val);
}

sub get_cam_front1m_frames
{
  my ($self) = @_;
  return $self->{cam_front1m_frames};
}

sub set_cam_left1m_size
{
  my ($self, $val) = @_;
  $self->{cam_left1m_size} = $val if defined($val);
}

sub get_cam_left1m_size
{
  my ($self) = @_;
  return $self->{cam_left1m_size};
}

sub set_cam_left1m_frames
{
  my ($self, $val) = @_;
  $self->{cam_left1m_frames} = $val if defined($val);
}

sub get_cam_left1m_frames
{
  my ($self) = @_;
  return $self->{cam_left1m_frames};
}
{
  my ($self, $val) = @_;
  $self->{cam_left1m_size} = $val if defined($val);
}

sub get_cam_left1m_size
{
  my ($self) = @_;
  return $self->{cam_left1m_size};
}

sub set_cam_left1m_frames
{
  my ($self, $val) = @_;
  $self->{cam_left1m_frames} = $val if defined($val);
}

sub get_cam_left1m_frames
{
  my ($self) = @_;
  return $self->{cam_left1m_frames};
}

sub set_cam_rear1m_size
{
  my ($self, $val) = @_;
  $self->{cam_rear1m_size} = $val if defined($val);
}

sub get_cam_rear1m_size
{
  my ($self) = @_;
  return $self->{cam_rear1m_size};
}

sub set_cam_rear1m_frames
{
  my ($self, $val) = @_;
  $self->{cam_rear1m_frames} = $val if defined($val);
}

sub get_cam_rear1m_frames
{
  my ($self) = @_;
  return $self->{cam_rear1m_frames};
}

sub set_cam_right1m_size
{
  my ($self, $val) = @_;
  $self->{cam_right1m_size} = $val if defined($val);
}

sub get_cam_right1m_size
{
  my ($self) = @_;
  return $self->{cam_right1m_size};
}

sub set_cam_right1m_frames
{
  my ($self, $val) = @_;
  $self->{cam_right1m_frames} = $val if defined($val);
}

sub get_cam_right1m_frames
{
  my ($self) = @_;
  return $self->{cam_right1m_frames};
}

1;

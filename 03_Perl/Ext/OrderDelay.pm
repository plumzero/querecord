
#!/usr/bin/env perl -w

package OrderDelay;

sub new
{
    my $class = shift;
    my $self = {
        reqid => shift,
        
        None => shift,
        
        None_Pending => shift,
        
        Pending_Accepted => shift,
        Pending_TotalRemoved => shift,
        Pending_Failed => shift,
        
        Accepted_TotalMatch => shift,
        Accepted_PartialRemoved => shift,
        
        end_state => shift,
    };

    bless $self, $class;
    
    return $self;
}

sub setReqid
{
    my ($self, $id) = @_;
    
    $self->{reqid} = $id if defined($id);
    
    return $self->{reqid};
}

sub getReqid
{
    my ($self) = @_;
    
    return $self->{reqid};
}

sub setNone
{
    my ($self, $timepoint) = @_;
    
    $self->{None} = $timepoint if defined($timepoint);
    
    return $self->{None};
}

sub getNone
{
    my ($self) = @_;
    
    return $self->{None};
}

sub setNonePending
{
    my ($self, $delay) = @_;
    
    $self->{None_Pending} = $delay if defined($delay);
    
    return $self->{None_Pending};
}

sub getNonePending
{
    my ($self) = @_;
    
    return $self->{None_Pending};
}

sub setPendingAccepted
{
    my ($self, $delay) = @_;
    
    $self->{Pending_Accepted} = $delay if defined($delay);
    
    return $self->{Pending_Accepted};
}

sub getPendingAccepted
{
    my ($self) = @_;
    
    return $self->{Pending_Accepted};
}

sub setPendingTotalRemoved
{
    my ($self, $delay) = @_;
    
    $self->{Pending_TotalRemoved} = $delay if defined($delay);
    
    return $self->{Pending_TotalRemoved};
}

sub getPendingTotalRemoved
{
    my ($self) = @_;
    
    return $self->{Pending_TotalRemoved};
}

sub setPendingFailed
{
    my ($self, $delay) = @_;
    
    $self->{Pending_Failed} = $delay if defined($delay);
    
    return $self->{Pending_Failed};
}

sub getPendingFailed
{
    my ($self) = @_;
    
    return $self->{Pending_Failed};
}

sub setAcceptedTotalMatch
{
    my ($self, $delay) = @_;
    
    $self->{Accepted_TotalMatch} = $delay if defined($delay);
    
    return $self->{Accepted_TotalMatch};
}

sub getAcceptedTotalMatch
{
    my ($self) = @_;
    
    return $self->{Accepted_TotalMatch};
}

sub setAcceptedPartialRemoved
{
    my ($self, $delay) = @_;
    
    $self->{Accepted_PartialRemoved} = $delay if defined($delay);
    
    return $self->{Accepted_PartialRemoved};
}

sub getAcceptedPartialRemoved
{
    my ($self) = @_;
    
    return $self->{Accepted_PartialRemoved};
}

sub setEndState
{
    my ($self, $state) = @_;
    
    $self->{end_state} = $state if defined($state);
    
    return $self->{end_state};
}

sub getEndState
{
    my ($self) = @_;
    
    return $self->{end_state};
}

sub TO_JSON
{
    return { %{ shift() } };
}

1;

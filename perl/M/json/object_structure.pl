
#!/usr/bin/env perl -w

package Person;

sub new
{
    my $class = shift;
    my $self = {
        _firstName => shift,
        _lastName => shift,
        _ssn => shift,
    };
    
    bless $self, $class;
    
    return $self;
}

sub setFirstName
{
    my ($self, $firstName) = @_;
    
    $self->{_firstName} = $firstName if defined($firstName);
    
    return $self->{_firstName};
}

sub setLastName
{
    my ($self, $lastName) = @_;
    
    $self->{_lastName} = $lastName if defined($lastName);
    
    return $self->{_lastName};
}

sub setSSN
{
    my ($self, $ssn) = @_;
    
    $self->{_ssn} = $ssn if defined($ssn);
    
    return $self->{_ssn};
}

sub TO_JSON
{
    return { %{ shift() } };
}


package main;

use JSON;

my %data;

$data{1} = new Person("XiaoMing", "Wang", 123456); 
$data{2} = new Person("XiaoLi", "Li", 123457);
$data{3} = new Person("DaQi", "Lin", 123458);
$data{4} = new Person("DaGang", "Zhao", 123459);

my $xsjson = JSON->new->utf8()->convert_blessed(1)->encode(\%data);

printf("xsjson=%s\n", $xsjson);

my %stdata = %{JSON->new->utf8()->convert_blessed(1)->allow_nonref(1)->decode($xsjson)};

foreach my $key (keys %stdata)
{   
    my %person = %{$stdata{$key}};
    
    foreach my $k (keys %person)
    {
        if ($k eq "_firstName") {
            printf("first name is: %s\n", $person{$k});
        } elsif ($k eq "_lastName") {
            printf("last name is: %s\n", $person{$k});
        } elsif ($k eq "_ssn") {
            printf("ssn is: %d\n", $person{$k});
        } else {
            printf("error! no this member %s\n", $k);
        }
    }
}


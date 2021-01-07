
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

my $object = new Person("XiaoMing", "Wang", 123456);    
$data{1} = $object;   
$data{2} = new Person("XiaoLi", "Li", 123457);
$data{3} = new Person("DaQi", "Lin", 123458);
$data{4} = new Person();

my $xsjson = JSON->new->utf8()->convert_blessed(1)->encode(\%data);

printf("xsjson=%s\n", $xsjson);

### 修改
$data{3}->setFirstName("XiaoQi");

my $xsjson = JSON->new->utf8()->convert_blessed(1)->encode(\%data);

printf("xsjson=%s\n", $xsjson);

### 填参
$data{4}->setFirstName("DaGang");
$data{4}->setLastName("Zhao");
$data{4}->setSSN(1234569);

my $xsjson = JSON->new->utf8()->convert_blessed(1)->encode(\%data);

printf("xsjson=%s\n", $xsjson);
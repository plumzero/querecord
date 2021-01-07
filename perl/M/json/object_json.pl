
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
    
    print "firstName: $self->{_firstName}\n";
    print "lastName: $self->{_lastName}\n";
    print "ssn: $self->{_ssn}\n";
    
    bless $self, $class;
    
    return $self;
}

sub setFirstName
{
    my ($self, $firstName) = @_;
    
    $self->{_firstName} = $firstName if defined($firstName);
    
    return $self->{_firstName};
}

sub getFirstName
{
    my ($self) = @_;
    
    return $self->{_firstName};
}

sub TO_JSON
{
    return { %{ shift() } };
}


package main;

use JSON;

{
    my $object = new Person("小明", "王", 123456);

    my $firstName = $object->getFirstName();

    printf("设置前姓名为: %s\n", $firstName);

    $object->setFirstName("小强");

    $firstName = $object->getFirstName();

    printf("设置后姓名为: %s\n", $firstName);
}


{
    my $json = JSON->new->utf8();

    $json->convert_blessed(1);
    
    my $object = new Person("XiaoMing", "Wang", 123456);
    
    $sjson = $json->encode($object);
    
    printf("sjson=%s\n", $sjson);
}



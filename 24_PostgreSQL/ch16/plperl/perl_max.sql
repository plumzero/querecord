
CREATE FUNCTION perl_max(integer, integer)
RETURNS integer AS
$$
    my ($x, $y) = @_;
    if (not defined $x) {
        return undef if not defined $y;
        return $y;
    }
    return $x if not defined $y;
    return $x if $x > $y;
    return $y;
$$
LANGUAGE plperl;

SELECT perl_max(10, 20);

DROP FUNCTION IF EXISTS perl_max(integer, integer);

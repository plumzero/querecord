
#!/usr/bin/env perl -w

use DBI;
use strict;

my $host = "127.0.0.1";
my $port = 5432;
my $driver = "Pg";
my $database = "testdb";
my $dsn = "DBI:$driver:database=$database;host=$host;port=$port";
my $userid = "postgres";
my $password = "1234";

my $dbh = DBI->connect($dsn, $userid, $password) or die $DBI::errstr;

print "Opened database successfully\n";

my $stmt = qq(UPDATE COMPANY set SALARY = 25000.00 where ID = 1;);

my $rv = $dbh->do($stmt) or die $DBI::errstr;
if ($rv < 0) {
    print $DBI::errstr;
} else {
    print "Total number of rows updated: $rv\n";
}

$stmt = qq(SELECT id, name, address, salary from COMPANY;);

my $sth = $dbh->prepare($stmt);

$rv = $sth->execute() or die $DBI::errstr;
if ($rv < 0) {
    print $DBI::errstr
}

while (my @row = $sth->fetchrow_array()) {
    print "ID = " . $row[0] . "\n";
    print "NAME = " . $row[1] . "\n";
    print "ADDRESS = " . $row[2] . "\n";
    print "SALARY = " . $row[3] . "\n\n";
}

print "operation done successfully\n";

$sth->finish();

$dbh->disconnect();
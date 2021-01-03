
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

my $stmt = qq(INSERT INTO COMPANY(ID, NAME, AGE, ADDRESS, SALARY)
              VALUES (1, 'Paul', 32, 'California', 20000.00),
                     (2, 'Allen', 25, 'Texas', 15000.00),
                     (3, 'Teddy', 23, 'Norway', 2000.00)
             );

my $rv = $dbh->do($stmt) or die $DBI::errstr;

$stmt = qq(INSERT INTO COMPANY(ID, NAME, AGE, ADDRESS, SALARY)
           VALUES(4, 'Mark', 25, 'Rich-Mond', 65000.00));

$rv = $dbh->do($stmt) or die $DBI::errstr;

print "records inserted successfully\n";

$dbh->disconnect();

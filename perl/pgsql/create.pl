
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

my $stmt = qq(CREATE TABLE COMPANY
             (ID        INT PRIMARY KEY     NOT NULL,
              NAME      TEXT                NOT NULL,
              AGE       INT                 NOT NULL,
              ADDRESS   CHAR(50),
              SALARY    REAL
             );
             );
        

my $rv = $dbh->do($stmt);
if ($rv < 0) {
    print $DBI::errstr;
} else {
    print "created table successfully\n";
}

$dbh->disconnect();
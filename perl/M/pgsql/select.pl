
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

my $stmt = qq(SELECT id, name, address, salary from COMPANY;);

# 预处理 SQL
my $sth = $dbh->prepare($stmt);

# 执行 SQL
my $rv = $sth->execute() or die $DBI::errstr;
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

# 释放语句句柄
$sth->finish();

$dbh->disconnect();
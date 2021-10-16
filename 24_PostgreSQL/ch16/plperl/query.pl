
\o /dev/null

DO
$$
    # 指定行数获取
    {
        my $query = "SELECT * FROM tbl_trade_order";
        my %rvs = %{spi_exec_query($query, 5)};
        my $status = $rvs{'status'};
        my $nrows = $rvs{'processed'};

        elog(NOTICE, "执行状态: $status, 返回行数: $nrows");

        foreach my $rn (0 .. $nrows - 1) {
            my %row = %{$rvs{rows}[$rn]};
            foreach my $field (keys %row) {
                # elog(INFO, "$field => $row{$field}");
            }
        }
    }

    # 一行一行获取，用于表数据行数过多时
    # spi_query + spi_fetchrow 组合
    {
        my $counter = 0;
        my $query = "SELECT * FROM tbl_trade_order";
        my $sth = spi_query($query);
        while (defined ($row = spi_fetchrow($sth))) {
            my $id = $row->{'id'};
            my $serverId = $row->{'serverId'};
            $counter += 1;
            elog(INFO, "$id, $serverId");
        }
        elog(INFO, "---> $counter");
    }

$$ LANGUAGE plperl;

\o
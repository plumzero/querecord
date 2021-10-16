
-- 读文件，获得映射表
CREATE OR REPLACE FUNCTION set_group_kvs(fname text)
RETURNS void AS
$$
    use warnings;
    use encoding "utf-8";

    open(FH, "<$_[0]")
        or elog(ERROR, "cannot open $_0 for reading: ($!)");
    while ($line = <FH>) {
        my $id;
        my $group;
        chomp($line);
        my @fields = split(/,/, $line);
        foreach my $field (@fields) {
            my @kv = split(/:/, $field);
            if ($kv[0] eq "id") {
                $id = $kv[1];
            } elsif ($kv[0] eq "group") {
                $group = $kv[1];
            }
        }
        $_SHARED{$id} = $group;
    }
$$
LANGUAGE plperlu;

-- 根据键获取值，键为 accountid
CREATE OR REPLACE FUNCTION get_group_val(k text)
RETURNS text AS
$$
    return $_SHARED{$_[0]};
$$
LANGUAGE plperlu;

-- 写入文件
CREATE OR REPLACE FUNCTION write_to_file(fname text, lns text)
RETURNS void AS
$$
    use warnings;
    use encoding "utf-8";

    open(FH, ">>$_[0]")
        or elog(ERROR, "cannot open $_0 for append: ($!)");

    print FH $_[1];

    close(FH);
$$
LANGUAGE plperlu;

-- 处理流程
DO
$$
DECLARE
    _infilepath text;
    _outfilepath text;
    _group text;
    _accountid text;
BEGIN
    -- 必须要使用绝对路径
    _infilepath := '/path/to/file';
    PERFORM set_group_kvs(_infilepath);

    SELECT '9574' INTO _accountid;
    SELECT get_group_val(_accountid) INTO _group;
    RAISE INFO '%', _group;

    -- 写入文件
    -- 如果要写入换行，可以通过 format 格式化，如下:
    --  SELECT format(E'%s\n', _group) INTO _group;
    _outfilepath := '/tmp/out.txt';
    PERFORM write_to_file(_outfilepath, _group);
END;
$$ LANGUAGE plpgsql;

-- 消除
DROP FUNCTION IF EXISTS set_group_kvs(text);
DROP FUNCTION IF EXISTS get_group_val(text);
DROP FUNCTION IF EXISTS write_to_file(text, text);

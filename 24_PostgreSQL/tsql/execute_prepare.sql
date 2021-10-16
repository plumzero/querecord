
CREATE TABLE IF NOT EXISTS tbl_exprepare(id integer, place text, ok boolean);

PREPARE fooplan(integer, text, boolean) AS
    INSERT INTO tbl_exprepare(id,place,ok) VALUES($1,$2,$3);

EXECUTE fooplan(1, 'Hunter Valley', 't');

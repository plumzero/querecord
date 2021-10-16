
CREATE OR REPLACE FUNCTION set_var(name text, var text) RETURNS
text AS $$
    if ($_SHARED{$_[0]} = $_[1]) {
        return 'ok';
    } else {
        return "cannot set shared variable $_[0] to $_[1]";
    }
$$ LANGUAGE plperl;

CREATE OR REPLACE FUNCTION get_var(name text) RETURNS text AS $$
    return $_SHARED{$_[0]};
$$ LANGUAGE plperl;

SELECT set_var('sample', 'Hello, PL/Perl! How is tricks?');
SELECT get_var('sample');

DROP FUNCTION IF EXISTS set_var(text, text);
DROP FUNCTION IF EXISTS get_var(text);

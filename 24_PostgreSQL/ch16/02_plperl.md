
编写 plperl 脚本，你需要了解一些 Perl 的语法。

plperl 脚本的编写方法参考 postgres-13 手册 PL/Perl 部分，具体页数为 1285 ~ 1300 。


```sql
    DO $$
        # PL/Perl code
    $$ LANGUAGE plperl;
```
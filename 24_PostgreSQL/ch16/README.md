
PostgreSQL 支持多种形式的语言编写脚本，如 plpgsql、plperl、plpython 和 pltcl 等。其中 plpgsql 是默认就有的，是 PostgreSQL 的原生脚本语言，语法简单，所提供的函数也满足绝大多数使用需求。

不过 plpgsql 对外部文件(如磁盘文件)读写支持度不太友好，所提供的数据结构也较单一，这个时候使用者可以使用 plperl 或 plpython 来达到这些开发需求。

这里简单介绍 plpgsql 和 plperl 脚本的编写。

plpgsql 脚本中可以直接使用 PostgreSQL 提供的很多函数，也可以在脚本中直接执行 SQL 语句，很是方便。

plperl 在处理一些复杂场景时可能会派上用场，如复杂数据结构处理、与磁盘文件交互等。不过 plperl 无法直接使用 PostgreSQL 提供的函数，而且需要通过相应函数动态执行 SQL 语句。

现实中，也可以将二者结合在一起使用。

[plpgsql脚本参考](plpgsql)

[plperl脚本参考](plperl)

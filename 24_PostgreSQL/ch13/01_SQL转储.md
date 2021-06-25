
SQL转储就是将数据对象通过工具输出到由 SQL 命令组成的文件中，也可以称为转储数据，PostgreSQL 提供了 `pg_dump` 和 `pg_dumpall` 工具进行 SQL 转储，这两个工具都不会阻塞其他数据库请求。

pg_dump 和 pg_dumpall 用法大致相同，只是 pg_dump 只能转储单个数据库，如果需要转储数据库的全局对象，则使用 pg_dumpall。


### SQL转储

pg_dump 的用法为:
```shell
    pg_dump [OPTION]... [DBNAME]
```
pg_dump 常用的 `OPTION` 可选项有:
* `-F, --format=c|d|t|p`: 这个参数选择 dump 输出的文件格式，可选的值有:
    * `c`: 输出一个自定义的格式
    * `d`: 将表和其他对象输出为文件，并保存在一个目录中
    * `t`: 输出为 tar 包
    * `p`: 输出为纯文本 SQL 脚本
* `-j, --jobs=NUM`: 当使用目录输出格式(F 参数的值为 d)时，可以同时开始多少个表进行 dump 。
* `-a, --data-only`: 只 dump 表中的数据。
* `-c, --clean`: 在重建前先 DROP 准备重建的对象。
* `-C, --create`: 包含创建 Database 的命令。
* `-n, --schema-only`: 指定 Schema 。
* `-N, --exclude-schema=SCHEMA`: 排除指定的 Schema 。
* `-t, --table=TABLE`: 指定转储包含的表。
* `-T, --exclude-table=TABLE`: 指定转储时不包含的表。
* `--inserts`, `--column-inserts`: 默认地，pg_dump 输出的 SQL 文件内使用 PostgreSQL 特有的 COPY 命令，可以使用这两个参数指定转储出的 SQL 文件使用 INSERT 命令。该方式通过逐行插入数据的恢复方式会比较缓慢，但用于非 PostgreSQL 的异构数据库是非常有用的。

关于 `--inserts --column-inserts` 的不使用与使用转储结果对比:
示例命令:
```shell
    postgres$: pg_dump -Fp -a --inserts --column-inserts -t mytable -p 5432 mydb > mydb.mytable.sql
```

不使用 `--inserts --column-inserts`:
```sql
    COPY public.score (id, subject, stu_name, score) FROM stdin;
    1	Chinese	francs	70
    2	Chinese	matiler	70
    3	Chinese	tutu	80
    4	English	matiler	75
    5	English	francs	90
    6	English	tutu	60
    7	Math	francs	80
    8	Math	matiler	99
    9	Math	tutu	65
    \.
```

使用 `--inserts --column-inserts`:
```sql
    INSERT INTO public.score (id, subject, stu_name, score) VALUES (1, 'Chinese', 'francs', 70);
    INSERT INTO public.score (id, subject, stu_name, score) VALUES (2, 'Chinese', 'matiler', 70);
    INSERT INTO public.score (id, subject, stu_name, score) VALUES (3, 'Chinese', 'tutu', 80);
    INSERT INTO public.score (id, subject, stu_name, score) VALUES (4, 'English', 'matiler', 75);
    INSERT INTO public.score (id, subject, stu_name, score) VALUES (5, 'English', 'francs', 90);
    INSERT INTO public.score (id, subject, stu_name, score) VALUES (6, 'English', 'tutu', 60);
    INSERT INTO public.score (id, subject, stu_name, score) VALUES (7, 'Math', 'francs', 80);
    INSERT INTO public.score (id, subject, stu_name, score) VALUES (8, 'Math', 'matiler', 99);
    INSERT INTO public.score (id, subject, stu_name, score) VALUES (9, 'Math', 'tutu', 65);
```

pg_dumpall 用法参数与 pg_dump 大致相同，但可以转储数据库中的全局对象，例如所有数据库用户:
```shell
    postgres$ pg_dumpall -r -p 5432
```


### SQL转储的恢复

当转储的格式是纯文本形式时，使用 psql 运行转储出的 SQL 文本即可。例如:
```shell
    postgres$ psql -p 5432 mydb < mydb.mytable.sql
```

当转
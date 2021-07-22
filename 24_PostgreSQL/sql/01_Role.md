
### CREATE ROLE

为数据库集簇添加新的数据库角色。角色作为一个实体可以拥有数据库对象并具有数据库相关的权限。角色可以视为"用户"或"组"，或者二者兼具，这取决于使用场景。

```sql
    CREATE ROLE name [ [ WITH ] option [ ... ] ]
```
`option` 可取值(部分)有:
* `LOGIN` 和 `NOLOGIN`: 是否允许该角色登录。默认为`NOLOGIN`。
* `CONNECTION LIMIT connlimit`: 如果该角色可登录，则设定该角色可连接数。默认为 -1，表示无限制。
* `[ENCRYPTED] PASSWORD 'password'`: 指定角色的登录密码。最好使用 ENCRYPTED 加密密码。
* `VALID UNTIL 'timestamp'`: 设定角色密码的有效期限。缺省为永久。

注意: 通过 `ALTER ROLE` 可以改变角色属性，通过 `DROP ROLE` 可以移除一个角色。不过，更好的做法是使用 `GRANT` 和 `REVOKE` 代替前面两个命令。

示例: 创建一个可登录的角色 jonathan:
```sql
    CREATE ROLE jonathan LOGIN;
```

示例: 创建一个可登录的角色，设置密码并设定密码有效期限:
```sql
    CREATE ROLE miriam WITH LOGIN PASSWORD 'jw8s0F4' VALID UNTIL '2005-01-01';
```


### GRANT

定义访问权限。

`GRANT` 有两类不同的用法，一种是为数据库对象(如表、列、视图、序列、数据库、函数、过程、表空间等)赋权，另一种是赋予角色某些权限。

第一种做法是将数据库对象的一些权限赋给一些角色。将数据库对象的权限赋给其所有者是没有必要的，因为该对象所有者已经具有了关于这个数据库对象的所有权限。但是数据库对象的所有者可以自己选择是否来取消对数据库对象的某些权限。这类权限有:
* `SELECT`
* `INSERT`
* `UPDATE`
* `DELETE`
* `TRUNCATE`
* `REFERENCES`
* `TRIGGER`
* `CREATE`
* `CONNECT`
* `TEMPORARY`
* `EXECUTE`
* `USAGE`
* `ALL PRIVILEGES`: 将数据库对象的所有权限赋给某个角色，`PRIVILEGES` 可忽略。

```sql
    GRANT { { SELECT | INSERT | UPDATE | DELETE | TRUNCATE | REFERENCES | TRIGGER }
            [, ...] | ALL [ PRIVILEGES ] }
                ON { [ TABLE ] table_name [, ...] | ALL TABLES IN SCHEMA schema_name [, ...] }
                TO role_specification [, ...] [ WITH GRANT OPTION ]
    
    GRANT { { SELECT | INSERT | UPDATE | PEFERENCES } ( column_name [, ...] ) 
            [, ...] | ALL [ PRIVILEGES ] ( column_name [, ...] ) }
                ON [ TABLE ] table_name [, ...]
                TO role_specification [, ...] [ WITH GRANT OPTION ]
        
    GRANT { { CREATE | CONNECT | TEMPORARY | TEMP }
            [, ...] | ALL [ PRIVILEGES ] }
                ON DATABASE database_name [, ...]
                TO role_specification [, ...] [ WITH GRANT OPTION ]

    GRANT { CREATE | ALL [ PRIVILEGES ] }
                ON TABLESPACE tablespace_name [, ...]
                TO role_specification [, ...] [ WITH GRANT OPTION ]
```
`role_specification` 可取值为:
* `[ GROUP ] role_name`
* `PUBLIC`
* `CURRENT_USER`
* `SESSION_USER`

第二种做法是给角色赋予其他角色的某些权限。
```sql
    GRANT role_name [, ...] TO role_specification [, ...]
        [ WITH ADMIN OPTION ]
        [ GRANTED BY role_specification ]
```
`role_specification` 可取值同上。



PostgreSQL 还支持非关系数据类型 json 。

```sql
    testdb=> SELECT '{"a":1, "b":2}'::json;
        json      
    ----------------
    {"a":1, "b":2}
    (1 row)
```

```sql
    testdb=> CREATE TABLE test_json1(id serial primary key, name json);
    CREATE TABLE
    testdb=> INSERT INTO test_json1(name) VALUES('{"col1":1,"col2":"hello","col3":"world"}');
    INSERT 0 1
    testdb=> INSERT INTO test_json1(name) VALUES('{"col1":2,"col2":"hello","col3":"kitty"}');
    INSERT 0 1
    testdb=> SELECT * FROM test_json1;
    id |                   name                   
    ----+------------------------------------------
    1 | {"col1":1,"col2":"hello","col3":"world"}
    2 | {"col1":2,"col2":"hello","col3":"kitty"}
    (2 rows)
```

### 查询 json 数据

通过 `->` 操作符可以查询 json 数据的键值:
```sql
    testdb=> SELECT name->'col3' FROM test_json1 WHERE id=1;
    ?column? 
    ----------
    "world"
    (1 row)
```

如果想以文体格式返回 json 字段键值可以使用 `->>` 操作符:
```sql
    testdb=> SELECT name->>'col3' FROM test_json1 WHERE id=1;
    ?column? 
    ----------
    world
    (1 row)
```

### jsonb 与 json 差异

PostgreSQL 支持两种 JSON 数据类: `json` 和 `jsonb`，两种类型在使用上几乎完全相同，两者主要区别如下:
* json 存储格式为文本而 jsonb 存储格式为二进制
* json 写入比 jsonb 快，但检索比 jsonb 慢

除了以上区别外，在使用过程两者也存在差异。

例如 jsonb 输出的键的顺序和输入不一样，而 json 的输出键的顺序和输入完全一样:
```sql
    testdb=> SELECT '{"bar":"baz","balance":7.77,"active":false}'::jsonb;
                        jsonb                       
    --------------------------------------------------
    {"bar": "baz", "active": false, "balance": 7.77}
    (1 row)
    testdb=> SELECT '{"bar":"baz","balance":7.77,"active":false}'::json;
                        json                     
    ---------------------------------------------
    {"bar":"baz","balance":7.77,"active":false}
    (1 row)
```

另外，jsonb 类型会去掉输入数据中键值的空格，json 则不会:
```sql
    testdb=> SELECT ' {"id":1,    "name":"fangyi"  }  '::jsonb;
                jsonb            
    -----------------------------
    {"id": 1, "name": "fangyi"}
    (1 row)

    testdb=> SELECT ' {"id":1,    "name":"fangyi"  }  '::json;
                json                
    -----------------------------------
    {"id":1,    "name":"fangyi"  }  
    (1 row)
```

此外，jsonb 会删除重复的键，仅保留最后一个。而 json 会保留重复的键值。

在大多数应用场景下建议使用 jsonb，除非有特殊的需求，比如对 json 的键顺序有特殊的要求。

### jsonb 与 json 操作符

字符串是否作为顶层键值:
```sql
    testdb=> SELECT ((SELECT name FROM test_json1 WHERE id=1)::jsonb) ? 'col1';
    ?column? 
    ----------
    t
    (1 row)

    testdb=> SELECT ((SELECT name FROM test_json1 WHERE id=1)::jsonb) ? 'col4';
    ?column? 
    ----------
    f
    (1 row)
```

删除 json 数据的键/值:
```sql
    testdb=> SELECT ((SELECT name FROM test_json1 WHERE id=1)::jsonb) - 'col2';
            ?column?           
    ------------------------------
    {"col1": 1, "col3": "world"}
    (1 row)

    testdb=> SELECT * FROM test_json1;
    id |                   name                   
    ----+------------------------------------------
    1 | {"col1":1,"col2":"hello","col3":"world"}
    2 | {"col1":2,"col2":"hello","col3":"kitty"}
    (2 rows)
```
注意，此时表中内容并未更新。

### jsonb 键/值的追加、删除、更新

jsonb 键/值追加可通过 `||` 操作符。

为某个记录追加:
```sql
    testdb=> SELECT * FROM test_json1;
    id |                             name                              
    ----+---------------------------------------------------------------
    2 | {"col1":2,"col2":"hello","col3":"kitty"}
    1 | {"col1": 1, "col2": "hello", "col3": "world", "col4": "four"}
    (2 rows)
```

jsonb 键/值的删除有两种方法，一种是通过 `-` 删除，另一种通过 `#-` 删除。

对某个记录进行删除:
```sql
    testdb=> SELECT * FROM test_json1;
    id |                     name                      
    ----+-----------------------------------------------
    2 | {"col1":2,"col2":"hello","col3":"kitty"}
    1 | {"col1": 1, "col2": "hello", "col3": "world"}
    (2 rows)
```

通过操作符 `#-` 删除指定键/值，通常用于嵌套 json 数据删除的场合，如下面删除嵌套 "contact" 中的 "fax" 键/值:
```sql
    testdb=> SELECT '{"name":"James","contact":{"phone":"01234 567890","fax":"01987 543210"}}'::jsonb #- '{contact,fax}'::text[];
                            ?column?                         
    ---------------------------------------------------------
    {"name": "James", "contact": {"phone": "01234 567890"}}
    (1 row)
```

更新也有两种方式，一种是通过 `||` 操作符进行覆盖，一种是通过 `jsonb_set` 函数:
```sql
    testdb=> UPDATE test_json1 SET name = (SELECT name FROM test_json1 WHERE id=1)::jsonb || '{"col3":"sir"}' WHERE id=1;
    UPDATE 1
    testdb=> SELECT * FROM test_json1;
    id |                    name                     
    ----+---------------------------------------------
    2 | {"col1":2,"col2":"hello","col3":"kitty"}
    1 | {"col1": 1, "col2": "hello", "col3": "sir"}
    (2 rows)
```

jsonb_set 函数语法如下:
```sql
    jsonb_set(target jsonb, path text[], new_value json[, create_if_missing boolean])
```
target 指源 jsonb 数据，path 指路径，new_value 指更新后的键值，create_if_missing 值为 true 表示如果键值不存在则添加，为 false 表示如果键值不存在则不添加。

```sql
    testdb=> SELECT jsonb_set('{"col":"1"}'::jsonb, '{col}', '"100"'::jsonb, false);
    jsonb_set    
    ----------------
    {"col": "100"}
    (1 row) 
```

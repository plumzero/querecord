
DDL(Data Definition Language，数据定义语言)用来创建或者删除存储数据用的数据库以及数据库中的表等对象。

DDL 包含以下几种指令:
- `CREATE`: 创建数据库和表等对象
- `DROP`: 删除数据库和表等对象
- `ALTER`: 修改数据库和表等对象的结构


### CREATE

```sql
    CREATE DATABASE shop;
```

```sql
    CREATE TABLE Product
    (
        product_id      CHAR(4)         NOT NULL,
        product_name    VARCHAR(100)    NOT NULL,
        product_type    VARCHAR(32)     NOT NULL,
        sale_price      INTEGER,
        purchase_price  INTEGER,
        regist_date     DATE,
        PRIMARY KEY(product_id)
    );
```
语句中的表名 `Product` 在实际创建后会转换为小写 `product`。如果要保持实际表名不变，需要在创建语句中将表名用 `""` 引起来。

这里在创建表时引入了两种约束，分别是非空(`NOT NULL`)约束和主键(`PRIMARY KEY`)约束。

### DROP

```sql
    DROP TABLE Product;
```

删除了的表是无法恢复的!

### ALTER

修改表名
```sql
    ALTER TABLE Poduct RENAME TO Product;
```

添加表字段
```sql
    ALTER TABLE Product ADD COLUMN product_name_pinyin VARCHAR(100);
```

删除表字段
```sql
    ALTER TABLE Product DROP COLUMN product_name_pinyin;
```

表字段重命名
```sql
    ALTER TABLE Product RENAME product_name TO product_desc;
```

更改表字段类型
```sql
    ALTER TABLE Product ALTER COLUMN sale_price TYPE double precision;  -- 将 sale_price 更改为 double precision 类型
    ALTER TABLE Product ALTER COLUMN purchase_price TYPE integer[] USING ARRAY[purchase_price]; -- 将 purchase_price 更改为数组类型
    ALTER TABLE Product ALTER COLUMN product_type TYPE VARCHAR(32)[] USING ARRAY[product_type]; -- 将 product_type 更改为数组类型
```

表定义变更之后是无法恢复的!

恢复到原来的表测试...

插入测试数据:
```sql
    INSERT INTO Product VALUES('0001', 'T恤衫',   '衣服',     1000, 500, '2009-09-20');
    INSERT INTO Product VALUES('0002', '打孔器',  '办公用品', 500,  320,  '2009-09-11');
    INSERT INTO Product VALUES('0003', '运动T恤', '衣服',     4000, 2800, NULL);
    INSERT INTO Product VALUES('0004', '菜刀',    '厨房用具', 3000, 2800, '2009-09-20');
    INSERT INTO Product VALUES('0005', '高压锅',  '厨房用具', 6800, 5000, '2009-01-15');
    INSERT INTO Product VALUES('0006', '叉子',    '厨房用具', 500,  NULL, '2009-09-20');
    INSERT INTO Product VALUES('0007', '擦菜板',  '厨房用具', 880,  790,  '2008-04-28');
    INSERT INTO Product VALUES('0008', '圆珠笔',  '办公用品', 100,  NULL, '2009-11-11');
```
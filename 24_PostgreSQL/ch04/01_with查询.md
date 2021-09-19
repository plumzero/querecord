
`WITH` 查询是 PostgreSQL 支持的高级 SQL 特性之一，这一特性常称为 `CTE(Common Table Expressions)`。WITH 查询在复杂查询中定义一个辅助语句(可理解成在一个查询中定义的临时表)，这一特性常用于复杂查询或递归查询应用场景。

### 复杂查询使用 CTE

简单 CTE 示例:
```sql
    WITH t AS (
        SELECT generate_series(1,3)
    )
    SELECT * FROM t;
```

以上语句执行结果与如下语句等价:
```sql
    SELECT * FROM generate_series(1,3) as t;
```

不过 CTE 可以简化 SQL 并且减少嵌套，由于可以预先定义辅助语句，之后可以在主查询中多次调用。

复杂 CTE 示例:
```sql
    WITH regional_sales AS (
            SELECT region, SUM(amount) AS total_sales
            FROM orders
            GROUP BY region
        ), top_regions AS (
            SELECT region
            FROM regional_sales
            WHERE total_sales > (SELECT SUM(total_sales) / 10 FROM regional_sales)
        )
    SELECT region,
           product,
           SUM(quantity) AS product_units,
           SUM(amount) AS product_sales
    FROM orders
    WHERE region IN (SELECT region FROM top_regions)
    GROUP BY region, product;
```

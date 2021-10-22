
`CASE` 表达式也是函数的一种。

CASE 表达式是在区分情况时使用的，这种情况的区分在编程中通常称为`(条件)分支`。

简单 CASE 表达式:
```sql
    CASE <表达式>
        WHEN <表达式> THEN <表达式>
        WHEN <表达式> THEN <表达式>
        WHEN <表达式> THEN <表达式>
        ...
        ELSE <表达式>
    END
```

搜索CASE表达式:
```sql
    CASE WHEN <求值表达式> THEN <表达式>
         WHEN <求值表达式> THEN <表达式>
         WHEN <求值表达式> THEN <表达式>
         ...
         ELSE <表达式>
    END
```
CASE 表达式会从对最初的 WHEN 子句中的 "<求值表达式>" 进行求值开始执行。所谓求值，就是要调查该表达式的真值是什么。如果结果为真(TRUE)，那么就返回 THEN 子句中的表达式，CASE 表达式的执行到此为止。如果结果不为真，那么就跳转到下一条 WHEN 子句的求值当中。如果直到最后的 WHEN 子句为止返回结果都不为真，那么就会返回 ELSE 中的表达式，执行终止。

简单表达式示例:
```sql
    SELECT product_name,
        CASE WHEN product_type = '衣服'
             THEN 'A: ' || product_type
             WHEN product_type = '办公用品'
             THEN 'B: ' || product_type
             WHEN product_type = '厨房用具'
             THEN 'C: ' || product_type
             ELSE NULL
        END AS abc_product_type
    FROM Product;
```

搜索表达式示例:
```sql
    SELECT product_name,
        CASE WHEN product_type = '衣服'
             THEN 'A: ' || product_type
             WHEN product_type = '办公用品'
             THEN 'B: ' || product_type
             WHEN product_type = '厨房用具'
             THEN 'C: ' || product_type
             ELSE NULL
        END AS abc_product_type
    FROM Product;
```

因为是一个表达式，所以 CASE 表达式可以书写在任意的位置。

实现行列转换:
```sql
    SELECT product_type, SUM(sale_price) AS sum_price
        FROM Product
            GROUP BY product_type;
```

使用 CASE 表达式进行行列转换:
```sql
    SELECT SUM(CASE WHEN product_type = '衣服'
                    THEN sale_price ELSE 0 END) AS sum_price_clothes,
           SUM(CASE WHEN product_type = '厨房用具'
                    THEN sale_price ELSE 0 END) AS sum_price_kitchen,
           SUM(CASE WHEN product_type = '办公用品'
                    THEN sale_price ELSE 0 END) AS sum_price_office
    FROM Product;
```

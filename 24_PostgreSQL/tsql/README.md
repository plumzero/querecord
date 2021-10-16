
### 变量定义与赋值

变量的定义:
```sql
    s integer;
    this_date date := start_date;
```

变量的别名:
```sql
    new_name ALIAS FOR old_name;
```

变量赋值的方式:
```sql
    a integer;
    b integer;
    a := 10;
    SELECT 100,200 INTO a,b;
```


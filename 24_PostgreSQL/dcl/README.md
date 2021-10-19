
DCL(Data Control Language, 数据控制语言)用来确认或者取消对数据库中的数据进行的变更。除此之外，还可以对 RDBMS 的用户是否有权限操作数据库中的对象(数据库表等)进行设定。

DCL 包含以下几种指令:
- `COMMIT`: 确认对数据库中的数据进行的变更
- `ROLLBACK`: 取消对数据库中的数据进行的变更
- `GRANT`: 赋予用户操作权限
- `REVOKE`: 取消用户的操作权限

### 事务

* 事务是需要在同一个处理单元中执行的一系列更新处理的集合。通过使用事务，可以对数据库中的数据更新处理的提交和取消进行管理。
* 事务处理的终止指令包括 COMMIT(提交处理)和 ROLLBACK(取消处理)两种。
* DBMS 的事务具有原子性(Atomicity)、一致性(Consistency)、隔离性(Isolation)和持久性(Durability)四种特性，统称为 `ACID` 特性。
    * 原子性: 指在事务结束时，其中所包含的更新处理要么全部执行，要么完全不执行。
    * 一致性: 指的是事务中包含的处理要满足数据库提前设置的约束，如主键约束或者 NOT NULL 约束等。
    * 隔离性: 指的是保证不同事务之间互不干扰的特性。该特性保证了事务之间不会互相嵌套。比如，即使某个事务向表中添加了记录，在没有提交之前，其他事务也是看不到新添加到记录的。
    * 持久性: 指的是事务(不论是提交还是回滚)结束后，DBMS 能够保证该时间点的数据状态会被保存的特性。即使由于系统故障导致数据丢失，数据库也一定能通过某种手段进行恢复。保证持久性的方法根据实现的不同而不同，其中最常见的就是将事务的执行记录保存到硬盘等存储介质中(该执行记录称为日志)。当发生故障时，可以通过日志恢复到故障发生前的状态。

在 RDBMS 中，事务是对表中数据进行更新的单位。简单来讲，事务就是<strong>需要在同一个处理单元中执行的一系列更新处理的集合</strong>。

使用事务开始语句和事务结束语句，将一系列 DML 语句(INSERT/UPDATE/DELETE语句)括起来，就实现了一个事务处理。

PostgreSQL 中实现一个事务处理过程的示例:
```sql
    BEGIN TRANSACTION;

    UPDATE Product SET sale_price = sale_price - 1000 WHERE product_name = '运动T恤';
    UPDATE Product SET sale_price = sale_price + 1000 WHERE product_name = 'T恤衫';

    COMMIT;
```

事务的结束需要用户明确地给出提示。结束事务的指令有如下两种。
- `COMMIT`: 提交事务包含的全部更新处理的结束指令，相当于文件处理中的覆盖保存。一旦提交，就无法恢复到事务开始前的状态了。
- `ROLLBACK`: 取消事务包含的全部更新处理的结束指令，相当于文件处理中的放弃保存。一旦回滚，数据库就会恢复到事务开始之前的状态。

PostgreSQL 中所有的 SQL 指令语句都在事务内执行，即使不执行 BEGIN，这些命令语句也会在执行时悄悄被括在 BEGIN 和 COMMIT (如果成功的话)之间。

索引可以提高查询效率。

MongoDB 索引定义在 collection 级别，并且支持在 collection 的任何字段及下级字段上创建索引。

collection 默认创建一个 `_id` 唯一性索引，该索引可防止客户端向同一集合中插入同样 _id 的两条记录，_id 字段上的索引是无法被丢弃的。

### 创建索引

在 name 字段上创建一个单键降序索引:
```js
    db.collection.createIndex({ name: -1 })
```

索引的默认命名方式是键与键方向(升序/降序)的连结(以下画线作为分隔)。比如索引 `{item: 1, quantity: -1}` 的索引名称为 `item_1_quantity_-1`。

也可以自定义索引名。比如需要经常查询 products 集合来填充当前清单数据的话，可以将对 `item` 和 `quantity` 创建的索引命名为 `query for inventory`:
```sh
    db.products.createIndex(
        { item: 1, quantity: -1 },
        { name: "query for inventory" }
    )
```

不可以重命名索引，通过 `db.collection.getIndexes()` 可以查看索引名称。

### 索引类型

MongoDB 提供了多种索引类型来支持特定类型的数据及查询。

#### 单字段 Single Field

除了默认的 `_id` 索引外，MongoDB 同样支持用户自定义基于单个文档中对单个字段的升降序索引。

对于 Single-Field 索引，使用何种排序(升序/降序)关系不大，因为 MongoDB 可以从不同方向遍历此索引。

#### 复合索引 Compound Index

MongoDB 支持基于多个字段的复合索引。

了解复合索引中字段列表的排序很重要。例如，现在有一个复合索引其内容为 `{ userid: 1, score: -1 }`，复合索引首先以 `userid` 进行排序，对于每个 userid 值再使用 `score` 进行排序。

#### 多键索引 Multikey Index

MongoDB 使用多键索索引用于对数组元素的索出。如果要索引的字段是一个数组，MongoDB 会为数组中的每个元素创建单独分开的索引条目。利用多键索引可以查询到文档中数组元素的某个字段。

如果索引字段对应值是一个数组，MongoDB 会自行决定是否为其创建一个多键索引，程序员不需要做任何操作。

#### 哈希索引 Hashed Indexes

为了支持哈希分片，MongoD 也提供了哈希索引类型，它以某个字段对应值的哈希作为索引。

哈希索引只支持相等匹配。


### 索引类型

#### 唯一性索引 Unique Indexes

保证了 MongoDB 每条记录针对该类型索引字段的唯一性。除了唯一性约束之外，唯一性索引在功能上可以与 MongoDB 中的其他索引通用。

#### 局部索引 Partial Indexes

只对一个集合中满足某种特定过滤条件的文档进行索引。由于是对集合中的子集文档进行索引，所以要创建和维护上具有低存储要求、低性能成本的特点。

#### 稀疏索引 Sparse Indexes

稀疏特性保证了索引中只包含文档中具有索引字段的条目，在索引时会跳过文档中不具有索引的字段。

#### TTL索引

利用此索引，MongoDB 可以定期自动清理集合中的过期文档，可以用于对日志、会话等仅需要保存有限一段时间的信息数据处理。

#### 隐藏索引 Hidden Indexes

略


### 索引的使用

索引可以提高读操作的效率，关于如何选择索引，可以参考[查询计划](https://docs.mongodb.com/v4.4/core/query-plans/#std-label-read-operations-query-optimization)。


### 索引和排列规则

为了将索引用于对字符串的比较，为此必须指定同样的操作规则。

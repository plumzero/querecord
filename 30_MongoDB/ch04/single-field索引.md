
MongoDB 为集合中的文档提供了完整的索引支持。缺省情况下，所有的集合都有一个字段名为 `_id` 的索引，应用和使用者也可以添加额外的索引以支持更重要的查询和操作。

在每次执行创建索引操作之后，可以通过 `db.collection.getIndexes()` 查看索引信息。

### 在单个字段上创建一个升序索引

以下面的 `records` 集合为例:
```json
{
  "_id": ObjectId("570c04a4ad233577f97dc459"),
  "score": 1034,
  "location": { state: "NY", city: "New York" }
}
```
为 records 集合中的 `score` 字段创建一个降序索引:
```js
    db.records.createIndex( { score: 1 } )
```
索引字段的参数值描述了针对该字段的索引类型。比如在上面的例子中 `1` 就表示 score 是升序索引，而 `-1` 就是降序索引。

索引创建后，将会在对 `score` 的查询中提供支持:
```sh
    db.records.find({ score: 2 })
    db.records.find({ score: { $gt: 10 }})
```

### 在嵌入式字段上创建一个索引

程序员可以像在顶层字段一样，为嵌入式文档中的字段创建索引。

仍以 `records` 集合为例，在 `location.state` 字段上创建一个索引:
```js
    db.records.createIndex({ "location.state": 1 })
```

索引创建后，将会在对 `location.state` 的查询中提供支持:
```js
    db.records.find( { "location.state": "CA" } )
    db.records.find( { "location.city": "Albany", "location.state": "NY" } )
```

### 在嵌入式文档上创建一个索引

仍以 `records` 集合为例。针对整个 `location` 字段创建一个索引:
```js
    db.records.createIndex( { location: 1 } )
```

支持查询:
```js
    db.records.find( { location: { city: "New York", state: "NY" } } )
```

### 其他考虑

在创建索引时应用可能会遇到性能降低的情况，包括对读写访问集合的限制。

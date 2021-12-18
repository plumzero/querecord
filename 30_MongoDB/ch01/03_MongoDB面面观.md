
MongoDB 以文档(document，更准确来说是 BSON 文档)的形式将数据记录存储在集合(collection)中。一个数据库中可以存储一个或多个集合。

创建数据库:
```sh
    use myNewDB
    db.createUser({user:"tester",pwd:"pwd123",roles:["dbOwner"]})
    db.createUser({user:"writer",pwd:"pwd456",roles:["readWrite"]})
    db.createUser({user:"reader",pwd:"pwd789",roles:["read"]})
```

以 tester 身份认证后查看用户信息:
```sh
    show users
```

以 writer 身份认证后写入数据:
```sh
    db.myNewCollection1.insertOne({x: 2})
```

以 reader 身份认证后查看数据:
```sh
    db.myNewCollection1.find()
```


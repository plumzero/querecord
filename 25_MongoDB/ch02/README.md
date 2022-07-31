
### database

`db` 表示当前所处数据库:
```sh
    > db
```

`use <db>` 用来切换数据库:
```sh
    > use test
```
使用者在切换之前不必创建对应的数据库，MongoDB 在第一次存入数据时会创建该库，这也包括创建第一个 collection 。


### collection

MongoDB 在 collections 中存储 documents 
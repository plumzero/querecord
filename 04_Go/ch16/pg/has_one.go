
package main

import (
	"log"

	"github.com/go-pg/pg/v10"
	"github.com/go-pg/pg/v10/orm"
)

type User struct {
	Id     int64
	Name   string
	Emails []string
}

// 一个 Story 包含一个 User
type Story struct {
	Id       int64
	Title    string
	AuthorId int64
	Author   User `pg:"rel:has-one"`	// 原示例程序中为 *User，这里为了更直观地打印出结果，改为了 User。那么就有一个疑问， ★1 这里是否应该使用指针?
}
// 关于 ★1
//  应该认识到，实际使用时该处应该定义为一个 *User，而暂以 User 替代只是为了使打印结果更直观而已。
//  为什么应该使用指针呢?
//      个人理解表中数据结构化到对象中后，该对象就保存了一份对表的拷贝。程序在执行过程中，可能会对这份拷贝作出修改，
//      数据库也很可能希望随时将这种更改同步到库中，此时定义为指针更加合适。
//  其他关系同是如此。

func createSchema(db *pg.DB) error {
	models := []interface{}{
		(*User)(nil),
		(*Story)(nil),
	}

	for _, model := range models {
		err := db.Model(model).DropTable(&orm.DropTableOptions{
			IfExists: true,
			Cascade:  true,
		})
		if err != nil {
			return err
		}
		err = db.Model(model).CreateTable(&orm.CreateTableOptions{
            Temp: false,
            IfNotExists: true,
		})
		if err != nil {
			return err
		}
	}
	return nil
}

func main() {
	db := pg.Connect(&pg.Options{
		Addr: "127.0.0.1:5432",
		User: "pguser",
		Password: "",
		Database: "mydb",
	})
	defer db.Close()

	err := createSchema(db)
	if err != nil {
		panic(err)
	}

	// 添加测试数据
	user1 := &User{
		Name:   "admin",
		Emails: []string{"admin1@admin", "admin2@admin"},
	}
	_, err = db.Model(user1).Insert()
	if err != nil {
		panic(err)
	}
	log.Printf("user1.Id=%d", user1.Id)

	user2 := &User{
		Name:   "root",
		Emails: []string{"root1@root", "root2@root"},
	}
	_, err = db.Model(user2).Insert()
	if err != nil {
		panic(err)
	}

	story1 := &Story{
		Title:    "Cool story",
		AuthorId: user1.Id,
	}
	_, err = db.Model(story1).Insert()
	if err != nil {
		panic(err)
	}
	log.Printf("story1.Id=%d", story1.Id)

	story2 := &Story{
		Title:    "Cool poetry",
		AuthorId: user2.Id,
	}
	_, err = db.Model(story2).Insert()
	if err != nil {
		panic(err)
	}

	// 单表内查询所有
	var users []User
	err = db.Model(&users).Select()
	if err != nil {
		panic(err)
	}
	log.Println("单表内查询所有:", users)

	// 单表内主键查询
	user := &User{Id: user1.Id}
	err = db.Model(user).WherePK().Select()
	if err != nil {
		panic(err)
	}
	log.Println("单表内主键查询:", user)

	// 一对一关联查询

    // ★2 对下面语句的理解
    //  a. Model 中的表作主表，即 Story 作主表
    //  b. Relation 中的表作副表，即 Author，也就是 User 作副表
    //  整个语句用 SQL 表示为: SELECT (字段列) FROM Story INNER JOIN User ON (联结条件) WHERE Story.Id = story1.Id;
    //  现在的问题是联结条件是什么?
	story := new(Story)
	err = db.Model(story).
		Relation("Author").
		Where("Story.Id = ?", story1.Id).
		Select()
	if err != nil {
		panic(err)
	}
	log.Println("has-one Where(id=story1.Id):", story)

    // ★3 联结条件是什么?

    // 在上面的测试中，并不清楚 Id 在作为普通查询条件的同时，是否也作为联结查询条件。
    // 或者说联结查询条件是怎么确定的，是根据 WHERE 中出现的字段而定的? 还是默认以 Id 作为联结键?
    // 第一种不太可能，第二种有可能，毕竟每个参与到 ORM 中的对象结构体都必须要求带有一个 Id 属性字段。
	
    // 不过，还是要测试一下
	story = new(Story)
	err = db.Model(story).
		Relation("Author").
		Where("Story.Title = ?", story2.Title).
		Select()
	if err != nil {
		panic(err)
	}
	log.Println("has-one Where(id=story2.Title):", story)
    // 测试发现，看起来确实是将 Id 作为联结查询条件的...
    // 这时 SQL 语句应该可以修改为: SELECT (字段列) FROM Story INNER JOIN User ON Story.Id = User.Id WHERE Story.Id = story1.Id;
	// 不过，真的是这样吗？

    // 试想一下，参与到 ORM 关系中的对象结构体，确实每个结构体都会带有一个 Id 字段，但是实际中能够保证这些 Id 字段同义吗? 如果不能保证，那么联结得到的结果集
    // 就有可能是没有意义的。这时以 Id 作为联结查询条件就有问题了...

	// 细心查看会发现 Story 中还有一个 AuthorId 字段，字面意思理解大概就是 Author 字段所对应的 Id，这是一个很重要的信息。初次接触不以为意，但对 ORM 来说这是不可或
    // 缺的。如果在实际应用中没有类似字段，反而应该引起程序员的足够警惕。
	// 在上面的测试中，将 story1 和 story2 中的 AuthorId 字段值分别赋值为 user1 和 user2 对应在 Id，这里进行一些独立地涂改对比测试(在上述代码中并未体现):
	// 	1. 将 story1 和 story2 的 AuthorId 字段值分别赋值为非用户 Id(在这里就是既不等于 user1.Id, 也不等于 user2.Id)，查询得到的 story 结果中 Author 字段为空
	//  2. 在 Story 结构中保留 AuthorId 字段，但在创建 Story 对象时不为该字段赋值(此时默认赋值为0)，查询得到的 story 结果中 Author 字段为空
	//  3. 在 Story 结构中去除 AuthorId 字段，查询得到的 story 结果中 Author 字段不为空
	//	4. 在 Story 结构中将 AuthorId 字段修改为其他名称，比如 XId，为该字段任意赋值，查询得到的 story 结果中 Author 字段不为空

	// 发现了什么呢?
	// 原来 ORM 会将 AuthorId 解析为 Author 和 Id, 之后去 Author 类型(即 User)对应的表中找 Id 字段，以 Id 字段作为联结条件进行查询。
	// 而如果没有 AuthorId 字段，才会使用 Id 字段作为默认联结条件进行查询。

	// 事实上，User 和 Story 只能以 AuthorId(如果指定的话)或 Id(作为默认)为联结条件，如果去掉 AuthorId，同时增加 AuthorName，两表也并不会以 AuthorName 作为
	// 联结条件，而是以 Id 作为默认联结条件。
	// 验证文件见: has_one2.go
    // 事实上，参与 ORM 关系中的结构体对象，只能以 Id 作为联结条件进行查询(或显式指定如 AuthorId 等变量名称，或作为默认)。比如以 AuthorName 代替 AuthorId, 并不会以
    // AuthorName 作为联结条件，而是默认选择 Id 。
    
    // 这时 SQL 语句应该修改为: SELECT (字段列) FROM Story INNER JOIN User ON Story.AuthorId = User.Id WHERE Story.Id = story1.Id;

    // 一条简单的两表联查示例 SQL 语句:
    //  SELECT s.id, s.title, s.author_id, u.name, u.emails FROM Stories AS s INNER JOIN Users AS u ON s.author_id = u.id WHERE s.id = 1;
    //  -- SQL 关键字大写，表首字母大写，表字段小写 --

	// 上面的查询只会返回一条记录，所以只定义一个 story 不会错误
	// 通过定义一个数组可以存放多条返回记录
	var stories []Story
	err = db.Model(&stories).
		Relation("Author").
		Select()
	if err != nil {
		panic(err)
	}
	log.Println("has-one 返回多个结果集:", stories)
}
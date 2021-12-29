
package main

import (
	"log"

	"github.com/go-pg/pg/v10"
	"github.com/go-pg/pg/v10/orm"
)

type Profile struct {
	Id     int
	Lang   string
	Active bool
	UserId int      // 以 User.Id 作为联结条件字段
}

// 可以看到，同 has-one 相比，User 中的 Profiles 是一个数组。

// 不过有一点不同的是 User 作为主表，按照 has-one 的方式来，它的结构体字段中应该有 ProfileId 啊，但是作为联结的 Id 却跑到了 Profile 中的 UserId 中...
// 不过也容易理解，User 与 Profile 是一对多的关系，User 保存着 Profile 的元素数组，其中的每个元素 Id 未必是相同的，如此，联结字段 UserId 在 Profile
// 中也是理所当然的了

// 从 has-many 的示例中可以看到，对于联结键的设定是灵活的(根据需要决定它应该出现在哪里)。
// 比如在之前的 has-one 测试中，也可以将联结键放在 User 中(即为 User 结构体添加一个 StroyId 字段)，这样做的话，就是以 Story 中的 Id 作为联结字段了。
// 这样一想，更加觉得 Story 中 AuthorId 字段的存在确有其意义，它让使用者清晰地知道，联结字段是 Author 中的 Id，而不是 Story 中的 Id 。而将 AuthorId 去掉
// 也可以输出，纯粹是因为 Story.Id 与 User.Id 是序列创建(程序自动从 1 开始创建)的，巧合而已。

type User struct {
	Id       int
	Name     string
	Profiles []Profile `pg:"rel:has-many"`     //原示例程序中为 []*Profile，这里为了更直观地打印出结果，改为了 []Profile。具体见 has-one ★1
}

func createSchema(db *pg.DB) error {
	models := []interface{}{
		(*User)(nil),
		(*Profile)(nil),
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
		Name:   "user-1",
	}
	_, err = db.Model(user1).Insert()
	if err != nil {
		panic(err)
	}

	user2 := &User{
		Name:   "user-2",
	}
	_, err = db.Model(user2).Insert()
	if err != nil {
		panic(err)
	}

	profile1 := &Profile{
		Lang: "en",
		Active: true,
		UserId: 1,
	}
	_, err = db.Model(profile1).Insert()
	if err != nil {
		panic(err)
	}
	log.Printf("profile1.Id=%d", profile1.Id)

	profile2 := &Profile{
		Lang: "ru",
		Active: true,
		UserId: 1,
	}
	_, err = db.Model(profile2).Insert()
	if err != nil {
		panic(err)
	}

	profile3 := &Profile{
		Lang: "md",
		Active: false,
		UserId: 1,
	}
	_, err = db.Model(profile3).Insert()
	if err != nil {
		panic(err)
	}

	// 主表为 User, 副表为 Profile，联结键为 User.Id
	var users []User
	err = db.Model(&users).
			Column("user.*").
            Relation("Profiles").
            // Relation("Profiles", func(q *pg.Query) (*pg.Query, error) {
            //     return q.Where("active IS TRUE"), nil
            // }).
            Select()
    if err != nil {
        panic(err)
    }
    log.Println(users)
    
    // 以上查询结果等同于 SQL
	// 	SELECT u.id, u.name, p.id, p.lang, p.active, p.user_id FROM Users AS u INNER JOIN Profiles AS p ON u.id = p.user_id;
	// 折行显示
    //  SELECT u.id, u.name, p.id, p.lang, p.active, p.user_id
    //      FROM Users AS u
    //          INNER JOIN Profiles AS p
    //              ON u.id = p.user_id;
}

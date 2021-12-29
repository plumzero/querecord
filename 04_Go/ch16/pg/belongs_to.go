
package main

import (
	"log"

	"github.com/go-pg/pg/v10"
	"github.com/go-pg/pg/v10/orm"
)

type User struct {
	Id      int
	Name    string
	Profile Profile `pg:"rel:belongs-to"`	// 原示例程序中为 *Profile，这里为了更直观地打印出结果，改为了 Profile。具体见 has-one ★1
}

type Profile struct {
	Id     int
	Lang   string
	UserId int
}

// 同 has-one 相比， belongs-to 反过来了
// 事实上 belongs-to 正是对 has-one 的回应，也是描述一对一的关系，只是在语义方面有所不同。比如小明有一个本子，这个本子属于小明(潜在意思是不属于其他人)。

// 测试发现，将 belongs-to 换成 has-one, 本测试的输出结果集等同。
// 实际应用中 belongs-to 很少使用，有 has-one 足够了

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
		UserId: 1,
	}
	_, err = db.Model(profile1).Insert()
	if err != nil {
		panic(err)
	}
	log.Printf("profile1.Id=%d", profile1.Id)

	profile2 := &Profile{
		Lang: "ru",
		UserId: 2,
	}
	_, err = db.Model(profile2).Insert()
	if err != nil {
		panic(err)
	}

	// User 作主表，Profile 作副表，联查
	var users []User
	err = db.Model(&users).
		Column("user.*").
		Relation("Profile").
		Select()
	if err != nil {
		panic(err)
	}
	log.Println(users)
}
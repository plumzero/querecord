
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

type Story struct {
	Id       int64
	Title    string
	AuthorName string
	Author   User `pg:"rel:has-one"`	// 如果将 User 改为 *User, 关联查询后打印 story 结果，会显示一个地址
}

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

	// story1 和 story2 的 AuthorName 都是 user1.Name
	// story1 和 story3 的 Title 都是 'Cool story'
	story1 := &Story{
		Title:    "Cool story",
		AuthorName: user1.Name,
	}
	_, err = db.Model(story1).Insert()
	if err != nil {
		panic(err)
	}
	log.Printf("story1.Id=%d", story1.Id)

	story2 := &Story{
		Title:    "Cool poetry",
		AuthorName: user1.Name,
	}
	_, err = db.Model(story2).Insert()
	if err != nil {
		panic(err)
	}

	story3 := &Story{
		Title:    "Cool story",
		AuthorName: user2.Name,
	}
	_, err = db.Model(story3).Insert()
	if err != nil {
		panic(err)
	}

	// 一对一关联查询
	var stories []Story
	err = db.Model(&stories).
		Relation("Author").
		Where("Story.Title = ?", story1.Title).
		Select()
	if err != nil {
		panic(err)
	}
	log.Println("has-one 返回结果集:", stories)

	// 测试结果发现，返回结果集为 story1 和 story3，其中 story3.Author 字段为空
	// 说明未以 AuthorName 作为联结条件
}
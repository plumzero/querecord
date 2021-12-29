
package main

import (
	"log"

	"github.com/go-pg/pg/v10"
	"github.com/go-pg/pg/v10/orm"
)

// 分别从 Order 角度和 Item 角度定义一对多关系，从而实现多对多关系。

type Order struct {
	Id		int
	Items	[]Item `pg:"many2many:order_to_items"`
}

type Item struct {
	Id int
	Orders	[]Order `pg:"many2many:item_to_orders"`
}

type OrderToItem struct {
	OrderId int
	ItemId  int
}

type ItemToOrder struct {
	OrderId int
	ItemId  int
}

func init() {
	// Register many to many model so ORM can better recognize m2m relation.
	// This should be done before dependant models are used.
	orm.RegisterTable((*OrderToItem)(nil))
	orm.RegisterTable((*ItemToOrder)(nil))
}

func createSchema(db *pg.DB) error {
	models := []interface{}{
		(*Order)(nil),
		(*Item)(nil),
		(*OrderToItem)(nil),
		(*ItemToOrder)(nil),
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
	item1 := &Item{}
	_, err = db.Model(item1).Insert()
	if err != nil {
		panic(err)
	}

	item2 := &Item{}
	_, err = db.Model(item2).Insert()
	if err != nil {
		panic(err)
	}

	order1 := &Order{}
	_, err = db.Model(order1).Insert()
	if err != nil {
		panic(err)
	}

	ordertoitem1 := &OrderToItem{
		OrderId: 1,
		ItemId: 1,
	}
	_, err = db.Model(ordertoitem1).Insert()
	if err != nil {
		panic(err)
	}
	ordertoitem2 := &OrderToItem{
		OrderId: 1,
		ItemId: 2,
	}
	_, err = db.Model(ordertoitem2).Insert()
	if err != nil {
		panic(err)
	}

	item2order1 := &ItemToOrder{
		OrderId: 1,
		ItemId: 1,
	}
	_, err = db.Model(item2order1).Insert()
	if err != nil {
		panic(err)
	}
	item2order2 := &ItemToOrder{
		OrderId: 1,
		ItemId: 2,
	}
	_, err = db.Model(item2order2).Insert()
	if err != nil {
		panic(err)
	}	

	// 测试
	var orders []Order
	err = db.Model(&orders).Relation("Items").Select()
	if err != nil {
		panic(err)
	}
	log.Println(orders)

	var items []Item
	err = db.Model(&items).Relation("Orders").Select()
	if err != nil {
		panic(err)
	}
	log.Println(items)
}
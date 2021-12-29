
package main

import (
	"log"

	"github.com/go-pg/pg/v10"
	"github.com/go-pg/pg/v10/orm"
)

// 先看一个 has-many 的映射关系，使用 Order.Id 作为联查键。
/*
	type Order struct {
		Id		int
		Items	[]Item `pg:"rel:has-many"`
	}

	type Item struct {
		OrderId int
		Id 		int
	}
*/

// 为了实现多对多的关系，对 has-many 映射关系需要作三处改动(仍以上述为例):
//	1. 将标签换为 `pg:"many2many:order_to_items"`
//	2. 去除 Item 中的 OrderId
//  3. 创建一个单纯的结构体用于映射
// 具体如下:

type Order struct {
	Id		int
	Items	[]Item `pg:"many2many:order_to_items"`	// 原示例程序中，数组元素也并未定义为指针
}

type Item struct {
	Id int
}

type OrderToItem struct {
	OrderId int
	ItemId  int
}

// 乍看一下是能发现从 Order 到 Item 的一对多关系，但细看一下又觉得对从 Item 到 Order 的一对多关系描述却不太清晰...
// 这种疑惑是对的，上面的三个结构确实只实现了从 Order 到 Item 的一对多关系。
// ★4 那所谓的多对多关系又该怎么理解呢?

// 如何更好地认识多对多的关系，个人觉得可以从不同的角度去理解。举例如下:
// 	 比如 A B C 三种苹果和甲乙两地...
//	 起初，将 A B 两种苹果卖往甲地，观察此时的状态。从甲的角度看，它拥有 A B 两种苹果，可以记为 '甲(A,B)'。从苹果角度看，可以记为 'A(甲)'，'B(甲)'。
//	 现在，将 B C 两种苹果卖往乙地，观察此时的状态。从地点角度看，各地拥有的苹果可以记为 '甲(A,B)','乙(B,C)'。从苹果角度看，记为 A(甲)，B(甲，乙)，C(乙)。
// 可以看出来，从不同的角度更容易理解多对多的关系。也应该认识到，参与多对多关系的两方，没有主次之分。

// ★5 那为什么在上面的结构中，只看到了一对多的关系呢？
// 这是因为，可以从不同的角度来理解这种关系，但实现的时候只能选择一个角度去做。
// 本示例是从在 Order 的角度来实现的。从 Item 角度实现的示例可以参考 many2many2.go

func init() {
	// Register many to many model so ORM can better recognize m2m relation.
	// This should be done before dependant models are used.
	orm.RegisterTable((*OrderToItem)(nil))
}

func createSchema(db *pg.DB) error {
	models := []interface{}{
		(*Order)(nil),
		(*Item)(nil),
		(*OrderToItem)(nil),
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

	// 测试
	var orders []Order
	err = db.Model(&orders).Relation("Items").Select()
	if err != nil {
		panic(err)
	}
	log.Println(orders)
}
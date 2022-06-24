
// 关于索引

package main

import (
	"context"
	"log"
	"time"

	// "go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo/options"

	"mgdtest.com/mongodb"
	// "mgdtest.com/model"
)

// 辅助函数，打印索引
func indexPrint(indexView mongo.IndexView) {
	opts := options.ListIndexes().SetMaxTime(2 * time.Second)	// 最大允许执行时间为 2 秒
	cursor, err := indexView.List(context.TODO(), opts)
	if err != nil {
		log.Fatal(err)
	}
	defer func() {
		cursor.Close(context.TODO())
	} ()
	var results []bson.M	// bson.M 差不多就类似于 map[string]interface{} 吧
	if err = cursor.All(context.TODO(), &results); err != nil {
		log.Fatal(err)
	}
	log.Printf("%v", results)
}

// 索引是否存在
func indexExists(indexView mongo.IndexView, indexName string) (bool, error) {
	cursor, err := indexView.List(context.TODO())
	if err != nil {
		return false, err
	}
	defer func() {
		cursor.Close(context.TODO())
	} ()
	for cursor.Next(context.TODO()) {
		if cursor.Current.Lookup("name").StringValue() == indexName {
			return true, nil
		}
	}
	return false, cursor.Err()
}

func main() {
	client := mongodb.MgoCli()
	coll := client.Database("my_db").Collection("my_collection")

	// 获取索引视图
	indexView := coll.Indexes()
	indexPrint(indexView)

	// 创建单索引
	kvi := mongo.IndexModel{
		Keys: bson.D{{"score", 1}},
	}
	if _, err := indexView.CreateOne(context.TODO(), kvi); err != nil {
		log.Fatal(err)
	}
	indexPrint(indexView)
	// 判断某个索引是否存在
	if bl, err := indexExists(indexView, "score_1"); err != nil {
		log.Fatal(err)
	} else {
		if bl {
			log.Printf("index 'score_1' exist")
		} else {
			log.Printf("index 'score_1' not exist")
		}
	}
	// 清除一个索引(DropOne 可以清除一个单索引，也可以清除一个联合索引，这里以单索引为例)
	if _, err := indexView.DropOne(context.TODO(), "score_1"); err != nil {
		log.Fatal(err)
	}
	indexPrint(indexView)

	// 创建联合索引
	//   这里创建两个联合索引: {name: 1, email: 1} and {name: 1, age: 1}，前者采用默认索引名(name_1_email_1),后者指定索引名为 nameAge
	models := []mongo.IndexModel{
		{
			Keys: bson.D{{"name", 1}, {"email", 1}},
		},
		{
			Keys:    bson.D{{"name", 1}, {"age", 1}},
			Options: options.Index().SetName("nameAge"),
		},
	}
	opts := options.CreateIndexes().SetMaxTime(2 * time.Second)		// 2 秒完成
	_, err := indexView.CreateMany(context.TODO(), models, opts)
	if err != nil {
		log.Fatal(err)
	}
	indexPrint(indexView)
	// 清除所有索引
	if _, err := indexView.DropAll(context.TODO()); err != nil {
		log.Fatal(err)
	}
	indexPrint(indexView)
}
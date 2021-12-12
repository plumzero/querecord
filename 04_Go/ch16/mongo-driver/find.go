
package main

import (
	"context"
	"log"
	// "time"

	"go.mongodb.org/mongo-driver/mongo/options"
	// "go.mongodb.org/mongo-driver/bson/primitive"

	"mgdtest.com/mongodb"
	"mgdtest.com/model"
)

func main() {
	client := mongodb.MgoCli()
	coll := client.Database("my_db").Collection("my_collection")

	cond := model.FindByJobName{JobName: "job multi1"}
	cursor, err := coll.Find(context.TODO(), cond, options.Find().SetSkip(0), options.Find().SetLimit(2))
	if err != nil {
		log.Fatal(err)
	}
	defer func() {
		if err = cursor.Close(context.TODO()); err != nil {
			log.Fatal(err)
		}
	} ()
	
	// 遍历获取
	for cursor.Next(context.TODO()) {
		var lr model.LogRecord
		if err = cursor.Decode(&lr); err != nil {
			log.Fatal(err)
		}
		log.Println("one by one:", lr)
	}
	// 整个获取
	var results []model.LogRecord
	if err = cursor.All(context.TODO(), &results); err != nil {
		log.Fatal(err)
	}
	for _, result := range results {
		log.Println("get all:", result)
	}
}

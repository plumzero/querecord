
package main

import (
	"context"
	"log"
	"time"

	"go.mongodb.org/mongo-driver/bson/primitive"

	"mgdtest.com/mongodb"
	"mgdtest.com/model"
)

func main() {
	client := mongodb.MgoCli()
	coll := client.Database("my_db").Collection("my_collection")

	log_record := model.LogRecord{
		JobName: "job1",
		Command: "echo 1",
		Err:	 "",
		Content: "1",
		Tp: model.ExecTime {
			StartTime: time.Now().Unix(),
			EndTime: time.Now().Unix() + 10,
		},
	}
	result, err := coll.InsertOne(context.TODO(), log_record)
	if err != nil {
		log.Println(err)
		return
	}
	// _id: 默认生成一个全局唯一 ID
	id := result.InsertedID.(primitive.ObjectID)
	log.Println("自增ID", id.Hex())
}


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

	result, err := coll.InsertMany(context.TODO(), []interface{}{
		model.LogRecord{
			JobName: "job multi1",
			Command: "echo multi1",
			Err:	 "",
			Content: "1",
			Tp: model.ExecTime {
				StartTime: time.Now().Unix(),
				EndTime: time.Now().Unix() + 10,
			},
		},
		model.LogRecord{
			JobName: "multi2",
			Command: "echo multi2",
			Err:	 "",
			Content: "2",
			Tp: model.ExecTime {
				StartTime: time.Now().Unix(),
				EndTime: time.Now().Unix() + 10,
			},
		},
	})
	if err != nil {
		log.Println(err)
		return
	}
	if result == nil {
		log.Fatal("result is nil")
	}
	for _, v := range result.InsertedIDs {
		id := v.(primitive.ObjectID)
		log.Println("自增ID", id.Hex())
	}
}

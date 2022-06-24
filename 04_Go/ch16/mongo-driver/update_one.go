
package main

import (
	"context"
	"log"
	
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo/options"
	
	"mgdtest.com/mongodb"
	"mgdtest.com/model"
)

func main() {
	client := mongodb.MgoCli()
	coll := client.Database("my_db").Collection("personals")

    {
        persons := []model.PersonalInfo{
            { Name: "xiaoming", Gender: "M", Age: 8,  Email: "xiaoming@email.com", Status: true },
            { Name: "xiaohong", Gender: "F", Age: 18, Email: "xiaohong@email.com", Status: true },
            { Name: "xiaocai",  Gender: "F", Age: 24, Email: "xiaocai@email.com",  Status: true },
            { Name: "laowang",  Gender: "M", Age: 37, Email: "laowang@email.com",  Status: true },
        }
    
        for _, person := range persons {
            b, err := bson.Marshal(person)
            if err != nil {
                log.Fatal("bson.Marshal: ", err)
            }
            
            var d bson.D
            err = bson.Unmarshal(b, &d)
            if err != nil {
                log.Fatal("bson.Unmarshal: ", err)
            }
            // log.Printf("%v", d)
    
            // 按照 Name 更新
            filter := bson.D{{"name", person.Name}}
            update := bson.D{{"$set", d}}
            opts := options.Update().SetUpsert(true)    // 如果没有则直接插入
            if res, err := coll.UpdateOne(context.TODO(), filter, update, opts); err != nil {
                log.Fatal("coll.UpdateOne: ", err)
            } else {
                log.Printf("matchedCount: %d, modifiedCount: %d", res.MatchedCount, res.ModifiedCount)
            }
        }
    }

    {
        // 对满足 Gender = F, Age < 20 的进行更新
        //  对记录整个更新
        the_person := model.PersonalInfo{ Name: "xiaoli", Gender: "F", Age: 17, Email: "xiaoli@email.com", Status: false }
        b, err := bson.Marshal(the_person)
        if err != nil {
            log.Fatal("bson.Marshal: ", err)
        }
        var d bson.D
        err = bson.Unmarshal(b, &d)
        if err != nil {
            log.Fatal("bson.Unmarshal: ", err)
        }
        filter := bson.D{{"gender", "F"},{"age", bson.D{{"$lt", 20}}}}
        update := bson.D{{"$set", d}}
        opts := options.Update().SetUpsert(true)
        if res, err := coll.UpdateOne(context.TODO(), filter, update, opts); err != nil {
            log.Fatal("coll.UpdateOne: ", err)
        } else {
            log.Printf("matchedCount: %d, modifiedCount: %d", res.MatchedCount, res.ModifiedCount)
        }
    }

    {
        // 对满足 Age > 30 的进行更新
        //  只更新记录中的某个字段
        filter := bson.D{{"age", bson.D{{"$gt", 30}}}}
        update := bson.D{{"$set", bson.D{{"status", false}}}}
        opts := options.Update().SetUpsert(true)
        if res, err := coll.UpdateOne(context.TODO(), filter, update, opts); err != nil {
            log.Fatal("coll.UpdateOne: ", err)
        } else {
            log.Printf("matchedCount: %d, modifiedCount: %d", res.MatchedCount, res.ModifiedCount)
        }
    }
}


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
    if err := coll.Drop(context.Background()); err != nil {
		log.Fatal(err)
	}

    coll = client.Database("my_db").Collection("personals")

	persons := []interface{}{
		model.PersonalInfo{ Name: "bOb",      Gender: "M", Age: 5,  Email: "bOb@email.com",	   	 Status: true },
		model.PersonalInfo{ Name: "xiaoming", Gender: "M", Age: 8,  Email: "xiaoming@email.com", Status: true },
		model.PersonalInfo{ Name: "xiaohong", Gender: "F", Age: 18, Email: "xiaohong@email.com", Status: true },
		model.PersonalInfo{ Name: "bob",      Gender: "M", Age: 15, Email: "bob@email.com",	   	 Status: true },
		model.PersonalInfo{ Name: "xiaocai",  Gender: "F", Age: 24, Email: "xiaocai@email.com",  Status: true },
		model.PersonalInfo{ Name: "laowang",  Gender: "M", Age: 37, Email: "laowang@email.com",  Status: true },
		model.PersonalInfo{ Name: "Bob",      Gender: "M", Age: 25, Email: "Bob@email.com",	   	 Status: true },
	}

	if _, err := coll.InsertMany(context.TODO(), persons); err != nil {
		log.Fatal(err)
	}

	animals := []string{"cow", "goat"}
	var docs []interface{}
	for i := 0; i < len(animals); i++ {
		docs = append(docs, bson.D{{"name", animals[i]},{"age", i},{"status",true}})
	}
	if _, err := coll.InsertMany(context.Background(), docs); err != nil {
		log.Fatal(err)
	}

    {
        // 删除没有 gender 的记录
        filter := bson.D{{"gender", bson.D{{"$exists", false}}}}
        if _, err := coll.DeleteMany(context.Background(), filter); err != nil {
            log.Fatal(err)
        }
    }

    {
        // 删除 Name 为 bob 的记录，Bob 不区分大小写
        // Delete at most one document in which the "name" field is "Bob" or "bob".
        // Specify the SetCollation option to provide a collation that will ignore
        // case for string comparisons.
        opts := options.Delete().SetCollation(&options.Collation{
            Locale:    "en_US",
            Strength:  1,
            CaseLevel: false,
        })
        if res, err := coll.DeleteMany(context.TODO(), bson.D{{"name", "bob"}}, opts); err != nil {
            log.Fatal(err)
        } else {
            log.Printf("deletedCount: %d", res.DeletedCount)
        }
    }

    {
        // 删除 age <= 20 的记录
        if res, err := coll.DeleteMany(context.Background(), bson.D{{"age", bson.D{{"$lte",20}}}}); err != nil {
            log.Fatal(err)
        } else {
            log.Printf("deletedCount: %d", res.DeletedCount)
        }
    }

    {
        // 如果 filter 为空，则会删除所有记录
        if res, err := coll.DeleteMany(context.Background(), bson.D{}); err != nil {
            log.Fatal(err)
        } else {
            log.Printf("deletedCount: %d", res.DeletedCount)
        }
    }
}
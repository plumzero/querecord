
package main

import (
	"log"
	"go.mongodb.org/mongo-driver/bson"

	"mgdtest.com/model"
)

func main() {
	testM := bson.M {
		"jobName": "job multi1",
	}
	var raw bson.Raw
	tmp, _ := bson.Marshal(testM)
	bson.Unmarshal(tmp, &raw)

	log.Printf("%v", testM)
	log.Printf("%v", raw)

	{
		// 通过 bson.Marshal 将结构体转为 bytes，再通过 bson.Unmarshal 将 bytes 转为 bson.D 或 bson.M
		person := model.PersonalInfo{ Name: "xiaoming", Age: 10, Email: "xiaoming@email.com" }

		b, err := bson.Marshal(person)
		if err != nil {
			log.Fatal("bson.Marshal: ", err)
		}
		
		var m bson.M
		err = bson.Unmarshal(b, &m)
		if err != nil {
			log.Fatal("bson.Unmarshal: ", err)
		}
		log.Printf("%v", m)

		// 关于数组，暂时没有更好的办法。先单个元素的处理
	}

	{
		// 通过 bson.Marshal 将结构体转为 bytes，再通过 bson.Unmarshal 将 bytes 转为 bson.D 或 bson.M
        persons := []model.PersonalInfo{
            { Name: "xiaoming", Gender: "M", Age: 8,  Email: "xiaoming@email.com", Status: true },
            { Name: "xiaohong", Gender: "F", Age: 18, Email: "xiaohong@email.com", Status: true },
            { Name: "xiaocai",  Gender: "F", Age: 24, Email: "xiaocai@email.com",  Status: true },
            { Name: "laowang",  Gender: "M", Age: 37, Email: "laowang@email.com",  Status: true },
        }

		b, err := bson.Marshal(persons)
		if err != nil {
			log.Fatal("bson.Marshal: ", err)
		}
		
		var m bson.M
		err = bson.Unmarshal(b, &m)
		if err != nil {
			log.Fatal("bson.Unmarshal: ", err)
		}
		log.Printf("%v", m)

		// 关于数组，暂时没有更好的办法。先单个元素的处理
	}
}
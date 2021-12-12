
package main

import (
	"log"
	"go.mongodb.org/mongo-driver/bson"
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
}
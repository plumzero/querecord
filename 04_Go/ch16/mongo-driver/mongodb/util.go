
package mongodb

import (
	"context"
	"log"

	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
)

var _mongo_addr = "mongodb://localhost:27017"

var _mgo_cli *mongo.Client

func initDb() {
	var err error
	_mgo_cli, err = mongo.Connect(context.TODO(), options.Client().ApplyURI(_mongo_addr))
	if err != nil {
		log.Fatal(err)
	}
	err = _mgo_cli.Ping(context.TODO(), readpref.Primary())
	if err != nil {
		log.Fatal(err)
	}
}

func MgoCli() *mongo.Client {
	if _mgo_cli == nil {
		initDb()
	}

	return _mgo_cli
}
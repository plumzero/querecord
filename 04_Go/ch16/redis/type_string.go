
package main

import (
    "context"
    "fmt"

    redis "github.com/go-redis/redis/v8"
)

var ctx = context.Background()

func main() {
    rdb := redis.NewClient(&redis.Options{
        Addr:       ":6379",
        Password:   "",
        DB:         0,
    })

    err := rdb.Set(ctx, "mykey", "myvalue", 0).Err()
    if err != nil {
        panic(err)
    }

    val, err := rdb.Get(ctx, "mykey").Result()
    if err != nil {
        panic(err)
    }
    fmt.Println("key", val)

    val, err = rdb.Get(ctx, "nokey").Result()
    if err == redis.Nil {
        fmt.Println("nokey does not exist")
    } else if err != nil {
        panic(err)
    } else {
        fmt.Println("nokey", val)
    }
}
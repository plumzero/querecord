
package main

import (
	"fmt"
	"log"
	"os"
	"strings"

	"github.com/spf13/viper"
)

func main() {
	confile := os.Args[1]
	last_backstash_index := strings.LastIndexByte(confile, '/')
	directory_name := confile[:last_backstash_index + 1]
	filename := confile[last_backstash_index + 1:]

	v := viper.New()
	v.SetConfigName(filename) 			// name of config file (without extension)
	v.SetConfigType("json") 			// REQUIRED if the config file does not have the extension in the name
	v.AddConfigPath(directory_name)               	// optionally look for config in the working directory
	
	err := v.ReadInConfig() // Find and read the config file
	if err != nil { // Handle errors reading the config file
		panic(fmt.Errorf("Fatal error config file: %w \n", err))
	}

	log.Printf("mode: %s", v.GetString("mode"))
	log.Printf("alarm: ip=%s, path=%s", v.GetString("alarm.ip"), v.GetString("alarm.path"))
	log.Printf("log: path=%s", v.GetString("log.path"))

	label := "grpc.caitong"
	log.Printf("grpc: %s, %s", v.GetString(label), v.GetString("grpc.gwt-sz2"))
	for k, v := range v.GetStringMapString("grpc") {
		log.Printf("  %s -> %s", k, v)
	}

	log.Printf("redis.real: addr=%s, password=%s", v.GetString("redis.real.addr"), v.GetString("redis.real.password"))
	log.Printf("mongo.real: addr=%s, user=%s, password=%s", v.GetString("mongo.real.addr"), v.GetString("mongo.real.user"), v.GetString("mongo.real.password"))

	log.Printf("service.market.restful.addr: %s", v.GetString("service.market.restful.addr"))

	latest_limit_prices := v.Get("service.market.Latest-Limit-Price").([]interface{})
	for i, v := range latest_limit_prices {
		log.Printf("  [%d] = %v", i, v)
		log.Printf("    name=%s", v.(map[string]interface{})["name"].(string))
		log.Printf("    receivers=%v", v.(map[string]interface{})["receivers"].([]interface{}))
		log.Printf("    weight=%f", v.(map[string]interface{})["weight"].(float64))
	}

	first := latest_limit_prices[0]
	log.Printf("|    name=%s", first.(map[string]interface{})["name"].(string))
	log.Printf("|    receivers=%v", first.(map[string]interface{})["receivers"].([]interface{}))
	log.Printf("|    weight=%f", first.(map[string]interface{})["weight"].(float64))

	items := first.(map[string]interface{})["receivers"].([]interface{})
	for _, v := range items {
		log.Printf("--> %s", v.(string))
	}


	indexmkdatas := v.Get("service.market.IndexMkdata").([]interface{})
	for i, v := range indexmkdatas {
		log.Printf("  [%d] = %v", i, v)
		log.Printf("    name=%s", v.(map[string]interface{})["name"].(string))
		log.Printf("    receivers=%v", v.(map[string]interface{})["receivers"].([]interface{}))
		log.Printf("    weight=%f", v.(map[string]interface{})["weight"].(float64))
	}

	minutemkdatas := v.Get("service.market.MinuteMkData").([]interface{})
	for i, v := range minutemkdatas {
		log.Printf("  [%d] = %v", i, v)
		log.Printf("    name=%s", v.(map[string]interface{})["name"].(string))
		log.Printf("    receivers=%v", v.(map[string]interface{})["receivers"].([]interface{}))
		log.Printf("    weight=%f", v.(map[string]interface{})["weight"].(float64))
	}

	log.Printf("service.indicator.restful.addr: %s", v.GetString("service.indicator.restful.addr"))
	POSTs := v.GetStringMapString("service.indicator.restful.POST")
	for k, v := range POSTs {
		log.Printf("  %s -> %s", k, v)
	}

	log.Printf("service.calc.grpc-server.addr: %s", v.GetString("service.calc.grpc-server.addr"))
	log.Printf("service.calc.grpc-server.cache-ttl: %d", v.GetInt("service.calc.grpc-server.cache-ttl"))
}
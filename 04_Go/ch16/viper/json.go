
package main

import (
	"fmt"

	"github.com/spf13/viper"
)

func main() {
	viper.SetConfigName("config") 			// name of config file (without extension)
	viper.SetConfigType("json") 			// REQUIRED if the config file does not have the extension in the name
	viper.AddConfigPath("/etc/appname/")   	// path to look for the config file in
	viper.AddConfigPath("$HOME/.appname")  	// call multiple times to add many search paths
	viper.AddConfigPath(".")               	// optionally look for config in the working directory
	
	err := viper.ReadInConfig() // Find and read the config file
	if err != nil { // Handle errors reading the config file
		panic(fmt.Errorf("Fatal error config file: %w \n", err))
	}

	fmt.Println("config name:", viper.Get("name"))
	fmt.Println("config log:", viper.Get("log"))
	fmt.Println("config redis:", viper.Get("redis"))

	/**
		func Get(key string) interface{} { return v.Get(key) }
	 */
	fmt.Println("config log.path:", viper.Get("log.path").(string))
	fmt.Println("config log.mode:", viper.Get("log.mode").(string))
	fmt.Println("config log.level:", viper.Get("log.level").(float64))

	fmt.Println("config redis.addr:", viper.Get("redis.addr").(string))
	fmt.Println("config redis.password:", viper.Get("redis.password").(string))
}
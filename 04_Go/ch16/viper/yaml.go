
package main

import (
	"fmt"

	"github.com/spf13/viper"
)

func main() {
	viper.SetConfigName("config") 			// name of config file (without extension)
	viper.SetConfigType("yaml") 			// REQUIRED if the config file does not have the extension in the name
	viper.AddConfigPath("/etc/appname/")   	// path to look for the config file in
	viper.AddConfigPath("$HOME/.appname")  	// call multiple times to add many search paths
	viper.AddConfigPath(".")               	// optionally look for config in the working directory
	
	err := viper.ReadInConfig() // Find and read the config file
	if err != nil { // Handle errors reading the config file
		panic(fmt.Errorf("Fatal error config file: %w \n", err))
	}

	fmt.Println("config app:", viper.Get("app"))
	fmt.Println("config redis:", viper.Get("redis"))

	/**
		func Get(key string) interface{} { return v.Get(key) }
	 */
	fmt.Println("config app.logFile:", viper.Get("app.logFile").(string))
	fmt.Println("config app.httpPort:", viper.Get("app.httpPort").(int))
	fmt.Println("config app.webSocketPort:", viper.Get("app.webSocketPort").(int))
	fmt.Println("config app.rpcPort:", viper.Get("app.rpcPort").(int))
	fmt.Println("config app.httpUrl:", viper.Get("app.httpUrl").(string))
	fmt.Println("config app.webSocketUrl:", viper.Get("app.webSocketUrl").(string))	
}
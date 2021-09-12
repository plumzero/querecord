
package main

import (
	"net/http"
	"encoding/json"
	"fmt"
)

type Greeting struct {
	Message string `json:"message"`
}

func Hello(w http.ResponseWriter, r *http.Request) {
	greeting := Greeting{ "Hello World" }

	message, _ := json.Marshal(greeting)
	w.Header().Set("Content-Type", "application/json")
	w.Write(message)
}

func main() {
	http.HandleFunc("/hello", Hello)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		fmt.Println(err)
	}
}
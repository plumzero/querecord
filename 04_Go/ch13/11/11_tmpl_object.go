
package main

import (
	"fmt"
	"html/template"
	"net/http"
)

func HelloHandleFunc(w http.ResponseWriter, r *http.Request) {
	t, err := template.ParseFiles("11_tmpl_object.tmpl")
	if err != nil {
		fmt.Println("template parsefile failed, err:", err)
		return
	}

	name := "golang"
	t.Execute(w, name)
}

func main() {
	http.HandleFunc("/", HelloHandleFunc)
	http.ListenAndServe(":8080", nil)
}
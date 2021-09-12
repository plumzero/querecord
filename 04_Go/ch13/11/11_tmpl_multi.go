
package main

import (
	"fmt"
	"html/template"
	"net/http"
)

type UserInfo struct {
	Name 	string
	Gender 	string
	Age 	int
}

func tmplSample(w http.ResponseWriter, r *http.Request) {
	tmpl, err := template.ParseFiles("./11_tmpl_multi.html", "./ul.html")
	if err != nil {
		fmt.Println("create template failed, err:", err)
		return
	}

	user := UserInfo{
		Name: "zhangSan",
		Gender: "male",
		Age: 28,
	}

	tmpl.Execute(w, user)
}

func main() {
	http.HandleFunc("/", tmplSample)
	http.ListenAndServe(":8080", nil)
}

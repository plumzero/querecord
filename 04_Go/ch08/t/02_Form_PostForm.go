
package main

import (
	"net/http"
	"log"
	"fmt"
)

func process(w http.ResponseWriter, r *http.Request) {

	if r.Method == "GET" {
		http.ServeFile(w, r, "02_Form_PostForm.html")
	}

	if r.Method == "POST" {
		r.ParseForm()
		fmt.Fprintln(w, "表单键值对和URL键值对: ", r.Form)
		fmt.Fprintln(w, "表单键值对: ", r.PostForm)
	}
}

func main() {
	http.HandleFunc("/process", process)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal("ListenAndServe:", err)
	}
}
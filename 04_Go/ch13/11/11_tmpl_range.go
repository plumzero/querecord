
package main


import (
	"html/template"
	"net/http"
)

func myhandler(w http.ResponseWriter, r *http.Request) {
	t, _ := template.ParseFiles("./11_tmpl_range.html")
	userInfo := []string{ "zhangSan", "liSi" }
	t.Execute(w, userInfo)
}

func main() {
	http.HandleFunc("/", myhandler)
	http.ListenAndServe(":8080", nil)
}

package main

import (
	"fmt"
	"html/template"
	"io/ioutil"
	"net/http"
)

// 无参函数，用作模板函数
func Welcome() string {
	return "Welcome"
}

// 有参函数，用作模板函数
func Doing(name string) string {
	return name + ", Learning Go Web template"
}

func sayHello(w http.ResponseWriter, r *http.Request) {
	htmlByte, err := ioutil.ReadFile("./03_tmpl_funcs.html")
	if err != nil {
		fmt.Println("read html failed, err:", err)
		return
	}
	// 匿名模板函数
	loveGo := func() (string) {
		return "I love Go"
	}
	// 链式操作在 Parse() 方法之前调用  Funcs() 函数，用来添加自定义的 loveGo 函数
	tmpl1, err := template.New("funcs").Funcs(template.FuncMap{"loveGo":loveGo}).Parse(string(htmlByte))
	if err != nil {
		fmt.Println("create template failed, err:", err)
		return
	}
	funcMap := template.FuncMap{
		"Welcome": Welcome,
		"Doing": Doing,
	}
	name := "coder"
	tmpl2, err := template.New("test").Funcs(funcMap).Parse("{{Welcome}}\n{{Doing .}}\n")
	if err != nil {
		panic(err)
	}
	
	// 渲染模板，将结果写入 w
	tmpl1.Execute(w, name)
	tmpl2.Execute(w, name)
}

func main() {
	http.HandleFunc("/", sayHello)
	http.ListenAndServe(":8080", nil)
}
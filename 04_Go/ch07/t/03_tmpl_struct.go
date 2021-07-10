
package main

import (
    "html/template"
    "os"
)

type UserInfo struct {
    Name	string
    Gender	string
    Age 	int
}

func main() {
    tmpl, err := template.ParseFiles("./03_tmpl_struct.tmpl")
    if err != nil {
        panic("create template failed, err:" + err.Error())
    }

    user := UserInfo {
        Name: "Tom",
        Gender: "male",
        Age: 15,
    }

    if err := tmpl.Execute(os.Stdout, user); err != nil {
        panic(err)
    }
}
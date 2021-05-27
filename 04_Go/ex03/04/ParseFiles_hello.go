
package main

import (
    "html/template"
    "os"
)

func main() {
    t, err := template.ParseFiles("testdata/hello.html")
    if err != nil {
        panic(err)
    }

	locals := make(map[string]interface{})
	locals["name"] = "World"

    err = t.Execute(os.Stdout, locals)
    if err != nil {
        panic(err)
    }

    return
}
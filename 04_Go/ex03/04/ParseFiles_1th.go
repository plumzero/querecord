
package main

import (
    "html/template"
    "os"
)

func main() {
    t, err := template.ParseFiles("testdata/upload.html")
    if err != nil {
        panic(err)
    }

    err = t.Execute(os.Stdout, nil)
    if err != nil {
        panic(err)
    }

    return
}
package main

import (
	"html/template"
	"io/ioutil"
	"os"
)

func main() {
    files , err := ioutil.ReadDir("testdata")
    if err != nil {
        panic(err)
    }

    locals := make(map[string]interface{})
    images := []string{}

    for _, file := range files {
        images = append(images, file.Name())
    }
    locals["images"] = images
    
	t, err := template.ParseFiles("testdata/list.html")
	if err != nil {
		panic(err)
	}

	err = t.Execute(os.Stdout, locals)
	if err != nil {
		panic(err)
	}

	return
}

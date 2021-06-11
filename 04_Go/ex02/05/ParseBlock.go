
package main

import (
	"fmt"
	"os"
	"strings"
	"text/template"
)

func main() {
	const (
		master = `Names:{{block "list" .}}{{"\n"}}{{range .}}{{println "+" .}}{{end}}{{end}}`
		overlay = `{{define "list"}} {{join . ", "}}{{end}}`
	)
	var (
		funcs = template.FuncMap{"join": strings.Join}
		guardians = []string{ "Gamora", "Groot", "Nebula", "Rocket", "Star-Lord" }
	)

	masterTmpl, err := template.New("master").Funcs(funcs).Parse(master)
	if err != nil {
		fmt.Println(err)
	}

	overlayTmpl, err := template.Must(masterTmpl.Clone()).Parse(overlay)
	if err != nil {
		fmt.Println(err)
	}

	if err := masterTmpl.Execute(os.Stdout, guardians); err != nil {
		fmt.Println(err)
	}

	if err := overlayTmpl.Execute(os.Stdout, guardians); err != nil {
		fmt.Println(err)
	}
}
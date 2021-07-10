package main

import (
    "os"
    "text/template"
)

func main() {
    rangeTemplate := `
{{if .Kind}}
{{range $i, $v := .MapContent}}
{{$i}} => {{$v}}, {{$.OutsideContent}}
{{end}}
{{else}}
{{range .MapContent}}
{{.}}, {{$.OutsideContent}}
{{end}}
{{end}}`

    str1 := []string{"第一次 range", "用 index 和 value"}
    str2 := []string{"第二次 range", "没用 index 和 value"}

    type Content struct {
        MapContent		[]string
        OutsideContent	string
        Kind			bool
    }

    var contents = []Content {
        { str1, "第一次外面的内容", true },
        { str2, "第二次外面的内容", false },
    }

    t := template.Must(template.New("range").Parse(rangeTemplate))

    for _, c := range contents {
        err := t.Execute(os.Stdout, c)
        if err != nil {
            panic("executing template: " + err.Error())
        }
    }
}
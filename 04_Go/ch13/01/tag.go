
package main

import (
	"fmt"
	"reflect"
)

type Student struct {
	name string
	Age int			`json:"years"`
}

func main() {
	var pupil Student = Student{ "joke", 18 }
	setStudent := reflect.ValueOf(&pupil).Elem()

	sSAge, _ := setStudent.Type().FieldByName("Age")
	fmt.Println(sSAge.Tag.Get("json"))
}

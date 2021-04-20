package main

import (
	"fmt"
	"github.com/golang/protobuf/proto"
	"mypro.com/mypro"
)

func main() {
	s1 := &mypro.Student{
		Name: "jz01",
		Age: 23,
		Address: "cq",
		Cn: mypro.ClassName_class2,
	}

	ss := &mypro.Students{}
	ss.Person = append(ss.Person, s1)

	s2 := &mypro.Student{
		Name: "jz02",
		Age: 25,
		Address: "cd",
		Cn: mypro.ClassName_class3,
	}

	ss.Person = append(ss.Person, s2)
	ss.School = "cqu"

	fmt.Println("Students info:", ss)

	// Marshal takes a protocol buffer message
	// and encodes it into the wire format, returning the data.
	buffer, _ := proto.Marshal(ss)
	fmt.Println("Marshaled info:", buffer)
	//  Use UnmarshalMerge to preserve and append to existing data.
	data := &mypro.Students{}
	proto.Unmarshal(buffer, data)
	fmt.Println("Unmarshaled info:", data)
}

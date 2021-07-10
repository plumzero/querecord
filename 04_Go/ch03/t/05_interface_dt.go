
package main

import "fmt"

type Message interface {
	sending()
}

type User struct {
	name string
	email string
}

func (u *User) sending() {
	fmt.Printf("Sending user phone to %s<%s>\n", u.name, u.email)
}

type Admin struct {
	name string
	email string
}

func (a *Admin) sending() {
	fmt.Printf("Sending admin phone to %s<%s>\n", a.name, a.email)
}

func sendMessage(n Message) {
	n.sending()
}

func main() {
	bill := User{ "Barry", "barry@gmail.com" }
	sendMessage(&bill)

	lisa := Admin{ "Jim", "jim@gmail.com" }
	sendMessage(&lisa)
}
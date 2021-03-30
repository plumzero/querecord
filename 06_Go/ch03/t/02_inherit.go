
package main

import "fmt"

type Base struct {
	Name string
}

func (base * Base) Foo() { 
	fmt.Println("Base::Foo")
}
func (base * Base) Bar() { 
	fmt.Println("Base::Bar")
}

type Derived struct {
	Base
}

func (derived * Derived) Bar() {
	derived.Base.Bar()
	fmt.Println("Derived::Bar")
}

func main() {

	d := new(Derived)

	d.Bar();
}


package main

import "fmt"

type Rect struct {
    x, y float64
    width, height float64
}

func (r * Rect) Area() float64 {
    return r.width * r.height
}

func main() {

    rect := Rect{ 0, 0, 100, 200 }
    
    area := rect.Area()

    fmt.Println(area)
}
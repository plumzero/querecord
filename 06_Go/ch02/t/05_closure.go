
package main

import (
    "fmt"
)

func main() {
    var j int = 5           // j 是外部变量
    
    a := func() (func()) {
        var i int = 10      // i 是自由变量
        return func() {
            i++
            fmt.Printf("i, j: %d, %d\n", i, j);
        }
    }()
    
    a()
    
    j *= 2
    
    a()
}
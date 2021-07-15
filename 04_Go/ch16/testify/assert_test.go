package main

import (
  "testing"
  "github.com/stretchr/testify/assert"
  "fmt"
)

func TestSomething(t *testing.T) {

    // 全局 assert
    {
        fmt.Println("================> first test <================")
        // assert equality
        assert.Equal(t, 123, 123, "they should be equal")

        // assert inequality
        assert.NotEqual(t, 123, 456, "they should not be equal")

        // assert for nil (good for errors)
        // var pi *int32 = nil
        // assert.Nil(t, pi)

        // assert for not nil (good when you expect something)
        var str string = "Hello World"
        var ps *string = &str
        if assert.NotNil(t, ps) {
            // now we know that object isn't nil, we are safe to make
            // further assertions without causing any errors
            assert.Equal(t, "Hello World", *ps)
        }
    }

    // assert 对象
    {
        fmt.Println("================> second test <================")
        art := assert.New(t)

        // assert equality
        art.Equal(123, 123, "they should be equal")
    
        // assert inequality
        art.NotEqual(123, 456, "they should not be equal")
    
        // assert for nil (good for errors)
        // var pi *int32 = nil
        // art.Nil(t, pi)
    
        // assert for not nil (good when you expect something)
        var str string = "Hello World"
        var ps *string = &str
        if art.NotNil(ps) {
            // now we know that object isn't nil, we are safe to make
            // further assertions without causing any errors
            art.Equal("Hello World", *ps)
        }
    }
}

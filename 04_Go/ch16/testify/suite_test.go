
package main

import (
	"fmt"
	"testing"

	"github.com/stretchr/testify/suite"
)

type MySuite struct {
	suite.Suite
	myint int
	mystr string
}

// 执行 suite 之前，执行这个
func (s *MySuite) SetupSuite() {
	fmt.Println("========== do SetupSuite ==========")
}
// 执行 suite 之后，执行这个
func (s *MySuite) TearDownSuite() {
	fmt.Println("========== do TearDownSuite ==========")
}

// 每执行 suite 中的一个测试方法(method) 之前，都会执行这个
func (s *MySuite) SetupTest() {
	fmt.Println("do SetupTest")
	s.myint = 100
	s.mystr = "Hello World"
}
// 每执行 suite 中的一个测试方法(method) 之后，都会执行这个
func (s *MySuite) TearDownTest() {
	fmt.Println("do TearDownTest")
	s.myint = 0
	s.mystr = ""
}
// method  方法必须以 Test 开头。为了避免冲突，可以通过 "_" 连接
func (s *MySuite) Test_Int() {
	fmt.Println("do Test_Int")
	s.Equal(s.myint, 100)
}
// method
func (s *MySuite) Test_Str() {
	fmt.Println("do Test_Str")
	s.Equal(s.mystr, "Hello World")
}

func TestExampleOfMySuite(t *testing.T) {
	suite.Run(t, new(MySuite))
}



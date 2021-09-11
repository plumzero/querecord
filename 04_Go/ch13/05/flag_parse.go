
package main

import (
	"flag"
	"fmt"
	"os"
)

var (
	h, H bool

	v bool
	q *bool

	D string
	Conf string
)

func init() {
	flag.BoolVar(&h, "h", false, "帮助信息")
	flag.BoolVar(&H, "H", false, "帮助信息")

	flag.BoolVar(&v, "v", false, "显示版本号")

	flag.StringVar(&D, "D", "deamon", "set description")
	flag.StringVar(&Conf, "Conf", "/dev/conf/cli.conf", "set Conf filename")

	// 另一种绑定方式
	q = flag.Bool("q", false, "退出程序")

	// 改变默认的 Usage
	flag.Usage = usage

	flag.Parse()

	var cmd string = flag.Arg(0)
	fmt.Printf("----------\n")
    fmt.Printf("cli non=flags: %s\n", cmd)
    fmt.Printf("q: %t\n", *q)
    fmt.Printf("description: %s\n", D)
    fmt.Printf("Conf filename: %s\n", Conf)
    fmt.Printf("----------\n")
    
    fmt.Printf("there are %d non-flag input param\n", flag.NArg())
    for i, param := range flag.Args() {
        fmt.Printf("#%d :%s\n", i, param)
    }
}

func main() {
    flag.Parse()

    if h || H {
        flag.Usage()
    }
}

func usage() {
    fmt.Fprintf(os.Stderr, `CLI:8.0
Usage: Cli [-hvq] [-D description] [-Conf filename]

`)
    flag.PrintDefaults()
}
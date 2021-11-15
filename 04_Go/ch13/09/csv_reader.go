
package main

import (
	"encoding/csv"
	"fmt"
	"os"
	"bufio"
	"io"
)

func main() {
	fname := "reader.csv"
	file, err := os.OpenFile(fname, os.O_RDWR | os.O_CREATE, 0644)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	rio := bufio.NewReader(file)
	if rio == nil {
		panic("bufio.NewReader failed")
	}

	reader := csv.NewReader(rio)
	if reader == nil {
		panic("csv.NewReader failed")
	}
	reader.Comment = 't'			// 屏蔽首行，减少代码 time,code,...
	reader.ReuseRecord = true		// 重用缓存，加快速度
	for {
		record, err := reader.Read()
		if err == io.EOF {
			break
		}
		if err != nil {
			panic(err)
		}
		fmt.Println(len(record), "=>", record)
	}
}
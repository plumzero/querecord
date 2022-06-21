
package main

import (
	"regexp"
	"strings"
	"log"
)

func main() {
	re := `2022-06-13\$modelWgtsDict0610_539_473(online)\$[0-9a-zA-Z_\(\)]*\$zz500`
	s := "2022-06-13$modelWgtsDict0610_539_473(online)$testT01$zz500"

	isMatched_1, _ := regexp.MatchString(re, s)
	log.Printf("isMatched_1: %v", isMatched_1)

	re = strings.ReplaceAll(re, "(online)", `\(online\)`)
	isMatched_2, _ := regexp.MatchString(re, s)
	log.Printf("isMatched_2: %v", isMatched_2)
}
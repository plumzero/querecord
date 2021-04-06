
package main

import (
	"fmt"
	"os"
	"bufio"
	"log"

	"math/rand"
	"strings"
)

/**
	劈开:
		func Fields(s string) []string
	合并:
		func Join(elems []string, sep string) string
 */

func main() {

	var fname string = "filefortest.txt"

	file, err := os.OpenFile(fname, os.O_RDWR | os.O_CREATE, 0644)
	if err != nil {
		log.Fatal(err)
		return
	}

	defer file.Close()

	writer := bufio.NewWriter(file)
	if writer == nil {
		log.Fatal(err)
		return
	}

	var sentence string = "a b c d e f g h i j k l m n o p q r s t u v w x y z";

	for i := 0; i < 1024; i++ {
		words := strings.Fields(sentence)
		rand.Shuffle(len(words), func(i, j int) {
			words[i], words[j] = words[j], words[i]
		})
		wordstring := strings.Join(words, " ")
		
		_, err = writer.WriteString(wordstring + "\n")
		if err != nil {
			log.Fatal(err)
			return
		}
	}

	writer.Flush()

	fmt.Println("===== test over =====")
}
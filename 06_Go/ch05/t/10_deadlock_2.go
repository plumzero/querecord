package main

import "fmt"

func main() {
	messages := make(chan string, 1)

	msg := "hi"
	select {
		case messages <- msg:
			fmt.Println("sent message", msg)
	}

	go func() {
		fmt.Println("received message", <- messages)
	}()
}
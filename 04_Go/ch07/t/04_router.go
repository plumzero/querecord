
package main

import (
	"fmt"
	"log"
	"net/http"
)

func indexHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "indexHandler!")
}

func hiHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "hiHandler!")
}

func webHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "webHandler!")
}

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", indexHandler)
	mux.HandleFunc("/hi", hiHandler)
	mux.HandleFunc("/hi/web", webHandler)

	server := &http.Server{
		Addr: ":8080",
		Handler: mux,
	}

	if err := server.ListenAndServe(); err != nil {
		log.Fatal(err)
	}
}
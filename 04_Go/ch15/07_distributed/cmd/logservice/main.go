
package main

import (
	stlog "log"
	"dist.com/log"
	"dist.com/service"
	"fmt"
	"context"

	"dist.com/registry"
)

func main() {
	log.Run("./distributed.log")
	host, port := "localhost", "8000"

	serviceAddress := fmt.Sprintf("http://%s:%s", host, port)

	r := registry.Registration {
		ServiceName: registry.LogService,
		ServiceURL: serviceAddress,
	}
	ctx, err := service.Start(
		context.Background(),
		host,
		port,
		r,
		log.RegisterHandlers,
	)

	if err != nil {
		stlog.Fatalln(err)
	}
	<- ctx.Done()

	fmt.Println("Shutting down log service.")
}
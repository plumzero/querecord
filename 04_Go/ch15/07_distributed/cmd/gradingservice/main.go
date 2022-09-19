
package main

import (
	stlog "log"
	"dist.com/grades"
	"dist.com/service"
	"fmt"
	"context"

	"dist.com/registry"
)

func main() {
	host, port := "localhost", "6000"

	serviceAddress := fmt.Sprintf("http://%s:%s", host, port)

	r := registry.Registration {
		ServiceName: registry.GradingService,
		ServiceURL: serviceAddress,
	}
	ctx, err := service.Start(
		context.Background(),
		host,
		port,
		r,
		grades.RegisterHandlers,
	)

	if err != nil {
		stlog.Fatalln(err)
	}
	<- ctx.Done()

	fmt.Println("Shutting down grades service.")
}
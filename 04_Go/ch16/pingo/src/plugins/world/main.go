// Always create a new binary
package main

import (
	"github.com/dullgiulio/pingo"
)

// Create an object to be exported
type MyPlugin struct{}

// Exported method, with a RPC signature
func (p *MyPlugin) SayWorld(name string, msg *string) error {
    *msg = "World, " + name
    return nil
}

func main() {
	plugin := &MyPlugin{}

	// Register the objects to be exported
	pingo.Register(plugin)
	// Run the main events handler
	pingo.Run()
}

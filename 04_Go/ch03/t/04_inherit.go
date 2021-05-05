
package main

import (
	"runtime"
	"fmt"
)

type Log string

func (l *Log) Input(s string) {
	*l = Log(s)
}

func (l Log) Output() {
	fmt.Println(l)
}

type ExtLog struct {
	Log
	header string
	level int
}

func NewExtLog() *ExtLog {
	extLog := new(ExtLog)
	_, extLog.header, _, _ = runtime.Caller(1)
	extLog.level = 0
	return extLog
}

func (l *ExtLog) SetLevel(level int) {
	l.level = level
}

func (l ExtLog) Output() {
	if l.level <=0 {
		fmt.Print("DEBUG: ")
	} else if l.level == 1 {
		fmt.Print("INFO: ")
	} else if l.level == 2 {
		fmt.Print("WARNING: ")
	} else {
		fmt.Print("ERROR: ")
	}
	fmt.Println(l.header, ":", l.Log)
}

func main() {
	llog := NewExtLog()

	llog.SetLevel(1)
	llog.Input("Using input method of Log type")

	llog.Output()
}
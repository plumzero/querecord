
package busi

import (
    "strings"
    "fmt"
)

func WasteProcessorCallBack(in interface{}, userdata interface{}) (out interface{}, err error) {
    var str string

    if data, ok := in.(string); ok {
        str = strings.ToUpper(data)
    } else {
        panic("CellsDuelistCallBack unexpected")
    }

    return str, nil
}

func AgentJunkSendCallBack(userdata interface{})(out interface{}, err error) {
    var str string = "Hello Junk"
    fmt.Println("Junk will send:", str)

    return str, nil
}

func AgentJunkRecvCallBack(in interface{}, userdata interface{}) (err error) {
    if data, ok := in.(string); ok {
        fmt.Println("Junk Received:", data)
    } else {
        panic("AgentJunkRecvCallBack unexpected")
    }

    return nil
}

func AgentRubbishSendCallBack(userdata interface{})(out interface{}, err error) {
    var str string = "Hello Rubbish"
    fmt.Println("Rubbish will send:", str)

    return str, nil
}

func AgentRubbishRecvCallBack(in interface{}, userdata interface{}) (err error) {
    if data, ok := in.(string); ok {
        fmt.Println("Rubbish Received:", data)
    } else  {
        panic("AgentRubbishRecvCallBack unexpected")
    }

    return nil
}

func AgentTrashSendCallBack(userdata interface{})(out interface{}, err error) {
    var str string = "Hello Trash"
    fmt.Println("Trash will send:", str)

    return str, nil
}

func AgentTrashRecvCallBack(in interface{}, userdata interface{}) (err error) {
    if data, ok := in.(string); ok {
        fmt.Println("Trash Received:", data)
    } else  {
        panic("AgentTrashRecvCallBack unexpected")
    }

    return nil
}
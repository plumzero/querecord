
package main

import (
    "encoding/json"
    // "os"
    "strings"
    "fmt"
)

type FullOrder struct {
    Id 			string      `json:"id"`
    ServerId 	int         `json:"serverId"`
    OrderId 	string      `json:"orderId"`
    Symbol      string      `json:"symbol"`
    Account     int         `json:"account"`
    Type        int         `json:"type"`
    Status      int         `json:"status"`
    SubmitTime  float64     `json:"submitTime"`
    CloseTime   float64     `json:"closeTime"`
    AcceptTime  float64     `json:"acceptTime"`
    CreateTime  float64     `json:"createTime"`
    OrderVolumn int         `json:"orderVolumn"`
    DealVolumn  int         `json:"dealVolumn"`
    OrderPrice  int         `json:"orderPrice"`
    OrderType   int         `json:"orderType"`
    NTime       int         `json:"nTime"`
    Tag         string      `json:"tag"`
    Risker      string      `json:"risker"`
    Timeout     int         `json:"timeout"`
    Force       bool        `json:"force"`
    DealPrice   int         `json:"dealPrice"`
    ErrCode     string      `json:"errCode"`
    ErrDetail   string      `json:"errDetail"` 
}

type SomeOrder struct {
    Id 			string      `json:"id"`
    ServerId 	int         `json:"serverId"`
    Symbol      string      `json:"symbol"`
    Account     int         `json:"account"`
    Type        int         `json:"type"`
    Status      int         `json:"status"`
    CreateTime  float64     `json:"createTime"`
    SubmitTime  float64     `json:"submitTime"`
    AcceptTime  float64     `json:"acceptTime"`
    CloseTime   float64     `json:"closeTime"`
}

func main() {

    b := []byte(
        `{
            "id": "109350007",
            "serverId": 10,
            "orderId": "2",
            "symbol": "600375",
            "account": 10099,
            "type": -1,
            "status": 2,
            "submitTime": 1622684100638.034,
            "closeTime": 0,
            "acceptTime": 1622684100662.141,
            "createTime": 1622684100637.816,
            "orderVolumn": 1000,
            "dealVolumn": 0,
            "orderPrice": 72000,
            "orderType": 1,
            "nTime": 93500000,
            "tag": "t2",
            "risker": "t2",
            "timeout": 10000,
            "force": false,
            "dealPrice": 0,
            "errCode": "JErrorType_None",
            "errDetail": ""
        }`,
    )

    dec := json.NewDecoder(strings.NewReader(string(b)))

    // 解析全字段
    var fullOrder FullOrder
    if err := dec.Decode(&fullOrder); err != nil {
        fmt.Println(err)
        return
    }
    fmt.Println("---------- FullOrder ----------")
    fmt.Println("id          =", fullOrder.Id)
    fmt.Println("serverId    =", fullOrder.ServerId)
    fmt.Println("orderId     =", fullOrder.OrderId)
    fmt.Println("symbol      =", fullOrder.Symbol)
    fmt.Println("account     =", fullOrder.Account)
    fmt.Println("type        =", fullOrder.Type)
    fmt.Println("status      =", fullOrder.Status)
    fmt.Println("submitTime  =", fullOrder.SubmitTime)
    fmt.Println("closeTime   =", fullOrder.CloseTime)
    fmt.Println("acceptTime  =", fullOrder.AcceptTime)
    fmt.Println("createTime  =", fullOrder.CreateTime)
    fmt.Println("orderVolumn =", fullOrder.OrderVolumn)
    fmt.Println("dealVolumn  =", fullOrder.DealVolumn)
    fmt.Println("orderPrice  =", fullOrder.OrderPrice)
    fmt.Println("orderType   =", fullOrder.OrderType)
    fmt.Println("nTime       =", fullOrder.NTime)
    fmt.Println("tag         =", fullOrder.Tag)
    fmt.Println("risker      =", fullOrder.Risker)
    fmt.Println("timeout     =", fullOrder.Timeout)
    fmt.Println("force       =", fullOrder.Force)
    fmt.Println("dealPrice   =", fullOrder.DealPrice)
    fmt.Println("errCode     =", fullOrder.ErrCode)
    fmt.Println("errDetail   =", fullOrder.ErrDetail)

    // 解析部分字段
    dec = json.NewDecoder(strings.NewReader(string(b)))

    var someOrder SomeOrder
    if err := dec.Decode(&someOrder); err != nil {
        fmt.Println(err)
        return
    }
    fmt.Println("---------- SomeOrder ----------")
    fmt.Println("id          =", fullOrder.Id)
    fmt.Println("serverId    =", fullOrder.ServerId)
    fmt.Println("symbol      =", fullOrder.Symbol)
    fmt.Println("account     =", fullOrder.Account)
    fmt.Println("type        =", fullOrder.Type)
    fmt.Println("status      =", fullOrder.Status)
    fmt.Println("createTime  =", fullOrder.CreateTime)
    fmt.Println("submitTime  =", fullOrder.SubmitTime)
    fmt.Println("acceptTime  =", fullOrder.AcceptTime)
    fmt.Println("closeTime   =", fullOrder.CloseTime)
}


package main

import "fmt"

func SendNotification(user string) chan string {
    // 此处省略查询数据库获取新消息
    // 声明一个通道来保存消息
    notifications := make(chan string, 500)

    // 开启一个通道
    go func() {
        notifications <- fmt.Sprintf("Hi %s, welcome to our site!", user)
    }()

    return notifications
}

func main() {
    barry := SendNotification("barry")
    larry := SendNotification("larry")

    // 将获取的消息返回
    fmt.Println(<-barry)
    fmt.Println(<-larry)
}
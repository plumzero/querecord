
package faci

import (
    "time"
    "fmt"
)

type Agent struct {
    name        string
    ch          chan interface{}
    lastUse     time.Time           // 记录通道的最近一次的使用时间
}

func NewAgent(name string) *Agent {
    var agent Agent
    agent.name = name
    return &agent
}

/**
 * @cells       处理器
 * @slist       如果 slist 不为空，则其表示为要发往的代理端, 代理端作为发送端; 如果 slist 为空，则不作任何处理
 */
func (this * Agent) Login(cells * Cells, slist []string) {
    ch, err := cells.login(this, slist)
    if err != nil {
        fmt.Printf("[%s] failed to login to [%s]\n", this.name, cells.Name());
        return
    }

    this.ch = ch

    fmt.Printf("[%s] login to [%s] success\n", this.name, cells.Name())
}

/**
 * @cells       处理器
 */
func (this * Agent) Logout(cells * Cells) {
    err := cells.logout(this)
    if err != nil {
        fmt.Printf("ERROR: %v\n", err)
        return
    }

    fmt.Printf("[%s] logout from [%s] success\n", this.name, cells.Name())
}

func (this *Agent) Name() string {
    return this.name
}

func (this *Agent) Channel() chan interface{} {
    this.lastUse = time.Now()
    return this.ch
}

func (this *Agent) LastUse() time.Time {
    return this.lastUse
}

func (this *Agent) SetNow() {
    this.lastUse = time.Now()
}
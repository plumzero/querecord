
package faci

import (
    "fmt"
    "time"
)

type Agent struct {
    name string
    ch chan interface{}
    userdata interface{}
    running bool
    // timeout int32            // 微秒超时: <0 永久阻塞, >0 超时, =0 不实现非阻塞,为 0 时使用默认超时 3000ms
    interval int64              // 微秒 | 读代理任务间隔 | 合法值 >0, <= 0 时使用默认 3000ms
    timestamp string            // 记录上一次调用的时间戳
}

func NewAgent(name string, interval int64) *Agent {
    var agent Agent
    agent.name = name

    agent.interval = interval
    if (agent.interval <= 0) {
        agent.interval = 3000
    }

    return &agent
}

/**
 * @cells       服务
 * @sendcb      代理发送回调接口
 * @recvcb      代理接收回调接口
 * @slist       如果 slist 不为空，则其表示为要发往的代理端, 代理端作为发送端; 如果 slist 为空，则代理端作为接收端
 * @userdata    用户传入数据
 */
func (agent * Agent) Run(cells * Cells,
                         sendcb func(interface{})(interface{}, error),
                         recvcb func(interface{}, interface{})(error),
                         slist []string,
                         userdata interface{}) {

    // if sendcb != nil && recvcb != nil {
    //     panic("read callback and write callback can not both be exist for the moment")
    // }

    ch, err := cells.login(agent.name, slist)
    if err != nil {
        fmt.Printf("[%s] failed to login to [%s]\n", agent.name, cells.Name());
        return
    }

    agent.ch = ch
    agent.userdata = userdata
    agent.running = true

    if sendcb != nil {
        go func() {
            time.Sleep(200 * time.Millisecond)
            for {
                if agent.running == false {
                    break
                }

                b := time.Now()
                
                data, err := sendcb(agent.userdata)
                if err != nil {
                    fmt.Printf("[%s] failed at read callback\n", agent.name)
                    continue
                }

                // block it for reading
                if data != nil {
                    agent.ch <- data
                    fmt.Printf("[%s] sent to channel(%p)\n", agent.name, agent.ch)
                }

                e := time.Now()
                elapsed := e.Sub(b)
                var ticks int64 = elapsed.Milliseconds()

                timeleft := agent.interval - ticks
                if timeleft > 0 {
                    time.Sleep(time.Duration(timeleft) * time.Millisecond)
                }
            }
        }()
    }

    if recvcb != nil {
        go func() {
            for {
                if agent.running == false {
                    break
                }
                // block it for writing
                data := <- agent.ch
                if data != nil {
                    fmt.Printf("[%s] received from channel(%p)\n", agent.name, agent.ch)    
                    err := recvcb(data, agent.userdata)
                    if err != nil {
                        fmt.Printf("[%s] failed at write callback\n", agent.name)
                        continue
                    }
                }
            }
        }()
    }

    fmt.Printf("[%s] login to [%s] and run success\n", agent.name, cells.Name())

    return 
}

func (agent * Agent) Stop(cells * Cells) {
    err := cells.logout(agent.name)
    if err != nil {
        fmt.Printf("[%s] failed to logout from [%s]\n", agent.name, cells.Name())
        return
    }

    agent.running = false

    fmt.Printf("[%s] logout from [%s] success\n", agent.name, cells.Name())
}

func (agent *Agent) Name() string {
    return agent.name
}

func (agent *Agent) Interval() int64 {
    return agent.interval
}

func (agent *Agent) Timestamp() string {
    return agent.timestamp
}

func (agent *Agent) SetTimestamp(t string) {
    agent.timestamp = t
}
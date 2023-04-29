package faci

import (
    "errors"
    "fmt"
    "os"
    "os/signal"
    "sync"
    "syscall"
    "time"
)

// notice: member variables and its own initialization
type Cells struct {
    name     string
    channels map[string]chan interface{}
    linktabs map[string][]string
    signals  map[string]chan os.Signal
    wg       sync.WaitGroup
    mtx      sync.Mutex
    cellscb  func(interface{}, interface{}) (interface{}, error)
    userdata interface{}
}

func NewCells(name string,
              cellscb func(interface{}, interface{}) (interface{}, error),
              userdata interface{}) *Cells {

    return &Cells{
        name:     name,
        channels: make(map[string]chan interface{}, 256),
        linktabs: make(map[string][]string, 256),
        signals:  make(map[string]chan os.Signal, 256),
        cellscb:  cellscb,
        userdata: userdata,
    }
}

func (this *Cells) Name() string {
    return this.name
}

// login to cells
func (this *Cells) login(agent *Agent, slist []string) (ch chan interface{}, err error) {
    this.mtx.Lock()
    defer this.mtx.Unlock()

    agentname := agent.Name()
    // already logined, return the channel
    if _, ok := this.channels[agentname]; ok {
        return this.channels[agentname], nil
    }
    // create a channel, and then return it to agent
    x := make(chan interface{}, 8192)
    this.wg.Add(1)
    // create a timeout
    timeout := make(chan bool, 1)
    go func() {
        for {
            time.Sleep(1 * time.Second)
            timeout <- true
        }
    }()

    // save the login information
    this.channels[agentname] = x
    if len(slist) != 0 {
        this.linktabs[agentname] = slist
    }
    this.signals[agentname] = make(chan os.Signal, 1)
    signal.Notify(this.signals[agentname], syscall.SIGTERM, syscall.SIGINT)

    // go routine: to receive the data sent by agent
    go func() {
        time.Sleep(100 * time.Millisecond)
        fmt.Printf("Go routine for [%s] starting...\n", agentname)
        defer this.wg.Done()
        agent.SetNow()
        for {
            select {
            case sig := <-this.signals[agentname]:
                fmt.Printf("[%s] triggered signal %d and would exit\n", agentname, sig)
                goto End
            case <-timeout:
                now := time.Now()
                elapsed := now.Sub(agent.LastUse())
                var ticks int64 = elapsed.Milliseconds()
                if ticks > 30000 {
                    fmt.Printf("[%s] time out %d seconds\n", agentname, ticks / 1000)
                    agent.SetNow()
                }
            case data := <-ch:
                if this.cellscb != nil {
                    ss, _ := this.linktabs[agentname]
                    newdata, err := this.cellscb(data, this.userdata)
                    if newdata != nil && err == nil {
                        for _, ele := range ss {
                            if _, havechannel := this.channels[ele]; havechannel {
                                this.channels[ele] <- newdata
                                fmt.Printf("[%s] forward data to [%s]\n", agentname, ele)
                            } else {
                                fmt.Printf("[%s] found no channel about [%s] to send\n", agentname, ele)
                            }
                        }
                    }
                }
            }
        }
    End:
        agent.Logout(this)
    }()

    return x, nil
}

func (this *Cells) logout(agent *Agent) error {
    this.mtx.Lock()
    defer this.mtx.Unlock()

    agentname := agent.Name()

    if _, ok := this.channels[agentname]; ok {
        if _, musthave := this.signals[agentname]; musthave {
            // clear
            this.signals[agentname] <- syscall.SIGTERM
            time.Sleep(100 * time.Millisecond) // wait for the signal be finished

            close(this.signals[agentname])
            delete(this.signals, agentname)
            delete(this.channels, agentname)
            if _, orhave := this.linktabs[agentname]; orhave {
                delete(this.linktabs, agentname)
            } else {
                for _, ss := range this.linktabs {
                    for i, ele := range ss {
                        if ele == agentname {
                            if len(ss) == 1 {
                                ss = make([]string, 0)
                            } else if i == len(ss)-1 {
                                ss = ss[:i-1]
                            } else if i == 0 {
                                ss = ss[1:]
                            } else {
                                ss = append(ss[:i-1], ss[:i+1]...)
                            }
                        }
                    }
                }
            }

            return nil
        } else {
            // It should not been here
            return errors.New("agent " + agentname + " logout failed")
        }
    }
    
    return nil
}

// wait to exit
func (this *Cells) Wait() {
    fmt.Printf("[%s] wait to serve...\n", this.name)
    this.wg.Wait()
    fmt.Printf("[%s] exit success\n", this.name)
}

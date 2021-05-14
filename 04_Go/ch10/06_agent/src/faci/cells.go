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

func (cells *Cells) Name() string {
    return cells.name
}

// login to cells
func (cells *Cells) login(agent string, slist []string) (ch chan interface{}, err error) {
    cells.mtx.Lock()
    defer cells.mtx.Unlock()
    // already logined, return an error message
    if _, ok := cells.channels[agent]; ok {
        return nil, errors.New(agent + " had been created")
    }
    // create a channel, and then return it to agent
    x := make(chan interface{}, 8192)
    cells.wg.Add(1)
    // create a timeout
    timeout := make(chan bool, 1)
    go func() {
        for {
            time.Sleep(1 * time.Second)
            timeout <- true
        }
    }()

    // save the login information
    cells.channels[agent] = x
    if len(slist) != 0 {
        cells.linktabs[agent] = slist
    }
    cells.signals[agent] = make(chan os.Signal, 1)
    signal.Notify(cells.signals[agent], syscall.SIGTERM, syscall.SIGINT)

    // go routine: to receive the data sent by agent
    go func() {
        time.Sleep(100 * time.Millisecond)
        fmt.Printf("Go routine for [%s] starting...\n", agent)
        defer cells.wg.Done()
        last := time.Now()
        now := time.Now()
        for {
            select {
            case sig := <-cells.signals[agent]:
                fmt.Printf("[%s] triggered signal %d and would exit\n", agent, sig)
                goto End
            case <-timeout:
                elapsed := now.Sub(last)
                var ticks int64 = elapsed.Milliseconds()
                if ticks > 3000 {
                    fmt.Printf("[%s] time out %d seconds\n", agent, ticks/1000)
                }
            case data := <-ch:
                ss, havelist := cells.linktabs[agent]
                if havelist {
                    newdata, err := cells.cellscb(data, cells.userdata)
                    if newdata != nil && err == nil {
                        for _, ele := range ss {
                            if _, havechannel := cells.channels[ele]; havechannel {
                                cells.channels[ele] <- newdata
                                fmt.Printf("[%s](ch=%p) forward data to [%s](ch=%p)\n", agent, ch, ele, cells.channels[ele])
                            } else {
                                fmt.Printf("[%s](ch=%p) found no channel about [%s] to send\n", agent, ch, ele)
                            }
                        }
                    }
                } else {
                    fmt.Printf("[%s](ch=%p) found no target to send\n", agent, ch)
                }
                last = now
                now = time.Now()
            }
        }
    End:
        fmt.Printf("[%s] logout\n", agent)
    }()

    fmt.Printf("[%s](ch=%p) login success\n", agent, x)

    return x, nil
}

// logout the cells
func (cells *Cells) logout(agent string) error {
    cells.mtx.Lock()
    defer cells.mtx.Unlock()

    if _, ok := cells.channels[agent]; ok {
        if _, musthave := cells.signals[agent]; musthave {
            // clear
            cells.signals[agent] <- syscall.SIGTERM
            time.Sleep(100 * time.Millisecond) // wait for the signal be finished

            close(cells.signals[agent])
            delete(cells.signals, agent)
            delete(cells.channels, agent)
            if _, orhave := cells.linktabs[agent]; orhave {
                delete(cells.linktabs, agent)
            } else {
                for _, ss := range cells.linktabs {
                    for i, ele := range ss {
                        if ele == agent {
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
            return errors.New("agent " + agent + " logout failed")
        }
    }

    return errors.New("agent " + agent + " not found")
}

// wait to exit
func (cells *Cells) Wait() {
    fmt.Printf("[%s] wait to serve...\n", cells.name)
    cells.wg.Wait()
    fmt.Printf("[%s] exit success\n", cells.name)
}

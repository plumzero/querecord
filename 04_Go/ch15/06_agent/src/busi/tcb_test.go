
package busi

import (
    "testing"
    "time"
    "fmt"

    "faci"
)

func TestTcb(t * testing.T) {

    // one send, another one recv
    // test result: as expected
    {
        cells := faci.NewCells("Duelist", WasteProcessorCallBack, nil)

        var junker_name string = "Junk"
        var rubbisher_name string = "Rubbish"

        junker := faci.NewAgent(junker_name, 1000)
        rubbisher := faci.NewAgent(rubbisher_name, 1000)
        
        junker.Run(cells, AgentJunkSendCallBack, nil, []string{rubbisher_name}, nil)
        rubbisher.Run(cells, nil, AgentRubbishRecvCallBack, []string{}, nil)

        time.Sleep(3 * time.Second)

        junker.Stop(cells)
        rubbisher.Stop(cells)
        
        cells.Wait()

        fmt.Println("===== test ok: one send, another one recv =====")
    }

    // one send, more recv(not include self)
    // test result: as expected
    {
        cells := faci.NewCells("Duelist", WasteProcessorCallBack, nil)

        var junker_name string = "Junk"
        var rubbisher_name string = "Rubbish"
        var trasher_name string = "Trash"

        junker := faci.NewAgent(junker_name, 1000)
        rubbisher := faci.NewAgent(rubbisher_name, 1000)
        trasher := faci.NewAgent(trasher_name, 1000)
        
        junker.Run(cells, AgentJunkSendCallBack, nil, []string{rubbisher_name, trasher_name}, nil)
        rubbisher.Run(cells, nil, AgentRubbishRecvCallBack, []string{}, nil)
        trasher.Run(cells, nil, AgentTrashRecvCallBack, []string{}, nil)

        time.Sleep(3 * time.Second)

        junker.Stop(cells)
        rubbisher.Stop(cells)
        trasher.Stop(cells)
        
        cells.Wait()

        fmt.Println("===== test ok: one send, more recv(not include self) =====")
    }

    // more send, one recv(not include self)
    // test result: as expected
    {
        cells := faci.NewCells("Duelist", WasteProcessorCallBack, nil)

        var junker_name string = "Junk"
        var rubbisher_name string = "Rubbish"
        var trasher_name string = "Trash"

        junker := faci.NewAgent(junker_name, 1000)
        rubbisher := faci.NewAgent(rubbisher_name, 1000)
        trasher := faci.NewAgent(trasher_name, 1000)
        
        junker.Run(cells, AgentJunkSendCallBack, nil, []string{trasher_name}, nil)
        rubbisher.Run(cells, AgentRubbishSendCallBack, nil, []string{trasher_name}, nil)
        trasher.Run(cells, nil, AgentTrashRecvCallBack, []string{}, nil)

        time.Sleep(3 * time.Second)

        junker.Stop(cells)
        rubbisher.Stop(cells)
        trasher.Stop(cells)
        
        cells.Wait()

        fmt.Println("===== test ok: more send, one recv(not include self) =====")
    }

    // self send, self recv
    // test result: unexpected
    {
        // cells := faci.NewCells("Duelist", WasteProcessorCallBack, nil)

        // var junker_name string = "Junk"

        // junker := faci.NewAgent(junker_name, 1000)
        
        // junker.Run(cells, AgentJunkSendCallBack, AgentJunkRecvCallBack, []string{junker_name}, nil)

        // time.Sleep(2 * time.Second)

        // junker.Stop(cells)
        
        // cells.Wait()

        // fmt.Println("===== test ok: self send, self recv =====")
    }

    // one send, more recv(include self)
    // test result: untest, highly possible unexpected
    {

    }

    // more send, one recv(not include self)
    // test result: untest, highly possible unexpected
    {

    }
}
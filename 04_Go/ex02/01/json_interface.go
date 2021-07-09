
package main

import (
	"encoding/json"
	"io/ioutil"
	"strings"
	"fmt"
)

type MapSI = map[string]interface{}

func main() {
	content, err := ioutil.ReadFile("test.json")
	if err != nil {
		panic(err)
	}

	var conf map[string]interface{}
	dec := json.NewDecoder(strings.NewReader(string(content)))
	if err = dec.Decode(&conf); err != nil {
		panic(err)
	}

	// [log]
	log_path := conf["log"].(MapSI)["path"].(string)
	log_mode := conf["log"].(MapSI)["mode"].(string)
	fmt.Printf("log.path=%s,log.mode=%s\n", log_path, log_mode)
	
	// [cells]
	cells_name := conf["cells"].(MapSI)["name"].(string)
	fmt.Printf("cells.name=%s\n", cells_name)

	// [httpAlarm]
	httpAlarm_ip := conf["httpAlarm"].(MapSI)["ip"].(string)
	httpAlarm_path := conf["httpAlarm"].(MapSI)["path"].(string)
	fmt.Printf("httpAlarm.ip=%s,httpAlarm.path=%s\n", httpAlarm_ip, httpAlarm_path)

	// [grpc-LimitedPriceData]
	grpcLimitedPriceData := conf["grpc-LimitedPriceData"].([]interface{})
	for _, v := range grpcLimitedPriceData {
		// v_name := v["name"].(string)
		v_name := v.(MapSI)["name"].(string)
		v_addr := v.(MapSI)["addr"].(string)
		v_receivers := v.(MapSI)["receivers"].([]interface{})
		var recvlist []string
		for _, e := range v_receivers {
			recvlist = append(recvlist, e.(string))
		}
		v_weight := v.(MapSI)["weight"].(float64)
		fmt.Printf("name=%s,addr=%s,recvlist=%v,receivers=%f\n", v_name, v_addr, recvlist, v_weight)
	}

	// [redis-LimitedPriceData]
	redisLimitedPriceData := conf["redis-LimitedPriceData"].([]interface{})
	for _, v := range redisLimitedPriceData {
		v_name := v.(MapSI)["name"].(string)
		v_addr := v.(MapSI)["addr"].(string)
		v_password := v.(MapSI)["password"].(string)
		fmt.Printf("name=%s,addr=%s,password=%s\n", v_name, v_addr, v_password)
	}
}
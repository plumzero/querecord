
package main
import "fmt"

type PersonInfo struct {
	ID string
	Name string
	Address string
}

func main() {

	// 声明 初始化 遍历
	{
		var personDB map[string] PersonInfo

		personDB = map[string] PersonInfo {
			"1" : PersonInfo {"1", "Jack",   "Room 101,..."},
			"2" : PersonInfo {"2", "Lily",   "Room 201,..."},
			"3" : PersonInfo {"3", "Lucy",   "Room 202,..."},
			"4" : PersonInfo {"4", "Tom",    "Room 102,..."},
			"5" : PersonInfo {"5", "Jerry",  "Room 103,..."},
		}
		
		fmt.Println("lenOfMap=", len(personDB))
		for k,v := range personDB {
			fmt.Println(k, v)
		}

		fmt.Println()
	}

	// make创建 赋值/更新 删除 查找
	{
		personDB := make(map[string] PersonInfo, 4)

		personDB["1"] = PersonInfo{"1", "Jack",  "Room 101,..."}
		personDB["2"] = PersonInfo{"2", "Lily",  "Room 201,..."}
		personDB["3"] = PersonInfo{"3", "Lucy",  "Room 202,..."}
		personDB["4"] = PersonInfo{"4", "Tom",   "Room 102,..."}
		personDB["5"] = PersonInfo{"5", "Jerry", "Room 103,..."}

		personDB["4"] = PersonInfo{"4", "Jim",   "Room 102,..."}

		v, ok := personDB["2"]
		if ok {
			delete(personDB, "2")
		}

		fmt.Println("------------------>", v)

		fmt.Println("lenOfMap=", len(personDB))
		for k,v := range personDB {
			fmt.Println(k, v)
		}
	}
}
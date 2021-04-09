
package main

import (
	"fmt"
)

type MonsterCard struct {
	name   string
	race   string
	atk	   int
	def    int
}

type MagicCard struct {
	name   string
	kind   string
}

type TrapCard struct {
	name   string
	kind   string
}

// 从 interface{} 到具体类型转换时需要经过 type assertions 和 type switches
func handle_all(args ...interface{}) {
	for _, value := range args {
		switch value.(type) {
			case MonsterCard:
				if monster, ok := value.(MonsterCard); ok {
					fmt.Println("All Monster:", monster.name, monster.race, monster.atk, monster.def)
				}
			case MagicCard:
				if magic, ok := value.(MagicCard); ok {
					fmt.Println("All Magic:", magic.name, magic.kind)
				}
			case TrapCard:
				if trap, ok := value.(TrapCard); ok {
					fmt.Println("All Trap:", trap.name, trap.kind)
				}
			default:
				fmt.Println("All Unknown Type:", value)
		}
	}
}

func handle_monster(arg interface{}) {
	if monster, ok := arg.(MonsterCard); ok {
		fmt.Println("Monster:", monster.name, monster.race, monster.atk, monster.def)
	}
}

func handle_magic(arg interface{}) {
	if magic, ok := arg.(MagicCard); ok {
		fmt.Println("Magic:", magic.name, magic.kind)
	}
}

func handle_trap(arg interface{}) {
	if trap, ok := arg.(TrapCard); ok {
		fmt.Println("Trap:", trap.name, trap.kind)
	}
}


func deal_callback(f func(...interface{}), mc MonsterCard) {
	f(mc)
}

func main() {

	monster := MonsterCard{ "Madolche Queen Tiaramisu", "angel", 2200, 2100 }
	magic := MagicCard{ "Madolche Chateau",  "field" }
	trap := TrapCard{ "Madolche Lesson", "once" }

	// 可变参数
	{
		var cbargs map[string]func(...interface{})
		cbargs = make(map[string]func(...interface{}), 256)
	
		cbargs["All"] = handle_all
		cbargs["All"](monster, magic, trap)
	}

	// 一个参数
	{
		var cbarg map[string]func(args interface{})
		cbarg = make(map[string]func(args interface{}), 256)
	
		cbarg["Monster"] = handle_monster
		cbarg["Monster"](monster)

		cbarg["Magic"] = handle_magic
		cbarg["Magic"](magic)

		cbarg["Trap"] = handle_trap
		cbarg["Trap"](trap)
	}

	// 回调传入
	{
		fmt.Println()
		deal_callback(handle_all, monster)
	}
}
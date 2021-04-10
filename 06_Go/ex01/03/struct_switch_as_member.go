
package main

import (
	"fmt"
	"unsafe"
)

type E_TYPE string

const (
	WORKER    E_TYPE = "worker"
	FARMER           = "farmer"
	TEACHER          = "teacher"
	SCIENTIST        = "scientist"
	WAITER           = "waiter"
)

type Employee struct {
	baseWage float64
	eType    E_TYPE
}

type Worker struct {
	Employee
}

type Farmer struct {
	Employee
}

type Teacher struct {
	Employee
	classRemuneration float64
}

type Scientist struct {
	Employee
	yearEndBonus float64
}

type Waiter struct {
	Employee
}

func (e * Employee) getYearBaseSalary() float64 {
	return 12 * e.baseWage
}

func (e * Employee) PrintSalary() {
	fmt.Printf("%s's year salary: ", e.eType)
	switch e.eType {
	case WORKER:
		fallthrough
	case FARMER:
		fallthrough
	case WAITER:
		fmt.Printf("%.2f\n", e.getYearBaseSalary())
	case TEACHER:
		up := unsafe.Pointer(e)		// 父类指针转为通用指针
		rp := (*Teacher)(up)		// 通用指针转为子类指针
		fmt.Printf("total: %.2f (among classRemuneration=%.2f)\n", e.getYearBaseSalary() + rp.classRemuneration, rp.classRemuneration)
	case SCIENTIST:
		up := unsafe.Pointer(e)
		rp := (*Scientist)(up)
		fmt.Printf("total: %.2f (among yearEndBonus=%.2f)\n", e.getYearBaseSalary() + rp.yearEndBonus, rp.yearEndBonus)
	}
}

func main() {
	var worker *Worker = &Worker{Employee: Employee{baseWage: 120, eType: WORKER}}
	var farmer *Farmer = &Farmer{Employee: Employee{baseWage: 150, eType: FARMER}}
	var teacher *Teacher = &Teacher{Employee: Employee{baseWage: 250, eType: TEACHER}, classRemuneration: 500}
	var scientist *Scientist = &Scientist{Employee: Employee{baseWage: 350, eType: SCIENTIST}, yearEndBonus: 1000}
	var waiter *Waiter = &Waiter{Employee: Employee{baseWage: 150, eType: WAITER}}

	worker.PrintSalary()
	farmer.PrintSalary()
	teacher.PrintSalary()
	scientist.PrintSalary()
	waiter.PrintSalary()
}


package main

import "fmt"

func main() {
	// for
	{
		sum := 0
		
		for i := 0; i < 10; i++ {
			sum += i
		}

		fmt.Println("sum =", sum)
	}

	// 多重赋值
	{
		a := []int{ 1, 2, 3, 4, 5, 6 }

		for i, j := 0, len(a) - 1; i < j; i, j = i + 1, j - 1 {
			a[i], a[j] = a[j], a[i]
		}

		fmt.Println(a)
	}

	// break 
	{
		for j := 0; j < 5; j++ {
			for i := 0; i < 10; i++ {
				if i > 5 {
					break
				}
				fmt.Printf("%d ", i)
			}
		}
		fmt.Println()
	}
}
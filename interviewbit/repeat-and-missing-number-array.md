```c
package main

import (
	"fmt"
)

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func max(x, y int) int {
	if x > y {
		return x
	}
	return y
}

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}

func repeatedNumber(A []int) []int {
	sum := 0
	shouldBeSum := (len(A) * (len(A) + 1)) / 2
	repeatingNumber := 0

	for i := range A {
		sum += abs(A[i])
		index := abs(A[i]) - 1
		if A[index] > 0 {
			A[index] = -A[index]
		} else {
			repeatingNumber = index + 1
		}
	}

	missingNumber := shouldBeSum - (sum - repeatingNumber)

	return []int{repeatingNumber, missingNumber}
}

func main() {
	fmt.Println(repeatedNumber([]int{3, 1, 2, 5, 3}))
}
```

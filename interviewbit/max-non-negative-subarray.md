```c
package main

import (
	"fmt"
	"math"
)

func max(x, y int) int {
	if x > y {
		return x
	}
	return y
}

func maxset(A []int) []int {
	var i int
	for i = 0; i < len(A); i++ {
		if A[i] >= 0 {
			break
		}
	}

	if i == len(A) {
		return []int{}
	}

	maxStart, maxEnd, maxSum := i, i, math.MinInt32
	start, end, sum := i, i, 0

	for i = i; i < len(A); i++ {
		if A[i] >= 0 {
			end = i
			sum += A[i]
		} else {
			if (sum > maxSum) || (sum == maxSum && (end-start) > (maxEnd-maxStart)) {
				maxStart, maxEnd, maxSum = start, end, sum
			}
			start, sum = i+1, 0
		}
	}

	if (sum > maxSum) || (sum == maxSum && (end-start) > (maxEnd-maxStart)) {
		maxStart, maxEnd, maxSum = start, end, sum
	}
	return A[maxStart : maxEnd+1]
}

func main() {
	fmt.Println(maxset([]int{0, 0, -1, 0}))
}
```

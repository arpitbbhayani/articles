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

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}

func maxArr(A []int) int {
	maxVal1, maxVal2 := math.MinInt32, math.MinInt32
	minVal1, minVal2 := math.MaxInt32, math.MaxInt32
	for i := 0; i < len(A); i++ {
		maxVal1 = max(maxVal1, A[i]+i)
		minVal1 = min(minVal1, A[i]+i)
		maxVal2 = max(maxVal2, A[i]-i)
		minVal2 = min(minVal2, A[i]-i)
	}
	return max(maxVal1-minVal1, maxVal2-minVal2)
}

func main() {
	fmt.Println(maxArr([]int{1, 3, -1}))
}
```

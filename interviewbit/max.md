package main

import (
	"fmt"
)

func max(x, y int) int {
	if x > y {
		return x
	}
	return y
}

func maxSubArray(A []int) int {
	currentMax := A[0]
	globalMax := A[0]
	for i := 1; i < len(A); i++ {
		currentMax = max(A[i], currentMax+A[i])
		globalMax = max(globalMax, currentMax)
	}
	return globalMax
}

func main() {
	fmt.Println(maxSubArray([]int{-2, 1, -3, 4, -1, 2, 1, -5, 4}))
}

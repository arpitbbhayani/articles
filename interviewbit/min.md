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

func distance(x1, y1, x2, y2 int) int {
	return max(abs(x2-x1), abs(y2-y1))
}

func coverPoints(A []int, B []int) int {
	steps := 0
	for i := 1; i < len(A); i++ {
		x1, y1, x2, y2 := A[i-1], B[i-1], A[i], B[i]
		steps += distance(x1, y1, x2, y2)
	}
	return steps
}

func main() {
	fmt.Println(coverPoints([]int{4, 8, -7, -5, -13, 9, -7, 8},
	    []int{4, -15, -10, -3, -13, 12, 8, -8}))
}

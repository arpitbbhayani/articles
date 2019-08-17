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

func outOfBounds(i, j, n int) bool {
	return !(i >= 0 && i < n && j >= 0 && j < n)
}

func isCovered(i, j int, covered [][]bool) bool {
	if outOfBounds(i, j, len(covered)) {
		return true
	}
	return covered[i][j]
}

func generateMatrix(A int) [][]int {
	n := A
	matrix := make([][]int, n, n)
	for i := range matrix {
		matrix[i] = make([]int, n, n)
	}

	covered := make([][]bool, n, n)
	for i := range covered {
		covered[i] = make([]bool, n, n)
	}

	deltai := []int{0, 1, 0, -1}
	deltaj := []int{1, 0, -1, 0}

	x := 1
	i, j, k := 0, 0, 0
	ni, nj := 0, 0
	max := n*n + 2*n
	for y := 0; y < max; y++ {
		matrix[i][j] = x
		covered[i][j] = true
		ni = i + deltai[k]
		nj = j + deltaj[k]
		if isCovered(ni, nj, covered) {
			k = (k + 1) % 4
			x--
		} else {
			i, j = ni, nj
		}
		x++
	}

	return matrix
}

func main() {
	mat := generateMatrix(10)
	for i := range mat {
		for j := range mat[i] {
			fmt.Print(mat[i][j], " ")
		}
		fmt.Println()
	}
}
```

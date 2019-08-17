```
package main

import (
	"fmt"
)

func getRow(A int) []int {
	A++
	triangle := make([][]int, A, A)
	for i := range triangle {
		triangle[i] = make([]int, i+1, i+1)
	}

	triangle[0][0] = 1
	for i := 1; i < A; i++ {
		triangle[i][0] = 1
		for j := 1; j <= i; j++ {
			if j < i {
				triangle[i][j] = triangle[i-1][j] + triangle[i-1][j-1]
			} else {
				triangle[i][j] = 0 + triangle[i-1][j-1]
			}
		}
	}

	return triangle[A-1]
}

func main() {
	fmt.Println(getRow(0))
}
```

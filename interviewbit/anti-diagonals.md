```
package main

import (
	"fmt"
)

func diagonal(A [][]int) [][]int {
	if len(A) == 0 {
		return [][]int{}
	}

	var index int = 0

	ads := make([][]int, 2*len(A)-1, 2*len(A)-1)
	for i := 0; i < len(ads); i++ {
		ads[i] = make([]int, 0, len(A))
	}

	for column := 0; column < len(A); column++ {
		i, j := 0, column
		for j >= 0 && i < len(A) {
			ads[index] = append(ads[index], A[i][j])
			i++
			j--
		}
		index++
	}

	for row := 1; row < len(A); row++ {
		i, j := row, len(A)-1
		for j >= 0 && i < len(A) {
			ads[index] = append(ads[index], A[i][j])
			i++
			j--
		}
		index++
	}

	return ads
}

func main() {
	A := [][]int{}
	fmt.Println(diagonal(A))
}
```

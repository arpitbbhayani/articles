```
package main

import (
	"fmt"
)

func plusOne(A []int) []int {
	carry := 1
	for i := len(A) - 1; i >= 0; i-- {
		A[i] = A[i] + carry
		carry = A[i] / 10
		A[i] = A[i] % 10
	}

	var Ap1 []int
	if carry > 0 {
		Ap1 = append([]int{carry}, A...)
	} else {
		Ap1 = A
	}

	firstNonZero := 0
	for firstNonZero = range Ap1 {
		if Ap1[firstNonZero] != 0 {
			break
		}
	}
	return Ap1[firstNonZero:]
}

func main() {
	fmt.Println(plusOne([]int{0, 0, 9}))
}
```

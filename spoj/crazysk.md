```
def func(x,n):
	an = x
	a0 = n
	d = n - 1
	return (an-a0)/d + 1

import sys
input_data = sys.stdin.readlines()
i = 1
t = int(input_data[0])
while i <= t:
	x,n = map(int,input_data[i].split())
	items = x
	items += func(x,n)
	print items
	i += 1
```

```c
####
#	For python3
####

def gcd( a , b ):
	if b == 0:
		return a
	else:
		return gcd ( b , a % b )

t = int(input())

while t != 0:

	s = input()

	a , b = ( int(x) for x in s.split() )

	c = gcd(a,b)
	print(c)

	t = t - 1
```

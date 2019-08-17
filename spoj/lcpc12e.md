```c
from math import sqrt

# Using Cosine rule for triangles
# http://www.sparknotes.com/testprep/books/sat2/math2c/chapter9section9.rhtml

def main():
	t = input()
	i = 0
	while i < t:
		i += 1
		x1,y1,x2,y2,ac,l = map(float,raw_input().split())

		#Distance between the two centres
		ab = sqrt(pow(x1-x2,2)+pow(y1-y2,2))

		# Radius of the cricle by jhonny's empire
		bc = l/sqrt(2)
	
		cosa = (pow(ab,2)+pow(ac,2)-pow(bc,2))/(2*ab*ac)
		if cosa <= 1:
			ans = 2*ac*sqrt(1-pow(cosa,2))
			print "%d. %.3f" % (i,ans)
		else:
			print "%d. No problem" % (i)

if __name__ == '__main__':
	main()
```

```c
/*
	http://www.gogeometry.com/problem/p103_equilateral_triangle_heron_area_elearning.htm
*/
#include <stdio.h>
#include <math.h>

#define ROOT_3 1.7320508075688772935274463

int main ( int argc , char * argv[] ) {

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		double d,e,f,s;

		scanf("%lf%lf%lf" , &d,&e,&f);

		double area = (ROOT_3 * (d*d + e*e + f*f))/8;
		s = (d + e + f)/2;
		area += ( 1.5 * sqrt(s*(s-d)*(s-e)*(s-f))  );

		printf("%0.2lf\n" , area);
	}

	return 0;
}
```

```c
#include <stdio.h>
#define PI 3.141592653589793238462643383279
int main ( int argc , char * argv[] ) {

	int l;
	scanf("%d" , &l);

	while ( l != 0 ) {

		printf("%.2llf\n" , ( PI * (long double)(l/PI) * (long double)(l/PI) ) / 2 );

		scanf("%d" , &l);
	}

	return 0;
}
```

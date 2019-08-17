```c
#include <stdio.h>

int main ( int argc , char * argv[] ) {

	long long int t;
	scanf("%lld" , &t);

	while ( t-- ) {

		long long int a3 , al3 , sum;
		scanf("%lld%lld%lld" , &a3 , &al3 , &sum );

		long long int n = ( 2 * sum ) / ( a3 + al3 ) ;
		printf("%lld\n" , n);

		long long int d = (al3 - a3)/(n-5);
		long long int a1 = a3 - 2 * d;
		int i;
		printf("%lld " , a1);
		for ( i = 1 ; i < n ; i++ ) {
			a1 += d;
			printf("%lld " , a1);
		}
		printf("\n");

	}

	return 0;
}
```

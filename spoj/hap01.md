```c
#include <stdio.h>
#define DEBUG 0

int ab( long long int n ) {

	#if DEBUG
	printf("For n = %lld " , n);
	#endif
	int co = 0 , ce = 0;
	int *a = &co;
	int odd = 1;
	while ( n != 0 ) {
		if ( n & 1 ) {
			if ( odd ) {
				co ++;
			}
			else {
				ce ++;
			}
		}
		odd = 1 - odd;
		n = n >> 1;
	}

	#if DEBUG
	printf(" co = %d and ce = %d\n" , co , ce);
	#endif
	return co - ce;

}

int main ( int argc , char * argv[] ) {
	int t;
	scanf("%d" , &t);
	while ( t-- ) {
		long long int m,n,k;
		scanf("%lld%lld%lld",&m,&n,&k);
		long long int i = 0;

		int count = 0;
		for ( i = m ; i <= n ; i++ ) {
			long long int d = ab(i);
			if ( d == k || d == -k ) {
				count ++;
			}
		}
		printf("%d\n" , count);

	}

	return 0;
}
```

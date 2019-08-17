```c
#include <stdio.h>
#include <stdlib.h>

int comparator(const void *a, const void *b) {
	return (*(long long int *)a) - (*(long long int *)b);
}

int main ( int argc , char * argv[] ) {

	long long int t;
	char str[10000];

	scanf("%lld" , &t);

	while ( t-- ) {
		long long int n , i;
		scanf("%lld" , &n);

		long long int * array = ( long long int * ) malloc ( n * sizeof( long long int ) );

		for ( i = 0 ; i < n ; i++ ) {
			scanf("%s %lld" , str , &array[i]);
		}

		qsort( array , n , sizeof(long long int) , comparator );

		long long int sum = 0;

		for ( i = 0 ; i < n ; i++ ) {
			sum += abs((i+1)-array[i]);
		}

		printf("%lld\n" , sum);

	}

	return 0;
}
```

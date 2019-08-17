```
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

/**
	Arrangements ( Permutation )
	An = n!
	   = (n-1) [ An-1 + An-2 ]
	with A1 = 1 and A2 = 2

	Derangements
	Dn = (n-1) [ Dn-1 + Dn-2 ]
	with D1 = 0 and D1 = 1
*/

#define MOD 1000000007
#define SIZE 1000010
long long int array[SIZE];

int main ( int argc , char * argv[] ) {

	int i = 0;
	array[0] = 0;
	array[1] = 0;
	array[2] = 1;
	for ( i = 3 ; i < SIZE ; i++ ) {
		array[i] = ((i-1) * (array[i-1] + array[i-2])) % MOD;
	}

	int t;
	scanf("%d" , &t);
	while ( t-- ) {
		int x;
		scanf("%d" , &x);
		printf("%lld\n" , array[x]);
	}

	return 0;
}
```

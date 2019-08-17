```c
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000001
long long int pf[SIZE];
void populate_pf() {
	int i;
	for ( i = 2 ; i < SIZE ; i++ ) {
		if ( pf[i] != 0 )
			continue;
		int limit = SIZE/i;
		int j;
		for ( j = i ; j < SIZE ; j+=i ) {
			if ( pf[j] == 0 )
				pf[j] = i;
		}
	}

	//for ( i = 0 ; i < SIZE ; i++ ) {
	//	printf("%d " , pf[i]);
	//}
	//printf("\n");
}

void calculate() {
	int i = 0;
	for ( i = 3 ; i < SIZE ; i++ ) {
		pf[i] += pf[i-1];
	}
	//for ( i = 0 ; i < SIZE ; i++ ) {
	//	printf("%d " , pf[i]);
	//}
	//printf("\n");
}

int main ( int argc , char * argv[] ) {

	populate_pf();
	calculate();

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		int n;
		scanf("%d" , &n);
		printf("%lld\n" , pf[n]);
	}

	return 0;
}
```

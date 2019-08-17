```
#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
#define DEBUG 0

int compar ( const void * a , const void * b ) {
	return (*(long long int *)b) - (*(long long int *)a);
}

int main ( int argc ,char * argv[] ) {

	long long int t;

	scanf("%lld" , &t);
	while ( t-- ) {
		long long int m , n;
		scanf("%lld%lld" , &m , &n);

		long long int * am = (long long int *) malloc ( (m-1) * sizeof(long long int) );
		long long int * an = (long long int *) malloc ( (n-1) * sizeof(long long int) );

		long long int i = 0;
		for ( i = 0 ; i < m-1 ; i++ ) {
			scanf("%lld" , &am[i]);
		}
		for ( i = 0 ; i < n-1 ; i++ ) {
			scanf("%lld" , &an[i]);
		}
		
		qsort(am,m-1,sizeof(long long int),compar);
		qsort(an,n-1,sizeof(long long int),compar);

		long long int im = 0 , in = 0;
		long long int xc = 0 , yc = 0;
		long long int cost = 0;

		while ( im != m-1 && in != n-1 ) {

			long long int a = am[im];
			long long int b = an[in];

			if ( a > b ) {
				// Cut is made horizontal

				#if DEBUG
					printf("Cutting Horizontally :\n");
					printf("cost += %d\n" , (yc+1)*a );
				#endif

				xc ++; im ++;
				cost = (cost + ( (yc+1) * a)) % MOD;
			}
			else {
				// Cut is made vertical

				#if DEBUG
					printf("Cutting Vertically :\n");
					printf("cost += %d\n" , (xc+1)*b );
				#endif

				yc ++; in ++;
				cost = (cost + ( (xc+1) * b)) % MOD;
			}
		}

		while ( im != m-1 ) {
			long long int a = am[im];

			#if DEBUG
				printf("Cutting Horizontally :\n");
				printf("cost += %d\n" , (yc+1)*a );
			#endif

			xc ++; im ++;
			cost = (cost + ( (yc+1) * a)) % MOD;
		}
		
		while ( in != n-1 ) {
			long long int b = an[in];

			#if DEBUG
				printf("Cutting Vertically :\n");
				printf("cost += %d\n" , (xc+1)*b );
			#endif

			yc ++; in ++;
			cost = (cost + ( (xc+1) * b)) % MOD;
		}

		printf("%lld\n" , cost);

	}

	return 0;
}
```

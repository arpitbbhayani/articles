#include <stdio.h>
#include <stdlib.h>

int compar ( const void * a , const void * b ) {
	return (*(int *)a) - (*(int *)b);
}

int main ( int argc ,char * argv[] ) {

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		int n;
		scanf("%d" , &n);

		int i = 0;
		int * array = ( int *) malloc ( n * sizeof(int) );

		for ( i = 0 ; i < n ; i++ ) {
			scanf("%d" , &array[i]);
		}

		qsort(array , n , sizeof(int) , compar);

		if ( array[n-1] < n ) {
			printf("0\n");
			continue;
		}

		long long int s = 1;
		for ( i = 0 ; i < n ; i++ ) {
			s = s * (array[i] - i);
			s = s % 1000000007;
		}

		printf("%lld\n" , s);

	}
	printf("KILL BATMAN\n");

	return 0;
}

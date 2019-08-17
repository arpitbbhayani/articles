#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000010
#define DEBUG 0

int min ( int a , int b ) {
	return a <= b ? a : b;
}

int main ( int argc ,char * argv[]) {

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		int n;
		scanf("%d" , &n);

		int array[SIZE];
		int i = 0;

		for ( i = 0 ; i < SIZE ; i++ ) {
			array[i] = 0;
		}

		for ( i = 0 ; i < n ; i++ ) {
			int a;
			scanf("%d" , &a);
			array[a] ++;
		}

		#if DEBUG
		for ( i = 0 ; i < SIZE ; i++ ) {
			printf("%d " , array[i]);
		}
		printf("\n");
		#endif

		int count = 0;
		int limit = SIZE/2;
		for ( i = 0 ; i <= limit ; i++ ) {
		#if DEBUG
			printf("Checking i = %d , %d and %d\n" , i , array[i] , array[2*i]);
		#endif
			if ( array[i] != 0 ) {
				int m = min(array[i] , array[2*i]);
		#if DEBUG
				printf("min = %d\n" , m);
		#endif
				array[i] -= m;
				array[2*i] -= m;
				count += m;
			}
		}

		printf("%d\n" , count);

	}

	return 0;
}

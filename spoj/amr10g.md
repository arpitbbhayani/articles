#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compar(const void *a, const void *b) {
	return *(int *)a - *(int*)b;
}

int main ( int argc , char * argv[] ) {

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		int n , k , i;
		scanf("%d%d" , &n,&k);

		int * array = (int * ) malloc ( n * sizeof(int) );
		for ( i = 0 ; i < n ; i++ ) {
			scanf("%d" , &array[i]);
		}

		qsort( array , n , sizeof(int) , compar);

		int min = INT_MAX;
		for ( i = 0 ; i < n-k+1 ; i++ ) {
			//printf("%d - %d\n" , array[i] , array[i+k-1]);
			if ( array[i+k-1] - array[i] < min ) {
				min = array[i+k-1] - array[i];
			}
		}

		printf("%d\n" , min);

		free(array);
	}	

	return 0;
}

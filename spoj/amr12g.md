#include <stdio.h>
#include <stdlib.h>

int compar(const void *a, const void *b) {
        return *(int *)a - *(int*)b;
}

int readline( int m ) {

	char str[1024];
	char ch;
	int count = 0 , i = 0;

	scanf("%s" , str);

	for ( i = 0 ; i < m ; i++ ) {
//		printf("ch = %c\n" , ch);
		if ( str[i] == '*' )
			count ++;
	}

	return count;
}

int main ( int argc , char * argv[] ) {

	int t;
	scanf("%d" , &t);
	getchar();

	while ( t-- ) {
		int n , m , i , k;
		scanf("%d%d%d" , &n,&m,&k);
		int * array = (int *) malloc ( n * sizeof(int) );

		//printf("n = %d and m = %d and k = %d\n" , n , m , k);
		for ( i = 0 ; i < n ; i++ ) {
			//printf("Reading line : \n");
			array[i] = readline(m);
		}

		//printf("Before:\n");
		//for ( i = 0 ; i < n ; i++ ) {
		//	printf("%d " , array[i]);
		//}
		//printf("\n");
		for ( i = 0 ; i < k ; i++ ) {
			qsort(array , n , sizeof(int) , compar);
			array[0] = m - array[0];
		}

		//printf("After:\n");
		//for ( i = 0 ; i < n ; i++ ) {
		//	printf("%d " , array[i]);
		//}
		//printf("\n");

		for ( i = 1 ; i < n ; i++ ) {
			array[0] += array[i];
		}

		printf("%d\n" , array[0]);

	}

	return 0;
}

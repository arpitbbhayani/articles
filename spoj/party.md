#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int max ( int a , int b ) {
	return a > b ? a : b;
}

int main ( int argc , char * argv[] ) {


	while ( 1 ) {

	int budget , n , i , j;
	scanf("%d%d" , &budget , &n);

	if ( budget == 0 && n == 0 )
		break;

	int **array = (int **) calloc( sizeof(int *) , n+1 );
	for ( i = 0 ; i < n+1 ; i++ ) {
		array[i] = (int *) calloc ( sizeof(int) , budget+1 );
	}

	int * fun = (int *) malloc ( n * sizeof(int));
	int * fee = (int *) malloc ( n * sizeof(int));

	for ( i = 0 ; i < n ; i++ ) {
		scanf("%d%d" , &fee[i] , &fun[i]);
	}

	#if DEBUG
		printf("Budget:%d\n" , budget);
		printf("Number of parties:%d\n" , n);
		for ( i = 0 ; i < n ; i++ ) {
			printf("Party %d: Fee -> %d and fun -> %d\n" , i , fee[i] , fun[i]);
		}
	#endif

	for ( i = 1 ; i < n+1 ; i++ ) {
		for ( j = 1 ; j < budget+1 ; j++ ) {
			if ( fee[i-1] <= j ) {
				//array[i][j] = max ( array[i-1][j] , array[i-1][j-fee[i-1]] + fun[i-1] );

				int tn = array[i-1][j];
				int ts = array[i-1][j-fee[i-1]] + fun[i-1];
				if ( tn > ts ) {
					array[i][j] = tn;
				}
				else {
					array[i][j] = ts;
				}
			}
			else
				array[i][j] = array[i-1][j];
		}

	}

	#if DEBUG
		printf("Matrix:\n");
		for ( i = 0 ; i < n+1 ; i++ ) {
			for ( j = 0 ; j < budget+1 ; j++ ) {
				printf("%d " , array[i][j]);
			}
			printf("\n");
		}
	#endif

	i = budget;
	while ( array[n][i-1] == array[n][i] ) {
		i--;
	}

	printf("%d %d\n" , i , array[n][budget] );

	for ( i = 0 ; i < n+1 ; i++ ) {
		free(array[i]);
	}
	free(array);
	free(fee);
	free(fun);

	}

	return 0;
}

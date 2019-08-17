```c
#include <stdio.h>
#include <stdlib.h>

#define swap(array,i,j) int t; t=array[i];array[i]=array[j];array[j]=t;

void print_array ( long long int * array , long long int start , long long int end ) {

	long long int i = 0;
	printf("Array to count_inv : ");
	for ( i = start ; i <= end ; i++ ) {
		printf("%lld " , array[i]);
	}
	printf("\n");

}

long long int merge ( long long int * array , long long int l , long long int m , long long int h ) {

	//print_array ( array , l , h );
	//printf("h-l+3 = %d\n" , h-l+1);
	//int * b_array = (int *) malloc ( (h-l+1) * sizeof(int) );
	long long int b_array[200010];
	long long int i = 0 , j = 0 , k = 0;
	long long int count = 0;

	i = k = l;
	j = m+1;
	//printf("merging\n");
	while ( i <= m && j <= h ) {
		//printf("comparing array[i] = %d and array[j] = %d\n" , array[i] , array[j]);
		if ( array[i] <= array[j] ) {
			b_array[k++] = array[i++];
		}
		else {

			count += ( m - i + 1 );
			//printf("inversion exist so count++ = %d\n" , count);
			b_array[k++] = array[j++];
		}

	}
	if ( i > m ) {
		while ( j <= h ) {
			b_array[k++] = array[j++];
		}
	}
	else if ( j > h ) {
		while ( i <= m ) {
			b_array[k++] = array[i++];
		}
	}

	k = l;
//
	while ( k <= h ) {
		array[k] = b_array[k];
		k++;
	}
	//printf(" Array after merging :\n ");
	//print_array ( array , l , h);
	//printf("FREEEE RETURNING\n");
	//free(b_array);
	//printf("RETURNING\n");
	return count;
}

long long int count_inv ( long long int * array , long long int start , long long int end ) {

	//print_array ( array , start , end );

	if ( start >= end ) return 0;

	//printf("end - start > 1 ... so\n");

	long long int mid = (start + end ) / 2;
	//print_array ( array , start , mid );

	long long int count_l = count_inv ( array , start , mid );
	//printf("count_inv of left_array = %d\n" , count_l);
	//print_array ( array , mid+1 , end );

	long long int count_r = count_inv ( array , mid+1 , end );
	//printf("count_inv of right_array = %d\n" , count_r);

	long long int count_m = merge ( array , start , mid , end );
	//printf("count_inv of merge = %d\n" , count_m);

	return count_l + count_r + count_m;
}

int main ( int argc , char * argv[] ) {

	long long int n , i , t;
	long long int *array;

	scanf("%lld" , &t);

	while ( t-- ) {

		scanf("%lld" , &n);

		array = (long long int *) malloc ( n * sizeof(long long int) );

		for ( i = 0 ; i < n ; i++ ) {
			scanf("%lld" , &array[i]);
		}
		
		printf("%lld\n" , count_inv( array , 0 , n-1 ) );

		free(array);

	}

	return 0;
}
```

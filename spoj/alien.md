```c
#include <stdio.h>
#include <stdlib.h>

int main ( int argc , char * argv[] ) {

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		int n,b,i;
		scanf("%d%d" , &n , &b);
		int * array = (int *) malloc ( n*sizeof(int) );
		for ( i = 0 ; i < n ; i++ ) {
			scanf("%d" , &array[i]);
		}

		long long int sum = 0;
		long long int max_sum = 0;
		int size = 0;
		int max_size = 0;
		int x = 0;

		for ( i = 0 ; i < n ; i++ ) {

			if ( sum + array[i] <= b ) {
				sum += array[i];
				size += 1;
			}
			else {
				while ( sum + array[i] > b ) {
					sum -= array[x];
					size -= 1;
					x++;
				}
				sum += array[i];
				size += 1;

			}
			if ( (size > max_size) || ( max_size == size && max_sum > sum ) ) {
				max_sum = sum;
				max_size = size;
			}
		}
		printf("%lld %d\n" , max_sum , max_size);
		free(array);
	}

	return 0;
}
```

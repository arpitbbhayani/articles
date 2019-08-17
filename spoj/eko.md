```
#include <stdio.h>
#include <stdlib.h>

int main ( int argc ,char * argv[] ) {

	int i = 0;
	int max = -1 , *array;
	int n , k;

	scanf("%d%d" , &n,&k);

	array = (int *) malloc ( n * sizeof(int) );

	for ( i = 0 ; i < n ; i++ ) {
		scanf("%d" , &array[i]);
		if ( array[i] > max )
			max = array[i];
	}

	long long int low = 0;
	long long int high = max;
	long long int count = 0 , mid;
	long long int h = 0;

	while ( low <= high ) {
		mid = (high+low)/2;
		count = 0;
		for ( i = 0 ; i < n ; i++ ) {
			long long int temp = array[i] - mid;
			count += (temp > 0 ? temp : 0);
		}

		if ( count == k ) {
			h = mid;
			break;
		}
		else if ( count < k ) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
			// to have the lower bound of the cutting
			// this will be the case when this is the last
			// of the loop and Cutting from one unit above will give
			// give me smaller value.
			if ( mid > h )
				h = mid;
		}

	}

		printf("%lld\n" , h);

	return 0;
}
```

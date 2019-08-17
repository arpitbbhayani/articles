```c
/*
http://www.codechef.com/problems/FCTRL2
*/

#include <stdio.h>
#include <stdlib.h>

int main ( int argc , char * argv[] ) {

	int t , n , i , size = 1 , carry;
	int s;
	int a[160];

	scanf("%d" , &t );

	while ( t-- ) {
		size = 1;
		scanf("%d" , &n );

		if ( n == 0 || n == 1 ) {
			printf("1\n");
			continue;
		}

		a[0] = a[1] = 1;
		
		carry = 0;
		for ( i = 2 ; i <= n ; i++ ) {

			int j = 0;
			for ( j = 0 ; j < size ; j++ ) {
				s = a[j] * i + carry;
				a[j] = s % 10;
				carry = s / 10;
			}

			while ( carry != 0 ) {
				a[size] = carry % 10;
				carry /= 10;
				size ++;
			}
		}

		for ( i = size - 1 ; i >= 0 ; i-- )
			printf("%d" , a[i] );
		printf("\n");


	}

	return 0;
}
```

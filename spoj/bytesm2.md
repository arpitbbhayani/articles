```
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int a[101][101];

int max2 ( int a , int b ) {
	return a > b ? a : b;
}

int max3( int  a , int b , int c ) {
	return max2(a,max2(b,c));
}

int main ( int argc , char * argv[] ) {

	int h , w , t;
	scanf("%d" , &t);

	while ( t-- ) {
		scanf("%d%d" , &h,&w);

		int i , j;
		for ( i = 0 ; i < h ; i++ ) {
			for ( j = 0 ; j < w ; j++ ) {
				scanf("%d" , &a[i][j]);
			}
		}

		for ( i = 1 ; i < h ; i++ ) {
			for ( j = 0 ; j < w ; j++ ) {
				if ( j+1 <= w-1 && j-1 >= 0 ) {
					a[i][j] = max3(a[i][j] + a[i-1][j] ,
						a[i][j] + a[i-1][j-1] , 
						a[i][j] + a[i-1][j+1]);
				}
				else if ( j - 1 < 0 ) {
					a[i][j] = max2(a[i][j] + a[i-1][j] ,
						a[i][j] + a[i-1][j+1]);
				}
				else {
					a[i][j] = max2(a[i][j] + a[i-1][j] ,
						a[i][j] + a[i-1][j-1]);
				}
			}
		}

		int max = 0;
		for ( i = 0 ; i < w ; i++ ) {
			if ( a[h-1][i] > max )
				max = a[h-1][i];
		}
		printf("%d\n" , max);
	}

	return 0;
}
```

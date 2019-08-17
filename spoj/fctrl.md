```
/*
http://www.codechef.com/problems/FCTRL
*/

#include <stdio.h>

int main ( int argc , char * argv[] ) {
	int t = 0 , n = 0 , i = 0 ;
	int count_5 = 0;
	scanf("%d" , &t );

	while ( t-- ) {
		scanf("%d" , &n);
		count_5 = 0;
		i = 5;
		while ( i <= n ) {
			count_5 += (n/i);
			i *= 5;
		}

		/*for ( i = 1 ; i <= n ; i++ ) {
			s = i;
			while ( s % 5 == 0 ) {
				count_5 ++;
				s /= 5;
			}
		}*/
		printf("%d\n" , count_5);
	}

	return 0;
}
```

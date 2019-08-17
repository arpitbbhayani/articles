```c
#include <stdio.h>

int main( int argc , char * argv[] ) {
	int n,i;

	scanf("%d" , &n);

	while ( n != 0 ) {
		int pow = 1;
		for ( i = 0 ; i <= n ; i++ ) {
			if ( pow > n ) {
				printf("%d\n" , i-1);
				break;
			}
			pow = pow * 2;
		}
		scanf("%d" , &n);
	}
	return 0;
}
```

```
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int main ( int argc , char * argv[] ) {

	int n;
	int array[31];

	array[0] = 1;
	array[1] = 0;
	array[2] = 3;
	array[3] = 0;

	int i = 0;
	for ( i = 4 ; i < 31 ; i++ ) {
		array[i] = array[i-2] * 4 - array[i-4];
	}

	while ( 1 ) {
		scanf("%d" , &n);

		if ( n == -1 )
			break;

		printf("%d\n" , array[n]);
	}

	return 0;
}
```

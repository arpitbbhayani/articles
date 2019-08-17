```
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int main ( int argc , char * argv[] ) {

	int n;
	int i = 0;
	int hash[300000];
	scanf("%d" , &n);

	for ( i = 0 ; i < 300000 ; i++ ) {
		hash[i] = 0;
	}

	int group = 0;
	int count = 0;
	for ( i = 0 ; i < n ; i++ ) {
		int x;
		scanf("%d" , &x);

		hash[x] = 1;

		// New group when no one is around him
		if ( x > 0 && x < 30000 && hash[x-1] == 0 && hash[x+1] == 0 ) {
			count ++;
		}
		// when person to the left is present
		else if ( x > 0 && x < 30000 && hash[x-1] == 1 && hash[x+1] == 0 ) {
			// no change to count
		}
		// when person to the right is present
		else if ( x > 0 && x < 30000 && hash[x-1] == 0 && hash[x+1] == 1 ) {
			// no change to count
		}
		else if ( x > 0 && x < 30000 && hash[x-1] == 1 && hash[x+1] == 1 ) {
			count --;
		}
		else if ( x == 0 && hash[x+1] == 1 ) {
			// No change to count
		}
		else if ( x == 0 && hash[x+1] == 0 ) {
			count ++;
		}
		else if ( x == 30000 && hash[x-1] == 1 ) {
			// No change to count
		}
		else if ( x == 30000 && hash[x-1] == 0 ) {
			count ++;
		}
		printf("%d\n" , count);
	}
	printf("Justice\n");
	return 0;
}
```

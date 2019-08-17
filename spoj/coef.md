```
#include <stdio.h>

int main ( int argc , char * argv[] ) {

	int n , k;
	int i;

	int fact[13];
	fact[0] = 1;
	fact[1] = 1;

	for ( i = 2 ; i < 13 ; i++ ) {
		fact[i] = i * fact[i-1];
	}

	while ( scanf("%d%d" , &n , &k) != EOF ) {
		int c = fact[n];
		int t;
		for ( i = 0 ; i < k ; i++ ) {
			scanf("%d" , &t);
			c /= fact[t];
		}
		printf("%d\n" , c);

	}


	return 0;
}
```

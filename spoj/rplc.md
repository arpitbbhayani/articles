```c
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int main ( int argc , char * argv[] ) {

	long long int t;
	scanf("%lld" , &t);
	int i , j;
	for ( i = 1 ; i <= t ; i++ ) {
		long long int n;
		long long int need = 1LL;
		long long int life = 1LL;
		scanf("%lld" , &n);

		for ( j = 0 ; j < n ; j++ ) {
			long long int x;
			scanf("%lld" , &x);

			life += x;
			if ( life <= 0LL ) {

				long long int temp = life;
				temp = temp * -1LL;
				temp = temp + 1LL;

				need += temp;
				life += temp;
			}
		}

		printf("Scenario #%d: %lld\n" , i , need);
	}

	return 0;
}
```

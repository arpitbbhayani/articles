#include <stdio.h>

int main( int argc , char * argv[] ) {

	int n , t;

	scanf("%d" , &t);

	while ( t-- ) {
		scanf("%d" , &n);
		int ans = 0;
		int i = 0;
		for ( i = 2 ; i <= n ; i++ ) {
			ans = (ans + n + 1 - i) % i;
		}
		printf("%d\n" , ans+1);
	}

	return 0;
}

```c
#include <stdio.h>

long long int gcd ( long long int a , long long int b ) {
	if ( b == 0 )
		return a;
	return gcd ( b , a%b );
}

int main ( int argc , char * argv[] ) {
	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		long long int n;
		scanf("%lld" , &n);
		long long int i;
		for ( i = n/2 ; i>= 1 ; i-- ) {
			if ( gcd( n , i ) == 1 ) {
				printf("%lld\n" , i);
				break;
			}
		}

	}
	return 0;
}
```

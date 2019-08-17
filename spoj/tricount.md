#include <stdio.h>

int main( int argc , char * argv[] ) {

	int t ;

	scanf("%d" , &t);

	while ( t-- ) {
		long long int n;
		scanf("%lld" , &n);
		printf("%lld\n" , (n*(n+2)*(2*n+1))/8 );
	}

	return 0;
}

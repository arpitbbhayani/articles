#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int main ( int argc ,char * argv[] ) {

	long long int n;
	scanf("%lld" , &n);
	switch ( n % 10 ) {
		case 0:
			printf("2\n");
			break;
		default:
			printf("1\n");
			printf("%lld\n" , n % 10);
			break;
	}

	return 0;
}

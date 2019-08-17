#include <stdio.h>

int main( int argc , char * argv[] ) {
	int t;

	long long int h;
	scanf("%d" , &t);

	while ( t-- ) {
		scanf("%lld" , &h);
		printf("%lld\n" , (h * (h+1) / 6));
	}
	return 0;
}

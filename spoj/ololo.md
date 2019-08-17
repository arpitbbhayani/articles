#include <stdio.h>

int main ( int argc , char * argv[] ) {

	int n , t , i;

	scanf("%d" , &n);

	scanf("%d" , &t);

	for ( i = 0 ; i < n-1 ; i++ ) {
		int a;
		scanf("%d" , &a);

		t = t ^ a;
	}

	printf("%d\n" , t );

	return 0;
}

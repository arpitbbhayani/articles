#include <stdio.h>
#define SIZE 1000010

int visited[SIZE] = {0};

int main( int argc , char * argv[] ) {

	int i;
	char str[16];
	for ( i = 1 ; i < 1000000 ; i++ ) {

		if ( visited[i] == 0 )
			printf("%d\n" , i );

		int n = i;
		int sum = 0;
		while ( n != 0 ) {
			sum += (n%10);
			n /= 10;
		}

		if ( i+sum < SIZE )
			visited[i+sum] = 1;
	}
	return 0;
}

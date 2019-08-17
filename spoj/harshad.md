/*
	Sieve , sieve , prime
	digit
*/

#include <stdio.h>
#define SIZE 1000010
#define LIMIT 1000010

int visited[SIZE];
int array[SIZE];
int prime[SIZE];

int main( int argc , char * argv[] ) {

	int i , j;
	int count = 0;
	char str[16];

	for ( i = 2 ; i < LIMIT ; i++ )
		prime[i] = 1;

	for ( i = 2 ; i < LIMIT ; i++ )
		if ( prime[i] )
			for ( j = i ; i * j < LIMIT && i * j >= 0 ; j++ )
				prime[i*j]=0;

	for ( i = 1 ; i < LIMIT ; i++ ) {

		array[i] = count;

		if ( visited[i] == 0 && prime[i] == 1 ) {
			count++;
		}

		int n = i;
		int sum = 0;
		while ( n != 0 ) {
			sum += (n%10);
			n /= 10;
		}

		if ( i+sum < LIMIT && i+sum >= 0 )
			visited[i+sum] = 1;
	}

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		int a , b;
		scanf("%d%d" , &a , &b);
		printf("%d\n" , array[b+1] - array[a]);
	}

	return 0;
}

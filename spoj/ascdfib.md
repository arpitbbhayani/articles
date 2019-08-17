```
#include <cstdio>
#include <cstdlib>
#include <iostream>

#define DEBUG 1

#define MOD 100000
#define SIZE 1110000

using namespace std;

int array[SIZE];

int main ( int argc ,char * argv[] ) {

	array[1] = 0;
	array[2] = 1;

	for ( int i = 3 ; i < SIZE ; i++ ) {
		array[i] = (array[i-1] + array[i-2]) % MOD;
	}

	int t;
	scanf("%d" , &t);
	for ( int i = 1 ; i <= t ; i++ ) {

		int a,b;
		scanf("%d%d" , &a,&b);

		int ab[MOD];

		for ( int j = 0 ; j < MOD ; j++ ) {
			ab[j] = -1;
		}

		for ( int j = 0 ; j <= b ; j++ ) {
			ab[array[a+j]] ++;
		}

		int count = 100;
		printf("Case %d:" , i);
		for ( int j = 0 ; j < MOD ; j++ ) {
			if ( ab[j] == -1 )
				continue;
			for ( int k = 0 ; k <= ab[j] ; k++ ) {
				printf(" %d" , j);
				count --;
				if ( count == 0 )
					break;
			}
			if ( count == 0 )
				break;
		}
		printf("\n");
	}

	return 0;
}
```

```
/*
 * AMZRCK.cpp
 *
 *  The number of ways of selecting a playlist such that no two successive tracks are selected.
 *  Created on: May 31, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG 0

int main ( int argc , char * argv[] ) {

	long long int array[64];
	long long int limit = 1000000000LL;

	array[1] = 2LL;
	array[2] = 3LL;

	for ( int i = 3 ; ; i++ ) {
		array[i] = array[i-1] + array[i-2];
		if ( array[i] > limit )
			break;
	}

	int t;
	scanf("%d" , &t);
	while ( t-- ) {
		int x;
		scanf("%d" , &x);
		printf("%lld\n" , array[x]);
	}
	return 0;
}
```

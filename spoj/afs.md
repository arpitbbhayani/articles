```c
/*
 * AFS.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG 0

#define SIZE 1000000

long long int a[SIZE];
long long int afs[SIZE];

void precalculate() {
	for ( int i = 2 ; i < SIZE ; i++ ) {
		a[i] = 1;
	}

	for ( int i = 2 ; i < SIZE ; i++ ) {
		int j = 2;
		int n;
		while  ( (n = i*j) < SIZE ) {
			a[n] += i;
			j++;
		}
	}

	afs[0] = 0;
	afs[1] = 0;

	for ( int i = 2 ; i < SIZE ; i++ ) {
		afs[i] = a[i] + afs[i-1];
	}

}

int main ( int argc , char * argv[] ) {

	precalculate();

	int t;
	scanf("%d" , &t);
	while ( t-- ) {
		long long int a;
		scanf("%lld" , &a);
		printf("%lld\n" , afs[a]);
	}
	return 0;
}
```

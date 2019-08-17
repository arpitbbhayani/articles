```
/*
 * ACPC10D.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG 0
#define gc getchar
#define ll long long

int min2(int a , int b) {
	return a < b ? a : b;
}

int min3( int a , int b , int c ) {
	return min2(a,min2(b,c));
}

int min4( int a , int b , int c , int d ) {
	return min2 ( a , min3(b,c,d));
}

int main(int argc, char * argv[]) {

	int n , count = 1;
	scanf("%d", &n);
	while (n != 0) {

		int array[n][3];
		for ( int i = 0 ; i < n ; i++ ) {
			cin >> (array[i][0]);
			cin >> (array[i][1]);
			cin >> (array[i][2]);
		}

		array[0][2] += array[0][1];

		array[1][0] += array[0][1];
		array[1][1] += min3(array[1][0] , array[0][1] , array[0][2]);
		array[1][2] += min3(array[1][1] , array[0][1] , array[0][2]);


		for ( int i = 2 ; i < n ; i++ ) {
			array[i][0] += min2(array[i-1][0] , array[i-1][1]);
			array[i][1] += min4(array[i][0] , array[i-1][0] , array[i-1][1] , array[i-1][2]);
			array[i][2] += min3(array[i][1] , array[i-1][1],array[i-1][2]);
		}

		cout << count << ". " << array[n-1][1] << endl;

		scanf("%d", &n);
		count++;
	}
	return 0;
}
```

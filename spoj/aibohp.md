```
/*
 * AIBOHP.cpp
 *
 *  Created on: May 29, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG 0

int readline ( char * str ) {

	int i = 0;
	char ch;
	while ( (ch=getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int array[6101][6101];

int main ( int argc , char * argv[] ) {

	int t;
	char str[6110] , strr[6110];

	scanf("%d" , &t);

	getchar();

	while ( t-- ) {

		int n = readline(str);
		int k = 0;
		for ( int i = n-1 ; i >= 0 ; i-- ) {
			strr[k++] = str[i];
		}
		strr[k] = '\0';

		for ( int i = 0 ; i < n+1 ; i++ ) {
			for ( int j = 0 ; j < n+1 ; j++ ) {
				if ( i == 0 || j == 0 ) {
					array[i][j] = 0;
				}
				else if ( str[i-1] == strr[j-1] ) {
					array[i][j] = array[i-1][j-1] + 1;
				}
				else {
					array[i][j] = array[i-1][j] > array[i][j-1] ? array[i-1][j] : array[i][j-1];
				}
			}
		}

		cout << n - array[n][n] << endl;

	}
	return 0;
}
```

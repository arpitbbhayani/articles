/*
 * KNJIGE.c
 *
 *  Created on: Mar 27, 2014
 *      Author: Arpit Bhayani
 */


#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0
#define gc getchar_unlocked
#define ll long long

void scanint(ll int *x) {
	register ll int c = gc();
	*x = 0;
	for(;(c<48 || c>57);c = gc());
	for(;c>47 && c<58;c = gc()) {*x = (*x<<1) + (*x<<3) + c - 48;}
}

int readline ( char * str ) {

	int i = 0;
	char ch;
	while ( (ch=getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

#define SIZE 300001

int a[SIZE];

int main ( int argc , char * argv[] ) {

	int t = 1;
	while ( t-- ) {

		int n;
		int count = 0;
		int i;
		scanf("%d" , &n);
		for ( i = 0 ; i < n ; i++ ) {
			scanf("%d" , &a[i]);
		}

		#if DEBUG
			printf("Array : ");
			for ( i = 0 ; i < n ; i++ )
				printf("%d " , a[i]);
			printf("\n");
		#endif

		int max_1 = a[0];
		int max_2 = 0;

		for ( i = 1 ; i < n ; i++ ) {

			#if DEBUG
				printf("Comparing : %d and %d\n" , a[i] , max);
			#endif

			if ( a[i] > max_2 ) {
				if ( a[i] > max_1 )
					max_1 = a[i];
				else
					max_2 = a[i];
			}
			#if DEBUG
				printf("count = %d and max = %d\n" , count, max);
			#endif
		}

		if ( max_2 != a[0] )
			count = 1;

		count += (max_2-1);

		printf("%d\n" , count);

	}
	return 0;
}

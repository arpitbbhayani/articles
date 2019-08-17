/**
 *	Majority Element
 *		Moore's Voting Algorithm
 *	http://www.geeksforgeeks.org/majority-element/
 */
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int readline ( char * str ) {

	int i = 0;
	char ch;
	while ( (ch=getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

#define SIZE 1000000
int array[SIZE];

int find_candidate ( int n ) {

	int index , i;
	int count = 1;

	index = 0;
	for ( i = 1 ; i < n ; i++ ) {
		if ( array[index] == array[i] ) {
			count ++;
		}
		else {
			count --;
		}

		if ( count == 0 ) {
			index = i;
			count = 1;
		}
	}
	return array[index];
}

int main ( int argc , char * argv[] ) {

	int t , z , i;
	scanf("%d" , &t);
	for ( z = 1 ; z <= t ; z++ ) {
		int n;
		scanf("%d" , &n);

		for ( i = 0 ; i < n ; i++ ) {
			scanf("%d" , &array[i]);
		}

		int count = 0;
		int candidate = find_candidate(n);

		for ( i = 0 ; i < n ; i++ ) {
			if ( array[i] == candidate ) {
				count++;
			}
		}

		if ( count > n/2 ) {
			printf("YES %d\n" , candidate);
		}
		else {
			printf("NO\n");
		}

	}
	return 0;
}

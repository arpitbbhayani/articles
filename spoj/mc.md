```c
#include <stdio.h>
#include <stdlib.h>

int readline( char * str ) {
	int i = 0;
	char ch;
	while ( (ch = getchar() ) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

long long int lcs ( char * s , char * t , int ls , int lt ) {

	int i , j;
	int LEFT = 2;
	int TOP = 1;
	int CROSS = 3;
	int array[1002][1002];
	int dir[1002][1002];
	for ( i = 0 ; i < ls+1 ; i++ ) {
		for ( j = 0 ; j < lt+1 ; j++ ) {
			if ( j == 0 ) {
				array[i][j] = 0;
				dir[i][j] = TOP;
			}
			else if ( i == 0 ) {
				array[i][j] = 0;
				dir[i][j] = LEFT;
			}
			else if ( s[i-1] == t[j-1] ) {
				array[i][j] = array[i-1][j-1] + 1;
				dir[i][j] = CROSS;
			}
			else if ( array[i-1][j] > array[i][j-1] ) {
				array[i][j] = array[i-1][j];
				dir[i][j] = TOP;
			}
			else if ( array[i][j-1] > array[i-1][j] ) {
				array[i][j] = array[i][j-1];
				dir[i][j] = LEFT;
			}
			else {
				array[i][j] = array[i][j-1];
				dir[i][j] = LEFT;
			}
		}
	}
	/*printf("***************************************************************\n");
	printf("Array\n");
	for ( i = 0 ; i < ls+1 ; i++ ) {
		for ( j = 0 ; j < lt+1 ; j++ ) {
			printf("%d " , array[i][j] );
		}
		printf("\n");
	}
	printf("DIRECTION\n");
	for ( i = 0 ; i < ls+1 ; i++ ) {
		for ( j = 0 ; j < lt+1 ; j++ ) {
			printf("%d " , dir[i][j] );
		}
		printf("\n");
	}
	*/
	i = ls;
	j = lt;
	long long int sum = 0;

	while ( ! (i == 0 && j == 0) ) {
		if ( dir[i][j] == LEFT ) {
			sum += 30;
			j -= 1;
		}
		else if ( dir[i][j] == TOP ) {
			sum += 15;
			i -= 1;
		}
		else {
			i -= 1;
			j -= 1;
		}
	}

	return sum;
}

int main ( int argc , char * argv[] ) {

	char * s = ( char * ) malloc ( 1001 * sizeof(char) );
	char * t = ( char * ) malloc ( 1001 * sizeof(char) );

	int ls , lt;

	int i = 0 , j = 0;

	ls = readline(s);

	while ( s[0] != '#' && ls != -1 ) {
		lt = readline(t);

		printf("%lld\n" , lcs(s,t,ls,lt));

		ls = readline(s);
	}

	free(s);
	free(t);

	return 0;
}
```

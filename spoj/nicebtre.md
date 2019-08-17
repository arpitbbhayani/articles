#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int max ( int a , int b ) {
	return a > b ? a : b;
}

int readline( char * str ) {
	char ch;
	int i = 0;

	while ( (ch = getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int _height ( char * str , int l , int *i ) {

	if ( str[*i] == 'n' ) {
		(*i)++;
		int lh = _height ( str , l , i ) + 1;
		int rh = _height ( str , l , i ) + 1;
		return max(lh,rh);
	}
	else {
		if ( str[*i] == '\0' )
			return 0;

		#if DEBUG
			printf("Leaf found at i = %d\n" , *i);
		#endif
		(*i)++;
		return 0;
	}
}

int height ( char * str , int l ) {

	int i = 0;
	int h = _height ( str , l , &i );
	return h;
}

int main ( int argc ,char  * argv[] ) {

	int t;
	scanf("%d" , &t);

	char str[10010];
	getchar();
	while ( t-- ) {
		int l = readline(str);

		if ( l == 1 && str[0] == 'l' ) {
			printf("0\n");
			continue;
		}

		#if DEBUG
			printf("Length : %d\n" , l);
		#endif

		printf("%d\n" , height(str , l));
	}

	return 0;
}

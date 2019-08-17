#include <stdio.h>

int readline ( char * str ) {

	int i = 0;
	char ch;
	while ( (ch = getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int is_palin ( char * s , int l ) {

	int i = 0;
	int n = l/2;
	int j = l - 1;
	for ( i = 0 ; i < n ; i++ ) {
		if ( s[i] != s[j] )
			break;
		j--;
	}
	return i == n;
}

int main ( int argc , char * argv[] ) {

	int t;
	char s[16];
	scanf("%d" , &t);
	getchar();
	while ( t-- ) {

		int l = readline(s);

		if ( is_palin( s , l ) ) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}

	}
	return 0;
}

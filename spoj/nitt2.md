#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

void readline () {

	char ch;

	int number252 = 0;
	int number525 = 0;

	while ( (ch=getchar()) != '\n' ) {
		number252 = number252 * 10 + (ch-'0');
		number525 = number525 * 10 + (ch-'0');

		if ( number252 >= 252 ) {
			number252 = number252 % 252;
		}
		if ( number525 >= 525 ) {
			number525 = number525 % 525;
		}

	}

	if ( number252 == 0 ) {
		printf ("Yes");
	}
	else {
		printf("No");
	}
	printf(" ");
	if ( number525 == 0 ) {
		printf ("Yes");
	}
	else {
		printf("No");
	}
	printf("\n");
}

int main ( int argc , char * argv[] ) {

	int t , z;

	scanf("%d" , &t);
	getchar();
	for ( z = 1 ; z <= t ; z++ ) {
		readline();
	}
	return 0;
}

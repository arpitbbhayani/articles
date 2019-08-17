#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
#define NO 0
#define YES 1

int main ( int argc ,char *argv[] ) {

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		int n , i , answer = YES;

		scanf("%d" , &n);

		if ( n == 1 ) {
			int x;
			scanf("%d" , &x);
			if ( x == 0 )
				printf("YES\n");
			else
				printf("NO\n");

			continue;
		}

		int count = 0;
		scanf("%d" , &count);
		for ( i = 1 ; i < n ; i++ ) {

			int x;
			scanf("%d" , &x);

			x = x - count;
			if ( x < 0 )
				answer = NO;
			count = x;
		}

		if ( count == 0 && answer == YES )
			printf("YES\n");
		else
			printf("NO\n");

	}

	return 0;
}

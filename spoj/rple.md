#include <stdio.h>
#include <stdlib.h>

int main( int argc , char * argv[] ) {
	int t,i;
	scanf("%d" , &t);

	for ( i = 0 ; i < t ; i++ ) {

		int spy[1010] = {0};
		int civil[1010] = {0};
		int n,r,flag = 0;
		scanf("%d%d" , &n , &r);

		while ( r-- ) {
			int a,b;
			scanf("%d%d" , &a,&b);
			spy[a] = 1;
			civil[b] = 1;
		}

		int j = 0;
		for ( j = 0 ; j < n ; j++ ) {
			if ( spy[j] == 1 && civil[j] == 1 )
				flag = 1;
		}

		if ( flag == 0 ) {
			printf("Scenario #%d: spying\n" , i+1);
		}
		else {
			printf("Scenario #%d: spied\n" , i+1);
		}
	}

	return 0;
}

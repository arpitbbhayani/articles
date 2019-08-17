```c
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

#define WK 1
#define WH 2
#define WP 3
#define BK 4
#define BH 5
#define BP 6

int array[8][8];

void readChess( int * r , int * c) {

	char a[8][3];
	int i,j;

	for ( i = 0 ; i < 8 ; i++ ) {
		scanf("%s %s %s %s %s %s %s %s" , a[0] , a[1] ,a[2] ,a[3] ,a[4] ,a[5] ,a[6] ,a[7]);
		for ( j = 0 ; j < 8 ; j++ ) {
			if ( strcmp(a[j] , "WK") == 0 ) {
				array[i][j] = WK;
			}
			else if ( strcmp(a[j] , "WH") == 0 ) {
				array[i][j] = WH;
			}
			else if ( strcmp(a[j] , "WP") == 0 ) {
				array[i][j] = WP;
			}
			else if ( strcmp(a[j] , "BK") == 0 ) {
				array[i][j] = BK;
				*r = i;
				*c = j;
			}
			else if ( strcmp(a[j] , "BH") == 0 ) {
				array[i][j] = BH;
			}
			else if ( strcmp(a[j] , "BP") == 0 ) {
				array[i][j] = BP;
			}
			else {
				array[i][j] = 0;
			}
		}
	}

#if DEBUG
	for ( i = 0 ; i < 8 ; i++ ) {
		for ( j = 0 ; j < 8 ; j++ ) {
			printf("%d " , array[i][j]);
		}
		printf("\n");
	}
#endif
	
}

int isCheck( int r, int c ) {

	int whr[] = {-2,-1,1,2,2,1,-1,-2};
	int whc[] = {1,2,2,1,-1,-2,-2,-1};
	int wkr[] = {-1,0,1,1,1,0,-1,-1};
	int wkc[] = {1,1,1,0,-1,-1,-1,0};
	int wpr[] = {1,1,1,1,1,1,1,1};
	int wpc[] = {-1,1,-1,1,-1,1,-1,1};

	int nr , nc , i;
	for ( i = 0 ; i < 8 ; i++ ) {
		nr = r + whr[i];
		nc = c + whc[i];

		if ( nr >= 0 && nr <= 7 && nc >= 0 && nc <= 7 ) {
			if ( array[nr][nc] == WH ) {
				return 1;
			}
		}

		nr = r + wkr[i];
		nc = c + wkc[i];

		if ( nr >= 0 && nr <= 7 && nc >= 0 && nc <= 7 ) {
			if ( array[nr][nc] == WK ) {
				return 1;
			}
		}

		nr = r + wpr[i];
		nc = c + wpc[i];

		if ( nr >= 0 && nr <= 7 && nc >= 0 && nc <= 7 ) {
			if ( array[nr][nc] == WP ) {
				return 1;
			}
		}


	}

	return 0;


}

int main ( int argc ,char * argv[] ) {

	int t , n;
	scanf("%d" , &n);

	for (  t = 1 ; t <= n ; t++ ) {
		int r,c;
		readChess(&r,&c);

		int a = isCheck(r,c);

		if ( a == 1 ) {
			printf("Case #%d: Check\n" , t);
		}
		else {
			printf("Case #%d: Not Check\n" , t);
		}
	}

	return 0;
}
```

```c
#include <stdio.h>

int main ( int argc , char * argv[] ) {

	int t , z;
	scanf("%d" , &t);

	for ( z = 1 ; z <= t ; z++ ) {

		int n;
		int i , j , k;
		scanf("%d" , &n);
		int dist[n+1][n+1];

		for ( i = 1 ; i <= n ; i++ ) {
			for ( j = 1 ; j <= n ; j++ ) {
				scanf("%d" , &dist[i][j]);
			}
		}

		for ( k = 1 ; k <= n ; k++ ) {
			for ( i = 1 ; i <= n ; i++ ) {
				for ( j = 1 ; j <= n ; j++ ) {
					if ( dist[i][j] > dist[i][k] + dist[k][j] ) {
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}

		int r;
		int d = 0;

		scanf("%d" , &r);

		while ( r-- ) {
			int a , b;
			scanf("%d%d" , &a , &b);
			d += dist[a][b];
		}

		printf("Case #%d: %d\n" , z,d);

	}

	return 0;
}
```

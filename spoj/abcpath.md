```
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstdlib>
#include <cstring>

using namespace std;

struct node {
	int i;
	int j;
};

struct node make_node ( int i , int j ) {

	struct node n;
	n.i = i;
	n.j = j;
	return n;
}


int main( int argc , char * argv[] ) {

	int r , c;
	int lo = 1;
		
	char d[50][50];
	int a[50][50];
	int visited[50][50];

	scanf("%d %d" , &r,&c);

	while ( r != 0 && c != 0 ) {

		int i = 0;
		int max = 0;

		for ( i = 0 ; i < r ; i++ ) {
			scanf("%s" , d[i]);
		}

		memset( a , 0 , sizeof( a ) );
		memset( visited , 0 , sizeof( visited ) );

		queue< node > q;

		for ( int i = 0 ; i < r ; i++ ) {
			for ( int j = 0 ; j < c ; j++ ) {
				if ( d[i][j] == 'A' ) {

					max = 1;
					a[i][j] = 1;
					q.push( make_node(i,j) );
				}
			}
		}

		int m1[] = {-1,0,1,1,1,0,-1,-1};
		int m2[] = {-1,-1,-1,0,1,1,1,0};


		while ( !q.empty() ) {

			struct node n = q.front();
			q.pop();

			for ( int i = 0 ; i < 8 ; i++ ) {
				int x = m1[i] + n.i;
				int y = m2[i] + n.j;

				if ( x >= 0 && x < r && y >= 0 && y < c && (d[x][y] == (d[n.i][n.j] + 1)) ) {

					if ( !visited[x][y] ) {

						visited[x][y] = 1;

						a[x][y] = a[n.i][n.j] + 1;

						if ( a[x][y] > max )
							max = a[x][y];

						q.push ( make_node(x,y) );
					}

				}

			}

		}
		/*for ( int i = 0 ; i < r ; i++ ) {
			for ( int j = 0 ; j < c ; j++ ) {
				printf("%d " , a[i][j] );
			}
			printf("\n");
		}*/
		printf("Case %d: %d\n",lo++,max) ;
		scanf("%d%d" , &r , &c );
	}

	return 0;
}
```

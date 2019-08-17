#include <stdio.h>
#include <stdlib.h>

int lca ( int a , int b , int * height , int * parent , int n ) {

	if ( height[a] > height[b] ) {
		int t;
		t = a;
		a = b;
		b = t;
	}

	int pa = a , pb = b;

	while ( height[pa] != height[pb] ) {
		pb = parent[pb];
	}

	if ( pa == pb )
		return pa;

	while ( parent[pa] != parent[pb] ) {
		pa = parent[pa];
		pb = parent[pb];
	}

	if ( parent[pa] == 0 )
		return pa;
	else
		return parent[pa];
}

int main( int argc , char * argv[] ) {

	int t , i , z;
	scanf("%d" , &t);

	for ( z = 1; z <= t ; z++ ) {
		printf("Case %d:\n" , z);

		int n , i , j;
		int * height;
		int * parent;
		scanf("%d" , &n);

		height = ( int * ) calloc ( n+1 , sizeof(int) );
		parent = ( int * ) calloc ( n+1 , sizeof(int) );

		for ( i = 1 ; i <= n ; i++ ) {
			int k , l;
			scanf("%d" , &k);
			while ( k-- ) {
				scanf("%d" , &l);
				height[l] = height[i]+1;
				parent[l] = i;
			}
		}

		int k;
		scanf("%d" , &k);

		while ( k-- ) {
			int a,b;
			scanf("%d%d" , &a,&b);

			printf("%d\n" , lca( a,b, height , parent , n ));

		}

		free(height);
		free(parent);

	}

	return 0;
}

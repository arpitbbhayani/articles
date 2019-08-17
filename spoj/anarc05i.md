#include <stdio.h>
#include <stdlib.h>

void visit ( int **visited , int x , int y , int * count) {
	if ( visited[x][y] == 1 ) {
		(*count) ++;
	}
	else if ( visited[x][y] == 0 ) {
		visited[x][y] = 1;
	}
}

int main ( int argc , char * argv[] ) {

	int ** visited;
	char str[1001];
	int i,j;

	scanf("%s" , str);

	while ( str[0] != 'Q' ) {

		visited = (int **)calloc ( 2002 , sizeof(int*) );
		for ( i = 0 ; i < 2002 ; i++ ) {
			visited[i] = (int *) calloc ( 2002 , sizeof(int) );
		}

		int count = 0;
		int x=1001,y=1001;

		visited[x][y] = 1;

		for ( i = 0 ; str[i] != 'Q' ; i++ ) {
			switch( str[i] ) {
				case 'U':
					x -= 1;
					visit( visited , x , y , &count);
					break;
				case 'D':
					x += 1;
					visit( visited , x , y , &count);
					break;
				case 'L':
					y -= 1;
					visit( visited , x , y , &count);
					break;
				case 'R':
					y += 1;
					visit( visited , x , y , &count);
					break;
			}
		}

		printf("%d\n" , count);
		for ( i = 0 ; i < 2002 ; i++ ) {
			free(visited[i]);
		}
		free(visited);

		scanf("%s" , str);
	}

	return 0;

}

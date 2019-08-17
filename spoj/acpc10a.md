#include <iostream>
#include <cstdio>

using namespace std;

int main( int argc , char * argv[] ) {

	int a,b,c;

	scanf("%d%d%d" , &a,&b,&c);
	while ( a != 0 || b != 0 || c != 0 ) {

		if ( b - a == c - b ) {
			printf("AP %d\n" , c + (c-b) );
		}
		else if ( b/a == c/b ) {
			printf("GP %d\n" , c * (c/b));
		}

		scanf("%d%d%d" , &a,&b,&c);
	}

	return 0;
}

```
#include <stdio.h>

int main( int argc , char * argv[] ) {

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		int x,y;
		scanf("%d%d" , &x , &y);
		if ( y > x ) {
			printf("No Number\n");
		}
		else if ( (x + y) & 1 ) {
			printf("No Number\n");
		}
		else if ( x - y > 2 ) {
			printf("No Number\n");
		}
		else if ( x&1 && y&1 ){
			printf("%d\n" , x+y-1);
		}
		else {
			printf("%d\n" , x+y);
		}
	}

	return 0;
}
```

```c
#include <stdio.h>

int gcd ( int a , int b ) {
	if ( b == 0 )
		return a;
	return gcd ( b , a % b );
}

int main( int argc , char * argv[] ) {

	int t;
	scanf("%d" , &t);
	while ( t-- ) {
		int a,b;
		scanf("%d%d" , &a,&b );
		int g = gcd ( a , b );
		printf("%d %d\n" , b/g , a/g );
	}
	return 0;
}
```

```c
#include <stdio.h>

int main( int argc , char * argv[] ) {

	unsigned long long int n;
	scanf("%lld" , &n);

	if ( (n & (n-1)) == 0)
		printf("TAK\n");
	else
		printf("NIE\n");

	return 0;
}
```

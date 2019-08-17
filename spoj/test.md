```
#include <cstdio>
#include <iostream>

using namespace std;

int main( int argc, char * argv[] ) {
	int x;
	while(1) {
		scanf("%d", &x);
		if( x == 42 ) {
			break;
		}
		else {
			printf("%d\n", x);
		}
	}
	return 0;
}
```

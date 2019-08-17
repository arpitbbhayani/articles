```
#include <stdio.h>
#include <stdlib.h>

int main ( int argc , char * argv[] ) {

	char a[512] , b[512];

	scanf("%s %s" , a, b);

	while ( a[0] != '*' && b[0] != '*' ) {

		int chance = 0;

		int i = 0, flag = 0;

		while ( a[i] != '\0' ) {
			while ( a[i] != '\0' && a[i] == b[i] ) {
				i++;
			}
			while ( a[i] != '\0' && a[i] != b[i] ) {
				flag = 1;
				i++;
			}
			if ( flag == 1 )
				chance ++;
			flag = 0;
		}

		printf("%d\n" , chance);

		scanf("%s %s" , a, b);
	}
	return 0;
}
```

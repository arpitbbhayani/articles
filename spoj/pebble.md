```c
#include <stdio.h>

int main( int argc , char * argv[] ) {

	char str[4096];
	int j = 0;
	while ( scanf("%s" , str) != EOF ) {
		j++;
		int i = 0;
		int look_for_one = 0;
		int count = 0;

		while ( str[i] != '\0' && str[i++] == '0' );
		if ( str[i-1] == '1' )
			count = 1;
		for ( ; str[i] != '\0' ; i++ ) {
			if ( look_for_one && str[i] == '1' ) {
				look_for_one = 0;
				count++;
			}
			else if ( look_for_one == 0 && str[i] == '0' ) {
				look_for_one = 1;
				count++;
			}
		}
		printf("Game #%d: %d\n" , j,count);
	}

	return 0;
}
```

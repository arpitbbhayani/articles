```c
#include <stdio.h>
#include <string.h>

int main ( int argc , char * argv[] ) {

	int i = 0;
	char str[1024];

	scanf("%s" , str );

	int len = strlen(str);

	int lc = 0 , dc = 0;

	if ( str[0] == '0' && str[len-1] == '0' ) lc ++;
	if ( str[0] == '0' && str[len-1] == '1' ) dc ++;

	i = 1;

	while ( str[i] != '\0' ) {
	
		if ( str[i] == '0' && str[i-1] == '0' ) lc ++;
		if ( str[i] == '0' && str[i-1] == '1' ) dc ++;
		i++;
	}

	if ( lc == len || lc == dc ) {
		printf("EQUAL\n");
	}
	else if ( lc > dc ) {
		printf("SHOOT\n");
	}
	else if ( lc < dc ) {
		printf("ROTATE\n");
	}
	
	return 0;
}
```

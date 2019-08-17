```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ( int argc , char * argv[] ) {

	char a[1024] , b[1024];
	int h1[26] , h2[26] , i , j , k;

	while ( scanf("%s%s",a,b) != EOF ) {

		memset ( h1 , 0 , sizeof(h1) );
		memset ( h2 , 0 , sizeof(h2) );

		i = 0;
		while ( a[i] ) {
			h1[a[i] - 'a'] ++;
			i++;
		}

		i = 0;
		while ( b[i] ) {
			h2[b[i] - 'a'] ++;
			i++;
		}

		for ( i = 0 ; i < 26 ; i++ ) {
			k = h1[i] > h2[i] ? h2[i] : h1[i];
			for ( j = 0 ; j < k ; j++ )
				printf("%c" , i+'a');
		}
		printf("\n");

	}

	return 0;
}
```

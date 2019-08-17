```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

int readline ( char * str ) {

	int i = 0;
	char ch;
	while ( (ch=getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int main ( int argc , char * argv[] ) {

	char str[1000000];
	int t , z;
	for ( ;  ;  ) {

		scanf("%s" , str);
		int len = strlen(str);
		int substr_len = 1;

		if ( len == 1 && str[0] == '*' )
			break;

		while ( 1 ) {

			int i , j;

			if ( len % substr_len != 0 ) {

				//printf("continuing : len = %d and substr_length = %d\n"  , len , substr_len);

				substr_len++;
				continue;
			}

			//printf("For len = %d and substr_len = %d\n" , len , substr_len);

			for ( i = substr_len ; i < len ;  ) {

				for ( j = 0 ; j < substr_len ; j++ ) {
					//printf("Cmparing : %c and %c and i = %d and j = %d\n" , str[i] , str[j] , i , j);
					if ( str[i] != str[j] ) {
						break;
					}
					i++;
				}


				if ( j == substr_len ) {
					// Loop completed
					//printf("Loop Completed\n");
				}
				else {
					// break executed
					substr_len = i+1;
					//printf("Loop not Completed\n");
					break;
				}

			}

			if ( i == len ) {
				printf("%d\n" , len/substr_len);
				break;
			}
			else {
			}

		}



	}
	return 0;
}
```

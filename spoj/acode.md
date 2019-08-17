```c
#include <stdio.h>
#include <stdlib.h>

int readline ( char * str ) {
	int i = 0;
	char ch = 0;
	while ( (ch = getchar() ) != '\n' ) {
		str[i] = ch;
		i++;
	}
	str[i] = '\0';
	return i;
}

int main ( int argc , char * argv[] ) {

	int len = 0 , i = 0 ;
	char * str = (char *) calloc ( 5010 , sizeof(char) );
	long long int * array = (long long int *) calloc ( 5010 , sizeof(long long int) );

	char string[3] ;

	len = readline ( str );

	while ( str[0] != '0' ) {

		if ( len == 1 ) {
			printf("1\n");
			len = readline ( str );
			continue;
		}


		array [len] = 1 ;

		for ( i = len-1 ; i >= 0 ; i-- ) {

			if ( i == len-1 ) {
				if ( str[i] == '0' )
					array[i] = 0;
				else
					array[i] = 1;
				continue;
			}

			if ( str[i] == '0' ) {
				array[i] = 0;
				continue;
			}

			string[0] = str[i]; string[1] = str[i+1]; string[2] = '\0';

			//printf("Checking for string : %s\n" , string );

			int number = atoi ( string );

			if ( number <= 26 ) {
				if ( i == len-1 )
					array[i] = array[i+1] + 1;
				else
					array[i] = array[i+1] + array[i+2];
			}
			else {
				array[i] = array[i+1] ;
			}

			/*int j = 0 ;
			for ( j = 0 ; j < len ; j++ ) {
				printf("%lld " , array[j]);
			}
			printf("\n");
			*/
		}
		printf("%lld\n" , array[0]);
		//printf("%lld\n" , f);
		len = readline ( str );
	}

	return 0;
}
```

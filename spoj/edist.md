```
/**
 *	http://www.csse.monash.edu.au/~lloyd/tildeAlgDS/Dynamic/Edit/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

int array[2010][2010];

int readline ( char * str ) {
	int i = 0;
	char ch;

	while ( (ch = getchar()) != '\n' ) {
		str[i] = ch;
		i++;
	}
	str[i] = '\0';
	return i;
}

int min2 ( int a , int b ) {
	return a<b?a:b;
}

int min3 ( int a , int b , int c ) {
	return min2(a,min2(b,c));
}

int main ( int argc , char * argv[] ) {

	int t;
	scanf("%d" , &t);
	getchar();

	char a[2010] , b[2010];

	while ( t-- ) {

		scanf("%s" , a);
		scanf("%s" , b);

		int la = strlen(a);
		int lb = strlen(b);

		int i , j;
		for(i = 0 ; i <= lb ; i++)
			array[0][i] = i;
		for(i = 0 ; i <= la ; i++)
			array[i][0]=i;

		for ( i = 1 ; i <= la ; i++ ) {
			for ( j = 1 ; j <= lb ; j++ ) {

				int t1 = array[i-1][j-1] + ((a[i-1] == b[j-1]) ? 0 : 1);
				int t2 = array[i-1][j] + 1;
				int t3 = array[i][j-1] + 1;

				array[i][j] = min3(t1,t2,t3);

			}
		}
		printf("%d\n" , array[la][lb]);
		#if DEBUG
		printf("Array : \n");
		for ( i = 0 ; i < la+1 ; i++ ) {
			for ( j = 0 ; j < lb+1 ; j++ ) {
				printf("%d " , array[i][j]);
			}
			printf("\n");
		}
		#endif
	
	}

	return 0;
}
```

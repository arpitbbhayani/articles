```c
#include <stdio.h>
#include <stdlib.h>

void readline( char * a , char * b , int *la , int *lb ){
	
	*la = 0;
	*lb = 0;

	char ch;

	while ( (ch = getchar()) != ' ' ) {
		a[(*la)++] = ch;
	}
	a[*la] = '\0';

	while ( (ch = getchar()) != '\n' ) {
		b[(*lb)++] = ch;
	}
	b[*lb] = '\0';

}

void reduce ( char *a , int l ) {

	int i , j , k , flag = 0;
	int index = 0;

	for ( i = 0 ; i < l ;i++ ) {

		k = i;
		flag = 0;

		for ( j = 0 ; j <= index ; j++ ) {
			if ( a[j] == a[k] ) {

			}
			else {
				index = i;
				flag = 1;
				break;
			}
			k++;
		}
		if ( flag == 0 )
			i = k-1;
	}

	a[index+1] = '\0';
}

int main ( int argc ,char * argv[] ) {

	int t;
	char * a , * b ;
	scanf("%d" , &t);
	getchar();

	a = (char *) malloc ( 100010 );
	b = (char *) malloc ( 100010 );

	while ( t-- ) {

		int la = 0 , lb = 0;
		readline(a,b,&la,&lb);

		if ( la > lb ) {
			char * c = a;
			a=b;
			b=c;

			int temp = la;
			la = lb;
			lb = temp;
		}

		int i = 0 , j = 0;

		/*while ( 1 ) {
			if ( i == la - 1 && j == lb - 1 ) {
				printf("YES\n");
				break;
			}
			if ( a[i] == b[j] ) {
				i = (i + 1) % la;
				j = (j + 1) % lb;
			}
			else {
				printf("NO\n");
				break;
			}

		}*/

		reduce(a,la);
		reduce(b,lb);

		i = 0;
		while ( a[i] != '\0' && b[i] != '\0' ) {
			if ( a[i] != b[i] )
				break;
			i++;
		}

		if ( a[i] == b[i] && a[i] == '\0' )
			printf("YES\n");
		else
			printf("NO\n");

	}
	free(a);
	free(b);

	return 0;
}
```

```
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int readline ( char * str ) {

	int i = 0;
	char ch;
	while ( (ch=getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int is_int ( char * s ) {
	int i = 0;
	int num = 0;

	for ( i = 0 ; s[i] ; i++ ) {
		if ( (s[i] >= '0' && s[i] <= '9') ) {
			num = num * 10 + (s[i] - '0');
		}
		else {
			return -1;
		}
	}
	return num;
}

int main ( int argc , char * argv[] ) {

	int t , z;
	scanf("%d" , &t);
	for ( z = 1 ; z <= t ; z++ ) {
		char a[100],b[100],c[100];
		scanf("%s + %s = %s" , a , b ,c);

		#if DEBUG
			printf("a : %s\n" , a);
			printf("b : %s\n" , b);
			printf("c : %s\n" , c);
		#endif

		int aa = is_int(a);
		int ab = is_int(b);
		int ac = is_int(c);

		if ( aa == -1 ) {
			aa = ac - ab;
		}
		else if ( ab == -1 ) {
			ab = ac - aa;
		}
		else if ( ac == -1 ) {
			ac = aa + ab;
		}
		else {

		}

		printf("%d + %d = %d\n" , aa , ab , ac);

	}
	return 0;
}
```

```c
#include <stdio.h>

void readline ( char * str ) {
	char ch;
	int i = 0;
	while ( (ch = getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return;
}

int main( int argc, char * argv[] ) {

	int t , i;
	int key;

	char m[100010];

	scanf("%d" , &t);

	while ( t-- ) {
		scanf("%d" , &key);
		getchar();
		readline(m);

		for ( i = 0 ; m[i] != '\0' ; i++ ) {

			if ( m[i] == '.' ) {
				printf(" ");
				continue;
			}

			if ( key >= 0 && key <= 25 ) {
				if ( m[i] >= 'A' && m[i] <= 'Z' )
					printf("%c" , (((m[i]-'A') + key) % 26) + 'A');
				else
					printf("%c" , (((m[i]-'a') + key) % 26) + 'a');
			}
			else {

				if ( m[i] >= 'A' && m[i] <= 'Z' )
					printf("%c" , (((m[i]-'A') + key) % 26) + 'a');
				else
					printf("%c" , (((m[i]-'a') + key) % 26) + 'A');
			}
		}
		printf("\n");
	}
	
	return 0;
}
```

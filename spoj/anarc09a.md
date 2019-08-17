```
#include <stdio.h>
char stack[10000];
int top;

int readline( char *str ) {
        char ch;
	int i = 0;
        while ( ( ch = getchar() ) != '\n' ) {
                *str++ = ch;
		i++;
	}
        *str ='\0';
        return i;
}
void eval( int n , char * array , int l) {

	int ans = 0;
	top = -1;
	int i = 0;
	for( i = 0 ; i < l ; i++ ) {
		if( array[i] == '{' ) {
			top++;
			stack[top] = '{';
			//printf("Pushing : top = %d\n" , top);
			/* Top points to the location -> last element */
		}
		else if ( array[i] == '}' ) {
			if ( top == -1 ) {
				top++;
				stack[top] = '{';
				ans ++;
				//printf("Error case Pushing : top = %d and ans = %d\n" , top, ans);
			}
			else if ( top != -1 ) {
				if( stack[top] == '{' ) {
					top--;
					//printf("Popping : top = %d\n" , top);
				}
				else {
					top++;
					stack[top] = '{';
					//printf("Pushing : top = %d and ans = %d\n" , top, ans);
				}
			}
		}
	}
	//printf("TOP = %d ans = %d\n" , top , ans);	
	if ( l == 0 )
		printf("%d. %d\n" , n , 0);
	else {
		if( top == -1  && ans == 0 )
			printf("%d. %d\n" , n , 0);
		else {
			//printf("TOP = %d ans = %d\n" , top , ans);
			printf("%d. %d\n" , n , ((top+1)/2) + ans);
		}
	}
}

int main( int argc , char * argv[] ) {
	char array[10000];
	int l = 0 , i = 0;;
	while ( 1 ) {

		l = readline(array);
		if( array[0] == '-' )
			break;
		i++;
		eval(i,array,l);

	}
	return 0;
}
```

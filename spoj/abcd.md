```
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace std;

int main ( int argc , char * argv[] ) {

	int n;
	scanf("%d" , &n);
	n <<= 1;

	char * array = (char * ) malloc ( sizeof(char) * n );
	char * temp = (char * ) malloc ( sizeof(char) * 2 );

	getchar();

	for ( int i = 0 ; i < n ; i++ ) {
		array[i] = getchar();
	}

	char last;

	for ( int i = 0 ; i < n ; i+=2 ) {

		int flag[4] = {0};

		flag[array[i]-'A'] = 1;
		flag[array[i+1]-'A'] = 1;

		for ( int j = 0 ; j < 4 ; j++ ) {
			if ( flag[j] == 0 ) {
				flag[j] = 1;
				temp[0] = j+'A';
				break;
			}
		}

		for ( int j = 0 ; j < 4 ; j++ ) {
			if ( flag[j] == 0 ) {
				flag[j] = 1;
				temp[1] = j+'A';
				break;
			}
		}

		if ( i != 0 && temp[0] == last ) {
			char t = temp[0];
			temp[0] = temp[1];
			temp[1] = t;
		} 

		last = temp[1];
		printf("%c%c" , temp[0] , temp[1] );
	}
	printf("\n");

	free(array);
	free(temp);
	return 0;
}
```

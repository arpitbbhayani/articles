#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

char line[32768];

int main( int argc , char * argv[] ) {

	int t;
	scanf("%d\n", &t);

	while( t-- ) {
		fgets(line, 32768, stdin);
		int cnt = 1, len, maxcnt = 0, plen = -1;

		for( char *p = strtok(line, " \n\r\t") ; p != NULL; p = strtok(NULL , " \n\r\t") ) {
			len = strlen(p);
			if( len == plen )
				cnt++;
			else
				cnt = 1;
			if( cnt > maxcnt )
				maxcnt = cnt;
			plen = len;
		}

		printf("%d\n", maxcnt);
	}
	return 0;
}

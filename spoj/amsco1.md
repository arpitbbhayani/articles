```
#include <iostream>
#include <cstdio>
#include <cstring>

#define newl printf("\n")

using namespace std;

int main ( int argc , char * argv[] ) {

	char key[16] , text[256];
	int index[10];

	char cipher[256][9][3];

	while ( scanf("%s %s" , key , text) != EOF ) {

		int i , j;
		int len = 0;

		for ( i = 0 ; key[i] != '\0' ; i++ ) {
			index[ (key[i] - '0') - 1 ] = i;
		}

		len = i;
		int lent = strlen(text);
		int cflag = 2;
		int rflag = 1;

		int r = 0 ;

		memset ( cipher , '#' , sizeof(cipher) );

		for ( i = 0 ; text[i] != '\0' ; ) {

			rflag = (rflag == 2) ? 1 : 2;
			cflag = rflag;

			for ( j = 0 ; j < len ; j++ ) {
				if ( cflag == 2 ) {

					if ( text[i] == 0 ) break;

					cipher[r][j][0] = text[i];
					i++;

					if ( text[i] != '\0' ) {
						cipher[r][j][1] = text[i];
						i++;
						cipher[r][j][2] = '\0';
					}
					else {
						cipher[r][j][1] = '\0';
					}
					cflag = 1;
				}
				else {	

					if ( text[i] == 0 ) break;

					cipher[r][j][0] = text[i];
					i++;
					cipher[r][j][1] = '\0';
					cflag = 2;
				}
			}
			r++;
		}

		for ( i = 0 ; i < len ; i++ ) {
			int c = index[i];
			for ( j = 0 ; j < 256 ; j++ ) {
				if ( cipher[j][c][0] >= 'A' && cipher[j][c][0] <= 'Z' ) printf("%c" , cipher[j][c][0]);
				if ( cipher[j][c][1] >= 'A' && cipher[j][c][1] <= 'Z' ) printf("%c" , cipher[j][c][1]);
			}
		}
		newl;

	}

	return 0;
}
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min ( int a , int b ){
	if ( a < b )
		return a;
	return b;
}

int main ( int argc , char * argv[] ) {

	int t;

	while ( scanf("%d" , &t) != EOF ) {

		int s[3];
	
		memset(s,0,sizeof(s));
	
		while ( t-- ) {
	
			char str[4];
	
			scanf("%s" , str );
	
			if ( str[0] == '1' && str[2] == '4' ) {
				s[0]++;
			}
			else if ( str[0] == '1' && str[2] == '2' ) {
				s[1]++;
			}
			else if ( str[0] == '3' && str[2] == '4' ) {
				s[2]++;
			}

		}

		// Abotrika's 1 pizza
		int n = 1;
		int d = 0;

		d = min( s[0] , s[2] );
		n += d;
		s[0] -= d;
		s[2] -= d;

	
		//Combining two 1/2 into 1 pizza
		n += s[1]/2;
		s[1] = s[1] % 2;

		//Combining 2 1/4th and 1 1/2

		if ( s[1] == 1 && s[0] >= 2 ) {
			n += 1;
			s[0] -= 2;
			s[1] = 0;
		}

		if ( s[1] == 1 && s[0] == 1 ) {
			n += 1;
			s[0] = 0;
			s[1] = 0;
		}

		//Combining 2 1/4th and 1 1/2
		d = min ( s[0]/4 , s[1]);
		n += d;
		s[0] -= (2 * d);
		s[1] -= d;

		//Combingin all 1/4ths
		n += s[0]/4;
		if ( s[0] % 4 == 0 )
			s[0] = 0;
		else
			s[0] = 1;

		// Rest all will be comming form 1 pizza each

		n += (s[0] + s[1] + s[2]);
	
		printf("%d\n" , n);
	}

	return 0;
}
```

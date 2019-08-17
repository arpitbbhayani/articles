```
/*
	One half is the binary negation of other.
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>

#define DEBUG 1

using namespace std;

#define llu unsigned long long
#define gc getchar_unlocked

void scanint(llu int &x)
{
    register int c = getchar_unlocked();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

int main ( int argc , char * argv[] ) {

	llu int t , z;
	scanf("%llu" , &t);
	for ( z = 1 ; z <= t ; z++ ) {
		llu int n , k;
		scanint(n);
		scanint(k);

		int ans = 0;

		if ( k == 1 ) {
			printf("Male\n");
			continue;
		}
		else if ( k == 2 ) {
			printf("Female\n");
			continue;
		}

		k--;
		while ( k > 1 ) {
			if ( k & 1 )
				ans ++;
			k /= 2;
		}

		if ( ans & 1 )
			printf("Male\n");
		else
			printf("Female\n");

	}
	return 0;
}
```

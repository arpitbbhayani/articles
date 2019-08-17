```
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

#define DEBUG 1

using namespace std;

#define ll long long
#define gc getchar_unlocked

void scanint(ll int &x)
{
    register int c = getchar_unlocked();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}


int readline ( char * str ) {

	int i = 0;
	char ch;
	while ( (ch=getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

ll int array[100010];
ll int mem[100010];

ll int max ( ll int a , ll int b ) {
	return a > b ? a : b;
}

ll int max3 ( ll int a , ll int b , ll int c ) {
	return max(a,max(b,c));
}

ll int f( int start , int end ) {

	if ( start >= end )
		return 0;

	if ( mem[start] != 0 )
		return mem[start];

	if ( start == end - 3 ) {
		mem[start] = array[start] + array[start+1] + array[start+2];
	}
	else if ( start == end - 2 ) {
		mem[start] = array[start] + array[start+1];
	}
	else if ( start == end - 1 ) {
		mem[start] = array[start];
	}	
	else {
		mem[start] = max3(
			f(start+2 , end) + array[start] , \
			f(start+4 , end) + array[start] + array[start+1], \
			f(start+6 , end) + array[start] + array[start+1] + array[start+2] \
	 	);
	}

	return mem[start];
}

int main ( int argc , char * argv[] ) {

	ll int t , z;
	scanf("%lld" , &t);
	for ( z = 1 ; z <= t ; z++ ) {

		for ( int i = 0 ; i < 100010 ; i++ )
			mem[i] = 0;

		ll int n;
		scanint(n);
		for ( int i = 0 ; i < n ; i++ ) {
			scanint(array[i]);
		}

		printf("%lld\n" , f(0,n));

	}
	return 0;
}
```

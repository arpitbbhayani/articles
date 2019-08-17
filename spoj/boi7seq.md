#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define DEBUG 1
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

ll int max ( ll int a , ll int b ) {
	return a > b ? a : b;
}

int main ( int argc , char * argv[] ) {

	ll int t , z;
	ll int a , b;
	ll int sum = 0;

	scanint(t);

	scanint(a);

	for ( z = 2 ; z <= t ; z++ ) {
		scanint(b);
		sum += max(a,b);
		a = b;
	}
	printf("%lld\n" , sum);
	return 0;
}

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

#define SIZE 2020

ll int hash[SIZE];

int main ( int argc , char * argv[] ) {

	int t , z;
	scanf("%d" , &t);
	for ( z = 1 ; z <= t ; z++ ) {
		ll int x , n;
		scanint(x);
		scanint(n);

		for ( int i = 0 ; i < 2020 ; i++ )
			hash[i] = 0;

		ll int temp;
		ll int count = 0;

		for ( int i = 0 ; i < n ; i++ ) {
			scanint(temp);

			if ( x < temp )
				continue;

			count += ( hash[x-temp] );
			hash[temp] ++;

		}
		printf("%d. %lld\n" , z,count);
	}
	return 0;
}

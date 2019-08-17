#include <iostream>
#include <cstdio>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

map<int,int> prime_factors( long long int n ) {
	map<int,int> fact;

	while ( n % 2 == 0 ) {
		if ( fact.count(2) == 0 ) {
			fact[2] = 0;
		}
		fact[2]++;
		n /= 2;
	}

	for ( int i = 3; i <= sqrt(n) ; i+=2 ) {
		while ( n % i == 0 ) {
			if ( fact.count(i) == 0 ) {
				fact[i] = 0;
			}
			fact[i]++;
			n /= i;
		}
	}

	if ( n > 2 ) {
		if ( fact.count(n) == 0 ) {
			fact[n] = 0;
		}
		fact[n]++;
	}

	return fact;
}

int readline( char * str ) {

	int i = 0;
	char ch;
	while ( (ch = getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int gcd ( int a , int b ) {

	while ( a != b ) {
		if ( a > b )
			a = a - b;
		else if ( b > a )
			b = b - a;
	}
	return a;
}

int main( int argc , char * argv[] ) {

	int t;
	char s[128];

	scanf("%d" , &t);
	getchar();

	while ( t-- ) {
		readline(s);

		int i;
		for ( i = 0 ; s[i] != '\0' ; i++ ) {
			if ( s[i] == '.' )
				break;
		}
		if ( s[i] == '.' ) {
			int power = 1;
			int num = 0;
			i++;
			for ( ; s[i] != '\0' ; i++ ) {
				num = num * 10 + (s[i]-'0');
				power *= 10;
			}
			printf("%d\n" , power/gcd(num,power) );
		}
		else {
			printf("1\n");
		}

	}
	return 0;
}

/*
 * BAT3.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Arpit Bhayani
 */

#include <map>
#include <cmath>
#include <set>
#include <cstring>
#include <stack>
#include <vector>
#include <queue>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>

using namespace std;

#define si(x) scanf("%d" , &x)
#define sl(x) scanf("%ld" , &x)
#define sll(x) scanf("%lld" , &x)
#define sc(x) scanf("%c" , &x)
#define ss(x) scanf("%s" , &x)

#define pi(x) printf("%d\n" , x)
#define pl(x) printf("%ld\n" , x)
#define pll(x) printf("%lld\n" , x)
#define pc(x) printf("%c\n" , x)
#define ps(x) printf("%s\n" , x)

#define fup(i,a,b) for(int i=a;i<b;i++)
#define fdn(i,a,b) for(int i=a;i>=b;i--)

#define DEBUG 0
#define gc getchar
#define ll long long

#define SEPERATOR " : "

#define trace1(a) cout << #a << SEPERATOR << a << endl;
#define trace2(a,b) cout << #a << SEPERATOR << a << SEPERATOR << #b << SEPERATOR << b << endl;
#define trace3(a,b,c) cout << #a << SEPERATOR << a << SEPERATOR << #b << SEPERATOR << b << #c << SEPERATOR << c << endl;

void scanint(ll int &x) {
	register ll int c = gc();
	x = 0;
	for (; (c < 48 || c > 57); c = gc())
		;
	for (; c > 47 && c < 58; c = gc()) {
		x = (x << 1) + (x << 3) + c - 48;
	}
}

int readline(char * str) {

	int i = 0;
	char ch;
	while ((ch = getchar()) != '\n') {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

#define ASIZE 1010
int array[ASIZE];
int lis[ASIZE];

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		int n, m;
		si(n);
		si(m);

		for (int i = 0; i < n; i++) {
			si(array[i]);
			lis[i] = 1;
		}

		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (array[j] > array[i] || j == m) {
					lis[i] = max(lis[i], lis[j] + 1);
				}
			}
		}

		int result = lis[0];
		for (int i = 1; i < n; i++) {
			result = max(result, lis[i]);
		}
		pi(result);
	}
	return 0;
}

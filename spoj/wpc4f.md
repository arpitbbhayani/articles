```c
/*
 * WPC4F.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: Arpit Bhayani
 */

#include <map>
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

#define ASIZE 10

ll int min( ll int a, ll int b) {
	if (a < b)
		return a;
	return b;
}

ll int min3( ll int a, ll int b, ll int c) {
	return min(a, min(b, c));
}

ll int array[25][3];

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {

		int n;
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%lld%lld%lld", &array[i][0], &array[i][1], &array[i][2]);
		}

		for (int i = 1; i < n; i++) {
			array[i][0] = array[i][0] + min(array[i - 1][1], array[i - 1][2]);
			array[i][1] = array[i][1] + min(array[i - 1][0], array[i - 1][2]);
			array[i][2] = array[i][2] + min(array[i - 1][0], array[i - 1][1]);
		}

		printf("%lld\n",
				min3(array[n - 1][0], array[n - 1][1], array[n - 1][2]));
	}
	return 0;
}
```

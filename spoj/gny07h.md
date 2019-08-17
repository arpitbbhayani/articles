```c
/*
 * GNY07H.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: Arpit Bhayani
 */

#include<cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define sr(x) ((x)*(x))
double pi = acos(-1.0);

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

int main(int argc, char * argv[]) {
	int cas, r = 1;
	scanf("%d", &cas);
	while (cas--) {
		double ans = 1;
		int n = 4;
		int m;
		scanf("%d", &m);
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= m / 2; j++) {
				ans *= sr( cos(pi*i/(n+1)) ) + sr(cos(pi * j / (m + 1)));
				ans *= 4;
			}
		}
		printf("%d %.0f\n", r++, ans);
	}
}
```

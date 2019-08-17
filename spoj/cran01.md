/*
 * CRAN01.cpp
 *
 *  Created on: Jun 10, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

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

	int t;
	scanf("%d", &t);
	while (t--) {
		int n, m;
		int a, b;
		scanf("%d%d", &n, &m);
		scanf("%d%d", &a, &b);

		int t1, t2, t3, t4;
		t1 = abs(a - 1) + abs(b - 1);
		t2 = abs(a - 1) + abs(m - b);
		t3 = abs(m - b) + abs(n - a);
		t4 = abs(b - 1) + abs(n - a);

		printf("%d\n", max(t1, max(t2, max(t3, t4))));
	}
	return 0;
}

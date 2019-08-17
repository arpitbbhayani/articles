/*
 * GIRLSNBS.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: Arpit Bhayani
 */

#include <cmath>
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

	int g, b;
	scanf("%d%d", &g, &b);
	while (g != -1 && b != -1) {

		int r = (max(g,b)%(min(g,b)+1));
		if ( r == 0 )
			cout << (max(g,b)/(min(g,b)+1)) << endl;
		else
			cout << (max(g,b)/(min(g,b)+1)) + 1 << endl;

		scanf("%d%d", &g, &b);
	}
	return 0;
}

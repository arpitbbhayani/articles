```c
/*
 * SAMER08F.cpp
 *
 *  Created on: Jun 5, 2014
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

	long long int n;
	scanf("%lld", &n);

	while (n) {
		printf("%lld\n", (n * (n + 1) * (2 * n + 1)) / 6);
		scanf("%lld", &n);
	}

	return 0;
}
```

```
/*
 * BC.cpp
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

	int t, k = 0;
	scanf("%d", &t);
	while (t--) {

		k++;

		double a, b, c;
		ll int ans1 = 0, ans2 = 0;

		scanf("%lf%lf%lf", &a, &b, &c);

		ans1 = (a * b * c) - 1;

		while (a > 1) {
			ans2++;
			a /= 2;
		}

		while (b > 1) {
			ans2++;
			b /= 2;
		}
		while (c > 1) {
			ans2++;
			c /= 2;
		}

		printf("Case #%d: %lld %lld\n", k, ans1, ans2);
	}
	return 0;
}
```

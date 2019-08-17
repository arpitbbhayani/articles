```
/*
 * MAIN74.cpp
 *
 *  Created on: Jun 22, 2014
 *      Author: Arpit Bhayani
 */

#include <stack>
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

#define MOD 1000000007

ll int fib(ll int n) {

	n--;
	stack<int> s;

	ll int m[2][2] = { { 1LL, 1LL }, { 1LL, 0LL } };
	ll int f[2][2] = { { 1LL, 1LL }, { 1LL, 0LL } };

	while (n) {
		s.push(n & 1);
		n /= 2;
	}

	s.pop();

	ll int w, x, y, z;
	while (!s.empty()) {

		w = ((f[0][0] * f[0][0]) % MOD + (f[0][1] * f[1][0]) % MOD) % MOD;
		x = ((f[0][0] * f[0][1]) % MOD + (f[0][1] * f[1][1]) % MOD) % MOD;
		y = ((f[1][0] * f[0][0]) % MOD + (f[1][1] * f[1][0]) % MOD) % MOD;
		z = ((f[1][0] * f[0][1]) % MOD + (f[1][1] * f[1][1]) % MOD) % MOD;
		f[0][0] = w;
		f[0][1] = x;
		f[1][0] = y;
		f[1][1] = z;

		if (s.top() == 1) {

			w = ((f[0][0] * m[0][0]) % MOD + (f[0][1] * m[1][0]) % MOD) % MOD;
			x = ((f[0][0] * m[0][1]) % MOD + (f[0][1] * m[1][1]) % MOD) % MOD;
			y = ((f[1][0] * m[0][0]) % MOD + (f[1][1] * m[1][0]) % MOD) % MOD;
			z = ((f[1][0] * m[0][1]) % MOD + (f[1][1] * m[1][1]) % MOD) % MOD;
			f[0][0] = w;
			f[0][1] = x;
			f[1][0] = y;
			f[1][1] = z;
		}

		s.pop();
	}

	return f[0][0];
}

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		ll int x;
		scanf("%lld", &x);

		if (x == 0)
			printf("0\n");
		else if (x == 1)
			printf("2\n");
		else
			printf("%lld\n", fib(x + 3) % MOD);
	}
	return 0;
}
```

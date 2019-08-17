```c
/*
 * CSQUARE.cpp
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

ll int a, m, bsize = 0;
char b[250];

int readvars() {

	a = m = bsize = 0;

	char ch;

	while ((ch = getchar()) != ' ') {
		a = a * 10 + (ch - '0');
	}

	while ((ch = getchar()) != ' ') {
		b[bsize++] = ch;
	}

	while ((ch = getchar()) != '\n') {
		m = m * 10 + (ch - '0');
	}

	return 0;
}

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	getchar();

	while (t--) {

		ll int result = 1;

		readvars();

		a %= m;

		//cout << a << " " << m << endl;

		for (int i = bsize - 1; i >= 0; i--) {

			if (b[i] == '1') {
				result *= a;
			} else if (b[i] == '2') {
				result *= (a * a);
			}

			result %= m;

			//cout << "result : " << result << endl;
			a = (a * a * a) % m;
		}

		printf("%d\n", (int) result);
	}
	return 0;
}
```

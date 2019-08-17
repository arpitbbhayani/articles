```c
/*
 * BWIDOW.cpp
 *
 *  Created on: Jun 3, 2014
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

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		ll int n, maxi = 0, maxo = 0, index = 0;
		scanint(n);
		for (ll int i = 0; i < n; i++) {
			ll int x, y;
			scanint(x);
			scanint(y);
			if (x > maxi) {
				maxi = x;
				index = i + 1;
			} else if (y > maxo) {
				maxo = y;
			}
		}
		if (maxi > maxo) {
			cout << index << endl;
		} else {
			cout << -1 << endl;
		}
	}
	return 0;
}
```

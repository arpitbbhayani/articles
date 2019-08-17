```c
/*
 * IITWPC4A.cpp
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

char str[100010];

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		ll int m, n;
		scanf("%s", str);
		scanint(m);
		scanint(n);

		if (m <= n) {
			ll int result = 0, length = 0;
			ll int count = 0;

			for (int i = 0; str[i] != '\0'; i++) {
				if (str[i] == 'a') {
					count++;
				} else {
					result += (count / m) * n;
					result += count % m;
					result++;
					count = 0;
				}
				length++;
			}

			result += (count / m) * n;
			result += count % m;

			cout << length << " " << result << endl;

		} else {

			ll int result = 0, length = 0;
			ll int count = 0;

			for (int i = 0; str[i] != '\0'; i++) {
				if (str[i] == 'a') {
					count++;
				} else {
					result += (count / m) * n;
					result += count % m;
					result++;
					count = 0;
				}
				length++;
			}

			result += (count / m) * n;
			result += count % m;

			cout << result << " " << length << endl;

		}

	}
	return 0;
}
```

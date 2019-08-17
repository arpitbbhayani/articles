```c
/*
 * ALIEN2.cpp
 *
 *  Created on: May 29, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG 0
#define gc getchar

void scanint(int &x) {
	register int c = gc();
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

int min(int a, int b) {
	return a < b ? a : b;
}

int main(int argc, char * argv[]) {

	int n, k;

	scanint(n);
	scanint(k);

	int a[n], b[n];

	for (int i = 0; i < n; i++) {
		scanint(a[i]);
	}
	for (int i = 0; i < n; i++) {
		scanint(b[i]);
	}

	int ns = n , count , i;

	for (i = 1; i < n; i++) {

		int ta = a[i];

		a[i] = min(a[i - 1] + a[i], b[i - 1] + b[i] + a[i]);
		b[i] = min(b[i - 1] + b[i], a[i - 1] + ta + b[i]);

		if ( min(a[i],b[i]) > k ) {
			break;
		}

	}

	if ( i != n ) {
		ns = i;
		count = min(a[i - 1], b[i - 1]);
	}
	else {
		ns = n;
		count = min(a[n - 1], b[n - 1]);
	}

	cout << ns << " " << count << endl;

	return 0;
}
```

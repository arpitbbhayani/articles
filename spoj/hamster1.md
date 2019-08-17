```
/*
 * HAMSTER1.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

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

	int T, v, k1, k2;
	double theta, points, pi = 3.14159265;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		cin >> v >> k1 >> k2;
		if (k2 == 0) {
			theta = pi / 4.0;
		} else if (k1 == 0) {
			theta = pi / 2.0;
		} else {
			theta = atan(-(double) 4.0 * k1 / (double) k2) / 2;
			if (theta < 0)
				theta += pi / 2.0;
		}

		points = ((double) v * v) / 10.0
				* (k1 * sin(2.0 * theta) + k2 * sin(theta) * sin(theta) / 2.0);
		printf("%.3lf %.3lf\n", theta, points);
		//cout << points << endl;
	}
	return 0;
}
```

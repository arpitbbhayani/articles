```c
/*
 * HISTOGRA.cpp
 *
 *  Created on: Jun 19, 2014
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

ll int array[100001];

ll int hist(int t) {

	stack<ll int> s;
	ll int maxa = 0, tp, area;

	int i = 0;

	while (i < t) {
		if (s.empty() || array[i] >= array[s.top()]) {
			s.push(i++);
		} else {
			tp = s.top();
			s.pop();

			area = array[tp] * (s.empty() ? i : i - s.top() - 1);

			if (area > maxa)
				maxa = area;

		}
	}

	while (!s.empty()) {
		tp = s.top();
		s.pop();

		area = array[tp] * (s.empty() ? i : i - s.top() - 1);
		if (area > maxa)
			maxa = area;
	}

	return maxa;
}

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t != 0) {

		for (int i = 0; i < t; i++) {
			scanf("%lld", &array[i]);
		}

		printf("%lld\n", hist(t));

		scanf("%d", &t);
	}
	return 0;
}
```

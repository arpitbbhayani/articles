```c
/*
 * CTGAME.cpp
 *
 *  Created on: Jun 11, 2014
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

int array[1001][1001];

int maxarea(int * hist, int n) {

	/*printf("HISTOGRAM : ");
	 for ( int j = 0 ; j < n ; j++ ) {
	 printf("%d " , hist[j]);
	 }
	 printf("\n");*/

	stack<int> s;
	int maxarea = 0, tp, area, i = 0;
	while (i < n) {
		if (s.empty() || hist[s.top()] <= hist[i]) {
			s.push(i++);
		} else {
			tp = s.top();
			s.pop();
			area = hist[tp] * (s.empty() ? i : i - s.top() - 1);
			if (area > maxarea)
				maxarea = area;
		}
	}

	while (!s.empty()) {
		tp = s.top();
		s.pop();
		area = hist[tp] * (s.empty() ? i : i - s.top() - 1);
		if (area > maxarea)
			maxarea = area;
	}

	return maxarea;
}

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		char ch;
		int n, m;
		scanf("%d%d", &n, &m);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> ch;
				if (ch == 'R') {
					array[i][j] = 0;
				} else {
					array[i][j] = 1;
				}
			}
		}

		for (int i = 1; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (array[i][j] == 1)
					array[i][j] += array[i - 1][j];
			}
		}

		int maxa = 0;
		for (int i = 0; i < n; i++) {
			int temp = maxarea(array[i], m);
			if (temp > maxa)
				maxa = temp;
		}

		printf("%lld\n", (ll int) maxa * 3LL);

	}
	return 0;
}
```

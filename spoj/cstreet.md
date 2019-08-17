/*
 * CSTREET.cpp
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

int readline(char * str) {

	int i = 0;
	char ch;
	while ((ch = getchar()) != '\n') {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

struct edge {
	int u, v, c;
};

struct edge e[300000];

int compar(const void * a, const void * b) {
	return ((struct edge *) a)->c > ((struct edge *) b)->c;
}

int v[1001];

int getparent(int n) {
	while (v[n] != n) {
		n = getparent(v[n]);
	}
	return n;
}

void join(int a, int b) {
	if (a > b) {
		v[a] = b;
	} else {
		v[b] = a;
	}
}

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {

		int p, n, m;
		scanf("%d%d%d", &p, &n, &m);

		for (int i = 1; i <= n; i++) {
			v[i] = i;
		}

		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].c);
		}

		qsort(e, m, sizeof(struct edge), compar);

		ll int cost = 0;
		int count = 1;
		for (int i = 0; i < m; i++) {
			int u = getparent(e[i].u);
			int v = getparent(e[i].v);

			if (u != v) {

				cost += e[i].c;

				join(u, v);

				count++;
				if (count == n)
					break;
			}
		}

		printf("%lld\n", cost * p);
	}
	return 0;
}

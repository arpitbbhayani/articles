```
/*
 * HIGHWAYS.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: Arpit Bhayani
 */

#include <queue>
#include <climits>
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

#define SIZE 100001

int dist[SIZE];

struct edge {
	int v;
	int w;
};


bool operator <(struct edge a, struct edge b) {
	return a.w < b.w;
}

vector<edge> node[SIZE];

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {

		priority_queue< edge > q;

		int n, m, s, e;

		scanf("%d%d%d%d", &n, &m, &s, &e);

		for (int i = 1; i <= n; i++) {
			node[i].clear();
			dist[i] = INT_MAX;
		}

		for (int i = 0; i < m; i++) {
			int a, b, w;
			scanf("%d%d%d", &a, &b, &w);
			node[a].push_back((edge ) { b, w });
			node[b].push_back((edge ) { a, w });
		}

		dist[s] = 0;
		q.push((edge ) { s, 0 });

		while (!q.empty()) {
			edge p = q.top();
			q.pop();

			for (int i = 0; i < node[p.v].size(); i++) {
				edge k = node[p.v][i];
				if (dist[p.v] + k.w < dist[k.v]) {
					dist[k.v] = dist[p.v] + k.w;
					q.push(k);
				}
			}
		}

		if (dist[e] == INT_MAX) {
			printf("NONE\n");
		} else {
			printf("%d\n", dist[e]);
		}

	}
	return 0;
}
```

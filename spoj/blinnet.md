/*
 * BLINNET.cpp
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
	int u, v;
	int c;
};

int array[10010];
struct edge e[10000000];

int compar(const void * a, const void * b) {
	return ((struct edge *) a)->c > ((struct edge *) b)->c;
}

int getparent(int n) {
	while (array[n] != n) {
		n = getparent(array[n]);
	}
	return n;
}

void join(int a, int b) {
	if (a < b) {
		array[b] = a;
	} else {
		array[a] = b;
	}
}

int main(int argc, char * argv[]) {

	char temp[20];
	int t;
	scanf("%d", &t);
	while (t--) {

		int count_edge = 0;
		int n;
		scanf("%d", &n);
		getchar();

		for (int j = 1; j <= n; j++) {

			array[j] = j;

			getchar();
			readline(temp);

			int k, a, b;
			scanf("%d", &k);

			for (int i = 0; i < k; i++) {
				e[count_edge].u = j;
				scanf("%d%d", &e[count_edge].v, &e[count_edge].c);
				count_edge++;
			}
		}

		qsort(e, count_edge, sizeof(struct edge), compar);

		/*for ( int i = 0 ; i < count_edge ; i++ ) {
		 printf("(%d,%d) = %d\n" , e[i].u,e[i].v,e[i].c);
		 }*/

		int total_cost = 0;
		int vertices_done = 1;

		for (int i = 0; i < count_edge; i++) {

			int u = getparent(e[i].u);
			int v = getparent(e[i].v);

			//printf("For u = %d and v = %d , parent_u = %d and parent_v = %d\n",
			//		e[i].u, e[i].v, u, v);

			if (u != v) {

				vertices_done++;
				total_cost += e[i].c;

				//printf("Joining %d and %d \n", u, v);
				join(u, v);

				if (vertices_done == n)
					break;
			}
		}

		cout << total_cost << endl;

	}
	return 0;
}

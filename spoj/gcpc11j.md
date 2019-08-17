/*
 * GCPC11J.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: Arpit Bhayani
 */

#include <list>
#include <climits>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#define DEBUG 0
#define gc getchar
#define ll long long

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

#define SIZE 100001

list<int> node[SIZE];
int dfs[SIZE];

int dfs_function(int start, int n) {

	for (int i = 0; i < n; i++) {
		dfs[i] = -1;
	}

	stack<int> s;
	dfs[start] = 0;

	s.push(start);

	while (!s.empty()) {
		int parent = s.top();
		s.pop();

		for (list<int>::iterator itr = node[parent].begin();
				itr != node[parent].end(); itr++) {
			int child = *itr;

			if (dfs[child] != -1)
				continue;

			dfs[child] = dfs[parent] + 1;
			s.push(child);
		}
	}

	int max = INT_MIN;
	for (int i = 0; i < n; i++) {
		if (dfs[i] > max)
			max = dfs[i];
	}

	return max;

}

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		int n, a, b;
		//scanf("%d", &n);
		scanint(n);

		for (int i = 0; i < n; i++) {
			node[i].clear();
		}

		for (int i = 0; i < n - 1; i++) {
			//scanf("%d%d", &a, &b);
			scanint(a);
			scanint(b);
			node[a].push_back(b);
			node[b].push_back(a);
		}

		int min = INT_MAX;
		for (int i = 0; i < n; i++) {
			int max = dfs_function(i, n);
			if (max < min)
				min = max;
		}

		printf("%d\n", min);

	}
	return 0;
}

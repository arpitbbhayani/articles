```
/*
 * HERDING.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <vector>
#include <stack>

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

vector<int> nodes[1010*1010];
char str[1010][1010];
int visited[1010 * 1010];
stack<int> s;

void traverse(int n, int m, vector<int> * nodes) {

	int size = n * m;

	/*for (int i = 0; i < size; i++) {
	 cout << "Adjecency list of " << i << " : ";
	 for (vector<int>::iterator itr = nodes[i].begin();
	 itr != nodes[i].end(); itr++) {
	 cout << *itr << " ";
	 }
	 cout << endl;
	 }*/

	int count = 0;

	for (int i = 0; i < size; i++) {

		if (visited[i] == 1)
			continue;

		count++;

		s.push(i);
		visited[i] = 1;

		while (!s.empty()) {
			int parent = s.top();
			s.pop();

			for (vector<int>::iterator itr = nodes[parent].begin();
					itr != nodes[parent].end(); itr++) {
				int child = *itr;

				if (visited[child] == 1)
					continue;

				visited[child] = 1;
				s.push(child);

				//cout << child << " ";

			}

		}
	}

	cout << count << endl;

}

int main(int argc, char * argv[]) {

	int n, m;
	char ch;

	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; i++) {
		scanf("%s", str[i]);
	}

	int size = n * m;
	int s, t;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {

			s = i * m + j;

			switch (str[i][j]) {
			case 'S':

				if (i + 1 < n) {
					t = (i + 1) * m + j;
					nodes[s].push_back(t);
					nodes[t].push_back(s);
				}

				break;
			case 'W':

				if (j - 1 < m) {
					t = (i) * m + j - 1;
					nodes[s].push_back(t);
					nodes[t].push_back(s);
				}

				break;
			case 'N':

				if (i - 1 >= 0) {
					t = (i - 1) * m + j;
					nodes[s].push_back(t);
					nodes[t].push_back(s);
				}

				break;
			case 'E':
				if (j + 1 >= 0) {
					t = (i) * m + j + 1;
					nodes[s].push_back(t);
					nodes[t].push_back(s);
				}
				break;
			}
		}
	}

	traverse(n, m, nodes);

	return 0;
}
```

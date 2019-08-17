```c
/*
 * ELEVTRBL.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: Arpit Bhayani
 */

#include <queue>
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

int visited[1000010];

int main(int argc, char * argv[]) {

	int f, s, g, u, d;
	cin >> f >> s >> g >> u >> d;
	queue<pair<int, int> > q;

	q.push(make_pair(s, 0));

	while (!q.empty()) {

		int curfloor = q.front().first;
		int curlevel = q.front().second;
		q.pop();

		if (visited[curfloor] == 1) {
			continue;
		}

		visited[curfloor] = 1;

		if (curfloor == g) {
			cout << curlevel << endl;
			return 0;
		}

		if (curfloor + u <= f) {
			q.push(make_pair(curfloor + u, curlevel + 1));
		}

		if (curfloor - d > 0) {
			q.push(make_pair(curfloor - d, curlevel + 1));
		}

	}

	cout << "use the stairs" << endl;

	return 0;
}
```

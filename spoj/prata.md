```
/*
 * PRATA.cpp
 *
 *  Created on: Jun 22, 2014
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

int rank[51];
int mult[51];

int main(int argc, char * argv[]) {

	int t;
	int array[51];

	scanf("%d", &t);
	while (t--) {

		priority_queue<int, std::vector<int>, std::greater<int> > q;
		int count = 0;
		int p, l;

		scanf("%d%d", &p, &l);

		for (int i = 0; i < l; i++) {
			scanf("%d", &rank[i]);
			array[i] = rank[i];
			mult[i] = 1;

			q.push(rank[i]);
		}

		int time = 0;

		while (1) {
			//cout << "IN LOOP : count " << count << " and p = " << p << endl;

			time = q.top();
			q.pop();

			while (!q.empty() && q.top() == time)
				q.pop();

			for (int i = 0; i < l; i++) {
				if (array[i] == time) {
					count++;
					mult[i]++;
					array[i] = array[i] + rank[i] * mult[i];
					q.push(array[i]);
				}
			}

			if (count >= p)
				break;

		}

		printf("%d\n", time);

	}
	return 0;
}
```

```c
/*
 * DCEPC206.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

#define DEBUG 0
#define gc getchar
#define ll long long

long long int count = 0;

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

void merge(int * array, int low, int mid, int high) {

	queue<int> a, b, c;

	for (int i = low; i <= mid; i++) {
		a.push(array[i]);
	}

	for (int i = mid + 1; i <= high; i++) {
		b.push(array[i]);
	}

	while (!a.empty() && !b.empty()) {

		if (a.front() < b.front()) {
			c.push(a.front());
			count += (long long) a.front() * b.size();
			a.pop();
		} else {
			c.push(b.front());
			b.pop();
		}
	}

	while (!a.empty()) {
		c.push(a.front());
		a.pop();
	}

	while (!b.empty()) {
		c.push(b.front());
		b.pop();
	}

	int i = low;
	while (!c.empty()) {
		array[i++] = c.front();
		c.pop();
	}
}

void merge_sort(int * array, int low, int high) {

	if (low < high) {

		int mid = (low + high) / 2;
		merge_sort(array, low, mid);
		merge_sort(array, mid + 1, high);
		merge(array, low, mid, high);
	}
}

int main(int argc, char * argv[]) {

	int t, n;
	int array[100000];

	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &array[i]);
		}
		count = 0;

		merge_sort(array, 0, n - 1);
		printf("%lld\n", count);
	}

	return 0;
}
```

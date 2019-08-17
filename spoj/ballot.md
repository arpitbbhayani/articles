```
/*
 * BALLOT.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <climits>

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

int array[500010];

int num_ballot(int val, int n) {
	int count = 0;

	for (int i = 0; i < n; i++) {
		if ( array[i] > val ) {
			count += (array[i]/val);
			if ( array[i] % val > 0 )
				count++;
		}
		else {
			count++;
		}
	}

	return count;
}

int search(int low, int high, int b, int n) {

	low = 1;
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (num_ballot(mid, n) <= b) {
			high = mid;
		} else {
			low = mid + 1;
		}
	}
	return low;
}

int main(int argc, char * argv[]) {

	int n, b;
	scanf("%d%d", &n, &b);
	while (n != -1 && b != -1) {
		int min = INT_MAX, max = 0;

		for (int i = 0; i < n; i++) {
			scanf("%d", &array[i]);
			if (array[i] < min) {
				min = array[i];
			}
			if (array[i] > max) {
				max = array[i];
			}
		}

		printf("%d\n", search(min, max, b, n));

		scanf("%d%d", &n, &b);
	}
	return 0;
}
```

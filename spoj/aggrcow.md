```
/*
 * AGGRCOW.cpp
 *
 *  Created on: May 29, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG 0
#define gc getchar

void scanint(int &x) {
	register int c = gc();
	x = 0;
	for (; (c < 48 || c > 57); c = gc())
		;
	for (; c > 47 && c < 58; c = gc()) {
		x = (x << 1) + (x << 3) + c - 48;
	}
}

int compar(const void * a, const void * b) {
	return (*(int *) a) - (*(int *) b);
}

int can_adjust(int * array, int n, int k, int x) {

	int c = 1;
	int last = array[0];

	for (int i = 1; i < n; i++) {
		if (array[i] - last >= x) {
			c++;

			last = array[i];

			if (c == k)
				return 1;
		}
	}

	return 0;
}

int search(int * array, int n, int k) {

	int low = 0;
	int high = array[n - 1];

	while (low < high) {
		int mid = low + (high - low) / 2;

		if (can_adjust(array, n, k, mid) == 1) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}

	return low - 1;
}

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		int n, k;
		scanint(n);
		scanint(k);
		int array[n];

		for (int i = 0; i < n; i++) {
			scanint(array[i]);
		}

		qsort(array, n, sizeof(int), compar);

		cout << search(array, n, k) << endl;

	}
	return 0;
}
```

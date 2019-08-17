```
/*
 * CLASSICO.cpp
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

int array[2010];

int index_of_max(int left, int right) {
	int max = left;
	for (int i = left + 1; i <= right; i++) {
		if (array[i] > array[max])
			max = i;
	}
	return max;
}

int main(int argc, char * argv[]) {

	int t, casenum = 1;
	scanf("%d", &t);
	while (t--) {

		int n;
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%d", &array[i]);
		}

		printf("Case %d: ", casenum);

		if (n < 11) {
			printf("go home!\n");

		} else {

			int left = 0, right = n - 11, index;

			for (int i = 0; i < 10; i++) {
				index = index_of_max(left, right);
				printf("%d ", array[index]);
				left = index + 1;
				right++;
			}

			index = index_of_max(left, right);
			printf("%d\n", array[index]);

		}

		casenum++;

	}
	return 0;
}
```

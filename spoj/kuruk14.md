```c
/*
 * KURUK14.cpp
 *
 *  Created on: Jun 21, 2014
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

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		int n, x;

		scanf("%d", &n);

		int * array = (int *) calloc(n, sizeof(int));

		for (int i = 0; i < n; i++) {
			scanf("%d", &x);

			if (array[x] == 0) {
				array[x] = 1;
			} else if (array[x] == 1 && array[n - 1 - x] == 0) {
				array[n - 1 - x] = 1;
			}

		}

		int i = 0;
		for (i = 0; i < n; i++) {
			if (array[i] == 0) {
				break;
			}
		}

		if (i == n) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}

		free(array);

	}
	return 0;
}
```

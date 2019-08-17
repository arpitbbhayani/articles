```c
/*
 * ACS.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG 0

int main(int argc, char * argv[]) {
	int r[1234];
	int c[5678];
	for (int i = 0; i < 1234; i++) {
		r[i] = i;
	}
	for (int j = 0; j < 5678; j++) {
		c[j] = j;
	}

	char ch;

	int x;
	int y;
	int temp;
	int z;
	int i;
	while (cin >> ch) {
		switch (ch) {
		case 'R':
			cin >> x >> y;
			temp = r[x - 1];
			r[x - 1] = r[y - 1];
			r[y - 1] = temp;
			break;
		case 'C':
			cin >> x >> y;
			temp = c[x - 1];
			c[x - 1] = c[y - 1];
			c[y - 1] = temp;
			break;
		case 'Q':
			cin >> x >> y;
			printf("%d\n", r[x - 1] * 5678 + c[y - 1] + 1);
			break;
		case 'W':
			cin >> z;
			x = (z - 1) / 5678;
			y = (z - 1) % 5678;
			for (i = 0; i < 1234; i++) {
				if (r[i] == x)
					printf("%d ", i + 1);
			}
			for (i = 0; i < 5678; i++) {
				if (c[i] == y)
					printf("%d\n", i + 1);
			}
			break;
		}
	}

	return 0;
}
```

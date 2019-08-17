```
/*
 * CRSCNTRY.cpp
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

int array[2002][2002];
int a[2002], b[2002];

int lcs(int n, int m) {

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < m + 1; j++) {
			if (i == 0 || j == 0)
				array[i][j] = 0;
			else if (a[i - 1] == b[j - 1]) {
				array[i][j] = array[i - 1][j - 1] + 1;
			} else {
				array[i][j] = max(array[i - 1][j], array[i][j - 1]);
			}
		}
	}

	return array[n][m];
}

int main(int argc, char * argv[]) {

	int t, temp;
	scanf("%d", &t);
	while (t--) {

		int n = 0, m = 0;

		while (1) {
			scanint(temp);

			if (temp == 0)
				break;

			a[n++] = temp;
		}

		int max = -1;
		while (1) {
			int val;
			scanint(val);

			if (val == 0)
				break;

			b[0] = val;
			m = 1;

			while (1) {
				scanint(val);
				if (val == 0)
					break;
				b[m++] = val;
			}

			int templcs = lcs(n, m);

			if ( templcs > max )
				max = templcs;
		}

		printf("%d\n" , max);

	}
	return 0;
}
```

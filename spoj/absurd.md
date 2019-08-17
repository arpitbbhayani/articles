```
/*
 * ABSURD.c
 *
 *  Created on: Mar 8, 2014
 *      Author: Arpit Bhayani
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0
#define gc getchar

int readline(char * str) {

	int i = 0;
	char ch;
	while ((ch = getchar()) >= '\n') {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int nzero(int n1) {
	int n = n1;
	int val = 1;

	while (n != 0) {
		if (n % 10 == 0) {
			val *= 10;
			n = n / 10;
		} else
			break;
	}
	return val;
}


int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		int c;
		scanf("%d", &c);

		int lower = ceil((c * 0.95));
		int upper = ((c * 1.05));

		int v = absurdity(c);

#if DEBUG
		printf("NUMBER : %d ", c, v);
#endif

		/*int i = 0;
		for (i = lower; i <= upper; i++) {
			//printf("absurdity of %d = %d\n", i, absurdity(i));
			if (absurdity(i) < v) {
				break;
			}
		}

		if (i == upper + 1)
			printf("not absurd\n");
		else
			printf("absurd\n");

		*/

#if DEBUG
		printf("lower : %d and upper : %d\n", lower, upper);
#endif

		int numzero = nzero(c);
		//printf("Num zero = %d\n", numzero);
		int k = c / numzero;
		int l, m;

		if ((k % 10) <= 5) {
			l = k - (k % 10);
			m = k + (5 - (k % 10));

			l *= numzero;
			m *= numzero;

		} else {
			l = k - ((k % 10) - 5);
			m = k + (10 - (k % 10));

			l *= numzero;
			m *= numzero;

		}

#if DEBUG
		printf("l = %d and m = %d and c = %d\n", l, m, c);
#endif

		if ( ((l != c) && (lower <= l && upper >= l)) || ((m != c) && ((lower <= m && upper >= m) )))
			printf("absurd\n");
		else
			printf("not absurd\n");

	}
	return 0;
}

int absurdity(int n1) {

	int n = n1;
	int val = 1;

	while (n != 0) {
		if (n % 10 == 0) {
			n = n / 10;
		} else
			break;
	}

	int d = n % 10;

	int a = 0;
	while (n != 0) {
		a++;
		n = n / 10;
	}

	if (d == 5)
		val = 2 * a - 1;
	else
		val = 2 * a;

	return val;
}
```

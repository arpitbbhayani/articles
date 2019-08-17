```
/*
 * CIRCLE_E.c
 *
 *  Created on: Mar 6, 2014
 *      Author: Arpit Bhayani
 */

/**
 * http://en.wikipedia.org/wiki/Descartes'_theorem
 * The larger a circle, the smaller is the magnitude of its curvature, and vice versa.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0

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

		double r1, r2, r3;
		double curvature1, curvature2, curvature3;

		double curvature4, r4;

		scanf("%lf%lf%lf", &r1, &r2, &r3);

		curvature1 = 1 / r1;
		curvature2 = 1 / r2;
		curvature3 = 1 / r3;

		curvature4 = curvature1 + curvature2 + curvature3
				+ 2
						* sqrt(
								curvature1 * curvature2
										+ curvature2 * curvature3
										+ curvature3 * curvature1);

		r4 = 1/curvature4;

		printf("%.6lf\n" , r4);
	}

	return 0;
}
```

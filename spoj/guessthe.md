```
/*
 * GUESSTHE.c
 *
 *  Created on: Mar 6, 2014
 *      Author: Arpit Bhayani
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

long long int gcd(long long int a, long long int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

long long int lcm(long long int a, long long int b) {

	if (a < b) {
		int t = a;
		a = b;
		b = t;
	}

	long long int lcm = (a * b) / gcd(a, b);
	return lcm;
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

	long long int i, flag = 0;
	char ch;
	long long int number = 0;

	while (1) {

		i = 1;
		int array[21];

		for (i = 0; i < 21; i++) {
			array[i] = 0;
		}

		i = 1;
		ch = getchar();
		if (ch == '*') {
			break;
		} else if (ch == 'N') {
			array[i] = 1;
		}

		i++;
		number = 1;

		while ((ch = getchar()) != '\n') {
			if (ch == 'Y') {
				number = lcm(number, i);
			} else {
				array[i] = 1;
			}
			i++;
		}

		for (i = 1; i < 21; i++) {
			if (array[i] == 1) {
				if (number % i == 0) {
					number = -1;
					break;
				}
			}
		}

		printf("%lld\n", number);

	}
	return 0;
}
```

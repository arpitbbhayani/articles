```
/*
 * PRIME1.c
 *
 *  Created on: Mar 8, 2014
 *      Author: Arpit Bhayani
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0
#define gc getchar
#define ll long long

void scanint(int *x) {
	register int c = gc();
	*x = 0;
	for (; (c < 48 || c > 57); c = gc())
		;
	for (; c > 47 && c < 58; c = gc()) {
		*x = (*x << 1) + (*x << 3) + c - 48;
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

#define SIZE 32000
char array[SIZE];
unsigned int prime[SIZE];

int sieve32000() {

	unsigned int i, j;
	int index = 0;

	array[0] = 1;
	array[1] = 1;

	for (i = 2; i < SIZE; i++) {
		if (array[i] == 1)
			continue;
		array[i] = 0;
		prime[index++] = i;
		for (j = 2; j * i < SIZE; j++) {
			array[i * j] = 1;
		}
	}

	return index;

}

int main(int argc, char * argv[]) {

	int t, i, j;

	int k = (long long int) sieve32000();

	scanf("%d", &t);

	while (t--) {
		int n, m;
		scanf("%d%d", &n, &m);

		if (n == 1)
			n = 2;

		for (; n <= m; n++) {
			int is_prime = 1;
			int s = sqrt(n);

			for (i = 0; prime[i] <= s; i++) {
				if (n % prime[i] == 0) {
					is_prime = 0;
					break;
				}
			}

			if (is_prime == 1) {
				printf("%u\n", n);
			}
		}

		printf("\n");

	}
	return 0;
}
```

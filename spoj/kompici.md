```
/*
 * KOMPICI.c
 *
 *  Created on: Mar 7, 2014
 *      Author: Arpit Bhayani
 */

/**
 * Logic:
 * Create inverted index type stuff wherein all the numbers with similar digits are
 * grouped together.
 * Eg:
 *
 * consider numbers : 3,33,4,42,24,244,44
 * Numbers that will be grouped together are
 * 1 -> 3,33
 * 2 -> 4,44
 * 3 -> 24,42,244
 *
 * Group 2 and group3 will totally contribute 6 pairs
 * Group 1 individually will contribute 1 pair	(1)
 * Group 2 individually will contribute 1 pair	(1)
 * Group 3 individually will contribute 3 pairs (2+1)
 *
 * Total pairs = 6 + 1 + 1 + 3 = 11
 */
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0
#define SIZE 1<<10

int readline(char * str) {

	int i = 0;
	char ch;
	while ((ch = getchar()) != '\n') {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int array[SIZE];

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	getchar();

#if DEBUG
	printf("t = %d\n", t);
#endif

	char ch;

	int i = 0;
	long long int count = 0;
	int j, temp = 0;

	for (i = 0; i < t; i++) {
		temp = 0;
		while ((ch = getchar()) != '\n') {
			temp = temp | (1 << (ch - '0'));
		}
		array[temp]++;
	}

#if DEBUG
	for ( i = 0; i < SIZE; i++ ) {
		if ( array[i] )
		printf("Number : %d\n" , i);
	}
#endif

	count = 0;

	/**
	 * These are the pairs that the numbers will make with other numbers
	 */
	for (i = 0; i < SIZE; i++) {
		for (j = i + 1; j < SIZE; j++) {
			if (i & j) {
				count += (long long int) (array[i] * array[j]);
			}
		}
	}

	/**
	 * These are the paors that number will make within itself
	 */
	for (i = 0; i < SIZE; i++) {
		count += (long long int) (array[i] * (array[i] - 1) / 2);
	}

	printf("%lld\n", count);

	return 0;
}
```

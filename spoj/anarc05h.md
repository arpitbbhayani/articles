```
/*
 * ANARC05H.c
 *
 *  Created on: Mar 10, 2014
 *      Author: Arpit Bhayani
 */

/**
 * Constraints:
 * Length of string : 25
 * So max sum = 25 * 9 -> on safe side 300
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

int readline(char * str) {

	int i = 0;
	char ch;
	while ((ch = getchar()) >= '0' && ch <= '9') {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int array[30][300];

int count(int position, int previous_sum, int length, char * str) {

	int i = 0;

	/* Terminating Condition */
	if (position == length) {
		return 1;
	}

	/* If already evaluated for a given sub problem then return the value */
	if (array[position][previous_sum] != -1) {
		return array[position][previous_sum];
	}

	array[position][previous_sum] = 0;
	int local_count = 0;
	int sum = 0;

	for (i = position; i < length; i++) {
		sum += (str[i] - '0');

		/* If forward_sum is greater than the previous sum then call the method again */
		if (sum >= previous_sum) {
			local_count += count(i + 1, sum, length, str);
		}
	}

	array[position][previous_sum] = local_count;
	return local_count;
}

int main(int argc, char * argv[]) {

	int t = 1, i;
	char * str = (char *) malloc(30 * sizeof(char));

	scanf("%s", str);
	int len = strlen(str);

	while ( str[0] >= '0' && str[0] <= '9' ) {

		for (i = 0; i < 30; i++) {
			memset(array[i], -1, sizeof(array[i]));
		}
		printf("%d. %d\n", t++, count(0, 0, len, str));

		scanf("%s", str);
		len = strlen(str);
	}

	free(str);
	return 0;
}
```

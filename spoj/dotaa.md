/*
 * DOTAA.cpp
 *
 *  Created on: Mar 8, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG 0
#define gc getchar

int compar(const void * a, const void * b) {
	return (*(int *)b) > (*(int *)a);
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

void print_array(int * array, int n) {
	int i = 0;
	for (i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

/**
 * Moves 0th element to its appropriate space
 */
void special_ins_sort(int * array, int n) {
	int j = 0;
	int num = array[0];
	for (j = 1; j < n; j++) {
		if (array[j] > num) {
			array[j - 1] = array[j];
		} else {
			break;
		}
	}
	array[j - 1] = num;

}


int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {

		int n, m, d;

		scanf("%d%d%d" , &n , &m , &d);

		int * array = (int *) malloc(sizeof(int) * n);

		for (int i = 0; i < n; i++) {
			scanf("%d" , &array[i]);
		}

		qsort(array, n, sizeof(int), compar);

		int answer = 1;
		for (int i = 0; i < m; i++) {
			int val = array[0] - d;
			if (val <= 0) {
				answer = 0;
				break;
			} else {
				array[0] = val;
			}
			special_ins_sort(array, n);
		}

		if (answer) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}

		free(array);

	}
	return 0;
}

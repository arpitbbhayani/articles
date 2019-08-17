/*
 * BEENUMS.cpp
 * http://codegeeksblog.wordpress.com/2013/06/01/spoj-beenums-beehive-numbers/
 *  Created on: Jun 2, 2014
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
	int a, d, k, i;
	scanf("%d", &a);
	while (a != -1) {
		if ((a - 1) % 6 == 0) {
			for (i = 0; i <= a / 6; i++) {
				if (3 * i * (i + 1) + 1 == a) {
					printf("Y\n");
					break;
				}
			}
			if (i == (a / 6) + 1) {
				printf("N\n");
			}
		} else {
			printf("N\n");
		}
		scanf("%d", &a);
	}
	return 0;
}

/*
 * BUREAU.cpp
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

void scanint(ll int &x) {
	register ll int c = gc();
	x = 0;
	for (; (c < 48 || c > 57); c = gc())
		;
	for (; c > 47 && c < 58; c = gc()) {
		x = (x << 1) + (x << 3) + c - 48;
	}
}

int readint() {

	int t = 0;
	char ch = getchar();

	while (ch != '\n') {
		t = t * 10 + (ch - '0');
		ch = getchar();
	}

	return t;
}

char readstring() {

	char ret = 'd';
	char ch = getchar();

	if (ch == 'c') {
		ret = 'c';
	}

	while (ch != '\n' && ch != ' ') {
		ch = getchar();
	}

	return ret;
}

int cancel[100010];
int ok[100010];

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {

		int n;
		scanf("%d", &n);
		getchar();

		for (int i = 1; i <= n; i++) {

			int c = 0;

			if (readstring() == 'c') {
				c = readint();
				cancel[i] = c;
			} else {
				cancel[i] = 0;
			}

			ok[i] = 1;
		}

		for (int i = 1; i <= n; i++) {
			if (cancel[i] != 0 && ok[i] != 0) {
				//cout << "Cancelling : " << cancel[i] << endl;
				ok[cancel[i]] = 0;
			}
		}

		int count = 0;
		for (int i = 1; i <= n; i++) {
			count += ok[i];
		}

		printf("%d\n", count);

		count = 0;
		for (int i = 1; i <= n; i++) {
			if (ok[i]) {
				if (count != 0) {
					printf(" ");
				} else {
					count++;
				}
				printf("%d", i);
			}
		}
		printf("\n");

	}
	return 0;
}

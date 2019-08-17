```c
/*
 * POCRI.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: Arpit Bhayani
 */

#include <map>
#include <set>
#include <cstring>
#include <stack>
#include <vector>
#include <queue>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define si(x) scanf("%d" , &x)
#define sl(x) scanf("%ld" , &x)
#define sll(x) scanf("%lld" , &x)
#define sc(x) scanf("%c" , &x)
#define ss(x) scanf("%s" , &x)

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

#define ASIZE 10

int jo(int n, int k) {
	int ans = 0;
	for (int i = 2; i < n; i++) {
		ans = (ans + k) % i;
	}
	return ans + 1;
}

int main(int argc, char * argv[]) {

	int r, i, n, k, id;

	while (scanf("%d", &n), n != 0) {
		id = 1;
		while (true) {
			k = id;
			r = 0;
			i = 2;
			while (i <= n - 1) {
				r = (r + k) % i;
				i++;
			}
			if (r + 2 == 13)
				break;
			id++;
		}

		printf("%d\n", id);
	}

	return 0;
}
```

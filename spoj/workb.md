```c
/*
 * WORKB.cpp
 *
 *  Created on: Sep 13, 2014
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
#include <climits>

using namespace std;

#define si(x) scanf("%d" , &x)
#define sl(x) scanf("%ld" , &x)
#define sll(x) scanf("%lld" , &x)
#define sc(x) scanf("%c" , &x)
#define ss(x) scanf("%s" , &x)

#define pi(x) printf("%d\n" , x)
#define pl(x) printf("%ld\n" , x)
#define pll(x) printf("%lld\n" , x)
#define pc(x) printf("%c\n" , x)
#define ps(x) printf("%s\n" , x)

#define fup(i,a,b) for(int i=a;i<b;i++)
#define fdn(i,a,b) for(int i=a;i>=b;i--)

#define DEBUG 0
#define gc getchar
#define ll long long
#define llu unsigned long long

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

#define ASIZE 100010

llu array[ASIZE];

int main(int argc, char * argv[]) {

	int t, k = 1;
	scanf("%d", &t);
	while (t--) {

		llu cost = 0, cost_travel = 0, loss_sal = 0;
		llu n, a, b;

		scanf("%llu%lld%llu", &n, &a, &b);

		cost = 2 * a + n * b;
		cost_travel = 2 * a;
		loss_sal = 0;

		for (int i = 0; i < n; i++) {
			scanf("%llu", &array[i]);
		}

		for (int i = 1; i < n; i++) {
			loss_sal = (array[i] - array[i - 1] - 1) * b;
			if( loss_sal < cost_travel ) {
				cost += loss_sal;
			}
			else {
				cost += cost_travel;
			}
		}

		printf("Case #%d: %llu\n", k++, cost);
	}
	return 0;
}
```

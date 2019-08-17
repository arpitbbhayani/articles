```
/*
 * AP3.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: Arpit Bhayani
 */

#include <map>
#include <set>
#include <cstring>
#include <stack>
#include <vector>
#include<cmath>
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

int main(int argc, char * argv[]) {

	int t;

	double n1, n2, sq, i, x, y, z, k, l;
	long long int n, d, a, j;

	scanf("%d", &t);
	while (t--) {

		scanf("%lf %lf %lf", &x, &y, &z);

		i = 3.5 * x + 2.5 * y + z;
		k = i * i;
		l = 12 * z * (x + y);
		sq = sqrtl(k - l);
		n1 = (i + sq) / (x + y);
		n2 = (i - sq) / (x + y);

		if (ceil(n1) == floor(n1))
			n = (llrintl)(n1);
		else if (ceil(n2) == floor(n2))
			n = (llrintl)(n2);

		d = (llrintl)((y - x) / (n - 6));
		a = (llrintl)(x - 2 * d);

		printf("%lld\n", n);
		printf("%lld ", a);

		for (j = 0; j <= n - 3; j++) {
			a += d;
			printf("%lld ", a);
		}

		a += d;
		printf("%lld\n", a);

	}
	return 0;
}
```

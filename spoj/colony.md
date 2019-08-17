```c
/*
 * COLONY.cpp
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

#define ASIZE 55

ll int array[ASIZE];

int main(int argc, char * argv[]) {

	ll int level, x;

	array[1] = 2LL;
	array[2] = 4LL;

	for (int i = 3; i < ASIZE; i++) {
		array[i] = array[i - 1] * 2LL;
	}

	//while (1) {

	sll(level);
	sll(x);

	if (level == 0 && x == 0) {
		cout << "red" << endl;
		return 0;
	}

	if (level == 1 && x == 0) {
		cout << "blue" << endl;
		return 0;
	}

	if (level == 1 && x == 1) {
		cout << "red" << endl;
		return 0;
	}

	int opp = 0;

	while (1) {

		//cout << "Level " << level << " x = " << x << " and opposite = "
		//		<< opp << endl;

		if (x >= array[level] / 2) {
			x = x - array[level] / 2;
			level--;

		} else {
			level--;
			opp = 1 - opp;
		}

		if (level == 1)
			break;

	}

	//cout << "Level " << level << " x = " << x << " and opposite = " << opp
	//		<< endl;

	if (opp == 1) {
		if (x == 1)
			x = 0;
		else
			x = 1;
	}

	if (x == 0) {
		cout << "blue" << endl;
	} else {
		cout << "red" << endl;
	}

	//}

	return 0;
}
```

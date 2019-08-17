```
/*
 * MAIN12A.cpp
 *
 *  Created on: Jun 21, 2014
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

#define SIZE 1000001
//#define SIZE 21
int array[SIZE];

void generate() {

	int index = 2, num = 2, count = 0, index2 = 1;
	array[1] = 1;

	while (1) {
		count = array[index2];
		for (int j = 0; j < count; j++) {
			array[index++] = num;
			if (index == SIZE)
				break;
		}
		num++;
		index2++;
		if (index == SIZE)
			break;
	}

}

int main(int argc, char * argv[]) {

	generate();
	int t, c = 1;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		printf("Case #%d: %d\n", c, array[n]);
		c++;
	}
	return 0;
}
```

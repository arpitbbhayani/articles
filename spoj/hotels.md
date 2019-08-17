/*
 * HOTELS.cpp
 *
 *  Created on: Jun 19, 2014
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

ll int array[300001];

int main(int argc, char * argv[]) {

	int n;
	ll int x;
	scanf("%d%lld", &n, &x);
	for (int i = 0; i < n; i++)
		scanf("%lld", &array[i]);

	int start = 0, end = 0;
	ll int sum = 0, maxsum = 0;

	while (1) {

		while (end < n && sum + array[end] <= x) {
			//cout << "Adding : " << array[end] << endl;
			sum += array[end++];
		}

		if (sum > maxsum)
			maxsum = sum;

		//cout << "Subtracting : " << array[start] << endl;
		sum -= array[start++];

		if (end == n || start == n)
			break;

	}

	printf("%lld\n", maxsum);

	return 0;
}

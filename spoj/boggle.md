/*
 * BOGGLE.cpp
 *
 *  Created on: Jun 10, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <sstream>

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

	map<string, int> m;
	int score[] = { 0, 1, 1, 1, 1, 2, 3, 5, 11, 11 };

	int n;
	scanf("%d", &n);
	getchar();

	string str[n], word;

	for (int i = 0; i < n; i++) {
		getline(cin, str[i]);

		istringstream s(str[i]);
		while (s >> word) {
			m[word] += 1;
		}

	}

	int max = -1;
	for (int i = 0; i < n; i++) {
		int count = 0;

		istringstream s(str[i]);
		while (s >> word) {
			map<string,int>::iterator itr = m.find(word);
			if ( itr->second == 1 ) {
				if ( itr->first.size() > 7 ) {
					count += 11;
				}
				else {
					count += score[itr->first.size()];
				}
			}
		}

		if ( count > max ) {
			max = count;
		}
	}

	cout << max << endl;

	return 0;
}

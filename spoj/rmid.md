```c
/*
 * RMID.cpp
 *
 *  Created on: Aug 14, 2014
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

struct minheapcomparator {
	bool operator()(int i, int j) {
		return i > j;
	}
};

priority_queue<int> l;
priority_queue<int, vector<int>, minheapcomparator> r;

int check_size() {
	if (l.size() == r.size())
		return 0;
	if (l.size() > r.size()) {
		return -1;
	} else {
		return 1;
	}
}

void get_median(int &med) {

	int c = check_size();

	switch (c) {

	case 0:

		med = l.top();
		l.pop();
		break;

	case -1:

		med = l.top();
		l.pop();

		break;
	case 1:

		med = r.top();
		r.pop();

		break;
	}

}

void median(int current_element, int &med) {

	int c = check_size();

	switch (c) {
	case 0:

		if (current_element < med) {
			l.push(current_element);
			med = l.top();
		} else {
			r.push(current_element);
			med = r.top();
		}

		break;
	case -1:

		if (current_element < med) {
			int t = l.top();
			l.pop();
			r.push(t);

			l.push(current_element);

			med = l.top();
		} else {
			r.push(current_element);
			med = l.top();
		}

		break;
	case 1:

		if (current_element < med) {
			l.push(current_element);
			med = l.top();
		} else {

			int t = r.top();
			r.pop();
			l.push(t);

			r.push(current_element);
			med = l.top();

		}

		break;
	}

}

int main(int argc, char * argv[]) {

	int x;
	int med = 0;

	while ( si(x) != EOF ) {

		if (x == 0) {

			while (!l.empty())
				l.pop();

			while (!r.empty())
				r.pop();

			pc('\n');
		}

		else if (x == -1) {

			get_median(med);
			pi(med);

		}

		else {

			median(x, med);

		}

	}

	return 0;
}
```

```c
/*
 * EASYPIE.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: Arpit Bhayani
 */

#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <bitset>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <utility>
using namespace std;

template<class T> T _abs(T n) {
	return (n < 0 ? -n : n);
}
template<class T> T _max(T a, T b) {
	return (!(a < b) ? a : b);
}
template<class T> T _min(T a, T b) {
	return (a < b ? a : b);
}
template<class T> T sq(T x) {
	return x * x;
}
template<class T> T gcd(T a, T b) {
	return (b != 0 ? gcd<T>(b, a % b) : a);
}
template<class T> T lcm(T a, T b) {
	return (a / gcd<T>(a, b) * b);
}
template<class T> bool inside(T a, T b, T c) {
	return a <= b && b <= c;
}
template<class T> void setmax(T &a, T b) {
	if (a < b)
		a = b;
}
template<class T> void setmin(T &a, T b) {
	if (b < a)
		a = b;
}

#define ALL(c) c.begin(), c.end()
#define PB(x) push_back(x)
#define UB(s, e, x) upper_bound(s, e, x)
#define LB(s, e, x) lower_bound(s, e, x)
#define REV(s, e) reverse(s, e);
#define SZ(c) c.size()
#define SET(p) memset(p, -1, sizeof(p))
#define CLR(p) memset(p, 0, sizeof(p))
#define MEM(p, v) memset(p, v, sizeof(p))
#define i64 long long
#define ff first
#define ss second
#define DEBUG if(0)

typedef pair<string, int> psi;

const double EPS = 1e-9;
const double BIG = 1e15;
const int NIL = 0;
const int INF = 0x3f3f3f3f;

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	int t, n, i, subtime, teamid, probid;
	int attempt[10], timing[10], accepted[10], temp[64][10];
	map<string, int> M;
	map<string, int>::iterator itm;
	char team[8], prob[2], ver[2], solved[64][10];
	double avrtime, avrsub, acsub;

	scanf("%d", &t);
	while (t--) {

		M.clear();
		CLR(solved);
		CLR(temp);
		CLR(timing);
		CLR(attempt);
		CLR(accepted);
		i = 0;

		scanf("%d", &n);
		while (n--) {
			scanf("%d%s%s%s", &subtime, team, prob, ver);

			itm = M.find(team);
			if (itm == M.end())
				M.insert(psi(team, teamid = i++));
			else
				teamid = itm->second;

			probid = prob[0] - 'A';

			if (!solved[teamid][probid]) {
				temp[teamid][probid]++;
				if (ver[0] == 'A') {
					solved[teamid][probid] = 1;
					accepted[probid]++;
					timing[probid] += subtime;
				}
			}
		}

		for (teamid = 0; teamid < i; teamid++)
			for (probid = 0; probid < 9; probid++)
				if (solved[teamid][probid])
					attempt[probid] += temp[teamid][probid];

		for (i = 0; i < 9; i++) {
			if (accepted[i]) {
				acsub = accepted[i];
				avrtime = timing[i];
				avrtime /= acsub;
				avrsub = attempt[i];
				avrsub /= acsub;
				printf("%c %d %.2lf %.2lf\n", i + 'A', accepted[i], avrsub,
						avrtime);
			} else
				printf("%c 0\n", i + 'A');
		}
	}
	//system("pause");
	return 0;
}
```

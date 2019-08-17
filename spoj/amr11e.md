/*
 * AMR11E.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: Arpit Bhayani
 */

#include <string>
#include <cstdarg>
#include <utility>

#include <queue>
#include <stack>
#include <set>
#include <list>
#include <vector>
#include <queue>
#include <bitset>
#include <map>

#include <functional>
#include <sstream>
#include <algorithm>
#include <iostream>

#include <cstddef>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cstdio>

#include <stdexcept>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <ctime>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<double> VD;
typedef vector<VD> VVD;
typedef vector<string> VS;
typedef vector<VS> VVS;
typedef signed long long s64;
typedef unsigned long long u64;
typedef pair<int, int> PII;

#define all(a) a.begin(),a.end()
#define out(x) cout<<#x<<" = "<<(x)<<endl;
#define out2(x,y) out(x) out(y)
#define out3(x,y,z) out(x) out(y) out(z)
#define fillchar(a,i) memset(a,i,sizeof(a));
#define fori(i,max) for(int i=0;i<(int)(max) ;(i)++)
#define for2i(i,min,max) for(int i=min;i<(int)(max) ;(i)++)
#define forv(i,a) fori(i,(int)(a.size()))
#define forv2(i,j,a) forv(i,a) forv(j,(a)[i])
#define forIter(i, c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)

const int MAX = 3000;
const int LMT = 1000;
const int LEN = 5000000;

int primes[1000000], number[1000000];

VI lucky;
void sieve() {
	for (int p = 2; p < MAX; p++) // for all elements in array
			{
		if (primes[p] == 0) { // it is not multiple of any other prime
			primes[p] = 1; // mark it as prime

			// mark all multiples of prime selected above as non primes
			int c = 2;
			int mul = p * c;
			for (; mul < MAX;) {
				primes[mul] -= 1;

				if (primes[mul] + 3 == 0) {
					//cout<<primes[mul]<<"\t"<<mul<<"\n";
					//getchar();
					lucky.push_back(mul);
				}
				c++;
				mul = p * c;
			}
		}
	}
	sort(lucky.begin(), lucky.end());
}

int main() {
	sieve();
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		printf("%d\n", lucky[n - 1]);
	}
	return 0;
}

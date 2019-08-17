```
/*
 *  Author: Arpit Bhayani
 *  https://arpitbhayani.me
 */
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <deque>
#include <iostream>
#include <list>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#define ll long long

#define MIN(a, b) a < b ? a : b

using namespace std;

ll int gcd(ll int a, ll int b) {
    if(b == 0 ) {
        return a;
    }
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        ll int n, m;
        scanf("%lld%lld", &n, &m);
        ll int t;

        if(n < m) {
            t = n;
            n = m;
            m = t;
        }

        ll int g = gcd(n, m);
        ll int answer = (n/g) * (m/g);
        printf("%lld\n", answer);
    }
    return 0;
}
```

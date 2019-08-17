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

int gcd(int a, int b) {
    if( b == 0 ) {
        return a;
    }
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n, m, g, l;
        scanf("%d%d", &n, &m);
        g = gcd(n, m);
        l = (n * m) / g;
        printf("%d %d\n", g, l);
    }
    return 0;
}
```

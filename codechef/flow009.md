```c
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

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        ll int q, p;
        scanf("%lld%lld", &q, &p);
        double e = q * p;
        if(q > 1000) {
            e = e - (10 * e)/100;
        }
        printf("%lf\n", e);
    }
    return 0;
}
```

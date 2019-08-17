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
        ll int n, m, k, answer;
        scanf("%lld%lld%lld", &n, &m, &k);

        answer = abs(n-m);
        if( abs(n-m) <= k ) {
            k = abs(n-m);
        }
        answer = MIN(answer, abs(n-m) - k);

        printf("%lld\n", answer);
    }
    return 0;
}
```

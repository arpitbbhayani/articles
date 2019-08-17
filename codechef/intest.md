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
    ll int t, k, answer = 0;
    scanf("%lld", &t);
    scanf("%lld", &k);

    while( t-- ) {
        ll int x;
        scanf("%lld", &x);
        answer += (x % k == 0);
    }
    printf("%lld\n", answer);
    return 0;
}
```

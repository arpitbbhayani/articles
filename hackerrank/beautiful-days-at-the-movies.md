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
#define MAX(a, b) a > b ? a : b

using namespace std;


ll int reverse(ll int n) {
    ll int rn = 0;
    while(n) {
        rn = rn * 10 + n % 10;
        n = n / 10;
    }
    return rn;
}

int main() {
    int count = 0;
    ll int a, b, k;
    scanf("%lld%lld%lld", &a, &b, &k);

    for(ll int i = a; i <= b; i++) {
        if(abs(i - reverse(i)) % k == 0) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}
```

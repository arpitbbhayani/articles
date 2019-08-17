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
    int n, sum = 0, people = 0;
    scanf("%d", &n);

    // n = 1
    sum = 0;
    people = 5;
    for(int i = 1 ; i <= n; i++) {
        sum += people/2;
        people = (people/2) * 3;
    }
    printf("%d\n", sum);
    return 0;
}
```

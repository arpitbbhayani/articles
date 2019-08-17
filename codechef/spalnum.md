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

int array[100010];

int is_palin(int n) {
    int y = n;
    int x = 0;
    while(n) {
        int t = n % 10;
        x = x * 10 + t;
        n = n / 10;
    }
    return y == x;
}

int main(int argc, char *argv[]) {
    int t;
    for(int i = 1; i <= 100001; i++ ) {
        array[i] = is_palin(i);
    }

    scanf("%d", &t);

    while( t-- ) {
        int l, r;
        ll int answer = 0;
        scanf("%d%d", &l, &r);
        for(int i = l; i <= r ; i++) {
            if(array[i]) {
                answer += (ll int)(i);
            }
        }
        printf("%lld\n", answer);
    }
    return 0;
}
```

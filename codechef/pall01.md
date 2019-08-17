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

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n, m1, m2, t;
        scanf("%d", &n);
        m1 = 0;
        m2 = n;
        while(n) {
            t = n % 10;
            m1 = m1 * 10 + t;
            n = n / 10;
        }
        if( m1 == m2 ) {
            printf("wins\n");
        }
        else {
            printf("losses\n");
        }

    }
    return 0;
}
```

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
        int s;
        scanf("%d", &s);

        float g, h, d;
        if(s < 1500) {
            h = 0.1 * s;
            d = 0.9 * s;
        }
        else {
            h = 500;
            d = 0.98 * s;
        }
        g = s + h + d;
        printf("%g\n", g);

    }
    return 0;
}
```

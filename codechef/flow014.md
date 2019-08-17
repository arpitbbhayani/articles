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
        double h, c ,t;
        scanf("%lf%lf%lf", &h, &c, &t);

        int hb = h > 50;
        int cb = c < 0.7;
        int tb = t > 5600;

        if( hb == 1 && cb == 1 && tb == 1 ) {
            printf("10\n");
        }
        else if( hb == 1 && cb == 1 && tb == 0 ) {
            printf("9\n");
        }
        else if( hb == 0 && cb == 1 && tb == 1 ) {
            printf("8\n");
        }
        else if( hb == 1 && cb == 0 && tb == 1 ) {
            printf("7\n");
        }
        else if( hb == 0 && cb == 0 && tb == 0 ) {
            printf("5\n");
        }
        else {
            printf("6\n");
        }

    }
    return 0;
}
```

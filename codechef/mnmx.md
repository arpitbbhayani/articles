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

ll int array[50010];

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n;
        scanf("%d", &n);
        for(int i = 0 ; i < n ; i++ ) {
            scanf("%lld", &array[i]);
        }

        ll int min_val = array[0];
        for(int i = 1 ; i < n ; i++ ) {
            min_val = MIN(min_val, array[i]);
        }

        printf("%lld\n", min_val * (n-1));
    }
    return 0;
}
```

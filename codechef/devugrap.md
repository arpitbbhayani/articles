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

ll int array[100010];

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n, k;
        scanf("%d%d", &n, &k);
        for( int i = 0 ; i < n; i++ ) {
            scanf("%lld", &array[i]);
        }
        ll int answer = 0;
        for(int i = 0 ;i < n; i ++ ) {
            int d = array[i] % k;
            int m = MIN(d, k-d);
            if(array[i] == d) { // no buckets should be empty
                m = k-d;
            }
            answer += m;
        }

        printf("%lld\n", answer);
    }
    return 0;
}
```

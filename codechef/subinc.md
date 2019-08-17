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

ll int array[100010];
ll int dp[100010];

stack<ll int> s;

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n ; i++ ) {
            scanf("%lld", &array[i]);
        }

        ll int answer = 0;
        dp[0] = 1;

        for( int i = 1 ; i < n ; i++ ) {
            if(array[i] >= array[i-1]) {
                dp[i] = 1 + dp[i-1];
            }
            else {
                dp[i] = 1;
            }
        }

        for( int i = 0 ; i < n ; i++ ) {
            answer += dp[i];
        }

        printf("%lld\n", answer);
    }
    return 0;
}
```

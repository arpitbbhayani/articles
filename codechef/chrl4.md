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
int answer[100010];
int val[100010];
priority_queue<pair<double, int> > pq;
double temp[100010];
// Used to store logs because we need to determine the order even
// when multiplication is "mod" within bounded range

int main(int argc, char *argv[]) {
    int n, k;
    scanf("%d%d", &n, &k);
    for ( int i = 0 ; i < n ; i++ ) {
        scanf("%d", &val[i]);
        answer[i] = INT_MAX;
    }

    answer[0] = val[0];
    temp[0] = log(val[0]);

    pq.push(make_pair(-temp[0], 0)); // negative because we want smallest value

    for (int i = 1 ; i < n ; i++) {
        while (i - pq.top().second > k) {
            pq.pop();
        }
        temp[i] = log(val[i]) + temp[pq.top().second];
        answer[i] = (val[i] * 1LL * answer[pq.top().second]) % 1000000007;
        pq.push(make_pair(-temp[i], i));
    }

    printf("%d\n", answer[n-1]);
    return 0;
}
```

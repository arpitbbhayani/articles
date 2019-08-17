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
#define MAX(a, b) a > b ? a : b

using namespace std;

int readline(char *str) {
    int i = 0;
    char ch;
    while((ch = getchar()) != '\n') {
        str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}

int main(int argc, char *argv[]) {

    int t;
    scanf("%d", &t);
    while(t--) {
        ll int b, w;
        ll int x, y, z;
        scanf("%lld%lld", &b, &w);
        scanf("%lld%lld%lld", &x, &y, &z);

        ll int cost_b = b * x;
        ll int cost_w = w * y;

        ll int cost_b_from_w = b * (y + z);
        ll int cost_w_from_b = w * (x + z);

        ll int result;
        result = MIN((cost_b + cost_w), (cost_b + cost_w_from_b));
        result = MIN(result, (cost_w + cost_b_from_w));

        printf("%lld\n", result);
    }

    return 0;
}
```

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

int main(int argc, char *argv[]) {
    int x;
    float i, ans;

    scanf("%d%f", &x, &i);

    if (x % 5 != 0) {
        ans = i;
    }
    else {
        ans = i - x - 0.5;
        if (ans < 0) {
            ans = i;
        }
    }
    printf("%.2f\n", ans);
    return 0;
}
```

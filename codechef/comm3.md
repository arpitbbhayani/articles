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

    char answer[2][4] = {"no", "yes"};
    while( t-- ) {
        int count = 0;
        float r;
        int x[3], y[3];

        scanf("%f", &r);
        for(int i = 0 ; i < 3; i++) {
            scanf("%d%d", &x[i], &y[i]);
        }

        // first and second
        count += sqrt(((x[0] - x[1]) * (x[0] - x[1])) + ((y[0] - y[1]) * (y[0] - y[1]))) <= r;

        // first and third
        count += sqrt(((x[0] - x[2]) * (x[0] - x[2])) + ((y[0] - y[2]) * (y[0] - y[2]))) <= r;

        // second and third
        count += sqrt(((x[2] - x[1]) * (x[2] - x[1])) + ((y[2] - y[1]) * (y[2] - y[1]))) <= r;

        printf("%s\n", answer[count >= 2]);
    }
    return 0;
}
```

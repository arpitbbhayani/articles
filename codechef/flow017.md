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
        ll int a, b, c, answer;
        scanf("%lld%lld%lld", &a, &b, &c);

        if( (a > b && b > c) || (c > b && b > a) ) {
            answer = b;
        }
        else if( (a > c && c > b) || (b > c && c > a) ) {
            answer = c;
        }
        else {
            answer = a;
        }

        printf("%lld\n", answer);
    }
    return 0;
}
```

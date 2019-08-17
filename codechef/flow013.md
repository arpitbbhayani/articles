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
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if(a && b && c && (a+b+c) == 180) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}
```

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

int array[100010];

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n;
        scanf("%d", &n);
        for(int i = 0 ; i < 100010; i++ ) {
            array[i] = 0;
        }

        for(int i = 0 ; i < n ; i++ ) {
            int x;
            scanf("%d", &x);
            array[x] ++;
        }

        for(int i = 0 ; i < 100010; i++ ) {
            if(array[i] & 1) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}
```

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

int array[250001][2];

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n, x;
        scanf("%d", &n);
        for( int i = 0 ; i < n ; i++ ) {
            for( int j = 0 ; j < n ; j++ ) {
                scanf("%d", &x);
                array[x][0] = i;
                array[x][1] = j;
            }
        }

        int answer = 0;
        n = n * n;
        for ( int i = 2 ; i <= n; i++ ) {
            int xoff = abs(array[i][0] - array[i-1][0]);
            int yoff = abs(array[i][1] - array[i-1][1]);
            answer += (xoff + yoff);
        }
        printf("%d\n", answer);
    }
    return 0;
}
```

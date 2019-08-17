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

int gcd(int a, int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n, g;
        scanf("%d", &n);
        int * array = (int *) malloc(n * sizeof(int));
        for(int i = 0 ; i < n ; i++ ) {
            scanf("%d", &array[i]);
        }
        g = array[0];
        for(int i = 1; i < n; i++) {
            g = gcd(g, array[i]);
        }
        for(int i = 0 ; i < n; i++) {
            printf("%d ", array[i]/g);
        }
        printf("\n");

    }
    return 0;
}
```

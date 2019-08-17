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

int compar(const void * a, const void * b) {
    ll int * x = (ll int *)a;
    ll int * y = (ll int *)b;
    return *x > *y;
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n;
        scanf("%d", &n);
        for(int i = 0 ; i < n ; i++) {
            scanf("%lld", &array[i]);
        }

        qsort(array, n, sizeof(array[0]), compar);
        printf("%lld\n", array[0] + array[1]);
    }
    return 0;
}

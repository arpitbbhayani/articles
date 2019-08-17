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

int arr1[100001];
int arr2[100001];

int foo(int n, int m, ll int x) {
    ll int sum = 0;
    int i = 0, j = 0;
    int count = 0;

    while (i < n) {
        sum += (ll int) arr1[i];
        i++;
        if (sum > x) {
            i--;
            sum -= (ll int) arr1[i];
            break;
        }
    }
    count = i;

    while (j < m) {
        sum += (ll int) arr2[j];
        j++;
        while (sum > x && i > 0) {
            i--;
            sum -= (ll int) arr1[i];
        }
        count = (sum <= x) ? MAX( (count), (i + j) ) : count;
    }

    return count;
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);
    while( t-- ) {
        ll int x;
        int n, m;
        scanf("%d%d%lld", &n, &m, &x);

        for (int i = 0 ; i < n; i++) {
            scanf("%d", &arr1[i]);
        }

        for (int j = 0 ; j < m; j++) {
            scanf("%d", &arr2[j]);
        }

        printf("%d\n", foo(n, m, x));
    }
    return 0;
}
```

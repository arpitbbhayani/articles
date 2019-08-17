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

ll int arr[100010];
int cuts[100010];

ll int min(ll int a, ll int b) {
    return (a < b) ? a : b;
}

int compar(const void * a, const void * b) {
    return (*(int *)a) > (*(int *)b);
}

ll int process(int n, int m) {
    ll int sum = 0;
    qsort(cuts, m, sizeof(int), compar);

    for(int i = 0; i < m; i++) {
        int start = 0, end = 0;

        if(i == 0) {
            start = 0;
            end = cuts[i] - 1;
        }
        else {
            start = cuts[i-1] - 1;
            end = cuts[i] - 1;
        }

        for(int j = start; j < end; j++) {
            arr[j] = min(end - j, arr[j]);
        }
    }
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    for(int i = 0 ; i < n; i++) {
        scanf("%lld", &arr[i]);
    }
    int m;
    scanf("%d", &m);
    for( int i = 0 ; i < m; i++) {
        scanf("%d", &cuts[i]);
    }

    printf("%lld\n", process(n, m));
    return 0;
}
```

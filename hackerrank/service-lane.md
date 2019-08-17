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

int arr[100010];
int main(int argc, char *argv[]) {
    int n, t;
    scanf("%d%d", &n, &t);

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }

    while(t--) {
        int a, b;
        scanf("%d%d", &a, &b);

        int m = INT_MAX;
        for(int i = a ; i <= b ; i++) {
            m = MIN(m, arr[i]);
        }
        printf("%d\n", m);
    }

    return 0;
}
```

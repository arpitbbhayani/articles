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

int h[101];
int main(int argc, char *argv[]) {

    int n, x;
    scanf("%d", &n);
    for(int i = 0 ; i < n; i++) {
        scanf("%d", &x);
        h[x]++;
    }

    int m = 0;
    for(int i = 0 ; i < 101 ; i++) {
        m = MAX(h[i], m);
    }

    printf("%d\n", n - m);

    return 0;
}
```

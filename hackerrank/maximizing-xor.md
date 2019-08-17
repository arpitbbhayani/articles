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

int max(int a, int b) {
    return a > b ? a : b;
}

int main(int argc, char *argv[]) {
    int a, b, ans = 0;
    scanf("%d%d", &a, &b);
    for(int i = a; i <= b; i++) {
        for(int j = a; j <= b; j++) {
            ans = max(ans, i ^ j);
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

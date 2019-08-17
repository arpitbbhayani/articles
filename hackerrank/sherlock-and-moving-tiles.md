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

int main(int argc, char *argv[]) {
    long double l, s1, s2;
    cin >> l >> s1 >> s2;

    long double q;
    cin >> q;

    while(q--) {
        long double qi;
        cin >> qi;

        printf("%.4LF\n", ( (sqrt(2) * l - sqrt(2 * qi)) / abs(s1 - s2) ));
    }

    return 0;
}
```

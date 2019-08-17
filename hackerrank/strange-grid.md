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

int main(int argc, char *argv[]) {
    ll int r, c;
    cin >> r >> c;

    ll int m = 0;
    m = ((r + 1) / 2) * 10;

    if ( r & 1 ) {
        cout << m - 2 - 2 * (5 - c) << endl;
    }
    else {
        cout << m - 1 - 2 * (5 - c) << endl;
    }

    return 0;
}
```

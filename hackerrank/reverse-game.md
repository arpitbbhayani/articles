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
    int t;
    scanf("%d", &t);

    while(t--) {
        int n, k, x;
        cin >> n >> k;

        n--;

        if(n & 1) {
            if(k >= (n/2 + 1)) {
                x = 2 * (n - k);
            }
            else {
                x = 2 * k + 1;
            }
        }
        else {
            if(k >= (n/2)) {
                x = 2 * (n - k);
            }
            else {
                x = 2 * k + 1;
            }
        }

        cout << x << endl;

    }

    return 0;
}
```

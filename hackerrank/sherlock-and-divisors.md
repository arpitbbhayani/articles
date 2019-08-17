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
        ll int n, m, count = 0;
        cin >> n;

        m = (ll int) sqrt(n);

        for(int i = 1; i <= m; i++) {
            ll int f1 = i, f2 = n/i;

            if(n % f1 == 0) {
                if(f1 % 2 == 0) {
                    count++;
                }
                if(f2 % 2 == 0) {
                    count++;
                }
                if(f1 % 2 == 0 && f1 == f2) {
                    count--;
                }
            }
        }

        cout << count << endl;

    }

    return 0;
}
```

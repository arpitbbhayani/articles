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

using namespace std;

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n;
        char str[1024];
        scanf("%d", &n);
        scanf("%s", str);

        int np = 0, yp = 0, ip = 0;
        for(int i = 0 ; str[i]; i++) {
            char ch = str[i];
            if( ch == 'Y' )      { yp = 1; }
            else if( ch == 'N' ) { np = 1; }
            else                 { ip = 1; }
        }

        if( (yp && np && !ip) || (yp && !np && !ip) ) {
            printf("NOT INDIAN\n");
        }
        else if( (!yp && np && ip) || (!yp && !np && ip) ) {
            printf("INDIAN\n");
        }
        else {
            printf("NOT SURE\n");
        }
    }
    return 0;
}
```

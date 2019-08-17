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
        int answer = 0;
        char str[1024];
        scanf("%s", str);
        for( int i = 0 ; str[i]; i++ ) {
            answer += (str[i] - '0');
        }
        printf("%d\n", answer);
    }
    return 0;
}
```
